
#include<iostream>
#include<vector>
using namespace std;

void testcase(){
  int n,m,k,u,v;
  long p,x;
  cin>>n>>m>>x>>k;
  vector<vector<pair<int,long> > > adj(n);
  vector<vector<long> > dp(k+1,vector<long> (n,-1));
  vector<bool>is_sink(n,true);
  for(int i=0;i<m;i++){
    cin>>u>>v>>p;
    adj[v].push_back({u,p});//reverse!!
    is_sink[u] = false;
  }
  //dp[m][i] = max score we get with exactly m moves ending at vertex i;
  
  //base case, 0 moves
  dp[0][0]=0;
  for(int moves = 1; moves<=k; moves++){
    for(int i=0;i<n;i++){
      for(auto p : adj[i]){
        int from = p.first;
        int to = i;
        long c = p.second;
        if(dp[moves-1][from]!=-1){//if reached
          dp[moves][to] = max(dp[moves][to],dp[moves-1][from]+c);
        }
        else{
          dp[moves][to] = max(dp[moves][to],dp[moves-1][from]);
        }
      }
      if(is_sink[i]){
        dp[moves][0] = max(dp[moves][0],dp[moves][i]);
      }
      if(dp[moves][i]>=x){
        cout<<moves<<endl;
        return;
      }
    }
  }
  cout<<"Impossible"<<endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}