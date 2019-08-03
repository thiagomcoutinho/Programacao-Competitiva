#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> folha;

using namespace std;

vector<folha> preenche_folhas(int n){

  folha auxiliar(4);
  int pagina = 1;
  vector<folha> uma_folha(1);

  if(n <= 4){

    fill(auxiliar.begin(), auxiliar.end(), 0);

    for(int i=0; i<n; i++){
      auxiliar[i] = pagina;
      pagina++;
    }
    uma_folha[0] = auxiliar;
    return(uma_folha);
  }

  int n_folhas;
  if( n % 4 == 0){
    n_folhas = n/4;
  }
  else{
    n_folhas = (n/4) + 1;
  }
  vector<folha> folhas(n_folhas, folha(4));
  for(int j=0; j<n_folhas; j++){
    fill(folhas[j].begin(), folhas[j].end(), 0);
  }

  for(int i=0; i<n_folhas; i++){
    auxiliar[0] = pagina;
    pagina++;
    auxiliar[1] = pagina;
    folhas[i] = auxiliar;
    pagina++;
  }
  if(pagina < n){
    for(int i=(n_folhas-1); i>=0; i--){
      if(pagina != (n+1)){
        auxiliar = folhas[i];
        auxiliar[2] = pagina;
        folhas[i] = auxiliar;
      }
      else{
        break;
      }
      pagina++;
      if(pagina != (n+1)){
        auxiliar = folhas[i];
        auxiliar[3] = pagina;
        folhas[i] = auxiliar;
      }
      else{
        break;
      }
      pagina++;
    }
  }

  return(folhas);
}

void imprime_folhas(int n, vector<folha> folhas_preenchidas){

  printf("Printing order for %i pages:\n", n);
  int qtd_folhas = folhas_preenchidas.size();



  for(int i=0; i<qtd_folhas; i++){
    string s1, s2, s3, s4;

    if(folhas_preenchidas[i][0] == 0){
      s1 = "Blank";
    }
    else{
      s1 = to_string(folhas_preenchidas[i][0]);
    }
    if(folhas_preenchidas[i][1] == 0){
      s2 = "Blank";
    }
    else{
      s2 = to_string(folhas_preenchidas[i][1]);
    }
    if(folhas_preenchidas[i][2] == 0){
      s3 = "Blank";
    }
    else{
      s3 = to_string(folhas_preenchidas[i][2]);
    }
    if(folhas_preenchidas[i][3] == 0){
      s4 = "Blank";
    }
    else{
      s4 = to_string(folhas_preenchidas[i][3]);
    }

    for(int j=0; j<2; j++){
      if(j == 0){
        printf("Sheet %i, front: %s, %s\n", i+1, s4.c_str(), s1.c_str());
      }
      if(j == 1){
        if(folhas_preenchidas[i][1] != 0 || folhas_preenchidas[i][2] != 0){
          printf("Sheet %i, back : %s, %s\n", i+1, s2.c_str(), s3.c_str());
        }
      }
    }
  }
}

int main(){

  int n;

  cin >> n;
  while(n != 0){

    vector<folha> folhas_preenchidas = preenche_folhas(n);
    imprime_folhas(n, folhas_preenchidas);

    cin >> n;
  }

  return(0);
}
