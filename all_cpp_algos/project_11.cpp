// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
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
  // for (int i = 0; i < n; ++i) {
  //   // mate_map[i] != NULL_VERTEX: the vertex is matched
  //   // i < mate_map[i]: visit each edge in the matching only once
  //   if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) std::cout << i << " " << mate_map[i] << "\n";
  // }
}

void testcase(){
  int n,m;
  cin>>m>>n;
  char cc;
  vector<vector<char> > c(n,vector<char> (m,'.'));
  int num_vert = 0;
  graph G(n*m);
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      cin>>cc;
      if(cc=='x'){
        c[i][j]='x';
      }
      else{
        num_vert++;
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(c[i][j]=='.' && j+1<m && c[i][j+1]=='.'){
        boost::add_edge(i*m+j, i*m+j+1, G);
      }
      if(c[i][j]=='.' && i+1<n && c[i+1][j]=='.'){
        boost::add_edge(i*m+j, (i+1)*m+j, G);
      }
    }
  }
  int sz  = maximum_matching(G);
 // cout<<sz<<endl;
  
  if(2*sz == num_vert){
    cout<<"yes"<<endl;
  }
  else{
    cout<<"no"<<endl;
  }
}

int main()
{
  int t;
  cin>>t;
  while(t--){testcase();};
  return 0;
}
