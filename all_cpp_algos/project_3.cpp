///2
#include<iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


using namespace std;
// double floor_to_double(const K::FT& x)
// {
//   double a = std::floor(CGAL::to_double(x));
//   while (a > x) a -= 1;
//   while (a+1 <= x) a += 1;
//   return a;
// }
void testcase(){
  
  long n,xs,ys,a,b,c,v;
  cin>>xs>>ys>>n;//n = nr of lines.
  // create an LP with Ax <= b and no lower/upper bounds
  //variables: x,y,t, where (x,y) denotes the position
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  int row = 0;
  for(int i=0;i<n;i++){
    cin>>a>>b>>c>>v;
    if(a*xs+b*ys+c<0){
      //first, add constraint for (x,y) to be on the same side as (xs,ys)
      //that means, ax+by<=-c
      lp.set_a(0,row,a);
      lp.set_a(1,row,b);
      lp.set_b(row,-c);
      row++;
      long root = std::sqrt(a*a+b*b);
      //add time requirements
      long t_coeff = v*root;
      lp.set_a(0,row,a);
      lp.set_a(1,row,b);
      lp.set_a(2,row,t_coeff);
      lp.set_b(row,-c);
      row++;
    }
    else{
      //first, add constraint for (x,y) to be on the same side as (xs,ys)
      //that means, ax+by+c>=0 <-> -ax-by<=c
      lp.set_a(0,row,-a);
      lp.set_a(1,row,-b);
      lp.set_b(row,c);
      row++;
      long root = std::sqrt(a*a+b*b);
      //add time requirements
      long t_coeff = v*root;
      lp.set_a(0,row,-a);
      lp.set_a(1,row,-b);
      lp.set_a(2,row,t_coeff);
      lp.set_b(row,c);
      row++;
    }
  }
  
  
  // enforce that t is positive
  lp.set_l(2, true, 0);
  //maximize t <-> minimize -t;
  lp.set_c(2,-1);
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());

  cout<<-(s.objective_value_numerator() / s.objective_value_denominator()) <<endl;
  return;
  
  
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}