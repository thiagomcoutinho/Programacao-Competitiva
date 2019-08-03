#include <stdio.h>
#include <map>
#include <string>

using namespace std;

int main(){

  int n_casos;
  cin >> n_casos;

  for(int caso=0; caso<n_casos; caso++){
    // Le numero de candidatos
    int n_cand;
    cin >> n_cand;

    // STRING EM BRANCO
    string blank;
    getline(cin, blank);

    // LE NOMES DOS CANDIDATOS
    vector<string> nome_candidatos(n_cand);
    string nome_candidato;
    for(int i=0; i<n_cand; i++){
      getline(cin, nome_candidato);
      nome_candidatos[i] = nome_candidato;
    }
  }

  return(0);
}
