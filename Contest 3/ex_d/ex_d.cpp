#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

int main(){

	double p, j, m, x;
	double a, b, i;

	cin >> m >> p >> j >> x;

	p = p/100;
	j = j/100;

	if( m*j <= x ){
		printf("0\n");
		return(0);
	}

	a = log(x) - log(m*j);
	b = log((1-p));

	i = a/b;

	if(i >= 0){
		if(p > 1){
		printf("%.f\n", ceil(i));
		}
		else{
			printf("%.f\n", floor(i));
		}
	}
	else{
		printf("0\n");
	}
	
}