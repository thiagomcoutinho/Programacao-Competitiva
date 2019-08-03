#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> isSlump(string word){

  vector<int> retorno(2);

  if(word.at(0) == 'D' || word.at(0) == 'E'){
    if(word.size() > 1){
      if(word.at(1) == 'F'){
        int pos = 2;
        while(word.at(pos) == 'F'){
          pos++;
          if(pos == word.size()){
            retorno[0] = 0;
            retorno[1] = -1;
            return(retorno);
          }
        }
        if(word.at(pos) == 'G'){
          retorno[0] = 1;
          retorno[1] = pos+1;
          return(retorno);
        }
        vector<int> slump = isSlump(word.substr(pos));
        if(slump[0] == 1){
          retorno[0] = 1;
          retorno[1] = pos + slump[1];
          return(retorno);
        }
      }
    }
  }

  retorno[0] = 0;
  retorno[1] = -1;
  return(retorno);
}

vector<int> isSlimp(string word){

  vector<int> retorno(2);

  int pos;

  if(word.at(0) == 'A'){
    if(word.size() > 1){
      if(word.at(1) == 'H'){
        retorno[0] = 1;
        retorno[1] = 2;
        return(retorno);
      }
      else{
        if( word.at(1) == 'B' ){
          pos = 2;
          if(word.size()>2){
            vector<int> slimp = isSlimp(word.substr(pos));
            if( slimp[0] == 1 ){
              if( (slimp[1] + pos) < word.size() ){
                if( word.at(slimp[1] + pos) == 'C' ){
                  retorno[0] = 1;
                  retorno[1] = slimp[1] + (pos+1);
                  return(retorno);
                }
              }
            }
          }
        }
        else{
          pos = 1;
          vector<int> slump = isSlump(word.substr(pos));
          if( slump[0] == 1 ){
            if( (slump[1] + pos) < word.size() ){
              if( word.at(slump[1] + pos) == 'C'){
                retorno[0] = 1;
                retorno[1] = slump[1] + (pos+1);
                return(retorno);
              }
            }
          }
        }
      }
    }
  }

  retorno[0] = 0;
  retorno[1] = -1;
  return(retorno);
}

bool isSlurpy(string word){

  vector<int> slimp = isSlimp(word);
  if(slimp[0] == 1){
    if(slimp[1] < word.size()){
      vector<int> slump = isSlump(word.substr(slimp[1]));
      if(slump[0] == 1 && (word.size() == (slimp[1] + slump[1])) ){
        return(true);
      }
    }
  }

  return(false);
}

int main(){

  int n;
  char aux[60];

  fscanf(stdin, "%d", &n);

  stringstream ss;
  string s;
  printf("SLURPYS OUTPUT\n");
  for(int i=0; i<n; i++){
    fscanf(stdin, "%s", aux);
    ss << aux;
    ss >> s;
    ss.str("");
    ss.clear();

    bool slurpy = isSlurpy(s);
    if(slurpy){
      printf("YES\n");
    }
    else{
      printf("NO\n");
    }

  }
  printf("END OF OUTPUT\n");

  return(0);
}
