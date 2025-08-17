#include <iostream>
#include<vector>
#include<cmath>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};
using namespace std;
void testcase(){
  int n,ph,pg,eg,eh,fh,fg,sh,sg,u,v,c;
  int max_pref = pow(2,10);
  cin>>n>>pg>>ph>>eg>>eh>>fg>>fh>>sg>>sh;
  graph G(n+n+pg+ph);
  edge_adder adder(G);  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  vector<int> a(n);
  for(int i=0;i<n;i++){
    cin>>a[i];
  }
  adder.add_edge(v_source,0,sg,0);
  for(int i=0;i<eg;i++){
    cin>>u>>v>>c;
    adder.add_edge(u,v,c,0);
  }
  adder.add_edge(pg+n+n,v_sink,sh,0);
  for(int i=0;i<eh;i++){
    cin>>u>>v>>c;
    const int pf = pg+n+n;
    adder.add_edge(pf+v,pf+u,c,0);
  }
  for(int i=0;i<fg;i++){
    cin>>u>>v>>c;
    adder.add_edge(u,pg+v,c,0);
  }
  for(int i=0;i<fh;i++){
    cin>>u>>v>>c;
    adder.add_edge(pg+n+v,pg+n+n+u,c,0);
  }
  for(int i=0;i<n;i++){
    adder.add_edge(pg+i,pg+n+i,1,max_pref-a[i]);
  }
  // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
  
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
    s_flow += c_map[*e] - rc_map[*e];     
  }
    
  cout<<s_flow<< " " << max_pref*s_flow-cost2<<endl;
  return;
}

int main() {
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}