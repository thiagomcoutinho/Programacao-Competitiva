#include <stdio.h>
#include <iostream>
#include <cmath>

const double PI = 3.14159265359;

using namespace std;

int main(){

	double l, r;
	double resp, x, theta, phi, half_l, diag;

	cin >> l >> r;

	half_l = l/2;

	diag = sqrt(2)*l;

	if( r >= l/2 && r < diag/2 ){
		x = sqrt( (r*r) - (half_l*half_l) );
		theta = atan2(2*x, l);
		phi = ( (2*PI) - 8*theta ) / 4;
		resp = 2*( (x*l) + phi*r*r);
	}
	else if( r <= l/2 ){
		resp = r*r*PI;
	}
	else{
		resp = l*l;
	}

	printf("%.3f\n", resp);
}