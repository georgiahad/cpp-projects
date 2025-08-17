#include<iostream>
#include<vector>
#include<climits>
#include<set>
#include<cmath>
using namespace std;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
typedef std::vector<VVVI> VVVVI;
int n,m,k;
VI v;
struct Q{
  int f1;
  int f2;
  int f3;//stores last 3 fighters (type 0 if no).
};
struct K{
  int i1;
  int i2;
  int i3;
};
K encode(Q q1, Q q2,int diff){
  int i1 = 5*q1.f1+q1.f2;//?
  int i2 = 5*q2.f1+q2.f2;//??why only last 2 values
  int i3 = diff+12;
  return {i1,i2,i3};
}
Q insert(int val,Q &q){
  return {val,q.f1,q.f2};
}
int types (Q &q){
  if(m==2){
    return std::set<int>({0, q.f1, q.f2}).size() - 1;
  }
  else{
    return std::set<int>({0, q.f1, q.f2, q.f3}).size() - 1;
  }
}
int excitement (Q &q, int diff){
  return 1000*types(q)-int(pow(2,abs(diff)));
}
int rec (VVVVI &dp, int curr, Q &q1, Q &q2, int diff){
  
  if(abs(diff)>=12){
    return INT_MIN;//infeasible.
  }
  if(curr<=-1){
    return 0;
  }
  
  K k = encode(q1,q2,diff);
  int i1 = k.i1;
  int i2 = k.i2;
  int i3 = k.i3;
  if(dp[curr][i1][i2][i3]!=-1){
    return dp[curr][i1][i2][i3];
  }
  
  int best = INT_MIN;
  Q q1_new = insert(v[curr],q1);
  Q q2_new = insert(v[curr],q2);
  int excitement_1 = excitement(q1_new,diff+1);
  int excitement_2 = excitement(q2_new,diff-1);
  int take_1 = rec(dp,curr-1,q1_new,q2,diff+1);
  int take_2 = rec(dp,curr-1,q1,q2_new,diff-1); 
  if(excitement_1>=0){
    best = max(take_1+excitement_1,best);
  }
  if(excitement_2>=0){
    best = max(take_2+excitement_2,best);
  }
  dp[curr][i1][i2][i3] = best;
  return best;
}
void testcase(){
  cin>>n>>k>>m;
  v.clear();
  v = VI(n);
  //DP stores curr, q1(index encoding the types of the last m players in q1), q2, diff.
  //returns max excitement for that setting.
  VVVVI dp (n,VVVI(25,VVI(25,VI(25,-1))));
  for(int i=n-1;i>=0;i--){
    cin>>v[i];
    v[i]++;
    //inrcrease vi s.t. value 0 is reserved for no type.
  }
  Q initial = {0,0,0};
  int sol = rec(dp,n-1,initial,initial,0);
  cout<<sol<<endl;
  return;
}
int main(){
  int t;
  cin>>t;
  while(t--)
    testcase();
  return 0;
}