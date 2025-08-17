#include<iostream>
#include<vector>
#include<climits>
using namespace std;


int main(){
std::ios_base::sync_with_stdio(false);
  int t;cin>>t;
  while(t--){
    int n,m,r,b,x,y;
    cin>>n>>m;
    cin>>r>>b;
    vector<int> mini(n+1,INT_MAX);
    vector<int> maxi(n+1,-1);
    vector<vector<int> > adj(n);
    mini[n] = 0;
    maxi[n] = 0;
    for(int i=0;i<m;i++){
      cin>>x>>y;
      adj[x].push_back(y);
    }
    // Do the recursive calculations
    for(int i=n-1;i>=0;i--){
      for(int y : adj[i]){
        mini[i] = min(mini[i],maxi[y]+1);
        maxi[i] = max(maxi[i],mini[y]+1);
      }
    }

    if(mini[r]<mini[b]){
      cout<<"0"<<endl;
    }
    else if(mini[r]>mini[b]){
      cout<<"1"<<endl;
    }
    else{//if mini(b) == mini(r)
      if(mini[r]%2==1)
        cout<<"0"<<endl;
      else 
        cout<<"1"<<endl;
    }
  }
}