// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;
using namespace std;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return matching_size;
}



void testcase(){
  int N,M,A,S,C,D;
  cin>>N>>M>>A>>S>>C>>D;

  weighted_graph G(N);
  weight_map weights = boost::get(boost::edge_weight, G);
  for(int i=0;i<M;i++){
    char w; int x,y,z;
    cin>>w>>x>>y>>z;
    edge_desc e;
    e = boost::add_edge(x, y, G).first; weights[e]=z;
    if(w=='L'){
       e = boost::add_edge(y, x, G).first; weights[e]=z;
    }
  }

  vector<vector<int> >distmap(A,vector<int> (N));
  
  for(int i=0;i<A;i++){
    int a; cin>>a;
     boost::dijkstra_shortest_paths(G, a,
    boost::distance_map(boost::make_iterator_property_map(
      distmap[i].begin(), boost::get(boost::vertex_index, G))));
  }

  vector<vector<int> >T(A,vector<int>(S,INT_MAX));//stores distancecs from A to shelters.
  for(int i=0;i<S;i++){
    int s; cin>>s;
    for(int a=0;a<A;a++){
      T[a][i] = distmap[a][s];
    }
  }
  //bin search over smallest t.
  int l =0, r = INT_MAX;
  while(l<r){
    int mid = l+(r-l)/2;
    //build bipartite matching graph G''.
    graph GG(A+ C*S);
    for(int a=0;a<A;a++){
      for(int s=0;s<S;s++){
        if(T[a][s]!=INT_MAX){
          for(int c=0;c<C;c++){
            if(T[a][s]+(c+1)*D<=mid){
              boost::add_edge(a,A+c*S+s,GG);
            }
          }
        }
      }
    }
    //compute max matching.
    int m = maximum_matching(GG);
    if(m==A){
      r = mid;
    }
    else{
      l = mid+1;
    }
  }
  cout<<l<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}