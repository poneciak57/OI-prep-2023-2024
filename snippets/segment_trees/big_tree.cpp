#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int N = 1 << 20;

vec<int> seg_tree;
// mapa przechowuje indeksy w drzewie dla duzych wartosci
unordered_map<ll, int> poses;

void init(int n) {
  seg_tree = vec<int>(2*N, 0);

  vec<ll> inp(n);
  for(int i = N; i < N + n; i++) {
    cin>>inp[i - N];
  }
  // sortujemy wejscie rosnaca aby przypisac mu indeksy w drzewie w dobrej kolejnosci
  sort(inp.begin(), inp.end());

  // przypisujemy wartoscia indeksy w drzewie
  int ind = 1;
  for(auto i : inp) {
    poses[i] = ind++;
  }

  /**
   * Załózmy ze chcemy odnalezc teraz przedzial od 100000000 do 200000000
   * w normalnym drzewie przedzialowym nie byloby to mozliwe nawet jesli istnieje 10^5 wartosci
   * tutaj to nic trudnego znajdujemy poczatkowy i koncowy wierzcholek
   * int p = poses[100000000];
   * int k = poses[200000000];
   * jestesmy w stanie wykonac teraz operacje na drzewie w taki sposob
   * get_sum(1, p, k, 1, N);
   * operacja niczym nie bedzie sie roznic od tych implementowanych na statycznych drzewach
  */
}