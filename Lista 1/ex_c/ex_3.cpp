#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> update_position(vector<int> position, vector<int> limits, vector<vector<int> > &x_bound, vector<vector<int> > &y_bound, int curr_orient, bool &lost){

  int x = position[0];
  int y = position[1];

  int limite_x = limits[0];
  int limite_y = limits[1];

  // cout << "##PASSO: " << endl;
  //
  // cout << "POSICAO: " << position[0] << ", " << position[1] <<endl;
  // cout << "ORIENTACAO: " << curr_orient << endl;

  switch(curr_orient){
    case(0):
      if(y == limite_y){
        if(y_bound[1][x] == 0){
          lost=true;
        }
        if( x == 0 ){
          x_bound[0][y]--;
        }
        if( x == limite_x ){
          x_bound[1][y]--;
        }
        y_bound[1][x]--;
      }
      else{
        position[1]++;
      }
      break;
    case(1):
      if(x == limite_x){
        if(x_bound[1][y] == 0){
          lost=true;
        }
        if( y == 0 ){
          y_bound[0][x]--;
        }
        if( y == limite_y ){
          y_bound[1][x]--;
        }
        x_bound[1][y]--;
      }
      else{
        position[0]++;
      }
      break;
    case(2):
      if(y == 0){
        if(y_bound[0][x] == 0){
          lost=true;
        }
        if( x == 0){
          x_bound[0][y]--;
        }
        if( x == limite_x ){
          x_bound[1][y]--;
        }
        y_bound[0][x]--;
      }
      else{
        position[1]--;
      }
      break;
    default:
      if(x == 0){
        if(x_bound[0][y] == 0){
          lost=true;
        }
        if(y == 0){
          y_bound[0][x]--;
        }
        if(y == limite_y){
          y_bound[1][x]--;
        }
        x_bound[0][y]--;
      }
      else{
        position[0]--;
      }
  }

  // cout << "POSICAO: " << position[0] << ", " << position[1] <<endl;
  // cout << "ORIENTACAO: " << curr_orient << endl;

  return(position);
}

int main(){

  vector<vector<int> > vector_orientation(4, vector<int> (2));
  vector_orientation[0][0] = 1;
  vector_orientation[0][1] = 3;
  vector_orientation[1][0] = 2;
  vector_orientation[1][1] = 0;
  vector_orientation[2][0] = 3;
  vector_orientation[2][1] = 1;
  vector_orientation[3][0] = 0;
  vector_orientation[3][1] = 2;


  int x_limit, y_limit, x_init_pos, y_init_pos, orient;
  vector<int> position(2);
  vector<int> limits(2);
  char init_orient;

  // START
  cin >> x_limit >> y_limit;
  limits[0] = x_limit;
  limits[1] = y_limit;

  vector<vector<int> > x_bound(2, vector<int>(x_limit+1));
  vector<vector<int> > y_bound(2, vector<int>(y_limit+1));

  fill(x_bound[0].begin(), x_bound[0].end(), 0);
  fill(x_bound[1].begin(), x_bound[1].end(), 0);
  fill(y_bound[0].begin(), y_bound[0].end(), 0);
  fill(y_bound[1].begin(), y_bound[1].end(), 0);

  while(cin >> x_init_pos >> y_init_pos >> init_orient){
    switch(init_orient){
      case('N'):
        orient = 0;
        break;
      case('E'):
        orient = 1;
        break;
      case('S'):
        orient = 2;
        break;
      default:
        orient = 3;
    }

    position[0] = x_init_pos;
    position[1] = y_init_pos;

    // SEGUNDA LINHA
    bool lost = false;

    cin.ignore(256, '\n');

    string line_of_command;
    char command;
    getline(cin, line_of_command);
    // cout << "LINHA: " << endl;
    // cout << line_of_command << endl;
    for(int k=0; k<line_of_command.size(); k++){
      command = line_of_command[k];
      // cout << command << endl;
      switch(command){
        case('R'):
          if(!lost){
            orient = vector_orientation[orient][0];
          }
          break;
        case('L'):
          if(!lost){
            orient = vector_orientation[orient][1];
          }
          break;
        case('F'):
          if(!lost){
            position = update_position(position, limits, x_bound, y_bound, orient, lost);
          }
          break;
        default:
          break;
      }
    }

    char c_orient;

    switch(orient){
      case 0:
        c_orient = 'N';
        break;
      case 1:
        c_orient = 'E';
        break;
      case 2:
        c_orient = 'S';
        break;
      default:
        c_orient = 'W';
    }

    cout << position[0] << " " <<  position[1] << " " << c_orient;
    if(lost){
      cout << " LOST" << endl;
    }
    else{
      cout << endl;
    }
  }


  return(0);
}
