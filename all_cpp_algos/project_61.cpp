///1

#include<iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Point_2 P;

using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n){
  long x,y,a,b,r,s,t,u;
  bool first_intersection = true;
    cin>>x>>y>>a>>b;
    P start = P(x,y);
    R ray = R(start,P(a,b));
    vector<S> segments;
    S clipped_segment;
    P int_point;
    for(int i=0;i<n;i++){
      cin>>r>>s>>t>>u;
      segments.push_back(S(P(r,s),P(t,u)));
    }
    //shuffle segments
    std::random_shuffle(segments.begin(), segments.end());
    for(int i=0;i<n;i++){
      //if we found the first intersection, slip the ray to segment
      if (first_intersection == true && CGAL::do_intersect(segments[i],ray)) {
        first_intersection = false;
        auto o = CGAL::intersection(ray,segments[i]);
        if (const P* op = boost::get<P>(&*o)){
          int_point = *op;
          clipped_segment = S(start,int_point);
        }
        else if(const S* os = boost::get<S>(&*o)){
          if(CGAL::squared_distance(os->source(),start)<CGAL::squared_distance(os->target(),start))
            int_point = os->source();
          else
            int_point = os->target();
           clipped_segment = S(start,int_point);
        }
      }
      //second+ intersection found.
      if(!first_intersection && CGAL::do_intersect(segments[i],clipped_segment)){
         auto o = CGAL::intersection(ray,segments[i]);
         if (const P* op = boost::get<P>(&*o)){
          int_point = *op;
          clipped_segment = S(start,int_point);
        }
        else if(const S* os = boost::get<S>(&*o)){
          if(CGAL::squared_distance(os->source(),start)<CGAL::squared_distance(os->target(),start))
            int_point = os->source();
          else
            int_point = os->target();
           clipped_segment = S(start,int_point);
        }
      }
    }
    //int_point is now the closest point to start.
    //round down both coordinates.
    if(first_intersection==true){
      cout<<"no"<<endl;
      return;
    }
    double xx = floor_to_double(int_point.x());
    double yy = floor_to_double(int_point.y());
    cout<<xx<<" "<<yy<<endl;
    return;
}


int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int n;
  cin>>n;
  while(n!=0){
    testcase(n);
    cin>>n;
  }
}