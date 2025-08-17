#include<iostream>
#include<vector>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
   int n,x, evensums=0,oddsums=0;
   cin>>n;
   vector<int> v;
   vector<int> sums(n,0);
   for(int i=0;i<n;i++){
      cin>>x;
      v.push_back(x);
      if (i==0)
        sums[i] = x;
      else if(i>0)
        sums[i] = sums[i-1] + x;
   }
   for(int i=0;i<n;i++){
     if(sums[i]%2==0){
       evensums++;
     }
     else{
       oddsums++;
     }
   }
   int ans = evensums*(evensums-1)/2 + oddsums*(oddsums-1)/2 + evensums;
   cout<<ans<<endl;
  }
}