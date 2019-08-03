#include <stdio.h>
#include <vector>
#include <iostream>

typedef std::vector<int> pos;

using namespace std;

void imprime_tabuleiro(vector<vector<int> > maze, int b, int w){
  for (int i=0; i<=b; i++){
    for(int j=0; j<=w; j++){
      if(maze[i][j] == -1){
        cout << maze[i][j];
      }
      else{

      }
      cout << " " << maze[i][j];
    }
    cout << endl;
  }
}

bool direita_vazia(vector<vector<int> > maze, pos robo, pos passo, int axis, int sentido, vector<int> limits){

  bool vira_a_direita = false;

  // VERIFICA SE TEM ALGUMA COISA A DIREITA
  if(axis == 0){ // ANDANDO NA VERTICAL
    if(sentido > 0){
      if(robo[1] > 0){
        if(maze[robo[0]][robo[1]-1] != -1){
          vira_a_direita = true;
        }
      }
    }
    else{
      if(robo[1] < limits[1]){
        if(maze[robo[0]][robo[1]+1] != -1){
          vira_a_direita = true;
        }
      }
    }
  }
  else{ // ANDANDO NA HORIZONTAL
    if(sentido > 0){
      if( robo[0] < limits[0] ){
        if(maze[robo[0]+1][robo[1]] != -1){
          vira_a_direita = true;
        }
      }
    }
    else{
      if( robo[0] > 0 ){
        if(maze[robo[0]-1][robo[1]] != -1){
          vira_a_direita = true;
        }
      }
    }
  }

  return(vira_a_direita);
}

