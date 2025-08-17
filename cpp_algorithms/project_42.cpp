#include<iostream>
#include<vector>
using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n; cin>>n;
    vector<int> v;
    int ai;
    for(int i=0;i<n;i++){
      cin>>ai;
      v.push_back(ai);
    }
    int d; cin>>d;
    v.erase(v.begin()+d);
    int a,b; cin>>a>>b;
    v.erase(v.begin()+a,v.begin()+b+1);
    if(v.empty()){
      cout<<"Empty"<<endl;
    }
    else{
      for(int e : v){
        cout<<e<<" ";
      }
      cout<<endl;
    }
  }
}