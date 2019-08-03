#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

typedef std::vector<int> vi;
typedef std::vector<vi> AdjList;

using namespace std;

const int UNVISITED = -1;

vi v_num;
vi v_hi;
vi critic_points;
vi v_parent;
int rootEdges;
int root;
int it_num;

void DFS_tarjan(AdjList G, int u){

  int v;
  v_num[u] = it_num;
  v_hi[u] = it_num;
  it_num++;

  for(int i=0; i < (int)G[u].size(); i++){
    v = G[u][i];
    if(v_num[v] == UNVISITED){
      v_parent[v] = u;

      if(u == root){
        rootEdges++;
      }

      DFS_tarjan(G, v);

      if( v_hi[v] >= v_num[u] ){
        if( u != root ){ // APENAS PONTOS CRITICOS SEM SER NA BORDA
          // cout << "CRITICAL POINT" << endl;
          // cout << "V: " << v+1 << " U: " << u+1 << endl;
          critic_points[u] = 1;
        }
      }
      v_hi[u] = min(v_hi[v], v_hi[u]);

    }
    else if( v != v_parent[u] ){
      v_hi[u] = min(v_hi[u], v_num[v]);
    }
  }

}

int main(){

  int n, p, l;
  int sum_critic_points;
  string line;
  string value;
  istringstream iss;
  bool first;

  getline(cin, line);
  n = stoi(line);

  while(n != 0){

    // INITIALIZATION OF VARS
    AdjList G(n);
    critic_points.assign(n, 0);
    v_hi.assign(n, 0);
    v_num.assign(n, UNVISITED);
    v_parent.assign(n, 0);
    sum_critic_points = 0;
    it_num = 0;

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

    for(int i=0; i<n; i++){
      if(v_num[i] == UNVISITED){
        root = i;
        rootEdges = 0;
        DFS_tarjan(G, root);
        // cout << "CRITICAL: " << endl;
        // for(int j=0; j<n; j++){
        //   cout << critic_points[j] << endl;
        // }
        if( rootEdges > 1 ){
          // cout << "ROOT EDGES: " << rootEdges << endl;
          critic_points[root] = 1;
        }
      }
    }

    // cout << "FOI" << endl;
    for(int i=0; i<n; i++){
      // cout << critic_points[i] << endl;
      sum_critic_points += critic_points[i];
    }
    printf("%i\n", sum_critic_points);

    getline(cin, line);
    n = stoi(line);
  }
}
