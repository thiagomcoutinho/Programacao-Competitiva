#include <stdio.h>
#include <cmath>

using namespace std;

// FUNCOES RETIRADAS DO LIVRO 'COMPETITIVE PROGRAMMING 3'

const double epsilon = 1e-7;


// POINTS
typedef struct int_point_2d{ 
	int x, y; // coordenadas

	int_point_2d(){
		x = 0; 
		y = 0;
	}

	int_point_2d(int x_, int y_) : x(x_), y(y_) {}

}point2i;

typedef struct double_point_2d{
	double x, y;

	double_point_2d(){
		x = 0.0; 
		y = 0.0;
	}

	double_point_2d(double x_, double y_) : x(x_), y(y_) {}

	bool operator < (double_point_2d other_point) const{
		if( abs( x - other_point.x ) > epsilon ){
			return x < other_point.x;
		}
		return y < other_point.y;
	}

	bool operator == (double_point_2d other_point) const{
		if( abs( x - other_point.x ) < epsilon ){
			if( abs( y - other_point.y ) < epsilon ){
				return true;
			}
		}
		return false;
	}
}point2d;

double euclidDist(point2d p1, point2d p2){
	double deltax = (p1.x - p2.x); 
	double deltay = (p1.y - p2.y);

	return( sqrt(deltax*deltax + deltay*deltay) );
}

point2d rotate(point2d p, double theta){
	// TO-DO
}

// LINES
typedef struct line{ // ax + by = c
	double a, b, c;
}line;

bool areParallel(line l1, line l2){
	bool coeff_a = abs(l1.a - l2.a) < epsilon;
	bool coeff_b = abs(l1.b - l1.b) < epsilon;

	return(coeff_a && coeff_b);
}

bool areSame(line l1, line l2){
	bool coeff_c = abs(l1.c - l2.c) < epsilon;

	return(areParallel(l1, l2) && coeff_c);
}

// VETORES
typedef struct vetor{

	double x, y;
	vetor(double _x, double _y) {}

}vetor;

vetor toVec(point2d a, point2d b){
	return( vetor(b.x-a.x, b.y-a.y) );
}

vetor scaleVec(vetor a, double scalar){
	return( vetor(a.x*scalar, a.y*scalar) );
}

point2d translate(point2d p, vetor v){
	return( point2d(p.x + v.x, p.y + v.y) );
}


// CIRCLE
typedef struct circle{
	point2d p;
	double radius;

	circle(){ 
		p = point2d(0, 0); 
		radius = 1; 
	}

	circle(point2d _p, double _radius) : p(_p), radius(_radius) {}

}circle;



int main(){

}