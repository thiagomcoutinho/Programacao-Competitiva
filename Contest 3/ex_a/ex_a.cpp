#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
	int d, i, x, f;

	cin >> d >> i >> x >> f;

	if( d % 2 != 0 ){ // IMPAR
		if( f % 2 != 0 ){ 
			printf("%i\n", i+x);
		}
		else{
			printf("%i\n", i);
		}
	}
	else{ // PAR
		if( f % 2 != 0 ){
			printf("%i\n", i-x);
		}
		else{
			printf("%i\n", i);
		}
	}

}