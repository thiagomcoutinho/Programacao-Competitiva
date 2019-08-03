#include<stdio.h>
#include<vector>
#include<iostream>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

using namespace std;

vi visitados;
int soma;
const int UNVISITED = -1;

void DFS(AdjList G, int u){

  int v;
  visitados[u]++;

  for(int i=0; i<(int)G[u].size(); i++){
    v = G[u][i];
    if(visitados[v] == UNVISITED){
      soma++;
      DFS(G, v);
    }
  }

}

int main(){
  int e, l;
  int x, y;
  bool falha = false;
  int teste = 1;

  cin >> e >> l;
  while( (e+l) != 0 ){

    AdjList G(e);

    for(int i=0; i<l; i++){
      cin >> x >> y;
      x--, y--;
      G[x].push_back(y);
      G[y].push_back(x);
    }

    falha = false;
    for(int i=0; i<e; i++){
      visitados.assign(e, UNVISITED);
      soma = 0;
      DFS(G, i);
      if(soma != (e-1)){
        falha = true;
        break;
      }
    }

    printf("Teste %i\n", teste);
    if(falha){
      printf("falha\n");
    }
    else{
      printf("normal\n");
    }
    teste++;

    cin >> e >> l;

    if((e+l) != 0) printf("\n");

  }

}
