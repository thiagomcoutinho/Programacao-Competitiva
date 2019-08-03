#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

typedef struct vetor{
	int x, y;

	vetor(){x = 0; y = 0;}

	vetor(int x_, int y_) : x(x_), y(y_) {} // LENGTH OF VECTOR 

	vetor operator + (vetor q) const{  // SUM
		return( vetor(x + q.x, y + q.y) );
	}

	vetor operator - (vetor q) const{ // SUBTRACTION
		return( vetor(x - q.x, y - q.y) );
	}

	vetor operator * (int t) const { // SCALAR
		return( vetor(x*t, y*t) );
	}

	int operator * (vetor q) const { // DOT PRODUCT
		return(x*q.x + y*q.y);
	}

	int operator ^ (vetor q) const { // CROSS PRODUCT
		return(x*q.y - q.x*y);
	}

	bool operator == (vetor q) const{ // EQUALS
		return( (x-q.x == 0) && (y-q.y == 0) );
	}

	double len() const{
		return(hypot(x, y));
	}

	void print() const{
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

}vetor;

bool colinear(vetor p, vetor q){
	if( (p^q) == 0 ){
		return(true);
	}
	return(false);
}

bool CCW(vetor p, vetor q){
	if( (p^q) > 0 ){
		return(true);
	}
	return(false);
}

bool CW(vetor p, vetor q){
	if( (p^q) < 0 ){
		return(true);
	}
	return(false);
}

typedef struct ponto{
	int x, y;

	ponto(){x = 0; y = 0;} // CONSTRUTOR PADRAO

	ponto(int x_, int y_) : x(x_), y(y_) {}

	vetor operator - (ponto p2) const{
		return( vetor(x - p2.x, y - p2.y) );
	}

	bool operator == (ponto q) const{
		return( (x-q.x == 0) && (y-q.y == 0) );
	}

	void print () const{
		std::cout << x << " " << y << std::endl;
	}
	
}ponto;

typedef struct line{
	ponto p, q;
	int a, b, c;
	vetor n;

	line(){a = 0; b = 0; c = 0; n = vetor(0, 0);}

	line(ponto p_, ponto q_) : p(p_), q(q_){
		a = p.y-q.y;
		b = q.x - p.x;
		c = p.x*q.y - q.x*p.y;
		n = vetor(a, b);
	}

}line;

bool intersect(line l1, line l2, bool isSegLine){

	// USING CRAMER'S RULE
	int d = l1.n^l2.n;
	int d1, d2;
	long double x, y;

	ponto interval_x_square( min(l2.p.x, l2.q.x), max(l2.p.x, l2.q.x) ); // l2 E O SEGMENTO DO QUADRADO
	ponto interval_y_square( min(l2.p.y, l2.q.y), max(l2.p.y, l2.q.y) ); 

	ponto interval_x_l( min(l1.p.x, l1.q.x), max(l1.p.x, l1.q.x) ); // l2 E O SEGMENTO DO QUADRADO
	ponto interval_y_l( min(l1.p.y, l1.q.y), max(l1.p.y, l1.q.y) ); 

	if(d != 0){
		d1 = vetor(-l1.c, l1.b)^vetor(-l2.c, l2.b);
		d2 = vetor(l1.a, -l1.c)^vetor(l2.a, -l2.c);

		x = (long double)d1/(long double)d;
		y = (long double)d2/(long double)d;

		if(!isSegLine){
			return(true);
		}

		bool test_x_s = ( (x >= (long double)interval_x_square.x) && (x <= (long double)interval_x_square.y) );
		bool test_y_s = ( (y >= (long double)interval_y_square.x) && (y <= (long double)interval_y_square.y) );

		bool test_x_l = ( (x >= (long double)interval_x_l.x) && (x <= (long double)interval_x_l.y) );
		bool test_y_l = ( (y >= (long double)interval_y_l.x) && (y <= (long double)interval_y_l.y) );
		

		if(test_x_s && test_y_s && test_x_l && test_y_l){
			return(true);
		}
	}
	
	return(false);
}

typedef std::vector<pontos> Vpontos;

struct comparator{
	ponto O;

	comparator(ponto O_) : O(O_) {}

	bool operator () (ponto a, ponto b){
		return ( (vetor(a-O)^vetor(b-O)) >= 0 );
	}
};

Vpontos convexHull(Vpontos pontos){

	// GRAHAM'S METHOD O(nLogn)

	// FIND LEFTMOST POINT AND IF THE X COORDINATES MATCHES, FIND THE LOWEST
	int index = 0;
	int x = pontos[0].x;
	int y = pontos[0].y;

	for(int i=1; i<(int)pontos.size(); i++){
		if( pontos[i].x < x ){
			index = i;
			x = pontos[i].x;
			y = pontos[i].y;
		}
		else if(pontos[i].x == x){
			if(pontos[i].y < y){
				index = i;
				x = pontos[i].x;
				y = pontos[i].y;
			}
		}
	}
	ponto O(x, y);
	pontos.erase(pontos.begin() + index);

	// SORT THE REST OF POINTS BASED ON CLOCKWISE LOCATION AFTER point O;
	sort(pontos.begin(), pontos.end(), comparator(O));
	pontos.insert(pontos.begin(), O);


	// CONSTRUCT THE CONVEX HULL
	Vpontos cHull;
	cHull.push_back(pontos[0]);
	cHull.push_back(pontos[1]);

	int size;

	vetor v1, v2;

	for(int i=2; i<(int)pontos.size(); i++){
		size = (int)cHull.size()-1;

		v1 = vetor(cHull[size] - cHull[size-1]);
		v2 = vetor(pontos[i] - cHull[size]);
		if(CCW(v1, v2)){
			cHull.push_back(pontos[i]);
		}
		else{
			cHull.pop_back();
			i--;
		}

	}

	return(cHull);
}

using namespace std;

int main(){

	vetor i(1, 0);
	vetor j(0, 1);

	cout << "CROSS PRODUCT" << endl;
	int k = i^j; // CROSS PRODUCT
	int minus_k = j^i;
	cout << k << endl;
	cout << minus_k << endl;

	cout << "LENGTH" << endl;
	cout << i.len() << endl;

	cout << "SUM" << endl;
	vetor sum = i + j; // SUM
	cout << sum.x << " " << sum.y << endl;

	cout << "SUBTRACTION" << endl;
	vetor sub = i - j; // SUBTRACTION
	cout << sub.x << " " << sub.y << endl;

	cout << "DOT PRODUCT" << endl;
	int dot = i*j; // DOT PRODUCT
	cout << dot << endl;

	cout << "SCALAR" << endl;
	vetor i_scaled = i*10; // SCALAR
	cout << i_scaled.x << " " << i_scaled.y << endl;

	cout << "COLINEAR" << endl;
	cout << colinear(i, j) << endl;

	cout << "CCW" << endl;
	cout << CCW(i, j) << endl;

	cout << "CW" << endl;
	cout << CW(i, j) << endl;

	cout << "PONTO" << endl;
	ponto pi(1,0);
	ponto p0(0,0);
	vetor ip = pi - p0;
	cout << ip.x << " " << ip.y << endl;

	pi.print();

}