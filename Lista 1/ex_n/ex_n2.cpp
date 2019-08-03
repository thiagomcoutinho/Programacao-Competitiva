#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(){

  // NUMERO DE CASOS A SEREM TESTADOS
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

    // LE 'MATRIZ' DE VOTOS
    vector<vector<int> > votos;
    string linha;
    string voto;
    stringstream ss;
    bool le_votos = true;
    int indx;

    vector<int> cand_eliminados;

    while(le_votos){
      getline(cin, linha);
      if(!linha.empty()){
        ss.str("");
        ss.clear();
        ss << linha;
        vector<int> i_linha(n_cand);
        indx = 0;
        while(getline(ss, voto, ' ')){
          i_linha[indx] = stoi(voto);
          indx++;
        }
        votos.push_back(i_linha);
      }
      else{
        break;
      }
    }

    //////

    bool ganhador = false;
    while(!ganhador){

      vector<int> freq_votos_cand(n_cand);
      fill(freq_votos_cand.begin(), freq_votos_cand.end(), 0);
      int aux1;
      vector<int> auxiliar1;
      for(int i=0; i<votos.size(); i++){
        if(votos[i].size() != 0){
          aux1 = votos[i][0];
          for(int j=0; j<cand_eliminados.size(); j++){
            if(aux1 == cand_eliminados[j]){
              auxiliar1 = votos[i];
              auxiliar1.erase(auxiliar1.begin());
              votos[i] = auxiliar1;
            }
          }
          if(votos[i].size() != 0){
            aux1 = votos[i][0]-1;
            freq_votos_cand[aux1]++;
          }
        }
      }


      int a=0;
      int id1;
      for(int i=0; i<votos.size(); i++){
        id1 = i-a;
        if(votos[id1].empty()){
          votos.erase(votos.begin()+id1);
          a++;
        }
      }

      for(int i=0;i<freq_votos_cand.size(); i++){
        cout << freq_votos_cand[i] << endl;
      }

      // MENOR E MAIOR NUMERO DE VOTOS
      int maior = -1;
      int menor = 10000;

      for(int i=0; i<freq_votos_cand.size(); i++){
        if(freq_votos_cand[i] > maior){
          maior = freq_votos_cand[i];
        }
        if(freq_votos_cand[i] != 0 && freq_votos_cand[i] < menor){
          menor = freq_votos_cand[i];
        }
      }

      int metade_votos = votos.size()/2;

      vector<int> idx_maiores;
      vector<int> idx_menores;
      // PEGA ID DOS CANDIDATOS COM MAIOR NUMEOR E MENOR NUMERO DE VOTOS
      for(int i=0; i<n_cand; i++){
        if(freq_votos_cand[i] == maior){
          idx_maiores.push_back(i+1);
        }
        if(freq_votos_cand[i] == menor){
          idx_menores.push_back(i+1);
        }
      }

      // PEGA INDICE DOS MENORES E MAIORES VOTOS
      vector<int> indices_dos_menores_votos;
      for(int k=0; k<idx_menores.size(); k++){
        for(int l=0; l<votos.size(); l++){
          if(votos[l][0] == idx_menores[k]){
            indices_dos_menores_votos.push_back(l);
          }
        }
      }

      // for(int i=0; i<indices_dos_menores_votos.size(); i++){
      //   cout << indices_dos_menores_votos[i] << endl;
      // }

      // REGRAS DA ELEICAO
      int indx_maior;
      int indx_menor;
      int j=0;
      int size_cand_elem = cand_eliminados.size();
      vector<int> auxiliar_votos;

      if(maior > metade_votos){
        indx_maior = idx_maiores[0]-1;
        printf("%s\n", nome_candidatos[indx_maior].c_str());
        break;
      }
      if( idx_maiores.size() == (n_cand-cand_eliminados.size()) ){
        for(int r=0; r<idx_maiores.size(); r++){
          indx_maior = idx_maiores[r]-1;
          printf("%s\n", nome_candidatos[indx_maior].c_str());
        }
        break;
      }
      if(idx_menores.size() != 0){
        for(int j=0; j<idx_menores.size(); j++){
          cand_eliminados.push_back(idx_menores[j]);
        }
        for(int q=0; q<indices_dos_menores_votos.size(); q++){
          indx_menor = indices_dos_menores_votos[q];
          auxiliar_votos = votos[indx_menor];
          auxiliar_votos.erase(auxiliar_votos.begin());
          votos[indx_menor] = auxiliar_votos;
        }
        int indice;
        for(int q=0; q<votos.size(); q++){
          indice = q - j;
          if(votos[indice].empty()){
            votos.erase(votos.begin()+indice);
            j++;
          }
        }

      }
    }
    printf("\n");

  }

  return(0);
}
