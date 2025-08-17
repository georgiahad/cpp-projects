#include<iostream>
#include<vector>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,x,left = 0, right = 0, value=0,k, mini=0, minj=0,bestvalue;
    vector<int> v;
    cin>>n>>k;
    for(int i=0;i<n;i++){
      cin>>x;
      v.push_back(x);
    }
    //sliding window
    value = v[0];
    bestvalue = abs(v[0]-k);
    while(right<n){
      if(value < k){
        right++;
        value+=v[right];
      }
      if(abs(value-k)<bestvalue){
        bestvalue = abs(value-k) ;
        mini = left;
        minj = right;
      }
      if(value==k){
        break;
      }
      if(value>k){
        value = value - v[left];
        left++;
      }
      if(left>=right){
        right=left;
        value = v[left];
      }
    }
    cout<<mini<<" "<<minj<<endl;
  }

}