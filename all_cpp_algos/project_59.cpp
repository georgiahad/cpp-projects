
#include<iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

void testcase(){
  int n,m,k,t,teli,x,y,c;
  cin>>n>>m>>k>>t;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  vector< int > component_map(n);
  vector< int > size_of_component(n,0);
  vector<int> tel;//vertices part of the teleportation network
  for(int i=0;i<t;i++){
    cin>>teli;
    tel.push_back(teli);
  }
  for(int i=0;i<m;i++){
    cin>>x>>y>>c;
    edge_desc e;
    e = boost::add_edge(y, x, G).first; weights[e]=c;
  }
  
  //find strongly connected components.
  int ncc = boost::strong_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G)));

  
  for (int i = 0; i < t; ++i)
  {
    size_of_component[component_map[tel[i]]] ++;
  }

  for(int i=0;i<t;i++){
    int comp = component_map[tel[i]];
    int szc = size_of_component[comp];
    edge_desc e;
    e = boost::add_edge(tel[i], n + comp, G).first; weights[e]=szc-1;
    e = boost::add_edge(n + comp, tel[i], G).first; weights[e]=0;
  }
 int min_dist = 1000000;
 vector<int> dist_map = dijkstra_dist(G,n-1);
 for(int i=0;i<k;i++){
   min_dist = min (min_dist, dist_map[i]);
 }
 if(min_dist >= 1000000){
   cout<<"no"<<endl;
 }
 else{
   cout<<min_dist<<endl;
 }
 
}

int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}