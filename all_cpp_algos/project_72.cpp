///1
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int q; cin>>q;
    multimap<string,int> m;
    int a;
    string b;
    for(int i=0;i<q;i++){
      cin>>a>>b;
      if(a==0){
        m.erase(b);
      }
      else if (a>0){
        m.insert(pair<string,int>(b,a));
      }
    }
    string s;
    cin>>s;
    auto it = m.find(s);
    if(it==m.end()){
      cout<<"Empty"<<endl;
    }
    else{
      vector<int>res;
      for(it = m.begin();it!=m.end();it++){
        if(it->first==s){
          res.push_back(it->second);
        }
      }
      sort(res.begin(),res.end());
      for(auto iit : res)
        cout<<iit<<" ";
      cout<<endl;
    }
  }
}