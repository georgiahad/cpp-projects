#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int i; long l; string s; double d;
    cin>>i>>l>>s>>d;
    cout<<i<<" "<<l<<" "<<s<<" ";
    cout<<fixed<<setprecision(2)<<d<<endl;
  }
  
}