///1
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

void testcase(){
  int n,k,w,len,www;
  cin>>n>>k>>w;
  vector<int> c(n,0);
  vector<vector<int> >ww(w);
  for(int i=0;i<n;i++){
    cin>>c[i];
  }

  for(int i=0;i<w;i++){
    cin>>len;
    ww[i] = vector<int> (len);
    for(int j=0;j<len;j++){
      cin>>www;
      ww[i][j] = www;
    }
  }
    
  
  //case 1 : occupies only 1 waterway (0 included or not)
  //go through all w and use sliding window
  
  int max_islands = 0;
  int cap = 0;

  for(int i=0;i<w;i++){
    int l = 0;
    int r = 0;
    cap = c[ww[i][l]];
    while(l<ww[i].size() && r<ww[i].size()){
      if(cap==k){
        max_islands = max(max_islands,r-l+1);
        cap-=c[ww[i][l]];
        l++;
        if(l>=r){
          r = l;
          if(r >=ww[i].size()){
            break;
          }
          cap = c[ww[i][l]];
        }
      }
      else if(cap<k){
        r++;
        if(r >=ww[i].size()){
           break;
        }
        cap+=c[ww[i][r]];
      }
      else if(cap>k){
        cap-=c[ww[i][l]];
        l++;
        if(l>=r){
          r = l;
          if(r >=ww[i].size()){
            break;
          }
          cap = c[ww[i][l]];
        }
      }
    }
    
  }

  //case 2: occupies exactly 2 waterways
  //find all prefix sums and find 2 i ,j, s.t. p[i]+p[j]+c[0] = k

  vector<int> prefix_sums;//stores all of the prefix sums of the current waterway;
  //prefix sums do not include 0.
  map<int,int> rest_sums;//for key (= distances), store its distance from 0 (store the max one)
  for(int i=0;i<w;i++){

    prefix_sums = vector<int> (ww[i].size(),0);
    int sum = 0;
   
    //todo : check for ww[i].size = 1???!!!!
    for(int j=1;j<ww[i].size();j++){
      sum += c[ww[i][j]];
      if(sum+c[0]>=k){
        break;
      }
      prefix_sums[j] = sum;
      int diff = k - sum - c[0];
      //find another prefix sum that equals to diff.

      auto other = rest_sums.find(diff);
      if(other!=rest_sums.end()){//found
        max_islands = max(max_islands,other->second + j + 1);
      }
    }
    //add all prefix sums to rest_sums map
    for(int j=1;j<ww[i].size();j++){
      rest_sums[prefix_sums[j]] = max(rest_sums[prefix_sums[j]],j);
    }

  }

  cout<< max_islands <<endl;
}
  


  

int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}