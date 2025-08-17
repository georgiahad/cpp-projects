#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<int> dist;
queue<int> Q;
vector<vector<int> > adj;

void bfs(int start){
  Q.push(start);
  while(!Q.empty()){
    int v = Q.front();
    Q.pop();
    for(int x : adj[v]){
      if(dist[x]==-1){
        dist[x] = dist[v]+1;
        Q.push(x);
      }
    }
  }
  return;
}


int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,m,s,a,b;
    cin>>n>>m>>s;
    
    adj.clear();
    adj.resize(n);
    
    dist.clear();
    dist.resize(n,-1);
    
    for(int i=0;i<m;i++){
      cin>>a>>b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    for(int i=0;i<n;i++){
      sort(adj[i].begin(),adj[i].end());
    }
    dist[s]=0;
    bfs(s);

    for(int i=0;i<n;i++){
      cout<<dist[i]<<" ";
    }
    cout<<endl;
    
  }
}