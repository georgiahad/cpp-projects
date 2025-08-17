
#include<iostream>
#include<vector>
#include <cmath>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct H{
  int x;
  int y;
};

void testcase(){
  int n,m,x,y;
  long s;
  cin>>n>>m>>s;
  vector<H> nh;
  vector<H> ch;
  long nxsum=0;
  long nysum=0;
  long cxsum=0;
  long cysum=0;
  for(int i=0;i<n;i++){
    cin>>x>>y;
    nh.push_back(H{x,y});
    nxsum+=long(x);
    nysum+=long(y);
  }
  for(int i=0;i<m;i++){
    cin>>x>>y;
    ch.push_back(H{x,y});
    cxsum+=long(x);
    cysum+=long(y);
  }
  //variables: a,b,c

  //no upper or lower bounds.
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  //s-canal: ax+by=c <-> ax+by-c=0
  //enforce a = 1 (because s canal cannot be horizontal)
  lp.set_u(0,true,1);
  lp.set_l(0,true,1);
  
  //constraints:
  int row = 0;
  //nh to the left of s canal
  //ax+by-c<=0
  for(int i=0;i<n;i++){
    lp.set_a(0,row,nh[i].x);
    lp.set_a(1,row,nh[i].y);
    lp.set_a(2,row,-1);
    lp.set_b(row,0);
    row++;
  }
  //ch to right of s-canal
  //ax+by-c>=0
  for(int i=0;i<m;i++){
    lp.set_a(0,row,-ch[i].x);
    lp.set_a(1,row,-ch[i].y);
    lp.set_a(2,row,1);
    lp.set_b(row,0);
    row++;
  }
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()){
    cout<< "Yuck!" <<endl;
    return;
  }
  if(s!=-1){
    
    //sum of s-pipes<=s
    lp.set_a(0,row,cxsum-nxsum-s);
    lp.set_a(1,row,cysum-nysum);
    lp.set_a(2,row,n-m);
    lp.set_b(row,0);
    row++;
    sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible()){
      cout<< "Bankrupt!" <<endl;
      return;
    }
  }
  //if feasible, add w-canal constraints.
  //equation of w-canal : ay-bx+d=0.(since we enforced a=1, y=bx-d)
  
  //add variables: d (for the equation), l (for the length)
  
  for(int i=0;i<n;i++){
    //assume a = 1.
    lp.set_a(1,row,nh[i].x);
    lp.set_a(3,row,-1);
    lp.set_a(4,row,-1);
    lp.set_b(row,nh[i].y);
    row++;
    lp.set_a(1,row,-nh[i].x);
    lp.set_a(3,row,+1);
    lp.set_a(4,row,-1);
    lp.set_b(row,-nh[i].y);
    row++;
  }
   for(int i=0;i<m;i++){
    //assume a = 1.
    lp.set_a(1,row,ch[i].x);
    lp.set_a(3,row,-1);
    lp.set_a(4,row,-1);
    lp.set_b(row,ch[i].y);
    row++;
    lp.set_a(1,row,-ch[i].x);
    lp.set_a(3,row,+1);
    lp.set_a(4,row,-1);
    lp.set_b(row,-ch[i].y);
    row++;
  }
  lp.set_l(4,true,0);//l>=0
  lp.set_c(4, 1);//minimize l.

  sol = CGAL::solve_linear_program(lp, ET());
  //cout<<sol<<endl;
  cout<< fixed << setprecision(0) << ceil(CGAL::to_double(sol.objective_value())) << endl;

  return;
  
}
int main()
{
  
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
