#include <stdio.h>
#include <iostream>
#include <bitset>

typedef long long ll;

using namespace std;

bitset<1000000> bits;

ll n_of_coprimes(ll n){

  ll result = n;
  ll fatored_n = n;
  bool flag = false;

  bits.set();
  bits[0] = 0;
  bits[1] = 0;
  ll i = 2;

  while(!flag){

    if(bits[i]){
      for(ll j = i*i; j*j<= fatored_n; j += i){ // SET NON-PRIME FOR MULTIPLES OF i.
        bits[j] = 0;
      }
      if( i*i <= fatored_n ){ // SÓ PRECISA IR ATÉ RAIZ(N_FATORADO).
        if( fatored_n % i == 0 ){ // SE N É FATORADO POR i, MULTIPLICA POR FATOR DA FUNCAO.
          result = result - (result/i);  // N * (1 - 1/FATOR_PRIMO)
        }
        while( fatored_n % i == 0 ){ // FATORA N
          fatored_n = fatored_n/i;
        }
      }
      else{
        flag = true;
        break;
      }
    }

    i++;
  }

  if(fatored_n != 1){
    result = result - (result/fatored_n);
  }

  return(result);
}

int main(){

  ll n;
  cin >> n;

  while(n != 0){

    printf("%llu\n", n_of_coprimes(n));

    cin >> n;
  }

}
