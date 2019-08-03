    #include <stdio.h>
    #include <iostream>
    #include <cmath>
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
     
    }vetor;
     
    typedef struct ponto{
    	int x, y;
     
    	ponto(){x = 0; y = 0;} // CONSTRUTOR PADRAO
     
    	ponto(int x_, int y_) : x(x_), y(y_) {}
     
    	vetor operator - (ponto p2) const{
    		return( vetor(x - p2.x, y - p2.y) );
    	}
     
    	void print () const{
    		std::cout << x << " " << y << std::endl;
    	}
     
    	bool operator == (ponto q) const{
    		return( (x-q.x == 0) && (y-q.y == 0) );
    	}
    	
    }ponto;
     
    typedef std::vector<int> vi;
    typedef std::vector<ponto> Vpontos;
     
    using namespace std;
     
    bool colinear(vetor p, vetor q){
    	if( (p^q) == 0 ){
    		return(true);
    	}
    	return(false);
    }
     
    int main(){
     
    	int maximo = 0;
    	int n, m ,x, y, contador = 0, equals = 0;
    	ponto p0, p1, px;
    	vetor v1, vx;
     
    	cin >> m;
     
    	for(int j = 0; j<m; j++){
    		cin >> n;
     
    		maximo = 0;
    		contador = 0;
    		equals = 0;
     
    		Vpontos pontos(n);
    		vi lpv(n); // Lista de pontos visitados
     
    		for(int i=0; i < n; i++){
    			cin >> x >> y;
    			pontos[i] = ponto(x, y);
    		}
     
    		for(int i=0; i<n; i++){
     
    			p0 = pontos[i];
    			lpv.assign(n, 0);
    			lpv[i]++;
    			contador = 0;
    			equals = 0;
    			for(int j=i+1; j<n; j++){
    				if(lpv[j] == 0 && !(p0 == pontos[j]) ){
    					lpv[j]++;
    					p1 = pontos[j];
    					v1 = p1 - p0;
    					contador = 2; // CONTANDO OS DOIS PRIMEIROS PONTOS
    					for(int k=j+1; k<n; k++){
    						if(lpv[k] == 0){
    							px = pontos[k];
    							vx = px - p1;
    							if(colinear(vx, v1)){
    								contador++;
    							}
    						}
    					}
    				}
    				else if( p0 == pontos[j] ){
    					equals++;
    				}
    				if(contador > maximo){
    					maximo = contador; // PARA CONTAR COM O PONTO ATUAL TAMBEM
    				}
    				if(equals > maximo){
    					maximo = equals;
    				}
    			}
    		}
     
    		printf("%i\n", maximo);
    	}
    	
    } 