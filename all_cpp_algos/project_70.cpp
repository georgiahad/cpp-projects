#include<iostream>
#include<vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

typedef K::Point_2 P;

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


using namespace std;


double floor_to_double(const CGAL::Quotient<CGAL::Gmpz>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(){
  int n,m,c,x,y,s,d,u;
  long r;
  cin>>n>>m>>c;
  vector<P> pts;
  vector<int> a(n,0);
  vector<vector<int> > rws(n,vector<int>(m,0));
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  for(int i=0;i<n;i++){//read warehouses
    cin>>x>>y>>s>>a[i];
    pts.push_back(P(x,y));
    //add supply constraints
    for(int j=0;j<m;j++){
      lp.set_a(i*m+j,i,1);
    }
    lp.set_b(i,s);
  }
  for(int j=0;j<m;j++){
    cin>>x>>y>>d>>u;
    pts.push_back(P(x,y));
    for(int i=0;i<n;i++){
      //add demand and upper bound constraints.
      lp.set_a(i*m+j,n+3*j,1);
      lp.set_a(i*m+j,n+3*j+1,-1);
      lp.set_a(i*m+j,n+3*j+2,a[i]);
    }
    lp.set_b(n+3*j,d);
    lp.set_b(n+3*j+1,-d);
    lp.set_b(n+3*j+2,100*u);
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int x;
      cin>>x;
      rws[i][j]=x;
    }
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  vector<vector<int> > tws(n,vector<int>(m,0));
  vector<pair<P,long> > lines;
  for(int i=0;i<c;i++){
    cin>>x>>y>>r;
    P p = P(x,y);
    K::FT dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    if(dist<r*r){
      lines.push_back({p,r});
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      P wa = pts[i];
      P st = pts[n+j];
      for(auto l : lines){
        P cent = l.first;
        r = l.second;
        K::FT dist_w = CGAL::squared_distance(wa,cent);
        K::FT dist_s = CGAL::squared_distance(st,cent);
        bool w_in = dist_w<r*r;
        bool s_in = dist_s<r*r;
        if((w_in && !s_in) || (!w_in && s_in)){
          tws[i][j]++;
        }
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      lp.set_c(i*m+j,-100*rws[i][j]+tws[i][j]);
    }
  }
  Solution sol = CGAL::solve_linear_program(lp, ET());
  assert(sol.solves_linear_program(lp));
    

  if (sol.is_infeasible()){
    cout<<"RIOT!"<<endl;
  }
  else{
    CGAL::Quotient<CGAL::Gmpz> val = sol.objective_value();
    cout<<floor_to_double(-val/100)<<endl;
  }
  return;
}
int main(){
   std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}