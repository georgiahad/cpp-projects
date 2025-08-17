#include<iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Point_2 P;

using namespace std;

void testcase(int n){
  long x,y,a,b,r,s,t,u;
  bool found = false;
    cin>>x>>y>>a>>b;
    R ray = R(P(x,y),P(a,b));
    for(int i=0;i<n;i++){
      cin>>r>>s>>t>>u;
      if(!found){
        S segment = S(P(r,s),P(t,u));
        if (CGAL::do_intersect(ray,segment)) {
           cout<<"yes"<<endl;
           found = true;
        }
      }
    }
    if(!found)
      cout<<"no"<<endl;
    return;
}
int main()
{
  std::ios_base::sync_with_stdio(false);
  int n;
  cin>>n;
  while(n!=0){
    testcase(n);
    cin>>n;
  }
  
}