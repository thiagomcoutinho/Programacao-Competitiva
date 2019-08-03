#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(){

  string line;
  bool first = false;

  while(getline(cin, line)){

    for(int i=0; i<line.size(); i++){
      if(int(line[i]) == 34){
        if(!first){
          first = true;
          printf("``");
        }
        else{
          first = false;
          printf("''");
        }
      }
      else{
        printf("%c", line[i]);
      }
    }
    printf("\n");
  }

  return(0);
}
