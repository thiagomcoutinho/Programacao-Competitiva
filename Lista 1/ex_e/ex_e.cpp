#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool verifica(vector<int> seq, int m){

  int elemento = 1;
  vector<int> redes_desligadas;
  redes_desligadas.push_back(1);
  bool found;
  bool achou_13 = false;
  int indice=0;
  while(!achou_13){

    for(int p=0; p<m; p++){
      found = true;
      while(found){
        indice++;
        if(indice == seq.size()){
          indice = 0;
        }
        elemento = seq[indice];
        found = find(redes_desligadas.begin(), redes_desligadas.end(), elemento) != redes_desligadas.end();
      }
    }

    if(elemento == 13){
      achou_13 = true;
    }
    else{
      redes_desligadas.push_back(elemento);
    }

  }

  if(redes_desligadas.size()+1 == seq.size()){
    return(true);
  }
  else{
    return(false);
  }

}

int main(){

  int m, n;
  cin >> n;

  while(n != 0){
    vector<int> seq(n);
    m=1;

    for(int i=0; i<n; i++){
      seq[i] = i+1;
    }

    while(verifica(seq, m) == false){
      m++;
    }

    printf("%i\n", m);
    cin >> n;
  }

  return(0);
}
