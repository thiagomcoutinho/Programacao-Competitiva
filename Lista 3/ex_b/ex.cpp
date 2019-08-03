#include <stdio.h>
#include <iostream>
#include <cmath>

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

typedef struct segLine{
	ponto p, q;
	int a, b, c;
	vetor n;

	segLine(){a = 0; b = 0; c = 0; n = vetor(0, 0);}

	segLine(ponto p_, ponto q_) : p(p_), q(q_){
		a = p.y - q.y;
		b = q.x - p.x;
		c = p.x*q.y - q.x*p.y;
		n = vetor(a, b);
	}

}segLine;

using namespace std;

bool intersect(segLine l1, segLine l2){

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



int main(){

	// THE SIDES COUNT STARTS AT THE TOP SIDE AND GOES CLOCKWISE IN THE RECTANGLE
	// THE VERTICES OF THE RECTANGLE STARTS COUNTING AT THE UPPER LEFT AND GOES CLOCKWISE
	int n;
	int xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
	bool l1s1, l1s2, l1s3, l1s4;

	ponto lineStart, lineEnd, p1, p2, p3, p4;
	segLine line1, side1, side2, side3, side4;

	cin >> n;

	for(int i=0; i<n; i++){

		cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;

		ponto range_x( min(xleft, xright), max(xleft, xright));
		ponto range_y( min(ybottom, ytop), max(ybottom, ytop));

		xleft = range_x.x;
		xright = range_x.y;
		ybottom = range_y.x;
		ytop = range_y.y;

		bool x_inside1 = ( (xstart >= xleft) && (xstart <= xright) );
		bool y_inside1 = ( (ystart >= ybottom) && (ystart <= ytop) );
		
		bool x_inside2 = ( (xend >= xleft) && (xend <= xright) );
		bool y_inside2 = ( (yend >= ybottom) && (yend <= ytop) );

		if( (x_inside1 && y_inside1) || (y_inside2 && x_inside2) ){
			printf("T\n");
			continue;
		}


		lineStart = ponto(xstart, ystart);
		lineEnd = ponto(xend, yend);
		line1 = segLine(lineStart, lineEnd);

		p1 = ponto(xleft, ytop);
		p2 = ponto(xright, ytop);
		p3 = ponto(xright, ybottom);
		p4 = ponto(xleft, ybottom);
		side1 = segLine(p1, p2);
		side2 = segLine(p2, p3);
		side3 = segLine(p3, p4);
		side4 = segLine(p4, p1);

		l1s1 = intersect(line1, side1);
		l1s2 = intersect(line1, side2);
		l1s3 = intersect(line1, side3);
		l1s4 = intersect(line1, side4);

		if( l1s1 || l1s2 || l1s3 || l1s4 ){
			printf("T\n");
		}
		else{
			printf("F\n");
		}
	}

}
