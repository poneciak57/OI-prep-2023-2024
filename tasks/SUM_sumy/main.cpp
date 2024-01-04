#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


/**
 * Wybieramy najmniejsza liczbe ze zbioru 'A' i budujemy graf mozliwych modulo z liczby 'a'
 * "Budujemy" ten graf w domysle do kazdego wierzcholku mozemy dojsc przy uzyciu w jakiejs odleglosci bedacej inna wartoscia ze zbioru 'A'
 * Ai (aj)=> A((i + aj) mod a)
 * Na takim grafie od razu wykonujemy algorytm dijkstry wtedy otrzymujemy tablice odleglosci 'd'
 * w ktorej d[i] oznacza minimalna wartosc liczby 'p' ktora daje reszte z dzielenia przez 'a' rowna 'i' jesli dana liczba 
 * 'x' jest >= 'p' to wystepuja ona w zbiorze A'
*/

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;

  int a;
  cin>>a;
  vec<bool> v(a, false);
  vec<int> rels;
  for(int i = 0, t; i < n - 1; i++) {
    cin>>t;
    if(v[t % a]) continue;
    v[t % a] = true;
    rels.push_back(t);
  }

  vec<int> d(a, INT_MAX);
  // {dist, mod}
  priority_queue<pair<int,int>, vec<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.push({0, 0});
  d[0] = 0;

  while (!pq.empty()) {
    auto [dist, mod] = pq.top();
    pq.pop();

    if(d[mod] < dist) continue;

    for(auto r : rels) {
      int ndist = dist + r;
      int nmod = (mod + r) % a;
      if(d[nmod] > ndist) {
        d[nmod] = ndist;
        pq.push({ndist, nmod});
      }
    }
  }

  int q;
  cin>>q;
  while(q--) {
    int t;
    cin>>t;
    if(d[t % a] <= t) {
      cout<<"TAK\n";
    } else {
      cout<<"NIE\n";
    }
  }
  

  cout.flush();
}
