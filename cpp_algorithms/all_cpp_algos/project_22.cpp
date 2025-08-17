#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

struct Boats{
  int l;
  int p;
};

bool cmp_(const Boats &b1, const Boats &b2){
  return b1.p<b2.p;
}
void testcase(){
  int n,l,p;
  cin>>n;
  vector<Boats> b;
 
  for(int i=0;i<n;i++){
    cin>>l>>p;
    b.push_back(Boats{l,p});
  }
  sort(b.begin(),b.end(),cmp_);
  
  int num_boats = 1;

  int last_best_pos = b[0].p;//keeps track of the prev available position of curr that doesn't clash with curr.
  int curr_best_pos =  b[0].p;//keeps track of the last taken position before we place i.
  
  for(int i=1;i<n;i++){
    
    //if ith boat can be placed, place it and update boat count
    if(curr_best_pos<=b[i].p){
      last_best_pos = curr_best_pos;
      curr_best_pos = max(curr_best_pos+b[i].l,b[i].p);
      num_boats++;
    }
    else{
      //if not, try to remove curr and place i instead
      curr_best_pos = min(curr_best_pos,max(last_best_pos+b[i].l,b[i].p));
    }
  }
  cout<<num_boats<<endl;
}

int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}