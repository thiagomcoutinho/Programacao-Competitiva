#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>

typedef std::vector<int> casa;
typedef std::map<char, std::vector<casa> > pieces;

using namespace std;

void initialize_map(pieces &curr_map, int bw){
  vector<vector<int> > pos;
  if(bw = 0){
    curr_map.insert(make_pair('p', pos)); // peao
    curr_map.insert(make_pair('n', pos)); // cavalo
    curr_map.insert(make_pair('b', pos)); // bispo
    curr_map.insert(make_pair('r', pos)); // torre
    curr_map.insert(make_pair('q', pos)); // rainha
    curr_map.insert(make_pair('k', pos)); // rei
  }
  else{
    curr_map.insert(make_pair('P', pos)); // peao
    curr_map.insert(make_pair('N', pos)); // cavalo
    curr_map.insert(make_pair('B', pos)); // bispo
    curr_map.insert(make_pair('R', pos)); // torre
    curr_map.insert(make_pair('Q', pos)); // rainha
    curr_map.insert(make_pair('K', pos)); // rei
  }
}

bool check_peao(vector<casa> peoes, casa rei, vector<casa> board, int bw){

  casa peao;

  for(int i=0; i<peoes.size(); i++){

    peao = peoes[i];

    if( rei[0] == (peao[0]-1) || rei[0] == (peao[0]+1) ){

      if( abs(rei[0] - peao[0]) == 1 && abs(rei[1] - peao[1]) == 1){
        if(bw == 0){
          if(rei[0] > peao[0]){
            return(true);
          }
        }
        else{
          if(rei[0] < peao[0]){
            return(true);
          }
        }
      }

    }
  }

  return(false);
}

bool check_torre(vector<casa> torres, casa rei, vector<casa> board, int bw){

  casa torre;
  bool caminho_livre, possivel;
  int sentido, pos_torre, deslocamento;

  for(int i=0; i<torres.size(); i++){

    torre = torres[i];
    caminho_livre = true;
    possivel = false;

    if(rei[0] == torre[0]){ // horizontal
      possivel=true;
      pos_torre = torre[1];
      if(rei[1] > torre[1]){
        sentido = 1;
      }
      else{
        sentido = -1;
      }
      deslocamento = abs(torre[1] - rei[1])-1;
      for(int j=0; j<(deslocamento); j++){
        pos_torre += 1*sentido;
        if(board[rei[0]][pos_torre] == 1){
          caminho_livre = false;
          break;
        }
      }
    }

    if(rei[1] == torre[1]){ // vertical
      possivel=true;
      pos_torre = torre[0];
      if(rei[0] > torre[0]){
        sentido = 1;
      }
      else{
        sentido = -1;
      }
      deslocamento = abs(torre[0] - rei[0])-1;
      for(int j=0; j<(deslocamento); j++){
        pos_torre += 1*sentido;
        if(board[pos_torre][rei[1]] == 1){
          caminho_livre = false;
          break;
        }
      }
    }

    if(caminho_livre && possivel){
      return(true);
    }
  }

  return(false);
}

bool check_cavalo(vector<casa> cavalos, casa rei, vector<casa> board, int bw){

  casa cavalo;

  for(int i=0; i<cavalos.size(); i++){
    cavalo = cavalos[i];

    if( abs(rei[0] - cavalo[0]) == 2 ){
      if( abs(rei[1] - cavalo[1]) == 1){
        return(true);
      }
    }
    if( abs(rei[0] - cavalo[0]) == 1){
      if( abs(rei[1] - cavalo[1]) == 2 ){
        return(true);
      }
    }

  }
  return(false);
}

bool check_bispo(vector<casa> bispos, casa rei, vector<casa> board, int bw){

  casa bispo;
  int sentido_x, sentido_y, pos_x, pos_y, deslocamento;
  bool caminho_livre, possivel;

  for(int i=0; i<bispos.size(); i++){

    bispo = bispos[i];
    pos_x = bispo[0];
    pos_y = bispo[1];
    caminho_livre = true;
    possivel = false;

    if( abs(rei[0] - bispo[0]) == abs(rei[1] - bispo[1]) ){
      possivel = true;
      if(rei[0] > bispo[0]){
        sentido_x = 1;
      }
      else{
        sentido_x = -1;
      }
      if(rei[1] < bispo[1]){
        sentido_y = -1;
      }
      else{
        sentido_y = 1;
      }

      deslocamento = abs(rei[0] - bispo[0]);
      for(int j=0; j<(deslocamento-1); j++){
        pos_x += 1*sentido_x;
        pos_y += 1*sentido_y;
        if(board[pos_x][pos_y] == 1){
          caminho_livre=false;
          break;
        }
      }
    }

    if(caminho_livre && possivel){
      return(true);
    }

  }

  return(false);
}

bool check_rainha(vector<casa> rainha, casa rei, vector<casa> board, int bw){

  bool tipo_1 = check_torre(rainha, rei, board, bw);
  bool tipo_2 = check_bispo(rainha, rei, board, bw);
  bool retorno = tipo_1 || tipo_2;

  return(retorno);
}

void imprime_pecas(vector<casa> pecas){

  casa peca;

  for(int i=0; i<pecas.size(); i++){
    peca = pecas[i];
  }
}

int compute_check(pieces player, casa other_king, vector<casa> board, int bw){

  int p, n, b, r, q;
  char lp, ln, lb, lr, lq;
  if(bw == 0){
    lp = 'p';
    ln = 'n';
    lb = 'b';
    lr = 'r';
    lq = 'q';
  }
  else{
    lp = 'P';
    ln = 'N';
    lb = 'B';
    lr = 'R';
    lq = 'Q';
  }

  p = check_peao(player[lp], other_king, board, bw);
  n = check_cavalo(player[ln], other_king, board, bw);
  b = check_bispo(player[lb], other_king, board, bw);
  r = check_torre(player[lr], other_king, board, bw);
  q = check_rainha(player[lq], other_king, board, bw);

  return(p+n+b+r+q);
}

int main(){

  bool empty_board = false;
  int game=1;

  while(!empty_board){

    empty_board = true;

    vector<casa > board(8, casa(8));
    for(int i=0; i<8; i++){
      fill(board[i].begin(), board[i].end(), 0);
    }

    pieces white_pieces;
    pieces black_pieces;

    initialize_map(white_pieces, 1);
    initialize_map(black_pieces, 0);

    // LEITURA DO TABULEIRO
    char c;
    casa pos(2);
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        cin >> c;
        if( c != '.' ){
          empty_board = false;
          pos[0] = i;
          pos[1] = j;
          board[i][j]++;

          if( c >= 65 && c <= 90 ){ // BRANCO
            white_pieces[c].push_back(pos);
          }
          if( c >= 97 && c <= 122 ){ // PRETO
            black_pieces[c].push_back(pos);
          }
        }
      }
    }

    if(empty_board){
      break;
    }

    int check_black = 0;
    int check_white = 0;
    check_white = compute_check(black_pieces, white_pieces['K'][0], board, 0);
    check_black = compute_check(white_pieces, black_pieces['k'][0], board, 1);

    printf("Game #%i: ", game);
    if( check_black > 0 ){
      printf("black king is in check.\n");
    }
    else if( check_white > 0){
      printf("white king is in check.\n");
    }
    else{
      printf("no king is in check.\n");
    }

    game++;
  }

  return(0);
}
