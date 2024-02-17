#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

const int MAT_SIZE = 26;

// [from][to]
vec<vec<int>> mat(MAT_SIZE, vec<int>(MAT_SIZE, 0));

// litery ktore obecnie wystapily w ktoryms ciagu
vec<bool> avaible(MAT_SIZE, false);

// dodawanie litery do obecnie rozpatrywanych
void add_letter(int c) {
  avaible[c] = true;
} 

// dodawanie relacji z dwoch stringow
int add_rel(str s1, str s2) {
  for(int i = 0; i < min(s1.length(), s2.length()); i++) {
    if(s1[i] != s2[i]) {
      add_letter(s1[i] - 'A');
      add_letter(s2[i] - 'A');
      mat[s1[i] - 'A'][s2[i] - 'A'] = 1;
      return 1;
    }
  }
  return 0;
}

// zwraca litere ktora nie posiada krawedzi wchodzacych
int find_zero_in() {
  for(int i = 0; i < MAT_SIZE; i++) {
    bool found = false;
    if(!avaible[i]) continue;
    for(int j = 0; j < MAT_SIZE; j++) {
      if(mat[j][i] != 0) {
        found = true;
        break;
      }
    }
    if(!found) return i;
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  str s, prev = "";
  int c = 0;
  while(cin>>s) {
    if(s == "#") break;
    c += add_rel(prev, s);
    prev = s;
  }

  // wypisywanie matrycy
  // for(auto row : mat) {
  //   for(auto v : row) {
  //     cout<<v<<" ";
  //   }
  //   cout<<"\n";
  // }
  
  for(int i = 0; i < avaible.size(); i++) {
    if(!avaible[i]) continue;
    int zero_in = find_zero_in();
    
    // usuwanie relacji od [zero_in]
    for(int j = 0; j < MAT_SIZE; j++) mat[zero_in][j] = false;
    // dodawanie petelki aby wierzcholek nie byl rozpatrzony ponownie
    mat[zero_in][zero_in] = true;

    cout<<(char)(zero_in + 'A');
  }
  if(c == 0) cout<<prev[0];

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}