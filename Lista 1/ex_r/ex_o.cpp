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

bool BFS(graph g, int v, int cor){

  int n_edges, v_neighbour, cor_vizinhos;
  edge curr_edge;

  if(cor == 1){ // ATUALIZA COR P/ VIZINHOS
    cor_vizinhos = 0;
  }
  else{
    cor_vizinhos = 1;
  }

  g[v].color = cor; // ATUALIZA COR

  n_edges = g[v].edges.size();
  for(int i=0; i<n_edges; i++){ // ITERA SOBRE VIZINHOS
    curr_edge = g[v].edges[i]; // ARESTA ATUAL
    v_neighbour = curr_edge.vertices[1]; // INDICE DO VIZINHO ATUAL

    if(g[v_neighbour].color == -1){
      if(!BFS(g, v_neighbour, cor_vizinhos)){
        return(false);
      }
    }
    else{
      if(g[v_neighbour].color == cor){
        return(false);
      }
    }

  }

  return(true);
}

int main(){

  int n, m;
  int v1, v2;
  bool bicoloring;
  edge edg1, edg2;
  cin >> n;

  while(n != 0){

    graph g(n);
    cin >> m;

    // LE GRAFO
    for(int i=0; i<m; i++){
      cin >> v1 >> v2;

      edg1.vertices[0] = v1;
      edg1.vertices[1] = v2;
      edg2.vertices[0] = v2;
      edg2.vertices[1] = v1;

      g[v1].edges.push_back(edg1);
      g[v2].edges.push_back(edg2);
    }

    bicoloring = BFS(g, 0, 0);

    if(bicoloring){
      printf("BICOLORABLE.\n");
    }
    else{
      printf("NOT BICOLORABLE.\n");
    }

    cin >> n;
  }

  return(0);
}
