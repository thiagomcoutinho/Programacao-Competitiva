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
int sum_visitados;

void DFS(AdjList G, int u){

  int v;
  visitados[u]++;

  for(int i=0; i < (int)G[u].size(); i++){
    v = G[u][i];
    if(v != v_retirado){
      if(visitados[v] == UNVISITED){
        sum_visitados++;
        DFS(G, v);
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
        }
      }

      getline(cin, line);
      p = (line[0] - '0') - 1;
    }// TERMINOU O BLOCO

    // for(int i=0; i<(int)G.size(); i++){
    //   cout << "I: " << i+1 << endl;
    //   for(int j=0; j<(int)G[i].size(); j++){
    //     cout << G[i][j]+1 << " ";
    //   }
    //   cout << endl;
    // }

    // cout << "FOI: "<< endl;
    // cout << n << endl;
    int filho;
    bool first_diff;
    int valor_atual;
    for(int i=0; i<n; i++){
      v_retirado = i;
      first_diff = true;
      for(int j=0; j<(int)G[i].size(); j++){
        visitados.assign(n, UNVISITED);
        sum_visitados = 0;
        filho = G[i][j];
        DFS(G, filho);
        if(sum_visitados == 0){
          sum_critic_points++;
          break;
        }
        if(first_diff){
          valor_atual = sum_visitados;
          first_diff = false;
        }
        else{
          if(valor_atual != sum_visitados){
            sum_critic_points++;
            break;
          }
        }
      }
      // cout << "SUM VISITADOS: " << sum_visitados << endl;
    }

    printf("%i\n", sum_critic_points);

    getline(cin, line);
    n = stoi(line);
  }
}
