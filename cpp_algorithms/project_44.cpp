///2
//mincost maxflow
// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#include<vector>
using namespace std;

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

pair<int,int> maxfminc(graph G, int src, int to){
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    
   // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
  boost::successive_shortest_path_nonnegative_weights(G, src, to);
  int cost2 = boost::find_flow_cost(G);
  // Iterate over all edges leaving the source to sum up the flow values.
  int s_flow = 0;
  out_edge_it ee, eend;
  for(boost::tie(ee, eend) = boost::out_edges(boost::vertex(src,G), G); ee != eend; ++ee) {
    s_flow += c_map[*ee] - rc_map[*ee];     
  }
  return {s_flow,cost2};
}
void testcase(){
  int c,g,b,k,a,x,y,d,e;
  cin>>c>>g>>b>>k>>a;
  graph G(c);
  const vertex_desc v_source = boost::add_vertex(G);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  for(int i=0;i<g;i++){
    cin>>x>>y>>d>>e;
    adder.add_edge(x,y,e,d);
  }
  // Run the algorithm
  pair<int,int> initial_max_flow = maxfminc(G,k,a);
  int flow = initial_max_flow.first;
  int cost = initial_max_flow.second;
  if(cost<=b){
    cout<<flow<<endl;
    return;
  }
  adder.add_edge(v_source,k,0,0);
  edge_desc in = boost::edge(v_source,k,G).first;
  // edge_desc erev = r_map[ee];
  // int l = 0;
  // int r = flow;
  // int mid;
  // //find max flow with cost<=b
  // while(l<r){
  //   mid = (r+l+1)/2;
  //   //change src->k capacity.
  //   c_map[ee] = mid;
  //   c_map[erev] = 0; // reverse edge has no capacity!
  //   boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
  //   cost = boost::find_flow_cost(G);
  //   if(cost<=b){
  //     l = mid;
  //   }
  //   else{
  //     r = mid-1;
  //   }
  // }
  
  int start = 0, end = flow + 1;
  while (start < end) {
    int mid = start + (end - start) / 2;

    c_map[in] = mid;
    boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
    long flow = c_map[in] - rc_map[in], cost = boost::find_flow_cost(G);

    if (flow == mid && cost <= b)
      start = mid + 1;
    else
      end = mid;
  }

  std::cout << start - 1 << std::endl;
}
void testcase_(){
  int c, g, b, k, a; std::cin >> c >> g >> b >> k >> a;
  int src = c;
  graph G(src + 1);
  edge_adder adder(G);

  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  adder.add_edge(src, k, 0, 0);
  edge_desc in = boost::edge(src,k,G).first;
  for (int i = 0; i < g; i++) {
    int x, y, d, e; std::cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }

  int start = 0, end = b + 1;
  while (start < end) {
    int mid = start + (end - start) / 2;

    c_map[in] = mid;
    boost::successive_shortest_path_nonnegative_weights(G, src, a);
    long flow = c_map[in] - rc_map[in], cost = boost::find_flow_cost(G);

    if (flow == mid && cost <= b)
      start = mid+1;
    else
      end = mid;
  }

  std::cout << start-1 << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase_();
  }
  return 0;
}
