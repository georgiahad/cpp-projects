#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
using namespace std;

vector<bool> visited;
vector<vector<bool> > in_mst;
vector<vector<int> > max_dists, weights, adj_mst;

void fill_dists(const int root,const int curr,const int max){//find longest edge from path from root to curr.
  max_dists[root][curr] = max_dists[curr][root] = max;
  visited[curr] = true;
  for(auto next: adj_mst[curr]){
    if(!visited[next]){
      fill_dists(root,next,std::max(max, weights[curr][next]));
    }
  }
}
void testcase(){
  int n,idx, c;
  cin>>n>>idx;
  weighted_graph g(n);
  weights.clear();
  weights = vector<vector<int> >(n,vector<int>(n,0));
  
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      cin>>c;
      boost::add_edge(i,j,c,g);
      weights[i][j] = weights[j][i] = c;
    }
  }
 
  vector<int> pmap(n);
  boost::prim_minimum_spanning_tree(g,
    boost::make_iterator_property_map(pmap.begin(), boost::get(boost::vertex_index, g)),
    boost::root_vertex(idx-1)
    );
  //find cost of MST
  long cost = 0;
  adj_mst.clear();
  adj_mst = vector<vector<int> >(n);
  max_dists.clear();
  max_dists =vector<vector<int> >(n,vector<int>(n,0)); 
  in_mst.clear();
  in_mst = vector<vector<bool> >(n,vector<bool>(n,false));
  for(int i=0;i<n;i++){
    if(pmap[i]!=i){//if not root
      cost+=weights[i][pmap[i]];
      adj_mst[i].push_back(pmap[i]);
      adj_mst[pmap[i]].push_back(i);
      in_mst[i][pmap[i]] = in_mst[pmap[i]][i] = true;
    }
  }
  
  for (int i = 0; i < n; i++) {
    visited = std::vector<bool>(n, false);
    fill_dists(i, i, -1);
  }
  
  int best = INT_MAX;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(!in_mst[i][j]){
        best = min(best, weights[i][j]-max_dists[i][j]);
      }
    }
  }
  cout<<cost+best<<endl;
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