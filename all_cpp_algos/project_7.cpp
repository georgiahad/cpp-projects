#include<iostream>
using namespace std;
int main(){
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,a,sum;
    cin>>n;
    sum=0;
    for(int i=0;i<n;i++){
      cin>>a;
      sum+=a;
    }
    cout<<sum<<endl;
  }
}