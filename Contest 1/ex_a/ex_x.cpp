#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){


  int p, n, c;

  cin >> p >> n >> c;
  while( (p+n+c) != 0 ){

    map<int, int> mapa;
    map<int, int>::iterator it;

    int ponto;
    bool fim;
    bool palito;
    int tamanho;

    vector<int> l(p, 0);

    vector<vector<int> > m(n);
    for(int i=0; i<n; i++){
      m[i] = l;
    }

    for(int i=0; i<n; i++){
      for(int j=0; j<p; j++){
        cin >> m[i][j];
      }
    }

    for(int i=0; i<p; i++){

      palito = false;
      tamanho = 0;
      for(int j=0; j<n; j++){
        ponto = m[j][i];
        if(ponto == 0){
          if(palito){
            palito = false;
            it = mapa.find(tamanho);
            if( it != mapa.end() ){ // Já tem o tamanho
              mapa[tamanho]++;
            }
            else{
              mapa.insert(pair<int, int>(tamanho, 1));
            }
            tamanho = 0;
          }
        }
        else{
          if(!palito){
            palito = true;
          }
          tamanho++;
        }
      }
      it = mapa.find(tamanho);
      if( it != mapa.end() ){
        mapa[tamanho]++;
      }
      else{
        mapa.insert(pair<int, int>(tamanho,1));
      }

    }

    int soma = 0;
    for(int i=1; i<=p; i++){
      if( i >= c ){
        it = mapa.find(i);
        if( it != mapa.end() ){
          soma += mapa[i];
        }
      }
    }

    printf("%i\n", soma);

    cin >> p >> n >> c;

  }
}
