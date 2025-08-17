
#include<iostream>
#include<queue>
#include<vector>
#include<utility>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<size_t,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Face_iterator Face_iterator;

typedef std::pair<int,double> pa;
using namespace std;

struct cmp_ {
     bool operator()(const pa  &a, const pa  &b)
    {
        return a.second < b.second;
    }
};

typedef priority_queue<pa,vector<pa>,cmp_> PQ;//first: stores face index, second, stores distance.

void testcase(int n){

  int m, x,y;
  double d;
  vector<P> locations;
  for(int i=0;i<n;i++){
    cin>>x>>y;
    locations.push_back(P(x,y));
  }
  Triangulation t;
  t.insert(locations.begin(), locations.end());
  int nr_faces = t.number_of_faces();//number of faces of t;
  //give an index to the faces
  int num_faces = 1; 
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
     f->info() = num_faces++;
  t.infinite_face()->info() = 0;
  //widest path problem / maximum bottleneck path
  //for all faces, find max bottleneck path from infinite face to current face.
  //path between two faces whose minimum edge weight is the largest
  //graph with V = faces in triangulation, edges between adjacent faces with weight = length of the edge ^2.
  
  //make an adjecency list on faces (with weights being the length of the edge that the 2 faces connect.
  vector<vector<pa> >adj(num_faces);
  for(Face_iterator f = t.finite_faces_begin();f!=t.finite_faces_end();f++){
    int u = f->info();
     for (int i = 0; i < 3; ++i) {
            auto f1 = f->neighbor(i);
            auto p1 = f->vertex((i + 1) % 3)->point();
            auto p2 = f->vertex((i + 2) % 3)->point();
            // inputs are < 2^24, so double suffices
            double dist = CGAL::squared_distance(p1, p2);
           
            int v = f1->info();
            if(t.is_infinite(f1)){
              v=0;
            }
            adj[u].push_back({v, dist});
            if (v == 0) { // we do not go over infinite faces in the other direction (infinite faces are not considered in the for loop), so add here
                adj[v].push_back({u, dist});
            }
        }
  }

  vector<double>min_weight(num_faces,-1);//stores the largest minimum edge weight for the current face starting form infinite face.
  PQ q = PQ();

  q.push(make_pair(0,DBL_MAX));//push infinite face.
  min_weight[0] = DBL_MAX;

  while(!q.empty()){
    int curr = q.top().first;
    q.pop();
    for(auto j : adj[curr]){
      double l = j.second;
      if(min_weight[j.first]<min(min_weight[curr],l)){
        min_weight[j.first]=min(min_weight[curr],l);
        q.push(make_pair(j.first,min_weight[j.first]));
      }
    }
  } 
    
  cin>>m;
  for(int i=0;i<m;i++){
    cin>>x>>y>>d;
    P p = P(x,y);
    Triangulation::Face_handle f = t.locate(p);//get handle to the face that p is located
    double dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    if(d>dist){//if distance to closest point smaller that d, no
      cout<<"n";
    }
    else if(t.is_infinite(f) || min_weight[f->info()]>=4*d){
      cout<<"y";
    }
    else{
      cout<<"n";
    }
  }
  cout<<endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  int n;
  cin>>n;
  while(n!=0){
    testcase(n);
    cin>>n;
  }
}
