#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


bool cmp(int e1, int e2){
  return e1>e2;
}
int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,aa,x;
    cin>>n;
    vector<int> a;
    for(int i=0;i<n;i++){
      cin>>aa;
      a.push_back(aa);
    }
    cin>>x;
    if(x==0){//non decreasing
      sort(a.begin(),a.end());
    }
    if(x==1){
      sort(a.begin(),a.end(), cmp);
    }
    for(int i:a){
      cout<<i<<" ";
    }
    cout<<endl;
  }
}