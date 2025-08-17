#include<iostream>
#include<algorithm>
#include<climits>
#include<map>
#include<vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS >Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

using namespace std;
int elements_in_common(vector<int>&v1, vector<int>&v2){
  std::vector<int> v3;
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());
  std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
  return v3.size();
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,c,f,ctr;
    string ch;
    cin>>n>>c>>f;
    map<string,int> m;
    vector<vector<int> > stud(n);
    Graph g(n);
    ctr=1;
    for(int i=0;i<n;i++){
      for(int j=0;j<c;j++){
        cin>>ch;
        if(m.find(ch)==m.end()){//not found
          m[ch]=ctr;
          ctr++;
        }
        stud[i].push_back(m[ch]);
      }
      for(int j=0;j<i;j++){
        if(j!=i && elements_in_common(stud[i],stud[j])>f){
          //check if i, j have more than f elements in common.
          add_edge(i,j,g);
        }
      }
    }
    std::vector<vertex_desc> mate_map(n); // exterior property map
    boost::edmonds_maximum_cardinality_matching(g, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, g)));
    int matching_size = boost::matching_size(g,boost::make_iterator_property_map(mate_map.begin(),boost::get(boost::vertex_index, g)));
    if(matching_size==n/2){
      cout<<"not optimal"<<endl;
    }
    else{
      cout<<"optimal"<<endl;
    }
    
  }
  
  
}