
#include<iostream>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;
using namespace std;
void testcase(int n){
  int m, x,y;
  vector<P> locations;
  for(int i=0;i<n;i++){
    cin>>x>>y;
    locations.push_back(P(x,y));
  }
  Triangulation t;
  t.insert(locations.begin(), locations.end());
  cin>>m;
  for(int i=0;i<m;i++){
    cin>>x>>y;
    P p = P(x,y);
    Triangulation::Vertex_handle v = t.nearest_vertex(p);
    K::FT dist = CGAL::squared_distance(v->point(),p);
    cout<<fixed<<setprecision(0)<<dist<<endl;
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