vector<vector<int> > walk(vector<vector<int> > maze, vector<int> limits){

  vector<vector<int> > dir_passo(4, vector<int>(2));
  dir_passo[0][0] = 0; // NORTE(0)
  dir_passo[0][1] = -1;
  dir_passo[1][0] = 1; // EAST(1)
  dir_passo[1][1] = 1;
  dir_passo[2][0] = 0; // SOUTH(2)
  dir_passo[2][1] = 1;
  dir_passo[3][0] = 1; // WEST(3)
  dir_passo[3][1] = -1;

  vector<int> gira_esq(4); // ROTACAO A ESQUERDA
  gira_esq[0] = 3;
  gira_esq[1] = 0;
  gira_esq[2] = 1;
  gira_esq[3] = 2;

  vector<int> gira_dir(4); // ROTACAO A DIREITA
  gira_dir[0] = 1;
  gira_dir[1] = 2;
  gira_dir[2] = 3;
  gira_dir[3] = 0;

  int orient = 1; // COMECA INDO PARA EAST
  vector<int> passo(2); // AUXILIAR QUE CONTEM O PASSO DO ROBO

  maze[limits[0]][0] = -3; // FLAG DA POSICAO DE PARTIDA
  // INICIALIZA ROBO
  pos robo(2);
  robo[0] = limits[0];
  robo[1] = 0;

  int axis, sentido, pos_atual;
  bool vira_a_direita = false;
  bool nao_consegue_andar = false;
  bool logico;
  bool first = true;

  while(maze[robo[0]][robo[1]] != -2){

    while(!nao_consegue_andar){

      if(maze[robo[0]][robo[1]] == -2){
        break;
      }

      // cout << "CONSEGUE ANDAR" << endl;

      vira_a_direita = false;
      passo = dir_passo[orient];
      // cout << "PASSO: " << passo[0] << " " << passo[1] << endl;
      axis = passo[0];
      sentido = passo[1];

      vira_a_direita = direita_vazia(maze, robo, passo, axis, sentido, limits);
      // cout << "VIRA A DIREITA: " << vira_a_direita << endl;

      if(vira_a_direita){
        orient = gira_dir[orient];
        passo = dir_passo[orient];
        axis = passo[0];
        sentido = passo[1];
      }

      pos_atual = robo[axis];
      pos_atual += sentido;

      // cout << "ROBO: " << robo[0] <<" " << robo[1] << endl;
      // cout << "POS ATUAL: " << pos_atual << endl;

      if(!vira_a_direita){
        logico = pos_atual < 0 || pos_atual > limits[axis];
        if(axis == 0){
          if(logico || maze[pos_atual][robo[1]] == -1){
            nao_consegue_andar = true;
            break;
          }
        }
        else{
          if( logico || maze[robo[0]][pos_atual] == -1){
            nao_consegue_andar = true;
            break;
          }
        }
      }
      robo[axis] += sentido;
      maze[robo[0]][robo[1]]++;
      first = false;
      // cout << "ANDOU!!"<< endl << endl;
      // imprime_tabuleiro(maze, limits[0], limits[1]);
    }

    while(nao_consegue_andar){

      // cout << "NAO CONSEGUE ANDAR!" << endl;

      if(maze[robo[0]][robo[1]] == -2){
        break;
      }

      orient = gira_esq[orient]; // GIRA P ESQUERDA
      passo = dir_passo[orient]; // PEGA PASSO
      axis = passo[0]; // PEGA COORDENADA
      sentido = passo[1]; // PEGA SENTIDO DO PASSO

      pos_atual = robo[axis]; // POSICAO ATUAL
      pos_atual += sentido; // NOVA POSICAO

      // cout << "ROBO: " << robo[0] << " " << robo[1] << endl;
      // cout << "ORIENTACAO: " << orient << endl;
      // cout << "PASSO:" << passo[0] << " " << passo[1] << endl;
      // cout << "SENTIDO: " << sentido << endl;
      // cout << "POS ATUAL: " << pos_atual << endl;

      // VERIFICA SE NOVA POSICAO É VALIDA
      logico = pos_atual >= 0 && pos_atual <= limits[axis];
      // cout << "LOGICO " << logico << endl;
      // cout << "LIMITS: " << limits[0] << " " << limits[1];
      if(axis == 0){
        if( logico ){
          // cout << "IMPRIMINDO MAZE!" << endl;
          // cout << maze[pos_atual][robo[1]] << endl;
          if( maze[pos_atual][robo[1]] != -1 ){
            nao_consegue_andar = false;
            // cout << "VOLTOU A ANDAR!" << endl << endl;
            // imprime_tabuleiro(maze, limits[0], limits[1]);
            break;
          }
        }
      }
      else{
        if( logico ){
          // cout << "IMPRIMINDO MAZE!" << endl;
          // cout << maze[robo[0]][pos_atual] << endl;
          if(maze[robo[0]][pos_atual] != -1 ){
            nao_consegue_andar = false;
            // cout << "VOLTOU A ANDAR!" << endl << endl;
            // imprime_tabuleiro(maze, limits[0], limits[1]);
            break;
          }
        }
      }

    }

  }

  return(maze);
}

void imprime(vector<vector<int> > maze, int b, int w){
  // Nenhum, uma, duas, tres, quatro.
  vector<int>  freq(5);
  for(int i=0; i<b; i++){
    for(int j=0; j<w; j++){
      if(maze[i][j] == 1){
        freq[1]++;
      }
      if(maze[i][j] == 2){
        freq[2]++;
      }
      if(maze[i][j] == 3){
        freq[3]++;
      }
      if(maze[i][j] == 4){
        freq[4]++;
      }
      if(maze[i][j] == 0){
        freq[0]++;
      }
    }
  }
  freq[1]++;

  printf("%3i%3i%3i%3i%3i\n", freq[0], freq[1], freq[2], freq[3], freq[4]);

}

int main(){

  int b, w;
  cin >> b >> w;
  while(b != 0 && w != 0){

    vector<vector<int> > maze(b, vector<int>(w));
    char casa;
    int i_casa;

    for(int i=0; i<b; i++){
      for(int j=0; j<w; j++){
        cin >> casa;
        i_casa = casa - '0';
        if(i_casa == 1){
          maze[i][j] = -1;
        }
        else{
          maze[i][j] = 0;
        }
      }
    }

    vector<int> limits(2);
    limits[0] = b-1;
    limits[1] = w-1;

    vector<vector<int> > path = walk(maze, limits);
    imprime(path, b, w);

    cin >> b >> w;
  }

  return(0);
}
