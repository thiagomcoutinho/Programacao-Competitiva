#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;


void imprime(vector<vector<int> > array_v, vector<vector<int> > array_h, int n){

  for(int j=0; j<2*n; j++){
    if(j % 2 == 0){
      for(int i=0; i<n; i++){
        cout << "O";
        if(array_h[j/2][i]==1){
          cout << "--";
        }
        else{
          cout << "  ";
        }
      }
    }
    else{
      cout << endl;
      for(int i=0; i<n; i++){
        if(array_v[i][(j-1)/2] == 1){
          cout << "|  ";
        }
        else{
          cout << "   ";
        }
      }
      cout << endl;
    }
  }

}
bool walk(vector<vector<int> > array_h, vector<vector<int> > array_v, int tam, int i, int j){

  if(tam == 2){
    if(array_h[i][j] != 1){
      return(false);
    }
    if(array_h[i+1][j] != 1){
      return(false);
    }
    if(array_v[j][i] != 1){
      return(false);
    }
    if(array_v[j+1][i] != 1){
      return(false);
    }
  }
  else{

    int passos = tam-1;
    for(int a=0; a<passos; a++){ // CONEXOES HORIZONTAIS
      if(array_h[i][j+a] != 1){
        return(false); // LINHA SUPERIOR
      }
      if(array_h[i+passos][j+a] != 1){
        return(false); // LINHA INFERIOR
      }
    }

    for(int b=0; b<passos; b++){
      if(array_v[j][i+b] != 1){
        return(false);
      }
      if(array_v[j+passos][i+b] != 1){
        return(false);
      }
    }
  }


  return(true);
}

int main(){

  int n, m;
  int problem = 1;

  while(cin >> n){
    // LEITURA DOS PARAMETROS INICIAIS
    if(problem != 1){
      printf("\n");
      printf("**********************************\n\n");
    }
    printf("Problem #%i\n\n", problem);
    problem++;
    cin >> m;

    // CRIANDO MATRIZ
    vector<vector<int> > array_v(n, vector<int>(n));
    vector<vector<int> > array_h(n, vector<int>(n));
    for(int idx=0; idx<n; idx++){
      fill(array_v[idx].begin(), array_v[idx].end(), 0);
      fill(array_h[idx].begin(), array_h[idx].end(), 0);
    }

    // LEITURA DA MATRIZ
    char orient;
    int i, j;
    for(int linha=0; linha<m; linha++){
      cin >> orient >> i >> j;
      i--;
      j--;
      if(orient == 'H'){
        array_h[i][j] = 1;
      }
      else{
        array_v[i][j] = 1;
      }
    }

    // IMPRESSAO DA MATRIZ NA TELA
    // imprime(array_v, array_h, n);

    int qtd;
    vector<vector<int> > results;
    vector<int> aux(2);
    for(int tam=2; tam<=n; tam++){ // AUMENTA TAMANHO DOS QUADRADOS
      qtd = 0;
      for(int i=0; i<=(n-tam); i++){ // PERCORRE GRID
        for(int j=0; j<=(n-tam); j++){
          if(walk(array_h, array_v, tam, i, j)){
            qtd++;
          }
        }
      }
      if(qtd != 0){
        aux[0] = qtd;
        aux[1] = tam-1;
        results.push_back(aux);
      }

    }

    if(results.size() == 0){
      printf("No completed squares can be found.\n");
    }
    else{
      for(int i=0; i<results.size(); i++){
        aux = results[i];
        printf("%i square (s) of size %i\n", aux[0], aux[1]);
      }
    }
  }

  return(0);
}
