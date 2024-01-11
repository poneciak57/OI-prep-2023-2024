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

struct Node {
  int scc;
  vec<int> rels;
};

struct CNode {
  int c;
  // mozliwosci dojscia z danego wierzcholka do gmachu
  int pb {0};
  vec<int> rels;
};

vec<Node> graph;
vec<vec<int>> trans_graph;
vec<CNode> c_graph;
vec<CNode> c_trans_graph;


/**
 * Jesli graf posiada cykl z ktorego jest dojscie do gmachu to odpowiedzia bedzie "zawsze"
 * i wszystkie wierzcholki z SSC ktore maja dojscie do gmachu
 * 
 * dojscie do gmachu mozna sprawdzic uzywajac bfs lub dfs na transponowanym grafie SSC zaczynajac od n
 * 
 * jesli nie istnieje cykl z ktorego jest dojscie to aby uzyskac odpowiedz trzeba topologicznie posortowac graf SSC
 * (wystarczy tylko skladowa tego grafu ktora ma w sobie gmach)
 * i wykonac w takiej kolejnosci dynamika
 * 
 * ew zaczac od gmachu i na transponowanym grafie SSC isc od niego i dodawac ilosc mozliwosci
 * 
 * !!!
 * Jesli gmach lezy w SCC ktory jest > 1 elementowy to kazda nawet jednoelementowa skladowa moze osiagnac wartosc "zawsze" krazac dookola gmachu
*/

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, m;
  n += 1;
  graph = vec<Node>(n + 1);
  trans_graph = vec<vec<int>>(n + 1);

  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.emplace_back(b);
    trans_graph[b].emplace_back(a);
  }

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