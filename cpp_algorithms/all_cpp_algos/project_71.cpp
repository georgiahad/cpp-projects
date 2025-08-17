#include<iostream>
#include<vector>
#include<algorithm>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/pending/disjoint_sets.hpp>


typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Edge_iterator                                Edge_iterator;
typedef K::Point_2                                             P;

typedef boost::disjoint_sets_with_storage<> UF;

using namespace std;

struct Edge{
  int u;
  int v;
  K::FT length_squared; 
};

typedef std::vector<Edge>::const_iterator ECI;

void testcase(){
  
  int n,m,x,y,xs,ys,xt,yt;
  long p;
  string return_string="";
  cin>>n>>m>>p;
  vector< pair<P,int> > jammers;//stores jammer points and the index
  vector< pair<P,P> > missions;//stores missions
  UF uf(n);//union found structure for components of p-disks.
  K::FT a=0,b=0;
  UF ufa(n);//union found structure for components of a-disks.
  UF ufb(n);//union found structure for components of b-disks.
  
  //read jammer points
  for(int i=0;i<n;i++){
    cin>>x>>y;
    jammers.push_back(make_pair(P(x,y),i));
  }
  
  //read missions 
  for(int i=0;i<m;i++){
     cin>>xs>>ys>>xt>>yt;
     missions.push_back(make_pair(P(xs,ys),P(xt,yt)));
  }
  
  //Delaunay triangulation of jammers
  Delaunay t;
  t.insert(jammers.begin(), jammers.end());
  
  //find Dealunay edges and sort (incrceasing)
  vector<Edge> edges;
  for(Edge_iterator ei = t.finite_edges_begin();ei!=t.finite_edges_end();ei++){
    int u = ei->first->vertex((ei->second+1)%3)->info();
    int v = ei->first->vertex((ei->second+2)%3)->info();
    K::FT sq_len = t.segment(ei).squared_length();
    edges.push_back(Edge{u,v,sq_len});
  }
  
  //sort edges: once the components of the s and t jammers are combined, no need to continue
  sort(edges.begin(),edges.end(),[](const Edge& e1,const Edge& e2){
  return (e1.length_squared<e2.length_squared);});

  //find components of p-graph.
  //start with each vertex being a separate component
  //and whenever an edge has length<=p, combine th corresponding component.
  for (ECI e = edges.begin(); e != edges.end(); ++e)
  { 
    if( e->length_squared <= p)
      uf.union_set(e->u, e->v);
  }
  
  //used to find components of a and b graphs.
  ECI ai = edges.begin();
  ECI bi = edges.begin();
  
  for(int i=0;i<m;i++){
    
    //u and v correspond to the jammers closest to s and t.
    Delaunay::Vertex_handle v = t.nearest_vertex(missions[i].first);
    Delaunay::Vertex_handle u = t.nearest_vertex(missions[i].second);
    
    //squared distance from s and t required such that mission can be executed.

    K::FT dist_s = 4*CGAL::squared_distance(v->point(),missions[i].first);
    K::FT dist_t = 4*CGAL::squared_distance(u->point(),missions[i].second);
    
    int jv = v->info();//index of jammer at vertex v
    int ju = u->info();//index of jammer at vertex u
    
    //b = max(longest edge in EMST only for edges of missions that we are interested ("y" missions), dist_t, dist_s)
    if(uf.find_set(jv) == uf.find_set(ju) && dist_s<=p && dist_t<=p){
      //same component and both s and t reachable from a disk.
      return_string+="y";
      //update b (smallest power consumption that allows to execute the same set of missions as possible at power consumption p)
      b = max(b,max(dist_s,dist_t));
      for(;bi<edges.end();bi++){
        if(ufb.find_set(ju) != ufb.find_set(jv)){//add edges until we can reach t from s.
          ufb.union_set(bi->u, bi->v);
          b = max(bi->length_squared,b);
        }
        else{//if this mission can be executed with power b (ju and jv in the same component), stop searching.
          break;
        }
      }
    }
    else{
      return_string+="n";
    }
    //a = max(longest edge in EMST,dist_t,dist_s)->all missions can be executed
    a = max(a,max(dist_s,dist_t));
    //combine components and update a
    for(;ai<edges.end();ai++){
      if(ufa.find_set(ju) != ufa.find_set(jv)){
        ufa.union_set(ai->u, ai->v);
        a = max(ai->length_squared,a);
      }
      else{
        break;
      }
    }
    
  }
  cout<<return_string<<endl;
  cout<<fixed<<setprecision(0)<<a<<endl;
  cout<<b<<endl;
  
}


int main()
{
  int t;
  cin>>t;
  while(t--)
    testcase();
}
