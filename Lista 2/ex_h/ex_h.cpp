#include <stdio.h>
#include <iostream>
#include <vector>

typedef long long ll;
typedef std::vector<ll> vll;

using namespace std;

int main(){

  int n;
  cin >> n;

  ll m_adj[n][n];
  ll to_remove[n];
  vll sums(n);
  vll vec_i;
  vll vec_j;

  vec_i.reserve(n);
  vec_j.reserve(n);
  sums.assign(n, 0);

  for(ll i=0; i<n; i++){
    for(ll j=0; j<n; j++){
      cin >> m_adj[i][j];
    }
  }

  // for(int i=0; i<n; i++){
  //   for(int j=0; j<n; j++){
  //     cout << m_adj[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  for(ll i=0; i<n; i++){
    cin >> to_remove[i];
  }

  ll in;

  vll::iterator it_i;
  vll::iterator it_j;

  for(ll k=(n-1); k>=0; k--){
    in = to_remove[k] - 1;

    vec_i.push_back(in);
    vec_j.push_back(in);

    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        m_adj[i][j] = min(m_adj[i][j], m_adj[i][in] + m_adj[in][j]);
      }
    }

    for(it_i = vec_i.begin(); it_i != vec_i.end(); it_i++){
      for(it_j = vec_j.begin(); it_j != vec_j.end(); it_j++){
        sums[k] += m_adj[*it_i][*it_j];
      }
    }

  }

  for(ll i=0; i<n; i++){
    cout << sums[i] << " ";
  }
  // cout << endl;

}
