#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

int const UNVISITED = -1;

vi visitados;
vi parent;
int soma;
std::stack<int> s;

using namespace std;

void DFS_set(AdjList& undirected, AdjList& directed, int u, AdjList matrix_aux){

  int v;
  visitados[u]++;

  for(int i=0; i<(int)undirected[u].size(); i++){
    v = undirected[u][i];
    if( matrix_aux[u][v] != -1 ){
      if( visitados[v] == UNVISITED ){
        s.push(v);
        directed[u].push_back(v);
        matrix_aux[v][u] = -1;
        DFS_set(undirected, directed, v, matrix_aux);
      }
    }
  }
}

void DFS(AdjList& directed, int u){

  int v;
  visitados[u]++;

  for(int i=0; i<(int)directed[u].size(); i++){
    v = directed[u][i];

    if(visitados[v] == UNVISITED){
      soma++;
      DFS(directed, v);
    }
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

void reset_graph(AdjList& G){

  vector<int> aux;

  for(int i=0; i<(int)G.size(); i++){
    G[i] = aux;
  }
}

void unstack(stack<int> s){
  while(!s.empty()){
    s.pop();
  }
}

int main(){

  int n, m;
  int x, y;

  cin >> n >> m;
  while( (n+m) != 0 ){

    AdjList undirected(n);
    AdjList directed(n);
    AdjList matrix_aux(n);
    visitados.assign(n, UNVISITED);
    soma = 0;

    for(int i=0; i<n; i++){
      matrix_aux[i] = visitados;
    }

    for(int i=0; i<m; i++){
      cin >> x >> y;
      x--; y--;

      undirected[x].push_back(y);
      undirected[y].push_back(x);

      matrix_aux[x][y] = 1;
      matrix_aux[y][x] = 1;
    }

    // cout << "FOI: " << endl;
    // // AdjList directed(n);
    // DFS_set(undirected, directed, 1);

    // print_graph(directed);
    // reset_graph(directed);
    // print_graph(directed);
    //
    // visitados.assign(n, UNVISITED);
    // parent.assign(n, UNVISITED);
    // DFS_set(undirected, directed, 1);
    // visitados.assign(n, UNVISITED);
    // print_graph(directed);
    // DFS(directed, 0);
    // cout << "SOMA: " << soma << endl;
    int u;
    bool funciona = false;
    for(int i=0; i<n; i++){

      reset_graph(directed);

      parent[i] = i;

      DFS_set(undirected, directed, i, matrix_aux);
      print_graph(directed);

      u = s.top();
      unstack(s);
      visitados.assign(n, UNVISITED);

      soma = 0;

      DFS(directed, u);

      parent.assign(n, UNVISITED);
      visitados.assign(n, UNVISITED);
      cout << soma << endl;
      if(soma == (n-1)){
        funciona = true;
        break;
      }
      // cout << "SOMA: " << soma << endl;
    }

    if(funciona){
      printf("S\n");
    }
    else{
      printf("N\n");
    }

    // print_graph(directed);

    // int u;
    // for(int i=0; i<n; i++){
    //   AdjList directed(n);
    //   cout << "FOI "<<  endl;
    //   DFS(undirected, directed, i, true);
    //   cout << soma << endl;
    //   u = s.top();
    //   print_graph(directed);
    //   unstack(s);
    //   visitados.assign(n, UNVISITED);
    //   soma=0;
    //
    //   DFS(directed, directed, u, false);
    //   directed.clear();
    //   cout << soma << endl;
    // }

    // cout << "SOMA: " << soma << endl;

    cin >> n >> m;
  }

}
