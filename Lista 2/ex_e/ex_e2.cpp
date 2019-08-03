#include <stdio.h>
#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

using namespace std;

const int UNVISITED = -1;
const int INF = 1000000;

vi visitados;
vi parent;
vi stack;
vi v_num;
vi v_hi;
int n_scc;
int it_num;


void DFS_set(AdjList undirected, AdjList& directed, int u, AdjList& matrix_auxiliar){

  int v;
  visitados[u]++;

  for(int i=0; i<(int)undirected[u].size(); i++){
    v = undirected[u][i];
    parent[v] = u;
    if( matrix_auxiliar[u][v] != -1 ){
      if( visitados[v] == UNVISITED ){
        directed[u].push_back(v);
        matrix_auxiliar[v][u] = -1;
        DFS_set(undirected, directed, v, matrix_auxiliar);
      }
      else if( v != parent[u] ){
        directed[u].push_back(v);
      }
    }
  }

}


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
    while(1){
      int aux = stack.back();
      stack.pop_back();
      visitados[aux] = 0;
      if(aux == v){
        break;
      }
    }
    n_scc++;
  }

}

void print_graph(AdjList& G){

  for(int i=0; i<(int)G.size(); i++){
    cout << "I: " << i+1 << endl;
    cout << "J: ";
    for(int j=0; j<(int)G[i].size(); j++){
      cout << G[i][j]+1 << " ";
    }
    cout << endl << endl;
  }
}

void print_matrix(AdjList matrix_auxiliar){

  for(int i=0; i<(int)matrix_auxiliar.size(); i++){
    for(int j=0; j<(int)matrix_auxiliar.size(); j++){
      cout << matrix_auxiliar[i][j] << " ";
    }
    cout << endl;
  }

}

void reset_graph(AdjList& G){

  vector<int> aux;

  for(int i=0; i<(int)G.size(); i++){
    G[i] = aux;
  }

}

int main(){

  int n, m;
  int x, y;

  cin >> n >> m;
  while( (n+m) != 0 ){

    AdjList undirected(n);
    AdjList directed(n);
    AdjList matrix_auxiliar(n, vi(n, 0));
    AdjList matrix_salva(n, vi(n, 0));

    stack.clear();

    visitados.assign(n, UNVISITED);
    parent.assign(n, UNVISITED);
    v_num.assign(n, UNVISITED);
    v_hi.assign(n, 0);
    it_num = 0;

    // print_matrix(matrix_auxiliar);

    for(int i=0; i<m; i++){
      cin >> x >> y;
      x--; y--;

      undirected[x].push_back(y);
      undirected[y].push_back(x);

      matrix_auxiliar[x][y] = 1;
      matrix_auxiliar[y][x] = 1;
    }

    // print_graph(undirected);
    // print_matrix(matrix_auxiliar);

    matrix_salva = matrix_auxiliar;

    DFS_set(undirected, directed, 0, matrix_auxiliar);

    visitados.assign(n, 0);
    n_scc = 0;
    for(int i=0; i<n; i++){
      if( v_num[i] == UNVISITED ){
        DFS_tarjan(directed, i);
      }
    }

    if(n_scc == 1){
      printf("S\n");
    }
    else{
      printf("N\n");
    }

    // cout << n_scc << endl;

    // print_graph(directed);
    // print_matrix(matrix_auxiliar);

    cin >> n >> m;
  }

}
