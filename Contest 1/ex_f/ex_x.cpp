#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main(){

  int t, n;
  cin >> t >> n;
  while(t != 0 && n != 0){

    int soma=0;
    int aux;
    vector<int> times(t);
    string nome_time;

    bool empate = true;

    for(int i=0; i<t; i++){
      cin >> nome_time >> times[i];
      soma += times[i];
    }

    if(soma == 3*n){ // Só vitoria
      printf("0\n");
    }
    else{
      printf("%i\n", (3*n - (soma))/2);
    }

    cin >> t >> n;
  }
}
