#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > lerVotos(int n_cand){

  vector<vector<int> > votos;
  stringstream ss;
  string line;
  string aux;
  int indx;
  while(getline(cin, line)){
    if(!line.empty()){
      ss.str("");
      ss.clear();
      ss << line;
      vector<int> linha(n_cand);
      indx = 0;
      while(getline(ss, aux, ' ')){
        linha[indx] = stoi(aux);
        indx++;
      }
      votos.push_back(linha);
    }
    else{
      break;
    }
  }
  // cout << "PASSOU LER VOTOS" << endl;
  return(votos);
}

vector<int> contaVotos(int n_cand, vector<vector<int> > votos, vector<int> eliminados){

  int n_of_votes = votos.size();
  vector<int> votos_candidatos(n_cand);
  fill(votos_candidatos.begin(), votos_candidatos.end(), 0);
  int candidato;

  int j;
  bool valid;
  for(int i=0; i<n_of_votes; i++){
    j=0;
    valid = false;
    while(!valid){
      valid = true;
      for(int k=0; k<eliminados.size(); k++){
        if(eliminados[k] == votos[i][j]){
          valid=false;
          j++;
          break;
        }
      }
    }
    candidato = votos[i][j]-1;
    votos_candidatos[candidato]++;
  }

  // cout << "PASSOU CONTA VOTOS" << endl;
  return(votos_candidatos);
}



int main(){

  int n_casos;
  cin >> n_casos;

  for(int caso=0; caso<n_casos; caso++){
    // READ PARAMETERS
    int n_cand;
    cin >> n_cand;

    string aux;
    getline(cin, aux);

    vector<string> nomes_candidatos(n_cand);
    // NOMES DOS CANDIDATOS
    for(int i=0; i<n_cand; i++){
      getline(cin, aux);
      nomes_candidatos[i] = aux;
    }


    bool fim = false;
    vector<vector<int> > votos = lerVotos(n_cand);
    vector<int> eliminados;
    while(!fim){

      // COLOCAR NA RECURSAO
      // cout << "ANTES CONTA VOTOS"<< endl;
      // cout << votos.size() << endl;
      vector<int> votos_candidatos = contaVotos(n_cand, votos, eliminados);
      // cout << "FOI!" << endl;
      // for(int i=0; i<votos_candidatos.size(); i++){
      //   cout << "TESTEADNO AQUI:" << endl;
      //   cout << eliminados[0] << endl;
      //   cout << votos_candidatos[i] << endl;
      // }
      // cout <<" DEPOIS" << endl;
      // VERIFICACAO DE ETAPA
      int n_of_votes = votos.size();
      int metade_votos = n_of_votes/2;

      // vector<int> freq_votos(n_cand);
      // fill(freq_votos.begin(), freq_votos.end(), 0);

      // for(int v=0; v<n_of_votes; v++){
      //   for(int c=0; c<n_cand; c++){
      //     if(votos[v][0]-1 == c){
      //       freq_votos[c]++;
      //     }
      //   }
      // }

      int maior=-1;
      int menor= 100000;
      for(int f=0; f<votos_candidatos.size(); f++){
        if(votos_candidatos[f] != 0 && votos_candidatos[f] < menor){
          menor = votos_candidatos[f];
        }
        if(votos_candidatos[f] > maior){
          maior = votos_candidatos[f];
        }
      }

      // for(int i=0;i<freq_votos.size(); i++){
      //   cout << freq_votos[i] << endl;
      // }

      vector<int> maiores;
      vector<int> menores;

      for(int i=0; i<n_cand; i++){
        if(votos_candidatos[i] == maior){
          maiores.push_back(i+1);
        }
        if(votos_candidatos[i] == menor){
          menores.push_back(i+1);
        }
      }
      //
      // vector<int> idx_menores;
      // vector<int> idx_maiores;
      //
      // for(int i=0; i<votos.size(); i++){
      //   for(int m=0; m<maiores.size(); m++){
      //     if(votos[i][0] == maiores[m]){
      //       idx_maiores.push_back(i);
      //     }
      //   }
      //   for(int n=0; n<menores.size(); n++){
      //     if(votos[i][0] == menores[n]){
      //       idx_menores.push_back(i);
      //     }
      //   }
      // }

      int candidato;

      // cout <<"ELIMINADOS: "<< endl;
      // cout << eliminados.size() << endl;
      // cout << "MAIORES: " << endl;
      // cout << maiores.size() << endl;

      if(maiores.size() == n_of_votes){
        for(int i=0; i<maiores.size(); i++){
          candidato = maiores[i]-1;
          printf("%s\n", nomes_candidatos[candidato].c_str());
          fim = true;
        }
        break;
      }

      if((n_cand-eliminados.size()) == maiores.size()){
        for(int i=0; i<maiores.size(); i++){
          candidato = maiores[i]-1;
          printf("%s\n", nomes_candidatos[candidato].c_str());
          fim = true;
        }
        break;
      }

      vector<int> auxiliar;

      if(maior > metade_votos){
        candidato = maiores[0]-1;
        printf("%s\n", nomes_candidatos[candidato].c_str());
        fim = true;
      }
      if(menores.size() != 0){
        for(int i=0; i<menores.size(); i++){
          eliminados.push_back(menores[i]);
        }
      }
    }
    if(caso != n_casos-1){
      printf("\n");
    }
  }

  return(0);
}
