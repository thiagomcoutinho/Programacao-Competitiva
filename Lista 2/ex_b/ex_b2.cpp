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
vi stack;
vi visitados;
int it_num;
int n_scc;

void DFS_tarjan(AdjList G, int v){

  int u;
  it_num++;
  v_num[v] = it_num;
  v_hi[v] = it_num;
  stack.push_back(v);
  visitados[v] = 1;

  for(int i=0; i < (int)G[v].size(); i++){
    u = G[v][i];
    if(v_num[u] == UNVISITED){
      DFS_tarjan(G, u);
      v_hi[v] = min(v_hi[v], v_hi[u]);
    }
    else if(visitados[u]){
      v_hi[v] = min(v_hi[v], v_hi[u]);
    }
  }

  if(v_hi[v] == v_num[v]){
    // cout << "E AQUI" << endl;
    while(1){
      int aux = stack.back();
      stack.pop_back();
      visitados[aux] = 0;
      if(aux == v){
        break;
      }
    }
    // cout << "EMBAIXO" << endl;

    n_scc++;
  }

}

int main(){

  int n, m;
  int v, w;
  int teste=1;
  cin >> n >> m;

  while( (n+m) != 0 ){

    AdjList G(n);
    stack.clear();
    v_num.assign(n, UNVISITED);
    v_hi.assign(n, 0);
    visitados.assign(n, 0);
    it_num = 0;

    int p_count;
    for(int i=0; i<m; i++){
      cin >> v >> w;
      v--, w--; // OFFSET
      G[v].push_back(w);
      G[w].push_back(v);
    }

    n_scc = 0;
    for(int i=0; i<n; i++){
      if(v_num[i] == UNVISITED){
        DFS_tarjan(G, i);
      }
    }

    printf("Teste %i\n", teste);
    if(n_scc == 1){
      printf("normal\n");
    }
    else{
      printf("falha\n");
    }
    teste++;

    cin >> n >> m;
    if((n+m) != 0) printf("\n");
  }
}
