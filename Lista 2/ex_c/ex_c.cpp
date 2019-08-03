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
const int FLAG = -2;

vi visitados;
vi distancias;

void DFS(AdjList& G, AdjList& compact_G, int v){

  int u, w;
  int peso1, peso2;
  visitados[v]++;

  for(int i=0; i<(int)G[v].size(); i++){
    u = G[v][i].second; // vertice
    peso1 = G[v][i].first; // peso

    if( visitados[u] == UNVISITED ){

      for(int j=0; j<(int)G[u].size(); j++){
        w = G[u][j].second; // vertice
        peso2 = G[u][j].first; // peso

        if( visitados[w] == UNVISITED ){
          // CONDENSAMENTO
          cout << "FOI AQUI O: "<< endl;
          compact_G[v].push_back(make_pair(peso1 + peso2, w));
          DFS(G, compact_G, w);
        }

      }

    }

  }


}

void BFS(AdjList& G, AdjList& compact_G, int v){

  int u, w, peso, peso2;
  ii edge;

  queue<int> q;
  q.push(v);
  q.push(0); // level 0

  while(!q.empty()){
    v = q.front();
    q.pop();

    for(int i=0; i<(int)G[v].size(); i++){
      edge = G[v][i];
      u = edge.second;
      peso = edge.first;

      if(visitados[u] == UNVISITED){

        visitados[u]++;

        for(int j=0; j<(int)G[u].size(); j++){
          edge = G[u][j];
          w = edge.second;
          peso2 = edge.first;

          if(visitados[w] == UNVISITED){
            compact_G[i].push_back(ii(peso+peso2, w));
            q.push(w);
          }


        }
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
  pq.push( make_pair(0, start_vertex) );

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

        pq.push( make_pair(distancias[neighbour_vertex], neighbour_vertex) );
      }
    }

  }

}

int main(){

  int c, v;
  int c1, c2, peso;
  cin >> c >> v;

  AdjList G(c);
  AdjList compact_G(c);
  visitados.assign(c, UNVISITED);
  distancias.assign(c, INF);

  for(int i=0; i<v; i++){
    cin >> c1 >> c2 >> peso;
    c1--;
    c2--;
    G[c1].push_back(make_pair(peso, c2));
    G[c2].push_back(make_pair(peso, c1));
  }

  BFS(G, compact_G, 0);

  // Cria caminho condensando vertices dois em dois ( numero par de pedagios )
  // DFS(G, compact_G, 0);
  // // Shortest path
  Dijkstra(compact_G, 0);
  //
  // cout << "G: " << endl;
  // for(int i=0; i<(int)G.size(); i++){
  //   cout << "I: " << i+1 << endl;
  //   for(int j=0; j<(int)G[i].size(); j++){
  //     cout << "J: " << G[i][j].first << " " << G[i][j].second+1 << endl;
  //   }
  // }
  // cout << "COMPACT_G: " << endl;
  // for(int i=0; i<(int)compact_G.size(); i++){
  //   cout << "I: " << i+1 << endl;
  //   for(int j=0; j<(int)compact_G[i].size(); j++){
  //     cout << "J: " << compact_G[i][j].first << " " << compact_G[i][j].second+1 << endl;
  //   }
  // }
  // bool found = false;
  // int shortest_path;
  // ii aresta;
  // c--;
  // // cout << "C: "<< c << endl;
  // for(int i=0; i<(int)compact_G[0].size(); i++){
  //   aresta = compact_G[0][i];
  //   if(aresta.second == c){
  //     // cout << aresta.first << " " << aresta.second << endl;
  //     found = true;
  //     shortest_path = aresta.first;
  //     break;
  //   }
  // }
  //
  // if(found){
  //   printf("%i\n", shortest_path);
  // }
  // else{
  //   printf("-1\n");
  // }
  //
  // cout << "DISTANCIAS: " << endl;
  // for(int i=0; i<c; i++){
  //   cout << distancias[i] << endl;
  // }
  c--;

  if(distancias[c] < INF){
    printf("%i\n", distancias[c]);
  }
  else{
    printf("-1\n");
  }

}
