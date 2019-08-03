#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

double euclidean_dist(int x1, int y1, int x2, int y2){

	double dist;
	double deltax = x1-x2;
	double deltay = y1-y2;

	dist = sqrt(deltax*deltax + deltay*deltay);

	return dist;
}

int main(){

	int r1, x1, y1, r2, x2, y2;

	while(cin >> r1 >> x1 >> y1 >> r2 >> x2 >> y2){

		if( r1 >= euclidean_dist(x1, y1, x2, y2) + r2 ){
			printf("RICO\n");
		}
		else{
			printf("MORTO\n");
		}

	}
}