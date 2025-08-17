#include<iostream>
#include<vector>
using namespace std;


void testcase(){
  int n,m;
  cin>>n>>m;
  vector<vector<pair<int,int> > >fwd(n,vector<pair<int,int>>());
  vector<vector<pair<int,int> > >bwd(n,vector<pair<int,int>>());
  vector<vector<long> > dp(n,vector<long>(n,-1));
  for(int i=0;i<m;i++){
    int u,v,f;
    cin>>u>>v>>f;
    if(u<v)
      fwd[u].push_back({v,f});
    else{
      bwd[v].push_back({u,f});
    }
  }
  dp[0][0]=0;
  for(int sum = 0;sum<=2*(n-1);sum++){//nr of edges used total.
    for(int i=0;i<=sum;i++){
      int j = sum-i;
      if(i>=n || j>=n || (i==j&&i!=0) || dp[i][j]==-1)
        continue;
      for(auto p : fwd[i]){
        int nxt = p.first;
        long fi = p.second;
        if(nxt>=j)
          dp[nxt][j] = max(dp[nxt][j],fi+dp[i][j]);
      }
      for(auto p : bwd[j]){
        int nxt = p.first;
        long fi = p.second;
        if(nxt>=i)
          dp[i][nxt] =max(dp[i][nxt],fi+dp[i][j]);
      }
    }
  }
  cout<<dp[n-1][n-1]<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}