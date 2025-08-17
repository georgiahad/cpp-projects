#include<iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void testcase(int p){
  int a,b;
  cin>>a>>b;
  if(p==1){
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    lp.set_a(0,0,1);lp.set_a(1,0,1);lp.set_b(0,4);
    lp.set_a(0,1,4);lp.set_a(1,1,2);lp.set_b(1,a*b);
    lp.set_a(0,2,-1);lp.set_a(1,2,1);lp.set_b(2,1);
    lp.set_c(0,a);
    lp.set_c(1,-b);
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp)); 
    if (s.is_unbounded()) {
      cout<<"unbounded"<<endl;
    }
    else if (s.is_infeasible()) {
      cout<<"no"<<endl;
    }else{
      CGAL::Quotient<ET> res = s.objective_value();
      ET num = res.numerator();
      ET den = res.denominator();
      cout<<-num/den<<endl;
    }
  }
  else if(p==2){
    // create an LP with Ax >= b, no lower bound and  upper bound 0.
    Program lp (CGAL::LARGER, false, 0, true, 0); 
    lp.set_a(0,0,1);lp.set_a(1,0,1);lp.set_a(2,0,0);lp.set_b(0,-4);
    lp.set_a(0,1,4);lp.set_a(1,1,2);lp.set_a(2,1,1);lp.set_b(1,-a*b);
    lp.set_a(0,2,-1);lp.set_a(1,2,1);lp.set_a(2,2,0);lp.set_b(2,-1);
    lp.set_c(0,a);
    lp.set_c(1,b);
    lp.set_c(2,1);
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp)); 
    if (s.is_unbounded()) {
      cout<<"unbounded"<<endl;
    }
    else if (s.is_infeasible()) {
      cout<<"no"<<endl;
    }else{
      CGAL::Quotient<ET> res = s.objective_value();
      ET num = res.numerator();
      ET den = res.denominator();
      cout<<num/den<<endl;
    }
    
  }
}
int main()
{
  int p;
  cin>>p;
  while(p!=0){
    testcase(p);
    cin>>p;
  }
 
}
