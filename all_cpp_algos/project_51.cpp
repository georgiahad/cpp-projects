
#include<iostream>
#include<vector>
#include<climits>
using namespace std;


int rec(vector<int> &v,int n, int left, int right, vector<vector<int> > &memo){
  if(memo[left][right]!=-1){
    return memo[left][right];
  }
  if(right==left){
    memo[left][right]=v[left];
    return v[left];
  }
  else if(right == left+1){
    memo[left][right] = max(v[left],v[right]);
    return max(v[left],v[right]);
  }
  else{
    int v1=INT_MAX,v2=INT_MAX,v3=INT_MAX;

    if(left+2<n)
      v1 = rec(v,n,left+2,right,memo);
    if(left+1<n && right-1>=0)
      v2 = rec(v,n,left+1,right-1,memo);
    if(right-2>=0)
      v3 = rec(v,n,left,right-2,memo);
      
    memo[left][right] = max(v[left]+min(v1,v2), v[right]+min(v2,v3));
    return memo[left][right];
  }
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;cin>>t;
  while(t--){
    int n,a;
    vector<int> v;
    cin>>n;
    for(int i=0;i<n;i++){
      cin>>a;
      v.push_back(a);
    }
    vector<vector<int> >memo(n,vector<int> (n,-1));
    int maxval = rec(v, n, 0, n-1, memo);
    cout<<maxval<<endl;
  }
}