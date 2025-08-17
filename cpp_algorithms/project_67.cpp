#include <vector>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>

namespace boost
{
struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;
}

bool cmp(const std::pair<int,int>& p1,const std::pair<int,int>& p2){
  return (p1.first<p2.first) || (p1.first==p2.first && p1.second<p2.second);
}

void testcase(){
  using namespace boost;
  typedef adjacency_list< vecS, vecS, undirectedS, no_property,
        property< edge_component_t, std::size_t > >
        graph;
  typedef graph_traits< graph >::vertex_descriptor vertex;
  int n,m,a,b;
  std::cin>>n>>m;
  graph G(n);
  for(int i=0;i<m;i++){
    std::cin>>a>>b;
    add_edge(a,b,G);
  }
  
  property_map< graph, edge_component_t >::type component = get(edge_component, G);
  //component[e] = the label (nr) of the component that edge e is assigned to.
  std::size_t num_comps = biconnected_components(G, component);
  std::vector<int> nrofedgesincomponent(num_comps,0);
  std::vector<std::pair<int,int> > bridges;
  graph_traits< graph >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    nrofedgesincomponent[component[*ei]]++;
  }
  //components with only 1 edge -> that edge is a bridge.
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    if(nrofedgesincomponent[component[*ei]]==1){
      bridges.push_back(std::make_pair(std::min(source(*ei,G),target(*ei,G)),std::max(source(*ei,G),target(*ei,G))));
    }
  }
  sort(bridges.begin(),bridges.end(),cmp);
  std::cout<<bridges.size()<<std::endl;
  for(auto br: bridges){
    std::cout<<br.first<<" "<<br.second<<std::endl;
  }
  return;
}
int main(){
  
  int t; std::cin>>t;
  while(t--){
    testcase();
  }
}