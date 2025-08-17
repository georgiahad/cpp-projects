#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include<iostream>
#include<vector>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

vector<int> f,c,k,l,m;
vector<int> a, p, partial_sums_a, partial_sums_p,mem;
int n;
bool feasible(int idx_i,int idx_j){
   // create an LP with Ax <= b and lower bounds 0 and upper bounds 1.
  Program lp (CGAL::SMALLER, true, 0, true, 1); 
  //variables: h1, h2, h3;
  int row= 0;
  for(int i=0;i<n;i++){
    lp.set_a(0,row,-(k[i]+partial_sums_a[idx_i]*partial_sums_a[idx_i]));
    lp.set_a(1,row,-(l[i]+partial_sums_p[idx_j]*partial_sums_p[idx_j]));
    lp.set_a(2,row,-(m[i]+partial_sums_a[idx_i]*partial_sums_p[idx_j]));
    lp.set_b(row,c[i]-f[i]);
    row++;
  }
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    return false;
  }
  return true;
  
}
void testcase(){

  cin>>n;
  f = vector<int> (n);
  c = vector<int> (n);
  k = vector<int> (n);
  l = vector<int> (n);
  m = vector<int> (n);
  a = vector<int> (25);
  p = vector<int> (25);
  partial_sums_a = vector<int> (25);
  partial_sums_p = vector<int> (25);


  for(int i=0;i<n;i++){
    cin>>f[i]>>c[i]>>k[i]>>l[i]>>m[i];
  }

  for(int i=0;i<25;i++){
    if(i==0){
      partial_sums_a[i] = 0;
    }
    else{
      cin>>a[i];
      partial_sums_a[i]=a[i]+partial_sums_a[i-1];
    }
  }
  for(int i=0;i<25;i++){
    if(i==0){
      partial_sums_p[i]=0;
    }
    else{
      cin>>p[i];
      partial_sums_p[i]=p[i]+partial_sums_p[i-1];
    }
  }
  if(feasible(0,0)){
    cout<<0<<endl;
    return;
  }
  int best = 50;
  int mini = 24, minj = 24;
  int i,j;
  while(mini>=0 && feasible(mini,minj)){
    best = mini+minj;
    mini--;
    minj--;
  }
  if(best==50){
    cout<<"Impossible!"<<endl;
  }
  else{
    mini++;
    minj++;
    i = mini;
    j = minj;
    //explore bottom half
    while(i<=24 && j>=0){
      j--;
      while(j>=0 && feasible(i,j)){
        mini = i;
        minj = j;
        best = min(best,i+j);
        j--;
      }
      if(j>=0){
        i++;
      }
    }
  
   i = mini;
  j = minj;
    //explore upper half
    while(i>=0 && j<=24){
      i--;
      while(i>=0 && feasible(i,j)){
        mini = i;
        minj = j;
        best = min(best,i+j);
        i--;
      }
      if(i>=0){
        j++;
      }
    }
    
    cout<<best<<endl;
} 
}
int main()
{
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
