//try split and list
#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

long subsetsum_iterative(const vector<pair<long,long> >&moves, const long &T, const long &D) {
  long min_sum_t = LONG_MAX;
  bool found = false;
  for (int s = 0; s < 1<<moves.size(); ++s) { // Iterate through all subsets
    long sum_t = 0;
    long sum_d = 0;
    for (int i = 0; i < moves.size(); ++i) {
      if (s & 1<<i){//if i-th element in the subset
        sum_d += moves[i].first;
        sum_t += moves[i].second;
      }
      if(sum_t>=T){
        break;
      }
    }
    if (sum_t <T && sum_d>=D) {
      if(sum_t<min_sum_t){
        found = true;
        min_sum_t = sum_t;
      }
    }
  }
  if(!found){
    return -1;
  }
  return min_sum_t;
}

bool subsetsum(int i,const vector<pair<long,long> >&moves,  long T,  long D) {
   if (D <= 0 && T>0 ) return true;
   if (i<0 || T<0) return false;
  return subsetsum(i-1,moves, T-moves[i].second, D - moves[i].first) || subsetsum(i - 1, moves,T,D);
}

bool cmp_(const pair<long,long> &m1, const pair<long,long>&m2){
  return m1.second>m2.second;
}

bool split_list(const vector<pair<long,long> >&moves, const long &T, const long &D){
  
  int n1 = moves.size() / 2;
  int n2 = moves.size() - n1;

  vector<pair<long,long> > L1;
  vector<pair<long,long> > L2;
  
  long min_t = LONG_MAX;
  
  //split lists and search on each list individually for a soluition.
  //L1
   for (int s = 0; s < 1 << n1; ++s)
    { // Iterate through all subsets
        long sum_D = 0;
        long sum_T = 0;
        for (int i = 0; i < n1; ++i)
        {
            if (s & 1 << i)
            {
                sum_D += moves[i].first; // If i-th element in subset
                sum_T += moves[i].second;
            }
        }
        if(sum_D >= D && sum_T < T){
            return true;//min_t = min(min_t,sum_T);
        }
        if (sum_T < T)
            L1.push_back({sum_D, sum_T});
    }
    //L2
    for (int s = 0; s < 1 << n2; ++s)
    { // Iterate through all subsets
        long sum_D = 0;
        long sum_T = 0;
        for (int i = 0; i < n2; ++i)
        {
            if (s & 1 << i)
            {
                sum_D += moves[n1+i].first; // If i-th element in subset
                sum_T += moves[n1+i].second;
            }
        }
        if (sum_D >= D && sum_T < T){
          return true;//min_t = min(min_t,sum_T);
        }
        if (sum_T < T)
          L2.push_back({sum_D, sum_T});
    }
    // if(min_t!=LONG_MAX){
    //   return min_t;//if found here, will not find sth better afterwards.
    // }
    
    //sort, decreasing in t.
    sort(L2.begin(),L2.end(),cmp_);
    
    //for each t, use the max distance over all t'<t
    for(int i = L2.size()-2;i>=0;i--){
      L2[i].first = max(L2[i].first,L2[i+1].first);
    }
    //cout<<"sums"<<endl;
    //cout<<"L1"<<endl;
  // for(auto x:L1){
  //   cout<<x.first<< " "<<x.second<<endl;
  // }
  // cout<<"L2"<<endl;
  // for(auto x:L2){
  //   cout<<x.first<< " "<<x.second<<endl;
  // }
  //for each x in L1, find (bin search) a y in L2 s.t. x1&x2 satisfy criteria.
  for(auto x : L1){
    long d1 = x.first;
    long t1 = x.second;
    //find largest t2 s.t. t1+t2<T (& d1+d2>=D)
    auto y = upper_bound(L2.begin(),L2.end(),make_pair(D-d1,T-t1),cmp_);
    //if(y!=L2.end()) cout<<"y:"<< " " <<y->first<< " "<<y->second<<endl;
    if(y!=L2.end() && d1+y->first>=D && t1+y->second<T){
      min_t = min(min_t,t1+y->second);
      return true;
    }
  }
  return false;
  
}

// //void testcase1(){
//   int n,m;
//   long ss,d,t,D,T;
//   vector<pair<long,long> > moves;
//   vector<long>s;
//   cin>>n>>m>>D>>T;
//   for(int i=0;i<n;i++){
//     cin>>d>>t;
//     moves.push_back(make_pair(d,t));
//   }
//   for(int i=0;i<m;i++){
//     cin>>ss;
//     s.push_back(ss);
//   }
//   //for m=0
//   //check all possible subsets, calculate sums, check constraints. Take one that has min time.
//   long min_sum_t = subsetsum(moves,T,D);
//   if(min_sum_t==-1){
//     cout<<"Panoramix captured"<<endl;
//   }
//   else{
//     cout<<0<<endl;
//   }
  
// }

void testcase(){
  int n,m;
  long ss,d,t,D,T;
  vector<pair<long,long> > moves;
  vector<long>s;
  cin>>n>>m>>D>>T;
  for(int i=0;i<n;i++){
    cin>>d>>t;
    moves.push_back(make_pair(d,t));
  }
  for(int i=0;i<m;i++){
    cin>>ss;
    s.push_back(ss);
  }
  //check all possible subsets, calculate sums, check constraints. Take one that has min time.
  bool possible = split_list(moves,T,D);
  if(possible){//if no potion needed, done.
    cout<<"0"<<endl;
    return;
  }
  
  //bin search over all s.
  int left = 0;
  int right = m-1;
    
  while(left<=right){
    int mid = (left+right)/2;
    //add s[mid] to every movement (first element) performed
    //if now we found min_sum_t, we need at most i gulps ->right = mid;
    //else, we need more, left=mid+1;
    for(int j=0;j<moves.size();j++){
      moves[j].first+=s[mid];
    }
    if(split_list(moves,T,D)){//i gulps work
      right = mid;
      if(left==right)
        break;
    }
    else{
      left = mid+1;
    }
    for(int j=0;j<moves.size();j++){
      moves[j].first-=s[mid];
    }
  }
  if(left>=m){
    cout<<"Panoramix captured"<<endl;
    return;
  }
  else{
    cout<<left+1<<endl;//we start indexing with 0
    return;
  }

}




int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}