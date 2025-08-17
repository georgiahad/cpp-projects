
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;


void testcase(){
  
  long n,m,a,b,P,H,W,pi,hi,wi;
  
  cin>>n>>m;
  cin>>a>>b;
  cin>>P>>H>>W;
  vector<long> p(n+1),h(n+1),w(m+1);
  
  for(int i=0;i<n;i++){
    cin>>pi>>hi;
    p[i+1] = pi;
    h[i+1] = hi;
  }
  for(int i=0;i<m;i++){
    cin>>wi;
    w[i+1] = wi;
  }
  
  long l_min = std::numeric_limits<long>::min();
  vector<vector<vector<long> > > dp(H+1,vector<vector<long> >(n+1,vector<long>(n+1,l_min)));
  //dp[h][i][j] = max p from taking j out of the first i potions A with happiness sum at least h
  //start indexing from 1.
  
  //base case, only take 1 potion.
  for(int hh=0;hh<=H;hh++){
    for(int i=1;i<=n;i++){
      if(h[i]>=hh){
        dp[hh][i][1] = max(dp[hh][i-1][1],p[i]);
      }
      else{
        dp[hh][i][1] = dp[hh][i-1][1];
      }
    }
  }
  for(int j=2;j<=n;j++){
    for(int hh=0;hh<=H;hh++){
      for(int i=j;i<=n;i++){
        if(hh>=h[i]){
          dp[hh][i][j] = max(dp[hh-h[i]][i-1][j-1]+p[i],dp[hh][i-1][j]);
        }
        else{
          dp[hh][i][j] =  max(dp[0][i-1][j-1]+p[i],dp[hh][i-1][j]);
        }
      }
    }
  }
  
  

    
  //now, dp [H][n][j]//max p for taking j potions with h>=H.
  
  //search for smallest j (=#potions A) s.t. dp[H][n][j]>=P (& combine with potions B that fulfill W).

  sort(w.begin()+1,w.end(),[](const long &x1, const long &x2)-> bool {return x1>x2;});
  
  int num_a_pots;
  int num_b_pots;
  long curr_w = 0;
  for(num_b_pots = 1; num_b_pots<=m;num_b_pots++){
    curr_w+=w[num_b_pots];
    //look for smallest #pot_A s.t. P requirement satisfied.
    for(num_a_pots = 1;num_a_pots<=n;num_a_pots++){
      if(dp[H][n][num_a_pots] - num_b_pots*b>=P && curr_w-num_a_pots*a>=W ){
        cout<<num_a_pots+num_b_pots<<endl;
        return;
      }
    }
  }
  cout<<-1<<endl;
  return;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}
