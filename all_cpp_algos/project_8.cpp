///2
#include<iostream>
#include<vector>

using namespace std;
int m;
long rec(int l, int r, int player, int k,const vector<int> &x, vector<vector<int> > &memo){
  if(r<l){
    return 0;
  }   
  if(memo[l][r]!=-1){
      return memo[l][r];
  }
  if(player==k){
    if(l==r){
      memo[l][r] = x[l];
    }
    else if(r==l+1){
      memo[l][r] = max(x[l],x[r]);
    }
    else{
      memo[l][r] = max(x[l] + rec(l+1,r,(player+1)%m,k,x,memo),x[r] + rec(l,r-1,(player+1)%m,k,x,memo));
    }
  }
  else{
    memo[l][r] = min(rec(l+1,r,(player+1)%m,k,x,memo),rec(l,r-1,(player+1)%m,k,x,memo));
  }
  
  return memo[l][r];

}

void testcase(){
  int n,mm,k,xx;
  cin>>n>>mm>>k;
  m=mm;
  vector<int> x;
  vector<vector<int > >memo(n,vector<int> (n,-1));
  for(int i=0;i<n;i++){
    cin>>xx;
    x.push_back(xx);

  }
  //rec(l)(r)(player) = max amt of money player k can make, (it is the turn of player)
  long res = rec(0,n-1,0,k,x,memo);
  cout<<res<<endl;
}

int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}