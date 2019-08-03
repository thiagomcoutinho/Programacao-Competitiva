#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

using namespace std;

const int UNVISITED = -1;

vi v_num;
vi v_hi;
vi visited;
int it_num;
int u;

void DFS_tarjan(AdjList G, int v){

  it_num++;
  v_num[v] = it_num;
  v_hi[v] = it_num;

  // cout << "PUSH_BACK: ";
  // cout << v + 1 << endl;
  visited.push_back(v);

  for(int i=0; i < (int)G[v].size(); i++){
    u = G[v][i];
    if(v_num[u] == UNVISITED){
      DFS_tarjan(G, u);
    }
    v_hi[v] = min(v_hi[v], v_hi[u]);
  }

  // if(v_hi[v] == v_num[v]){
  //   cout << "V: " << v << endl;
  //   for(int i=0; i<(int)visited.size(); i++){
  //     cout << visited[i] << " ";
  //   }
  //   cout << endl;
  // }

}

int main(){

  int n, m;
  int v, w, p;
  int start_v;
  cin >> n >> m;

  while( (n+m) != 0 ){

    // cout << "INICIO"<< endl;

    AdjList G(n);
    visited.clear();
    v_num.assign(n, UNVISITED);
    v_hi.assign(n, 0);
    it_num = 0;
    start_v = 0;

    map<int, int> p1_count;
    for(int i=0; i<n; i++){
      p1_count.insert(pair<int,int>(i, 0));
    }

    int p_count;
    for(int i=0; i<m; i++){
      cin >> v >> w >> p;
      v--, w--; // OFFSET
      // cout << "V: " << v << "W: " << w << endl;
      G[v].push_back(w);

      if(p == 2){
        // start_v = v; // EVITA COMECOS RUINS
        G[w].push_back(v);
      }
      else{
        p1_count[v]++;
      }
    }

    for(int i=0; i<n; i++){
      if(p1_count[i] == 2){
        start_v = i;
      }
    }

    // for(int i=0; i<n; i++){
    //   cout << "V: " << i+1 << endl;
    //   for(int j=0; j<(int)G[i].size(); j++){
    //     cout << G[i][j]+1 << " ";
    //   }
    //   cout << endl;
    // }

    bool zero_edges = false;
    for(int i=0; i<n; i++){
      if( (int)G[i].size() == 0 ){
        zero_edges = true;
      }
    }

    if(zero_edges){
      printf("0\n");
    }
    else{
      DFS_tarjan(G, start_v);
      cout << "START V: " << start_v << endl;
      for(int i =0; i<n; i++){
        cout << v_hi[i] << " " << endl;
      }
      if( int(visited.size()) == n ){ // GARANTINDO A VOLTA

        int new_v = visited.back(); // IRMAO SECUNDARIO DE START_V
        int new_v2 = visited[1];    // IRMAO PRINCIPAL DE START_V
        visited.clear();
        v_num.assign(n, UNVISITED);
        v_hi.assign(n, 0);

        DFS_tarjan(G, new_v);
        int size_new_v = (int)visited.size();

        visited.clear();
        v_num.assign(n, UNVISITED);
        v_hi.assign(n, 0);
        DFS_tarjan(G, new_v2);
        int size_new_v2 = (int)visited.size();

        if( size_new_v == n && size_new_v2 == n){
          printf("1\n");
        }
        else{
          printf("0\n");
        }
      }
      else{
        printf("0\n");
      }
    }

    // cout << "CU" << endl;
    // cout << n << endl;
    // cout << visited.size() << endl;

    cin >> n >> m;
  }
}
