#include <stdio.h>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main(){

  int n, e;
  int x, y, h;
  cin >> n >> e;

  while( (n+e) != 0 ){

    vector<int> p(n, 1000000);
    vector<vector<int> > m(n);
    vector<vector<int> > w(n);

    for(int i=0; i<n; i++){
      m[i] = p;
      w[i] = p;
    }

    for(int i=0; i<e; i++){
      cin >> x >> y >> h;
      x--;
      y--;
      m[x][y] = h;
      w[x][y] = h;
    }

    int a1, a2 , a3;
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        if(m[i][j] < 1000000 && m[j][i] < 1000000){
          w[i][j] = 0;
        }
      }
    }

    for(int a=0; a < n; a++){
      for(int i=0; i< n; i++){
        for(int j=0; j<n; j++){
          w[i][j] = min(w[i][j], w[i][a] + w[a][j]);
        }
      }
    }

    int k;
    int o, d;
    cin >> k;
    for(int i=0; i<k; i++){
      cin >> o >> d;
      o = o-1;
      d = d-1;
      if(w[o][d] == 1000000){
        printf("Nao e possivel entregar a carta\n");
      }
      else{
        printf("%i\n", w[o][d]);
      }
    }

    printf("\n");
    cin >> n >> e;
  }

}
