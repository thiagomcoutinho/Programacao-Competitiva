#include <stdio.h>
#include <iostream>
#include <vector>

typedef struct edge{
  double weight;
  std::vector<int> vertices = std::vector<int>(2);
}edge;

typedef struct vertex{
  std::vector<edge> edges;
  int color = -1;
}vertex;

typedef std::vector<vertex> graph;

using namespace std;

bool BFS(graph &g, int v, int cor, vector<int> &count){

  int n_edges, v_neighbour, cor_vizinhos;
  edge curr_edge;

  g[v].color = cor; // ATUALIZA COR

  n_edges = g[v].edges.size();
  for(int i=0; i<n_edges; i++){ // ITERA SOBRE VIZINHOS
    curr_edge = g[v].edges[i]; // ARESTA ATUAL
    v_neighbour = curr_edge.vertices[1]; // INDICE DO VIZINHO ATUAL

    if(g[v_neighbour].color == -1){
      count[v]++;
      BFS(g, v_neighbour, cor_vizinhos, count);
    }

  }
  return(true);
}

int main(){

  int n, m;
  int v1, v2;
  bool bicoloring;
  edge edg1, edg2;
  int caso=1;
  cin >> n >> m;

  while(n != 0 && m != 0){

    graph g(n);
    // LE GRAFO
    for(int i=0; i<m; i++){
      cin >> v1 >> v2;

      v1--;
      v2--;

      edg1.vertices[0] = v1;
      edg1.vertices[1] = v2;
      edg2.vertices[0] = v2;
      edg2.vertices[1] = v1;

      g[v1].edges.push_back(edg1);
      g[v2].edges.push_back(edg2);

    }
    vector<int> count(n);
    fill(count.begin(), count.end(), 0);

    for(int i=0; i<n; i++){
      BFS(g, i, 1, count);
    }

    int soma = 0;
    for(int i=0;i <count.size(); i++){
      if(count[i] != 0){
        soma += count[i];
      }
    }
    int result = n - soma;

    printf("Case %i: %i\n", caso, result);
    caso++;
    cin >> n >> m;
  }

  return(0);
}
