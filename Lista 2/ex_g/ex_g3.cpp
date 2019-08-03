#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

using namespace std;

const int UNVISITED = -1;

vi visitados;
int v_retirado;
int cc, original_cc;

void DFS(AdjList G, int u){

  int v;

  if( u != v_retirado ){

    visitados[u]++;

    for(int i=0; i < (int)G[u].size(); i++){
      v = G[u][i];
      if(v != v_retirado){
        if(visitados[v] == UNVISITED){
          DFS(G, v);
        }
      }
    }

  }

}

int main(){

  int n, p, l;
  string line;
  string value;
  istringstream iss;
  bool first;

  int sum_critic_points;

  getline(cin, line);
  n = stoi(line);

  while(n != 0){

    // INITIALIZATION OF VARS
    AdjList G(n);
    sum_critic_points = 0;
    cc = 0;
    original_cc = 0;

    getline(cin, line);

    p = (line[0] - '0') - 1;
    while(p >= 0){
      iss.clear();
      iss.str(line);

      first = true;
      while(getline(iss, value, ' ')){
        if(!first){
          l = stoi(value) - 1;
          G[p].push_back(l);
          G[l].push_back(p);
        }
        else{
          first = false;
          p = stoi(value) -1;
        }
      }

      getline(cin, line);
      p = (line[0] - '0') - 1;
    }// TERMINOU O BLOCO

    v_retirado = -1;
    visitados.assign(n, UNVISITED);
    for(int i=0; i<n; i++){
      if(visitados[i] == UNVISITED){
        DFS(G, i);
        original_cc++;
      }
    }

    for(int j=0; j<n; j++){
      v_retirado = j;
      cc = 0;
      visitados.assign(n, UNVISITED);
      for(int i=0; i<n; i++){
        if(visitados[i] == UNVISITED && i != j){
          DFS(G, i);
          cc++;
        }
      }
      if( cc > original_cc ){
        sum_critic_points++;
      }
    }
    printf("%i\n", sum_critic_points);

    getline(cin, line);
    n = stoi(line);
  }
}
