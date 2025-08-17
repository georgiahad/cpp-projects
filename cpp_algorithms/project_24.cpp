///1
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;


int rec(const vector<pair<int,int> > &intervals, vector<int> finishtimes, int i, int member, vector<vector<int> > &memo){
  if(i<0 && member>0){
    return numeric_limits<int>::min();//fail
  }
  if(i<0 || member<=0){
    return 0;
  } 
  if(memo[i][member]!=-1){
    return memo[i][member];
  }
  int take_i,leave_i;
  int val = intervals[i].second-intervals[i].first+1;
  //weight when I ignore interval i.
  leave_i = rec(intervals,finishtimes,i-1,member,memo);
  //weight when I try to add i.
  //find last b_j s.t. b_j<a_i
  int j = std::upper_bound(finishtimes.begin(),finishtimes.end(),intervals[i].first,greater<int>()) - finishtimes.begin();
  j = finishtimes.size()-1-j;
  take_i = val + rec(intervals, finishtimes,j,member-1,memo);//if not found,j=-1, and next rec call will return min().
  memo[i][member] = max(leave_i,take_i);
  return memo[i][member];
}

void compute_intervals(vector<int> &v, vector<pair<int,int> > &intervals,int k, int n){
    int left = 0; int right=0;
    long sum = long(v[left]);
    while(right<n){
      if(sum==k){
        intervals.push_back({left,right});
        sum-=long(v[left]);
        left++;
       if(left>right){
          right=left;
          sum=long(v[left]);
        }
      }
      else if(sum<k){
       right++;
       sum+=long(v[right]);
      }
      else{//sum>k
        sum-=long(v[left]);
        left++;
        if(left>right){
         right=left;
         sum=long(v[left]);
       }
      }
    }
    return;
}

void testcase(){
   int n,m,k,value;
    vector<int> v;
    vector<pair<int,int> >intervals;
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
      cin>>value;
      v.push_back(value);
    }

    
    //step 1:compute all possible windows of sum = k (possibly overlapping)
    compute_intervals(v,intervals,k,n);
    if(intervals.size()<m){
      cout<<"fail"<<endl;
      return;
    }
   
    //step 2:take max length of at most m non-overlapping intervals.
    
    int sz = intervals.size();
    vector<vector<int> > memo(sz,vector<int> (m+1,-1));//stores the max length of intervals until interval i for m members
    vector<int> finishtimes;
    std::transform(begin(intervals), end(intervals),
                 std::back_inserter(finishtimes),
                 [](auto const& pair){ return (pair.second); });
    sort(finishtimes.begin(),finishtimes.end(),std::greater<int>());
    int ans = rec(intervals, finishtimes,sz-1,m,memo);
    if(ans<0){
      cout<<"fail"<<endl;
      return;
    }
    cout<<ans<<endl;
    return;
}


int main(){
  int t; cin>>t;
  while(t--){
   testcase();
  }
}
