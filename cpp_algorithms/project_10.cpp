///2
#include <iostream>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;


using namespace std;

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
  pair<int,int> moves [] = {{-1,-2}, {-1,2}, {1,-2}, {1,2},{-2,-1}, {-2,1}, {2,-1}, {2,1}};
  int n;
  cin>>n;
  int a[n][n]={};
  int count = 0;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cin>>a[i][j];
    }
  }
  graph G(n*n);
  edge_adder adder(G);
  
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  // Add some edges using our custom edge adder

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(a[i][j]==1){
        count++;
        //make it bipartite
        if((i+j)%2==0)
          adder.add_edge(v_source,i*n+j,1);
        else
          adder.add_edge(i*n+j,v_target,1);
      }
    }
  }
  
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if((i+j)%2==1){
        continue;
      }
      //find all possible moves from {i,j}.
      for(auto p : moves){
        int ii = i + p.first;
        int jj = j + p.second;
        if(ii>=0 && ii<n && jj>=0 && jj<n && a[ii][jj]!=0 && a[i][j]!=0){
          adder.add_edge(i*n+j,ii*n+jj,1); 
        }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);
  long maxMatching = flow;
  long minVC = maxMatching;
  long maxIS = count - minVC;
  
  cout<<maxIS<<endl;
}
int main() {
  
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
