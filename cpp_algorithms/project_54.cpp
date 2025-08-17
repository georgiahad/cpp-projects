
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_data_structure_2.h>

#include<iostream>
#include<vector>
#include<algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,IK>     Vb;
typedef CGAL::Triangulation_face_base_2<IK>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>             Tds;
typedef CGAL::Delaunay_triangulation_2<IK,Tds>                  Triangulation;
typedef Triangulation::Vertex_iterator                          Vertex_iterator;
typedef Triangulation::Edge_iterator                            Edge_iterator;
typedef Triangulation::Vertex_handle                            Vertex_handle;
typedef IK::Point_2                                             P;

using namespace std;

double ceil_to_double(const EK::FT  & x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x)    a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

EK::FT to_time_(const EK::FT  &d){
  return CGAL::sqrt((CGAL::sqrt(d)-1)/2);
}

void testcase(int n){
  
  int l,b,r,t,x,y;
  cin>>l>>b>>r>>t;
  vector<P> points;
  vector<IK::FT> distances(n,LONG_MAX);
  for(int i=0;i<n;i++){
    cin>>x>>y;
    points.push_back(P(x,y));
  }
  Triangulation dt;
  dt.insert(points.begin(), points.end());
  int num_pts=0;
  for(Vertex_iterator v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); ++v){
    v->info() = num_pts++;
    //find closest boundary to point (x,y) (i.e. to vertex v)
    int x = v->point().x();
    int y = v->point().y();
    IK::FT d1 = (x-l);
    IK::FT d2 = (r-x);
    IK::FT d3 = (t-y);
    IK::FT d4 = (y-b);
    IK::FT d = min(min(d1,d2),min(d3,d4));
    distances[v->info()] = 4 * d * d;
  }
  
  for (Edge_iterator e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e){
    //find closest vertex
    Vertex_handle v1 = e->first->vertex((e->second+1)%3);
    Vertex_handle v2 = e->first->vertex((e->second+2)%3);
    IK::FT dist = dt.segment(e).squared_length();
    distances[v1->info()] = min(distances[v1->info()],dist);
    distances[v2->info()] = min(distances[v2->info()],dist);
  }
  
  sort(distances.begin(),distances.end());
  
  EK::FT min_d = EK::FT (distances[0]);
  EK::FT mid_d = EK::FT (distances[n/2]);
  EK::FT max_d = EK::FT (distances[n-1]);
  
  EK::FT min_t = ceil_to_double(EK::FT(CGAL::sqrt((CGAL::sqrt(min_d)-1)/2)));
  EK::FT mid_t = ceil_to_double(EK::FT(CGAL::sqrt((CGAL::sqrt(mid_d)-1)/2)));
  EK::FT max_t = ceil_to_double(EK::FT(CGAL::sqrt((CGAL::sqrt(max_d)-1)/2)));
  
  cout<<min_t<< " " <<mid_t << " " <<max_t<<endl;
  
  return;
}

int main(){
  ios_base::sync_with_stdio(false);
  int n;
  cin>>n;
  while(n!=0){
    testcase(n);
    cin>>n;
  }
}