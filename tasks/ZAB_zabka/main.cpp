#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll n, k, m;
vec<ll> p;
vec<int> f;

/**
 * Rozwiazanie jeden dziala w czasie O(n * log_m) i korzysta z binary liftingu
 * Jest to implementacja pojedynczego binary liftingu ktora ma zlozonosc pamieciowa rzedu O(n)
*/
void solve1();

void solve2();

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>k>>m;

  f = vec<int>(n + 1);
  p = vec<ll>(n + 1);

  for(int i = 1; i <= n; i++) {
    cin>>p[i];
  }

  ll a = 1;
  f[1] = k + 1;
  for(int i = 2; i <= n; i++) {
    while(a + k + 1 <= n && p[a + k + 1] - p[i] < p[i] - p[a]) {
      a++;
    }
    if(p[i] - p[a] >= p[a + k] - p[i]) f[i] = a;
    else f[i] = a + k;
  }

  solve2();

  cout.flush();
}

// vec<int> ans(n + 1); // answers
// // {id_cyklu, pozycja w cyklu}
// vec<pair<int,int>> cykl(n + 1, {-1, -1});
// vec<vec<int>> cykle;
// vec<int> c(n + 1, -1); // count from the start of dfs
// vec<bool> v(n + 1, false); // is visited

// int WCyklu(int w, ll p) {
//   auto [cid, pos] = cykl[w];
//   return cykle[cid][(p + pos) % cykle[cid].size()];
// }

// vec<int> tt;
// vec<vec<int>> ngraph;
// void DFS(int v) {
//     tt.push_back(v);
//     if(tt.size() >= m) ans[v] = tt[tt.size() - m];
//     else ans[v] = WCyklu(tt[0], m - tt.size() + 1);
//     for(auto e : ngraph[v]) DFS(e);
//     tt.pop_back();
    
//   }

// void solve2() {
//   ans = vec<int>(n + 1);
//   // {id_cyklu, pozycja w cyklu}
//   cykl = vec<pair<int,int>>(n + 1, {-1, -1});
//   c = vec<int>(n + 1, -1);
//   v = vec<bool>(n + 1, false); 
//   // znajdowanie cykli w grafie
//   for(int i = 1; i <= n; i++) {
//     if(v[i]) continue;
//     int j = i;
//     int q = 0;
//     vec<int> t;
//     while(c[j] == -1 && f[j] != -1) {
//       t.push_back(j);
//       c[j] = q;
//       j = f[j];
//       v[j] = true;
//       q++;
//     }
//     // wierzcholek juz nalezy do cyklu ktory byl juz dodany
//     if(f[j] == -1) {
//       continue;
//     }

//     vec<int> cur_cykl;
//     // przechodzimy jeszcze raz po calym cyklu zapisujemy wyniki c mod m
//     // od q odejmujemy dystans ktory nie nalezy do cyklu i otrzymujemy dlugosc cyklu
//     int count = q - c[j];
//     int cur = j;
//     int odp = (m % count) + c[j];
//     int pos = 0;
//     do {
//       cykl[cur] = {cykle.size(), cur_cykl.size()};\
//       cur_cykl.push_back(cur);
//       // ans[cur] = t[odp];
//       odp = f[odp];
//       cur = f[cur];
//     } while(cur != j);
//     cykle.push_back(cur_cykl);

//     // usuwamy takze wierzcholki w cyklu (ich relacje)
//     do {
//       int next = f[cur];
//       f[cur] = -1;
//       cur = next;
//     } while(cur != j);
//   }

//   ngraph = vec<vec<int>>(n + 1);
//   for(int i = 1; i <= n; i++) {
//     if(f[i] == -1) continue;
//     ngraph[f[i]].push_back(i);
//   }

//   for(int i = 1; i <= n; i++) {
//     if(cykl[i].first != -1) {
//       DFS(i);
//     }
//   }
//   for(int i = 1; i <= n; i++) {
//     cout<<ans[i]<<" ";
//   }
// }

void solve1() {
  // we apply h on g
  auto zlozenie = [&](vec<int> &g, vec<int> &h) {
    vec<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
      w[i] = g[h[i]];
    }
    return w;
  };
  
  vec<int> g = f;
  vec<int> r(n + 1);
  for(int i = 1; i <= n; i++) r[i] = i;

  // traktujemy odleglosc jako liczbe binarna i uzywamy binary lifting w postaci szybkiego potegowania
  while(m > 0) {
    if(m % 2 == 1) {
      r = zlozenie(r, g);
    }
    m /= 2;
    g = zlozenie(g, g);
  }
  for(int i = 1; i <= n; i++) {
    cout<<r[i]<<" ";
  }
}