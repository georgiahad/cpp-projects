///4
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef Delaunay::Vertex_iterator Vertex_iterator;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef K::Point_2 P;

using namespace std;

struct Edge{
  int u;
  int v;
  K::FT sq_len;
};

struct B{
  P bone;
  Vertex_handle v;//nearest vertex
  K::FT dist;//distance to nearest vertex.
};

int max_nr_bones(long rad,const vector<B> &bones, const Delaunay &t, int n, int m,const  vector<Edge> &edges){
  //find max nr of bones we can collect with s = rad.
  // setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
 //find components of graph.
  for (auto e = edges.begin(); e != edges.end(); ++e){ 
    if( e->sq_len <= rad)
      uf.union_set(e->u, e->v);
    else{
      break;
    }
  }
  
  vector<int> nr_bones_in_component(n,0);
  
  for(int j=0;j<m;j++){
    K::FT dist = bones[j].dist;
    if(4*dist<=rad){
      int component = uf.find_set(bones[j].v->info());
      nr_bones_in_component[component] ++;
    }
    else{
      break;
    }
  }
  
  int a=0;
  for(int i=0;i<n;i++){
    if(nr_bones_in_component[i]>a){
      a = nr_bones_in_component[i];
    }
  }
  return a;
}

void testcase_1_2(){
  int n,m,k,x,y;
  long s;
  cin>>n>>m>>s>>k;
  vector<P> pts;
  vector<P> bones;
  for(int i=0;i<n;i++){
    cin>>x>>y;
    pts.push_back(P(x,y));
  }
  Delaunay t;
  t.insert(pts.begin(),pts.end());
  int num_vert=0;
  for(Vertex_iterator v = t.finite_vertices_begin();v != t.finite_vertices_end();v++){
    v->info() = num_vert++;
  }
  for(int i=0;i<m;i++){
    cin>>x>>y;
    bones.push_back(P(x,y));
  }
  vector<Edge> edges;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    K::FT sq_len_ = t.segment(e).squared_length();
    edges.push_back(Edge{i1,i2,sq_len_});
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return e1.sq_len<e2.sq_len; });

  // setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
 //find components of graph.
  for (auto e = edges.begin(); e != edges.end(); ++e)
  { 
    if( e->sq_len <= s)
      uf.union_set(e->u, e->v);
    else{
      break;
    }
  }
  
  vector<int> nr_bones_in_component(n,0);
  for(int j=0;j<m;j++){
    Delaunay::Vertex_handle v = t.nearest_vertex(bones[j]);
    K::FT dist = CGAL::squared_distance(v->point(),bones[j]);
    if(4*dist<=s){
      int component = uf.find_set(v->info());
      nr_bones_in_component[component] ++;
    }
  }
  
  int a=0;
  for(int i=0;i<n;i++){
    if(nr_bones_in_component[i]>a){
      a = nr_bones_in_component[i];
    }
  }
  cout<<a<< " " <<4*s<<endl;
  return;
  
}

void testcase_time_limit(){
  int n,m,k,x,y;
  long s;
  cin>>n>>m>>s>>k;
  vector<P> pts;
  vector<B> bones(m);
  for(int i=0;i<n;i++){
    cin>>x>>y;
    pts.push_back(P(x,y));
  }
  Delaunay t;
  t.insert(pts.begin(),pts.end());
  int num_vert=0;
  for(Vertex_iterator v = t.finite_vertices_begin();v != t.finite_vertices_end();v++){
    v->info() = num_vert++;
  }
  for(int i=0;i<m;i++){
    cin>>x>>y;
    bones[i].bone = P(x,y);
  }
  
  for(int j=0;j<m;j++){
    Delaunay::Vertex_handle v = t.nearest_vertex(bones[j].bone);
    K::FT dist = CGAL::squared_distance(v->point(),bones[j].bone);
    bones[j].dist = dist;
    bones[j].v = v;
  }
  vector<Edge> edges;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    K::FT sq_len_ = t.segment(e).squared_length();
    edges.push_back(Edge{i1,i2,sq_len_});
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return e1.sq_len<e2.sq_len; });
        
  std::sort(bones.begin(), bones.end(),
      [](const B& e1, const B& e2) -> bool {
        return e1.dist<e2.dist; });
        
  long l = 0;
  long r = 1e+15;
  long mid;
  //finds minimum 4*r^2 s.t. at least k bones are obtained.
  while(l<r){
    mid = (l+r)/2;
    if(max_nr_bones(mid,bones,t,n,m,edges)>=k){
      r = mid;
    }
    else{
      l = mid+1;
    }
  }
  cout<<max_nr_bones(s,bones,t,n,m,edges)<< " "<<l<<endl;
}


int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase_time_limit();
  return 0;
}
