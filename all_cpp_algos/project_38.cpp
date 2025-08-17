#include<iostream>
#include<vector>

using namespace std;

int testcase(){
  int n,h;
  cin>>n;
  vector<int>maxfall(n+1,-1);
  for(int i=1;i<=n;i++){ 
    cin>>h;
    maxfall[i] = i+h;
  }
  int totalmaxfall = maxfall[1];
  for(int i=1;i<=n;i++){
    if(maxfall[i]>=totalmaxfall)
      totalmaxfall = maxfall[i];
    if(i+1>=totalmaxfall)
        return totalmaxfall-1;
  }
  return n;
 
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int ans = testcase();
    cout<<ans<<endl;
  }
}