#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<std::vector<ii> > AdjList;

using namespace std;

const int UNVISITED = -1;
const int INF = 100000;

vi visitados;
vi distancias;

void condense_graph(AdjList& G, AdjList& G_condensed){

  // k --> u --> w

  int u, w;
  int peso1, peso2;

  int n = (int)G.size();

  for(int k=0; k<n; k++){

    for(int i=0; i<(int)G[k].size(); i++){
      u = G[k][i].second; // vertice
      peso1 = G[k][i].first; // peso1

      for(int j=0; j<(int)G[u].size(); j++){
        w = G[u][j].second; // vertice adjacente
        peso2 = G[u][j].first; // peso2

        G_condensed[k].push_back( ii(peso1 + peso2, w) );
      }
    }
  }

}

void Dijkstra(AdjList G, int start_vertex){

  priority_queue<ii, vector<ii>, greater<ii> > pq; // min heap
  ii current_edge(INF, UNVISITED);
  int current_vertex, neighbour_vertex;
  int current_weight, neighbour_weight;

  distancias[start_vertex] = 0;
  pq.push( ii(0, start_vertex) );

  while(!pq.empty()){

    current_edge = pq.top();
    pq.pop();

    current_vertex = current_edge.second;
    current_weight = current_edge.first;

    if( current_weight > distancias[current_vertex] ){
      continue;
    }

    for(int i=0; i<(int)G[current_vertex].size(); i++){

      current_edge = G[current_vertex][i];
      neighbour_vertex = current_edge.second;
      neighbour_weight = current_edge.first;

      // RELAX
      if(distancias[current_vertex] + neighbour_weight < distancias[neighbour_vertex]){
        distancias[neighbour_vertex] = distancias[current_vertex] + neighbour_weight;

        pq.push( ii(distancias[neighbour_vertex], neighbour_vertex) );
      }
    }

  }

}

int main(){

  int c, v;
  int c1, c2, peso;
  cin >> c >> v;

  AdjList G(c);
  AdjList G_condensed(c);
  visitados.assign(c, UNVISITED);
  distancias.assign(c, INF);

  for(int i=0; i<v; i++){
    cin >> c1 >> c2 >> peso;
    c1--;
    c2--;
    G[c1].push_back(make_pair(peso, c2));
    G[c2].push_back(make_pair(peso, c1));
  }

  condense_graph(G, G_condensed);
  Dijkstra(G_condensed, 0);

  c--;

  if(distancias[c] < INF){
    printf("%i\n", distancias[c]);
  }
  else{
    printf("-1\n");
  }

}
