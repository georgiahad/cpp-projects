#include<iostream>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef std::vector<P> Triangle;

using namespace std;

bool trianglecoverspoint(const Triangle &t, const P &p){
  return ( !CGAL::right_turn(t[0],t[1],p) && !CGAL::right_turn(t[2],t[3],p) && !CGAL::right_turn(t[4],t[5],p));

}

void testcase(){
  int n,m,x,y,q1,q2;
  vector<P> p;
  cin>>m>>n;
  
  vector<Triangle> triangles(n); //triangles[i][j]: stores point q[j] for ith triangle.
  vector< vector<int> > covers(n); //covers[i]:list of j s.t. triangle i covers segment defined by index j.
  
  //m-1 path segments
  for(int i=0;i<m;i++){
    cin>>x>>y;
    p.push_back(P(x,y));
  }
  
  //n triangles
  for(int i=0;i<n;i++){
    triangles[i].clear();
    for(int j=0;j<6;j++){
      cin>>q1>>q2;
      triangles[i].push_back(P(q1,q2));
    }
    
    // ensure correct (ccw) order for orientation tests
    for (int j = 0; j < 6; j+=2){
      if (CGAL::right_turn(triangles[i][j],triangles[i][j+1],triangles[i][(j+2)%6])) {
        P temp = triangles[i][j]; 
        triangles[i][j] = triangles[i][j+1];
        triangles[i][j+1] = temp;
      }
    }
  }
  
  //for each triangle, mark the parts it covers.
  for(int i=0;i<n;i++){
    for(int j=0;j<m-1;j++){
      //check if triangle i covers segment p[j]p[j+1] <-> both endpoints inside triangle
      if(trianglecoverspoint(triangles[i],p[j]) && trianglecoverspoint(triangles[i],p[j+1])){
        covers[i].push_back(j);
      }
    }
  }
  

  //sliding window over triangles, find min window of triangles which cover all segments
  int left = 0;
  int right = 0;
  vector<int> covered(m-1,0); //covered(j) # triangles covring segment starting with index j.
  int segmentscovered = 0;
  int k = n;
  for(auto j:covers[left]){
    covered[j]++;
    segmentscovered++;
  }
  while(right<n){

    if(segmentscovered==m-1){
      k = min(k,right-left+1);
      
      //remove segments covered by triangle indexed left.
      for(auto j:covers[left]){
        covered[j]--;
        if(covered[j]<=0){
          segmentscovered--;
          covered[j]=0;
        }
      }
      left++;
      //checks...
      if(left>right && left!=n){
        right = left;
        covered.clear();
        for(auto j:covers[left]){
          covered[j]++;
          segmentscovered++;
        }
      }
    }
    else if(segmentscovered<m-1){//not enoufg triangles, add more.
      right++;
      if(right!=n){
        //add segments covered by triangle indexed right.
        for(auto j:covers[right]){
          if(covered[j]==0){
            segmentscovered++;
          }
          covered[j]++;
        }
      }
    }
  }
  cout<<k<<endl;

  
}
int main()
{
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
}
