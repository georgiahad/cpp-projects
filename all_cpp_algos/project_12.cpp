#include<iostream>
#include<string>
using namespace std;
int main(){
  int t; cin>>t;
  while(t--){
    string a,b;
    cin>>a>>b;
    cout<<a.size()<<" "<<b.size()<<endl;
    cout<<a+b<<endl;
    string tempc;
    std::copy(a.crbegin(), a.crend(), std::back_inserter(tempc));
   
    string tempd;
    std::copy(b.crbegin(), b.crend(), std::back_inserter(tempd));
    
    string c,d;
    
    c = tempc;
    c[0] = tempd[0];
    
    d = tempd;
    d[0] = tempc[0];
    
    cout<<c<<" "<<d<<endl;
  }
}