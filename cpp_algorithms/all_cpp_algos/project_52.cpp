//flow problem, vertex capacities = 1
//find max flow

// Includes
// ========
#include <iostream>
#include<vector>
// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void testcase(){
  int n,m,S,D,x,y;
  cin>>n>>m>>S>>D;
  vector<vector<int> >adj(n);
  vector<int> s(S);
  vector<int> d(D);
  for(int i=0;i<m;i++){
    cin>>x>>y;
    adj[x].push_back(y);
  }
  for(int i=0;i<S;i++){
    cin>>s[i];
  }
  for(int i=0;i<D;i++){
    cin>>d[i];
  }
  graph G(2*n);
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  edge_adder adder(G);  
  for(int i=0;i<S;i++){
    adder.add_edge(v_source,s[i],1);
  }
  for(int i=0;i<D;i++){
    adder.add_edge(d[i]+n,v_sink,1);
  }
  //add vertex capacities.
  for(int i=0;i<n;i++){
    adder.add_edge(i,n+i,1);
  }
  //add connections, capacity = INF
   for(int i=0;i<n;i++){
    for(auto j : adj[i]){
      //edge from i to j -> edge from i out to j in
      adder.add_edge(i+n,j,INT_MAX);
    }
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << "\n";
  // Retrieve the capacity map and reverse capacity map
  const auto c_map = boost::get(boost::edge_capacity, G);
  const auto rc_map = boost::get(boost::edge_residual_capacity, G);


  
}
int main() {
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
