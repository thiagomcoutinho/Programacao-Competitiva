#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string process_word(string word){

  bool vogal = false;
  string ay("ay");
  if(word.at(0) == 'a' || word.at(0) == 'A' || word.at(0) == 'e' || word.at(0) == 'E'
  || word.at(0) == 'i' || word.at(0) == 'I' || word.at(0) == 'o' || word.at(0) == 'O'
  || word.at(0) == 'u' || word.at(0) == 'U'){
    vogal = true;
  }

  if(vogal){
    word.append(ay);
  }
  else{
    char aux = word.at(0);
    word.erase(word.begin());
    word = word + aux;
    word.append(ay);
  }

  return(word);
}

int main(){

  string line;
  string processed;
  string word;

  while(getline(cin, line)){

    bool palavra = false;

    for(int i=0; i<line.size(); i++){
      bool lowerCase = line.at(i) <= 90 && line.at(i) >= 65;
      bool upperCase = line.at(i) <= 122 && line.at(i) >= 97;

      if(lowerCase || upperCase){
        if(!palavra){
          palavra = true;
        }
        word += line.at(i);
      }
      else{
        if(palavra){
          palavra = false;
          processed.append(process_word(word));
          printf("%s", processed.c_str());
          word.clear();
          processed.clear();
        }
      }

      if(!palavra){
        printf("%c", line.at(i));
      }

    }
    printf("\n");
  }

  return(0);
}
