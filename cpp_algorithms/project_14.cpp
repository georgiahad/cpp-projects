#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
#include<set>
using namespace std;
vector<int> h;
vector<vector<int> > adj;
int n,m,k;
deque<int> path;
multiset<int> temp;//elements in set are ordered.
vector<int> res;

void dfs(int curr){

  path.push_back(curr);
  temp.insert(h[curr]);

  int removed_p = -1;
  int removed_h = -1;
  if(path.size()>m){//path too big, remove first element.
    removed_p = path.front();
    removed_h = h[removed_p];
    path.pop_front();
    temp.erase(temp.find(removed_h));
  }
  
  int temp_diff = *temp.rbegin()- *temp.begin();

  if(path.size()==m && temp_diff<=k){//found solution
    res.push_back(path.front());
  }
  //recurse
  for(auto child : adj[curr]){
    dfs(child);
  }
  //if we removed element at the beginning, add it back.
  if(removed_p!=-1){
    path.push_front(removed_p);
    temp.insert(removed_h);
  }
  //go one step up
  if(path.size()!=0){
    int b = path.back();
    path.pop_back();
    temp.erase(temp.find(h[b]));
  }
  return;
}
void testcase(){
  int hh,v,u;
  cin>>n>>m>>k;
  h.clear();
  path.clear();
  temp.clear();
  res.clear();
  adj = vector<vector<int> >(n);
  for(int i=0;i<n;i++){
    cin>>hh;
    h.push_back(hh);
  }
  for(int i=0;i<n-1;i++){
    cin>>u>>v;
    adj[u].push_back(v);
  }
  dfs(0);
  if(res.size()==0){
    cout<<"Abort mission"<<endl;
  }
  else{
    sort(res.begin(),res.end());
    res.erase( unique( res.begin(), res.end() ), res.end() );
    for(auto r : res){
      cout<<r<< " ";
    }
    cout<<endl;
  }
  return;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}