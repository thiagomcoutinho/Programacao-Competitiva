#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int mdc_euclidean(int s1, int s2){
  if(s1 == 0){
    return(s2);
  }
  return(mdc_euclidean(s2%s1, s1));
}
int main(){

  int n;

  fscanf(stdin, "%i", &n);
  int s1, s2;
  bool first = true;
  int pair;
  char aux[30];
  int result;

  for(int i=0; i<n; i++){
    fscanf(stdin, "%s", aux);
    s1 = stoi(aux, nullptr, 2);
    fscanf(stdin, "%s", aux);
    s2 = stoi(aux, nullptr, 2);
    if(s1 > s2){
      result = mdc_euclidean(s1,s2);
    }
    else{
      result = mdc_euclidean(s2, s1);
    }
    if(result != 1){
      printf("Pair #%i: All you need is love!\n", i+1);
    }
    else{
      printf("Pair #%i: Love is not all you need!\n", i+1);
    }
  }

  return(0);
}
