///1
#include<iostream>
#include<vector>
#include<algorithm>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>


// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

struct P{
  long x;
  long y;
};


double ceil_to_double(const CGAL::Quotient<ET> &x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a < x)
        a += 1;
    while (a - 1 >= x)
        a -= 1;
    return a;
}


void testcase(){
 
  int n,m,constr_nr=0;
  long x,y,h,w;
  cin>>n>>m>>h>>w;
  vector<P> posters(n+m);
  // create an LP with Ax <= b, lower bound 1 and no upper bounds
  // #variables = n
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  for(int i=0;i<n;i++){
    cin>>x>>y;
    posters[i] = P{x,y};
  }
  for(int i=n;i<m+n;i++){
    cin>>x>>y;
    posters[i] = P{x,y};
  }
 
  constr_nr = 0;
  for(int i=0;i<n;i++){
    
    //new posters
    for(int j=i+1;j<n;j++){
      //first hit horizontally or vertically?
      int xx = abs(posters[i].x-posters[j].x);
      int yy = abs(posters[i].y-posters[j].y);
      if(xx*h>yy*w){//if they first hit horizontally, add x-constraint
        lp.set_a(i,constr_nr,1);
        lp.set_a(j,constr_nr,1);
        ET b = ET(2*xx,w);
        lp.set_b(constr_nr,b);
        constr_nr++;
      }
      else{
        lp.set_a(i,constr_nr,1);
        lp.set_a(j,constr_nr,1);
        ET b = ET(2*yy,h);
        lp.set_b(constr_nr,b);
        constr_nr++;
      }
    }
    //closest old poster
    ET min_ = ET(INT_MAX);
    for(int j=n;j<n+m;j++){
      int xx = abs(posters[i].x-posters[j].x);
      int yy = abs(posters[i].y-posters[j].y);
      min_ = min (min_,max(ET(ET(2*xx,w)-1),ET(ET(2*yy,h)-1)));
    }
   
   
    if(m>0){
      
      lp.set_a(i,constr_nr,1);
      lp.set_b(constr_nr,min_);
      constr_nr++;
      
    }
  }
  for(int i=0;i<n;i++){
    lp.set_c(i,-2*(w+h));
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  CGAL::Quotient<ET> sol = s.objective_value();
  cout << fixed << setprecision(0) << long(ceil_to_double(-sol)) << "\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  
}