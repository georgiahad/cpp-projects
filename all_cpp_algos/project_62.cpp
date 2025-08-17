#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool testcase(){
  int n;
  cin>>n;
  vector<int> t(n,0);
  for(int i=0;i<n;i++){
    cin>>t[i];
  }
  //find the minimum time each ball can be deactivated
  //respecting the timing of its children and t[i].
  for(int i=0;i<=(n-3)/2;i++){
    t[2*i+1] = min ( t[2*i+1] , t[i]-1);
    t[2*i+2] = min ( t[2*i+2] , t[i]-1);
  }
  sort(t.begin(),t.end());
  for(int i=0;i<n;i++){
    if(t[i]<=i){
      return false;
    }
  }
  return true;
}
int main() {
  ios_base::sync_with_stdio(false);
  int t; 
  cin >> t;
  while(t--) {
    if(testcase()==true){
      cout<< "yes" << endl;
    }
    else{
      cout<< "no" << endl;
    }
  }
}