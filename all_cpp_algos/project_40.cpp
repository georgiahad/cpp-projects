///3
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

bool cmp(const int &a, const int &b){
  return a>b;
}

void testcase(){
  int n,m, rounds, boxesmoved;
  cin>>n>>m;
  vector<int> s(n);
  vector<int> w(m);
  vector<int> indexes(n,-1);
  vector<bool> boxmoved(m,false);
  for(int i=0;i<n;i++){
    cin>>s[i];
  }
  for(int i=0;i<m;i++){
    cin>>w[i];
  }
  sort(w.begin(),w.end(),cmp);
  sort(s.begin(),s.end(),cmp);
  if(w[0]>s[0]){//impossible if there is a w[i] that cannot be carried by anyone.
   cout<<"impossible"<<endl;
   return;
  }
  rounds = 0; boxesmoved = 0;
  //first, iterate through all ppl to find max index of box they can carry (round 1)
  for(int i=0;i<n;i++){
    auto idx = lower_bound(w.begin(),w.end(),s[i], cmp);//iterator pointing to the first element <=s[i]
    if(idx != w.end()){//check if available box
      indexes[i] = idx - w.begin();
      if(boxmoved[indexes[i]]==false){
        boxesmoved++;
      }
      boxmoved[indexes[i]]=true;
      
    }
    if(indexes[i]!=-1 && i-1>=0 && indexes[i] == indexes[i-1]){
      indexes[i] = indexes[i-1]+1;
      if(indexes[i]>=m){
        indexes[i]=-1;
      }
      if(indexes[i]!=-1){
        if(boxmoved[indexes[i]]==false){
          boxesmoved++;
        }
        boxmoved[indexes[i]]=true;
       // cout<<"round="<<rounds<< ", boxmoved="<<indexes[i]<<endl;
      }
    }
  }
  rounds = 1;
  //then, for each next round, move index to right accordingly.
  while(boxesmoved<m){
    //stop processing ppl once we found i with indexes[i]=-1
    for(int i=0;i<n;i++){
      while(indexes[i]!=-1 && boxmoved[indexes[i]]==true){
        indexes[i] = indexes[i]+1;
        if(indexes[i]>=m){
          indexes[i]=-1;
        }
      }
      if(indexes[i]!=-1){
        if(boxmoved[indexes[i]]==false){
          boxesmoved++;
        }
        boxmoved[indexes[i]]=true;
       // cout<<"round="<<rounds<< ", boxmoved="<<indexes[i]<<endl;
      }
      if(indexes[i]==-1){//if this person cannot carry books, none of the following can either.
        break;
      }
    }
    rounds++;
  }
  
  cout<<3*rounds-1<<endl;
  return;
}

void testcase2(){
  int n,m, rounds,maxw=0;
  cin>>n>>m;
  vector<int> s(n);
  vector<int> w(m);
  multiset<int,std::greater<int>> weights;
  for(int i=0;i<n;i++){
    cin>>s[i];
  }
  for(int i=0;i<m;i++){
    cin>>w[i];
    maxw=max(w[i],maxw);
    weights.insert(w[i]);
  }
  sort(s.begin(),s.end(),std::greater<int>());
  if(maxw>s[0]){//impossible if there is a w[i] that cannot be carried by anyone.
   cout<<"impossible"<<endl;
   return;
  }
  rounds = 0;
  while(!weights.empty()){
    for(int i=0;i<n;i++){
      auto idx = weights.lower_bound(s[i]);
      //auto idx = lower_bound(weights.begin(),weights.end(),s[i], cmp);//iterator pointing to the first element <=s[i]
      if(idx!=weights.end()){//if element found
        weights.erase(idx);
      }
      else{//if not found, then person i cannot carry anything->all following persons cannot eityer.
        break;
      }
    }
    rounds++;
  }
  cout<<3*rounds-1<<endl;
  return;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase2();
  }
}