
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<Index,K>     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Face_iterator Face_iterator;
typedef std::pair<int,K::FT> PA;
typedef K::Point_2 P;


K::FT max_ = K::FT(std::numeric_limits<int64_t>::max());
using namespace std;

struct cmp_ {
     bool operator()(const PA  &a, const PA &b)
    {
        return a.second < b.second;
    }
};

void testcase(){
  int n,m;
  long d,x,y,s;
  cin>>n>>m>>d;
  vector<pair<P,int> > dem;

  for(int i=0;i<n;i++){
    cin>>x>>y;
    dem.push_back({P(x,y),i});
  }
  
  Delaunay t;
  t.insert(dem.begin(),dem.end());

  int num_faces = 1; 
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
     f->info() = num_faces++;
  t.infinite_face()->info() = 0;

  vector<vector<PA> >adj(num_faces);

  for(Face_iterator f = t.finite_faces_begin();f!=t.finite_faces_end();f++){
    int fi = f->info();
    for(int i=0;i<3;i++){
      Vertex_handle u = f->vertex((i+1)%3);
      Vertex_handle v = f->vertex((i+2)%3);
      int fj = f->neighbor(i)->info();
      K::FT len = CGAL::squared_distance(u->point(),v->point());
      if(t.is_infinite(f->neighbor(i))){
        fj = 0;
      }
      adj[fi].push_back({fj,len});
      
      if(fj==0)//if fj infinite vertex, add other direction
        adj[fj].push_back({fi,len});
    }
  }

  priority_queue<PA,vector<PA>,cmp_> pq;//by default largest elemennt first.
  pq = priority_queue<PA,vector<PA>,cmp_>(); 
  vector<K::FT> bottleneck(num_faces,-1); //stores maximum minimum length edge length, this is to reach infinite vertex
  vector<K::FT> radi(num_faces,0);

  for(auto f = t.finite_faces_begin();f!=t.finite_faces_end();f++){
    P u = f->vertex(0)->point();
    P v = f->vertex(1)->point();
    P w = f->vertex(2)->point();
    K::Circle_2 c = K::Circle_2(u,v,w);
    K::FT rad = c.squared_radius();
    radi[f->info()] = rad;
  }

  //first dijkstra, to reach infinite face;
  bottleneck[0]  = max_;
  pq.push({0,max_});//push infinite vertex with bottleneck inf.

  while(!pq.empty()){
    int curr = pq.top().first;
    pq.pop();
    for(auto x : adj[curr]){
      int u = x.first;
      K::FT len = x.second;
      if(bottleneck[u]<min(bottleneck[curr],len)){
        bottleneck[u] = min(bottleneck[curr],len);
        pq.push({u,bottleneck[u]});
      }
    }
       
  }
  //second dijkstra, to safe faces
  radi[0] = max_;
   pq = priority_queue<PA,vector<PA>,cmp_>(); 
  //push all safe faces
  for(int i=0;i<num_faces;i++){
    pq.push({i,radi[i]});//infinite vertex is taken into account too.
  }
   while(!pq.empty()){
    int curr = pq.top().first;
    pq.pop();
    for(auto x : adj[curr]){
      int u = x.first;
      K::FT len = x.second;
      if(radi[u]<min(radi[curr],len)){
        radi[u] = min(radi[curr],len);
        pq.push({u,radi[u]});
      }
    }
       
  }

       
            
  for(int i=0;i<m;i++){
    cin>>x>>y>>s;
    P p = P(x,y);

    Vertex_handle v = t.nearest_vertex(p);
    K::FT dist = CGAL::squared_distance(v->point(),p);
    Delaunay::Face_handle f = t.locate(p);
    if(dist>=4*(s+d)*(s+d) || t.is_infinite(f)){
      cout<<"y";
    }
    else if(dist<(s+d)*(s+d)){
      cout<<"n";
    }
    else{//need to move to a safe space, either infinite face or a safe face.
      if(bottleneck[f->info()]>=(s+d)*(s+d)){//move to infinite face
        cout<<"y";
      }
      else if(radi[f->info()]>=4*(d+s)*(d+s)){//move to safe face
        cout<<"y";
      }
     else{
       cout<<"n";
     }
    }
  }
  cout<<endl;
  return;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    testcase();
  }
  return 0;
}