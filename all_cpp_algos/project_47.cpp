#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<bool> visited;
vector<int> discovery;
vector<int> finish;
vector<vector<int> >adj;
int times;

void dfs(int start){
  visited[start]=1;
  discovery[start] = times;
  times++;
  for(int i : adj[start]){
    if(!visited[i]){
      dfs(i);
    }
  }
  finish[start] = times;
  times++;
  return;
}


int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,m,s,a,b;
    cin>>n>>m>>s;
    adj.resize(n);
    adj.clear();
    visited.clear();
    discovery.clear();
    finish.clear();
    visited.resize(n,false);
    discovery.resize(n,-1);
    finish.resize(n,-1);
    times = 0;
    for(int i=0;i<m;i++){
      cin>>a>>b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    for(int i=0;i<n;i++){
      sort(adj[i].begin(),adj[i].end());
    }
   
    dfs(s);
    for (int tt:discovery){
      cout<<tt<<" ";
    }
    cout<<endl;
     for (int tt:finish){
      cout<<tt<<" ";
    }
    cout<<endl;
  }
}