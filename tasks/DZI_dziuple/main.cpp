#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int ss {-1};
  int liscie {0};
  vec<int> rels;
};

vec<Node> graph;
// // ilosci w kazdych skladowych jesli skladowa nie ma wierzcholkow to rzadna kolejna takze ich nie posiadas
// vec<int> sss;
// dlugosc osi dla spojnej skladowej
vec<int> dlugosc_osi;

// sprawdzamy czy graf jest acykliczny
// ustawiamy numery skladowych
// zliczamy ilosc lisci dla kazdego wierzcholka
// obliczamy wielkosc skladowych
// nie musimy wyznaczac osi gdyz jesli jakis wierzcholek jest lisciem to ma liscie = 0 a !0 = 1 
// wiec nie zmieni to naszego wyniku
bool dfs(int node, int prev, int ss) {
  if(graph[node].ss != -1) return false;
  // sss[ss]++;
  graph[node].ss = ss;
  bool ret = true;
  for(auto e : graph[node].rels) {
    if(graph[e].rels.size() == 1) {
      graph[node].liscie++;
    }
    if(e == prev) continue;
    ret = ret && dfs(e, node, ss);
  }
  return ret;
}

int get_dlugosc_osi(int node, int prev) {
  int res = graph[node].rels.size() > 1;
  for(auto e : graph[node].rels) {
    if(e == prev) continue;
    res += get_dlugosc_osi(e, node);
  }
  return res;
}

ll silnia(int n, ll mod) {
  ll res = 1;
  for(int i = 1; i <= n; i++) {
    res = (res * i) % mod;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  ll mod;
  cin>>n>>m>>mod;
  // mod = 100000007;
  // graf nie jest acykliczny
  if(m >= n) {
    cout<<"0";
    return 0;
  }

  graph = vec<Node>(n + 1);
  // sss = vec<int>(n + 1, 0); 
  dlugosc_osi = vec<int>(n + 1, 0);
  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.push_back(b);
    graph[b].rels.push_back(a);
  }
  
  int ss = 1;
  for(int i = 1; i <= n; i++) {
    if(graph[i].ss == -1) {
      if(!dfs(i, i, ss)) {
        cout<<"0";
        return 0;
      }
    } 
    dlugosc_osi[ss] = get_dlugosc_osi(i, i) + 2;
    ss++;
  }
  
  int male_skladowe = 0;
  int duze_skladowe = 0;
  ll res = 1;

  vec<ll> ss_lt(n + 1, 0);
  for(int i = 1; i <= n; i++) {
    if(graph[i].rels.size() == 0) {
      male_skladowe++;
      continue;
    }
    if(ss_lt[graph[i].ss] == 0) {
      duze_skladowe++;
      int ct = 2;
      if(dlugosc_osi[graph[i].ss] > 2) ct = 4;
      ss_lt[graph[i].ss] = ct;
      cout<<"ct: "<<ct<<"\n";
      res = (res * ct) % mod;
    }
    res = (res * silnia(graph[i].liscie, mod)) % mod;
  }
  res = (res * silnia(duze_skladowe, mod)) % mod;

  int wierzcholki_w_duzych = n - male_skladowe;
  for(int i = 1; i <= male_skladowe; i++) {
    res = (res * (wierzcholki_w_duzych + i + 1)) % mod;
  }

  cout<<res;



  cout.flush();
}
