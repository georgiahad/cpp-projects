
#include<iostream>
#include<cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void testcase(int n){
  int d,a,b,norm=0,sq_norm;
  cin>>d;
  // create an LP with Ax <= b, no lower bounds and no upper bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
    //radius positive
  lp.set_l(d,true,0);
  for(int i=0;i<n;i++){
    norm = 0;
    for(int j=0;j<d;j++){
      cin>>a;
      lp.set_a(j,i,a);
      norm+=a*a;
    }
    sq_norm = sqrt(norm);
    lp.set_a(d,i,sq_norm);
    cin>>b;
    lp.set_b(i,b);
  }
  //maximize radius
  lp.set_c(d,-1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_infeasible()) {
       cout << "none" << endl;
  }
  else if (s.is_unbounded()) {
      cout << "inf" << endl;
  }
  else {
    // Implicit round down due to integer division
    cout << - s.objective_value_numerator() / s.objective_value_denominator() << endl;
  }

}
int main()
{
  int n;
  cin>>n;
  while(n!=0){
    testcase(n);
    cin>>n;
  }

}
