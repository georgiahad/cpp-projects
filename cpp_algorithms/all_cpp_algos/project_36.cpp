#include<iostream>
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
} };

void testcase(){
  int h,w,n;
  string s;
  char fr,ba;
  cin>>h>>w;
  cin>>s;
  n = s.length();
  vector<vector<int>> front(h,vector<int>(w,-1));
  vector<vector<int>> back(h,vector<int>(w,-1));
  vector<int> letters_front(26,0);//counts letter occurrences front page
  vector<int> letters_note(26,0);//counts letter occurrences note
  vector<vector<int> > cap(26,vector<int>(26,0));//capacities of letters from front to back
  for(char ch:s)  {
    letters_note[ch-'A']++;
  }
    
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      cin>>fr;
      front[i][j] = fr-'A';
      letters_front[fr-'A']++;
    }
  }
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      cin>>ba;
      back[i][w-j-1] = ba-'A';
    }
  }
  
  //sanity check:
  if(h*w<n){
    cout<<"No"<<endl;
    return;
  }
  
  //create flow graph
  graph G(26);
  edge_adder adder(G);
  
  //add source and target
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  //add supply edges
  for(int i=0;i<26;i++){
    adder.add_edge(v_source,i,letters_front[i]);
  }
   //add demand edges
  for(int i=0;i<26;i++){
    adder.add_edge(i,v_sink,letters_note[i]);
  }
  //add edges from front to back
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      cap[front[i][j]][back[i][j]]++;
    }
  }
   for(int i=0;i<26;i++){
    for(int j=0;j<26;j++){
      adder.add_edge(i,j,cap[i][j]);
    }
  }
  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow==n){
    cout<<"Yes"<<endl;
    return;
  }
  cout<<"No"<<endl;
  return;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}