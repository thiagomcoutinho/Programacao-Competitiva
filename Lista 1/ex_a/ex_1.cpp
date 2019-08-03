#include <stdio.h>

int cycle_length(int n){

  int count = 1;

  while(n != 1){
    if(n % 2 != 0){
      n = 3*n + 1;
    }
    else{
      n = n/2;
    }
    count++;
  }

  return(count);
}

int main(){

  int i, j;

  while(fscanf(stdin, "%d %d", &i, &j) != EOF){

    printf("%d %d ", i, j);
    int k;
    if( i > j ){
      k = j;
      j = i;
      i = k;
    }

    int maior = 0;

    for(int k = i; k <= j; k++){
      int actual_cycle = cycle_length(k);
      if( actual_cycle > maior ){
        maior = actual_cycle;
      }
    }

    printf("%d\n", maior);

  }

  return(0);
}
