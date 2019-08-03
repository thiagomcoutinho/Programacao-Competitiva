#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(){

  int n, m; // Numero de elementos / Numero de linhas
  int caso = 36; // Caso escolhido
  int k = 1; // Iteracao
  int t = 3; // Tamanho da linha
  int a;
  cin >> n >> m;
  string aux;
  while( (n+m) != 0 ){
    if( k == caso ){
      cout << n << " " << m << endl;
      getline(cin, aux);
      for(int i = 0; i<m; i++){
        getline(cin, aux);
        cout << aux << endl;
      }
    }
    else{
      for(int i=0; i<m; i++){
        for(int j=0; j<t; j++){
          cin >> a;
        }
      }
    }
    k++;
    cin >> n >> m;
  }

}
