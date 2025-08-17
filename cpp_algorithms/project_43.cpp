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

void testcase_1(){
  int n,m,c,k,x,y;
  cin>>m>>n>>k>>c;
  graph G(n*m); 
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  vector<vector<int> > a(n,vector<int> (m,0));
  //read knight positions
  for(int i=0;i<k;i++){
    cin>>x>>y;
    a[y][x]=1;
  }
  
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      
      //start edges
      if(a[i][j]==1){
        adder.add_edge(v_source,i*m+j,1);
      }
      
      //edges between positions
      if(i+1<n){
        adder.add_edge(i*m+j,(i+1)*m+j,1);
      }
      if(j+1<m){
        adder.add_edge(i*m+j,i*m+j+1,1);
      }
      if(i-1>=0){
        adder.add_edge(i*m+j,(i-1)*m+j,1);
      }
      if(j-1>=0){
        adder.add_edge(i*m+j,i*m+j-1,1);
      }
      
      //boundary edges
      if(i==0 || i==n-1){
        adder.add_edge(i*m+j,v_sink,1);
      }
      if(j==0 || j==m-1){
        adder.add_edge(i*m+j,v_sink,1);
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout <<  flow << "\n";
   
 
}

void testcase(){
  int n,m,c,k,x,y;
  cin>>m>>n>>k>>c;
  graph G(2*n*m); 
  //in-vertices :  0-n*m-1
  //out-vertices : n*m-2*n*m-1
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  //read knight positions
  for(int i=0;i<k;i++){
    cin>>x>>y;
    //in-vertex.
    adder.add_edge(v_source,y*m+x,1);
  }
  
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      adder.add_edge(i*m+j,n*m+i*m+j,c);
      //edges between positions
      if(i+1<n){
        adder.add_edge(n*m+i*m+j,(i+1)*m+j,1);
      }
      if(j+1<m){
        adder.add_edge(n*m+i*m+j,i*m+j+1,1);
      }
      if(i-1>=0){
        adder.add_edge(n*m+i*m+j,(i-1)*m+j,1);
      }
      if(j-1>=0){
        adder.add_edge(n*m+i*m+j,i*m+j-1,1);
      }
      
      //boundary edges
      if(i==0 || i==n-1){
        adder.add_edge(n*m+i*m+j,v_sink,1);
      }
      if(j==0 || j==m-1){
        adder.add_edge(n*m+i*m+j,v_sink,1);
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout <<  flow << "\n";
   
}
int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}
