#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
  string line;

  int times = 0;
  char type;
  bool print = false;

  while(getline(cin, line)){
    for(int i=0; i < line.size(); i++){
      if(line[i] != '!'){
        if(line[i] >= 49 && line[i] <= 57){
          times = times + (line[i] - '0');
        }
        else{
          if(line[i] == 'b'){
            type = ' ';
          }
          else{
            type = line[i];
          }
          for(int j=0; j < times; j++){
            printf("%c", type);
          }
          times = 0;
        }
      }
      else{
        printf("\n");
      }
    }
    printf("\n");
  }

  return(0);
}
