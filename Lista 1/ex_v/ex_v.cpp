#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

void calcula_posicao(int t){

  int nivel = floor(sqrt(t));
  int inicio_nivel = pow(nivel, 2);
  int walk = t - inicio_nivel;

  int x = nivel+1;
  int y = nivel+1;

  if(walk == 0){
    if(nivel % 2 != 0){
      x = 1;
      y--;
    }
    else{
      y = 1;
      x--;
    }
  }
  else{
    if(nivel % 2 != 0){
      if( walk <= (nivel+1) ){
        x -= (nivel+1) - walk;
      }
      else{
        y += (nivel+1) - walk;

      }
    }

    else{
      if(walk <= (nivel+1) ){
        y += walk - (nivel+1);
      }
      else{
        x += (nivel+1) - walk;
      }
    }
  }

  printf("%i %i\n", x, y);
}

int main(){

  int t;
  bool end = false;

  while(!end){
    cin >> t;
    if(t == 0){
      end = true;
    }
    else{
      calcula_posicao(t);
    }
  }

  return(0);
}
