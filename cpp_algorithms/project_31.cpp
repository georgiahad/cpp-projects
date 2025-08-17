///1
#include<iostream>
#include<set>
using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int q; cin>>q;
    set<int> s;
    int a,b;
    for(int i=0;i<q;i++){
      cin>>a>>b;

      if(a==0){
        s.insert(b);
      }
      else{
        s.erase(b);
      }
    }
    if (s.empty()){
      cout<<"Empty"<<endl;
    }
    else{
      for(int i:s)
        cout<<i<<" ";
      cout<<endl;
    }
  
  }
}