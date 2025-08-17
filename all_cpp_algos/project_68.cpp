///2
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct res{
  long coins;//max nr of coins we collect in the subtree rooted at i.
  long nodes;//nr of nodes in the subree.
  long t;//traversal time for the whole subtee.
};

bool cmp_(const res &r1, const res &r2){
  return r1.t*r2.nodes<r2.t*r1.nodes;
}
res rec(int curr, const  vector<vector<pair<int,int> > > &adj, const vector<int> &g){
  //base case, leaf.
  if(adj[curr].size()==0){
    return {g[curr],1,0};
  }
  //explore neighbours.

  vector<res> rec_v;//stores results from all neighbours
    //cout<<"a"<<endl;
  for(auto j:adj[curr]){
    int ne = j.first;
    int l = j.second;
    res r = rec(ne,adj,g);
    rec_v.push_back({r.coins-r.nodes*l,r.nodes,r.t+2*l});//lost 2*l time, lost l coins for each node.
  }

  //sort according to traversal time per vertex ratio (increasing)
  sort(rec_v.begin(),rec_v.end(),cmp_);
  long total_c = 0;
  long total_nodes = 0;
  long total_time = 0;
  for(auto r : rec_v){
    //update coins
    total_c+=r.coins-total_time*r.nodes;//?
    total_nodes+=r.nodes;
    total_time+=r.t;
  }
  total_c+=g[curr];

  return {total_c,total_nodes+1,total_time};
}

void testcase(){
  int n,u,v,l;
  cin>>n;
  vector<int> g(n+1,0);
  vector<vector<pair<int,int> > > adj(n+1);
  for(int i=0;i<n;i++){
    cin>>g[i+1];
  }
  for(int i=0;i<n;i++){
    cin>>u>>v>>l;
    adj[u].push_back({v,l});
  }

  
  //recursively solve
  res r = rec(0,adj,g);
  cout<<r.coins<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}