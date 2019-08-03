#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

typedef std::vector<std::string> vs;

using namespace std;

int main(){

	string line;

	getline(cin, line);
	
	// ASCII 7 --> 55
	// ASCII 0 --> 48
	// ASCII + --> 43
	// ASCII * --> 42

	vs operands;
	string operand;
	string result;
	int a, b, c;

	// PROCESSA ANTES
	for(int i=0; i<(int)line.size(); i++){
		if(line[i] == 55){
			line[i] = 48;
		}
	}

	// SPLIT DA STRING
	istringstream iss1(line);
	while(getline(iss1, operand, ' ')){
		operands.push_back(operand);
	}

	// CONVERTE PARA NUMEROS
	a = stoi(operands.at(0));
	b = stoi(operands.at(2));

	// CONVERTE OPERADOR E FAZ OPERACAO
	if(operands[1][0] == 43){
		c = a + b;
	}
	else{
		c = a * b;
	}

	// CONVERTE RESULTADO FINAL P STRING
	result = to_string(c);
	// FILTRA RESULTADO FINAL
	for(int i=0; i<(int)result.size(); i++){
		if(result[i] == 55){
			result[i] = 48;
		}
	}
	// CONVERTE RESULTADO P INT
	c = stoi(result);

	cout << c << endl;
}