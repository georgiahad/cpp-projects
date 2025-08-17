#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  int max_dist = 0;
  for(int t=0;t<n;t++){
    max_dist = max(max_dist,dist_map[t]);
  }
  return max_dist;
}

int kruskal(const weighted_graph &G, const weight_map &weights) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int total_weight = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
   // std::cout << boost::source(*it, G) << " " << boost::target(*it, G) << "\n";
    total_weight += weights[*it];
  }
  return total_weight;
}

int main()
{
  
  int t;
  cin>>t;
  while(t--){
    int n,m,x,y,w;
    cin>>n>>m;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    for(int i=0;i<m;i++){
      cin>>x>>y>>w;
      edge_desc e;
      e = boost::add_edge(x,y,G).first;
      weights[e] = w; 
    }
    cout<<kruskal(G,weights)<<" "<<dijkstra_dist(G,0)<<endl;
    
  }
  return 0;
}