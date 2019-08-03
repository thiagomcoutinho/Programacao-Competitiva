#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int main(){

  int n;
  string gifter, receiver, aux;
  map<string, int> pessoas;
  vector<string> nomes;
  bool imprime_barra_n = false;

  while(cin >> n){
    if(imprime_barra_n){
      printf("\n");
    }
    imprime_barra_n = true;
    for(int i=0; i<n; i++){
      cin >> aux;
      nomes.push_back(aux);
      pessoas.insert(make_pair(nomes[i], 0));
    }

    int montante, divisor, parcela, resto;
    for(int j=0; j<n; j++){
      cin >> gifter;
      cin >> montante;
      cin >> divisor;
      if( divisor != 0 ){
        resto = montante % divisor;
        parcela = montante/divisor;
        pessoas[gifter] -= montante - resto;
        for(int k=0; k<divisor; k++){
          cin >> receiver;
          pessoas[receiver] += parcela;
        }
      }
    }

    for(int m=0; m<nomes.size(); m++){
      printf("%s %d\n", nomes[m].c_str(), pessoas[nomes[m]]);
      pessoas.erase(nomes[m]);
    }
    nomes.clear();
  }

  return(0);
}
