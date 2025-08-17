///1
#include<iostream>
#include<vector>
#include<algorithm>
#include<CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;

struct Bike{
  long y0;
  long x1;
  long y1;
  long idx;
};

bool comp_by_y0(const Bike &a, const Bike &b)
{
  return a.y0 < b.y0;
}
bool comp_by_idx(const Bike &a, const Bike &b)
{
  return a.idx < b.idx;
}

bool clash(const Bike &a, const Bike &b){
  
  //true if a clashes with b (precondition: a.y0>b.y0)

  CGAL::Gmpq slope_a = CGAL::Gmpq(a.y1-a.y0)/CGAL::Gmpq(a.x1);
  CGAL::Gmpq slope_b = CGAL::Gmpq(b.y1-b.y0)/CGAL::Gmpq(b.x1);
 
  CGAL::Gmpq slope_a_abs = abs(slope_a);
  CGAL::Gmpq slope_b_abs = abs(slope_b);
 
  if(slope_a<0 && slope_b<0){
    return (slope_a_abs > slope_b_abs);
  }
  else if(slope_a>0 && slope_b>0){
    return (slope_a_abs < slope_b_abs);
  }
  else if(slope_a>0 && slope_b<=0){
    return false;
  }
  else if(slope_a<=0 && slope_b>0){
    return true;
  }
  else{
    return false;//both slopes = 0.
  }
}

bool a_outlives_b(const Bike &a, const Bike &b){
  //true if b dies, false if a dies (precondition: a.y0>b.y0 and a and b clash)

  CGAL::Gmpq slope_a = CGAL::Gmpq(a.y1-a.y0)/CGAL::Gmpq(a.x1);
  CGAL::Gmpq slope_b = CGAL::Gmpq(b.y1-b.y0)/CGAL::Gmpq(b.x1);
 
  CGAL::Gmpq slope_a_abs = abs(slope_a);
  CGAL::Gmpq slope_b_abs = abs(slope_b);
 
 
  if(slope_a<0 && slope_b<0){
    return false;
  }
  else if(slope_a>0 && slope_b>0){
    return true;
  }
  // else if(slope_a>0 && slope_b<=0){
  //   //never happens, precondition.
  // }
  else if(slope_a<=0 && slope_b>0){
    if(slope_a_abs<slope_b_abs)
      return true;
    else
      return false;
  }
}

void testcase(){
  std::ios_base::sync_with_stdio(false);
  long n,y0,y1,x1;
  cin>>n;
  vector<Bike> b;
  vector<bool> forever(n,true);
  for(int i=0;i<n;i++){
    cin>>y0>>x1>>y1;
    b.push_back({y0,x1,y1,i});
  }

  sort(b.begin(),b.end(),comp_by_y0);
  
 
  for(int i=1;i<n;i++){
    for(int j=i-1;j>=0;j--){

      if(!forever[b[j].idx]){//if j dead already
        continue;
      }
      if(!clash(b[i],b[j])){
        break;
      }
      else{
        if(a_outlives_b(b[i],b[j])){//b dies
          forever[b[j].idx] = false;
        }
        else{//a dies
          forever[b[i].idx] = false;
          break;//i dies, no need to continue this iteration.
        }
      }
    }
  }
  
  sort(b.begin(),b.end(),comp_by_idx);
  for(int i=0;i<n;i++){
    if(forever[b[i].idx])
      cout<<b[i].idx<<" ";
  }
  cout<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}