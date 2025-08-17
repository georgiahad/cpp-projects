#include<iostream>
using namespace std;

int main(){
  std::ios_base::sync_with_stdio(false); // Always!
  int t;
  cin>>t;
  while(t--){
    int n,x;
    cin>>n;
    int sums[n][n] = {};
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        cin>>x;
        if(i>0 && j>0)
          sums[i][j] = sums[i][j-1] + sums[i-1][j] - sums[i-1][j-1] + x;
        else if(i>0 && j==0)
         sums[i][j] = sums[i-1][j] + x;
        else if (i==0 && j>0)
          sums[i][j] = sums[i][j-1] + x;
        else if (i==0 && j==0)
          sums[i][j] = x;
      }
    }
    int evensums = 0;
    for(int i1=0;i1<n;i1++){
      for(int i2=i1;i2<n;i2++){
        //for fixed i1 and i2, the value of the square (i1,i2,j1,j2) is sums[i2,j2]-sums[i2,j1]-sums[i1,j2]+sums[i1,j1]
        //->compute the expression above and then do the same as even pairs (linearly over j)
        int oddpairs = 0, evenpairs = 0;
        int sumofsums [n] = {};
        
        if(i1==i2){
          for(int j=0;j<n;j++){
            sumofsums[j] = sums[i2][j];
          }
          for(int j=0;j<n;j++){
            if( sumofsums[j] % 2 == 0)
              evenpairs++;
            else
              oddpairs++;
          }
          evensums += evenpairs*(evenpairs-1)/2 + oddpairs*(oddpairs-1)/2 +evenpairs;
        }
        else{
          for(int j=0;j<n;j++){
            sumofsums[j] = sums[i2][j] - sums[i1][j];
          }
          for(int j=0;j<n;j++){
            if( sumofsums[j] % 2 == 0)
              evenpairs++;
            else
              oddpairs++;
          }
          evensums += evenpairs*(evenpairs-1)/2 + oddpairs*(oddpairs-1)/2 +evenpairs;
        }
      }
    }
    cout<<evensums<<endl;
    
  }
}
