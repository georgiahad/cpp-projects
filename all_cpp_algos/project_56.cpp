#include <iostream>
#include <vector>
#include<algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges
//for colouring
typedef std::vector<boost::default_color_type > partition_t;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 P;

// we want to store an index with each vertex
typedef int Info;//stores component (first) and colour (second).
typedef CGAL::Triangulation_vertex_base_with_info_2<Info,K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Edge_iterator  Edge_iterator;
typedef Delaunay::Vertex_iterator  Vertex_iterator;
typedef Delaunay::Vertex_handle  Vertex_handle;

using namespace std;


void testcase(){
  int n,m,x,y,xa,ya,xb,yb;
  long r;
  cin>>n>>m>>r;
  graph G(n);
  vector< pair<P,int> >stations;
  vector< pair<P,P> >clues;
  
  for(int i=0;i<n;i++){
    cin>>x>>y;
    stations.push_back(make_pair(P(x,y),i));
  }

  //delaunay triangulation on stations.
  Delaunay t;
  t.insert(stations.begin(), stations.end());
  
  for(Edge_iterator e = t.finite_edges_begin();e!=t.finite_edges_end();e++){
    Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
    Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
    if(t.segment(e).squared_length()<=r*r){
      boost::add_edge(v1->info(),v2->info(),G);
    }
  }

  for(int i=0;i<m;i++){
    cin>>xa>>ya>>xb>>yb;
    clues.push_back({P(xa,ya),P(xb,yb)});
  }
 
  //check if bipartite.
  partition_t partition(n);
  bool is_bipartite = boost::is_bipartite(G,boost::get(boost::vertex_index,G),boost::make_iterator_property_map(partition.begin(),boost::get(boost::vertex_index,G)));
  
  if(is_bipartite){
    //need another check for the graph.
    //if is bipartite only with Delaunay edges, we can use the 2-colouring found by bgl
    //to create one triangulation for each colour class. 
    //Since same colour points should not be closer than r to each other, this
    //new triangulation should not include small edges. If it does, not bipartite.
    
    vector<P> p1;
    vector<P> p2;
    for(Vertex_iterator v = t.finite_vertices_begin();v!=t.finite_vertices_end();v++){
      int i = v->info();
      if(partition[i] == boost::color_traits< boost::default_color_type >::white()){
        p1.push_back(v->point());
      }
      else{
        p2.push_back(v->point());
      }
    }
    Delaunay t1,t2;
    t1.insert(p1.begin(),p1.end());
    t2.insert(p2.begin(),p2.end());
    for(Edge_iterator e = t1.finite_edges_begin();e!=t1.finite_edges_end();e++){
      if(t1.segment(e).squared_length()<=r*r){
        is_bipartite = false;
        break;
      }
    }
    for(Edge_iterator e = t2.finite_edges_begin();e!=t2.finite_edges_end();e++){
      if(t2.segment(e).squared_length()<=r*r){
        is_bipartite = false;
        break;
      }
    }
    
  }
  //find components.
  std::vector<int> component_map(n);  // We MUST use such a vector as an Exterior Property Map: Vertex -> Component
  int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  //solve clue.
  for(auto p : clues){
    if(!is_bipartite){
      cout<<"n";
      continue;
    }
    P ca = p.first;
    P cb = p.second;
    Vertex_handle vt1 = t.nearest_vertex(ca);
    Vertex_handle vtk1 = t.nearest_vertex(cb);
    int c1 = component_map[vt1->info()];
    int c2 = component_map[vtk1->info()];
    K::FT d1 = CGAL::squared_distance(vt1->point(),ca);
    K::FT d2 = CGAL::squared_distance(vtk1->point(),cb);
    if(CGAL::squared_distance(cb,ca)<=r*r){
      cout<<"y";
    }
    else if(d1>r*r || d2>r*r || c1!=c2){
      cout<<"n";
    }
    else{
      cout<<"y";
    }
  }
  cout<<endl;
}


int main() {
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
