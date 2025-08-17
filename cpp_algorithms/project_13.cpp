#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
int main(){
  int t; cin>>t;
  while(t--){
    int n,left,right, width,maxbars=-1, bars,bestposition,dist,mindist=INT_MAX;
    cin>>n;
    vector<int> positions(n,0);
    vector<int> bestpositions;
    for(int i=0;i<n;i++){
      cin>>positions[i];
    }
    sort(positions.begin(),positions.end());
    //sliding window
    left = 0;
    right = 0;
    while(left<n && right<n){
      width = positions[right]-positions[left];
      bars = right-left+1;
      dist = (width+1)/2;
      bestposition = positions[left] + dist;
      if( bars>maxbars || (bars==maxbars && dist<=mindist)){
        if(bars>maxbars || dist<mindist){//new best
          bestpositions.clear();
          mindist = dist;
        }
        maxbars = bars;
        if(width%2==1){// Odd width => best position not unique
          bestpositions.push_back(bestposition-1);
        }
        bestpositions.push_back(bestposition);
      }
      
      //move window
      if(right+1<n && positions[right+1]-positions[left]<=200){
        right++;
      }
      else{
        left++;
      }
    }
    sort(bestpositions.begin(),bestpositions.end());
    cout<<maxbars<<" "<<mindist<<endl;
    for(auto b : bestpositions){
      cout<<b<<" ";
    }
    cout<<endl;
    
  }
}