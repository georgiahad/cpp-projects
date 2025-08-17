#include<iostream>
#include<vector>

 // example: how to solve a simple explicit LP
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

// double floor_to_double(const ET& x)
// {
//   double a = std::floor(CGAL::to_double(x));
//   while (a > x) a -= 1;
//   while (a+1 <= x) a += 1;
//   return a;
// }

void testcase(int n,int m){
  int c,nr=0,mini,maxi;
  vector<pair<int,int> > mima;
  vector<int> prices(m);
  vector<vector<int> > nutr(m,vector<int>(n));
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  for(int i=0;i<n;i++){
    cin>>mini>>maxi;
    mima.push_back({mini,maxi});
  }
  for(int j=0;j<m;j++){
    cin>>prices[j];
    for(int i=0;i<n;i++){
      cin>>nutr[j][i];
    }
  }
  for(int j=0;j<m;j++){
    lp.set_c(j,prices[j]);
  }
  for(int i=0;i<n;i++){
    //set max
    for(int j=0;j<m;j++){
      lp.set_a(j,nr,nutr[j][i]);
    }
    lp.set_b(nr,mima[i].second);
    nr++;
    //set min
    //set max
    for(int j=0;j<m;j++){
      lp.set_a(j,nr,-nutr[j][i]);
    }
    lp.set_b(nr,-mima[i].first);
    nr++;
  }
   
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  if(s.is_infeasible ()){
    cout<<"No such diet."<<endl;
    return;
  }
  CGAL::Quotient<ET> sol = s.objective_value();
  cout << setprecision(0) << fixed << floor(CGAL::to_double(sol)) << endl;
}
int main()
{
  int n,m;
  cin>>n>>m;
  while(!(m==0 && n==0)){
    testcase(n,m);
    cin>>n>>m;
  }

}
