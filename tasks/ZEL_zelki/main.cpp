#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, k, M;
struct Cuk {
  int k;
  int m;
  ll c;
};

// [kolor][reszta]
vec<vec<ll>> dp;
vec<Cuk> cuks;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>k>>M;

  dp = vec<vec<ll>>(k + 1, vec<ll>(M, -1));
  dp[0][0] = 0;

  for(int i = 0; i < n; i++) {
    int k, m;
    ll c;
    cin>>k>>m>>c;
    cuks.push_back({k, m, c});
  }
  sort(cuks.begin(), cuks.end(), [](Cuk c1, Cuk c2) { return c1.k < c2.k; });

  // najmniejsze ciagi po jeden
  for(auto [k, m, c] : cuks) {
    for(int i = 0; i < M; i++) {
      if(dp[k - 1][i] == -1) continue;
      int nm = (m + i) % M;
      if(dp[k][nm] == -1) dp[k][nm] = dp[k - 1][i] + c;
      else dp[k][nm] = min(dp[k - 1][i] + c, dp[k][nm]);
    }
  }

  vec<ll> tab(M);
  for(int i = 0; i < M; i++) tab[i] = dp[k][i];
  tab[0] = 0;

  // wielokrotnosci
  for(int i = 1; i < M; i++) {
    if(tab[i] == -1) continue;
    ll v = tab[i];
    ll mult = 2;
    for(int j = 0; j < M; j++) {
      int ind = (i * mult) % M;
      ll cur_val = v * mult;
      if(tab[ind] == -1) tab[ind] = cur_val;
      else tab[ind] = min(tab[ind], cur_val);
      mult++;
    }
  }

  // sumowanie
  // {weight, v}
  vec<pair<int,int>> els;
  for(int i = 0; i < M; i++) if(tab[i] != -1) els.push_back({i, tab[i]});
  // [kolejne elementy][reszta z dzielenia]
  dp = vec<vec<ll>>(els.size(), vec<ll>(M, -1));
  dp[0][0] = 0;
  for(int i = 1; i < els.size(); i++) {
    auto [m, v] = els[i];
    for(int j = 0; j < M; j++) {
      if(dp[i - 1][j] == -1) continue;
      if(dp[i][j] == -1) dp[i][j] = dp[i - 1][j];
      else dp[i][j] = min(dp[i - 1][j], dp[i][j]);
      int nm = (m + j) % M;
      if(dp[i][nm] == -1) dp[i][nm] = v + dp[i - 1][j];
      else dp[i][nm] = min(dp[i][nm], v + dp[i - 1][j]);
    }
  }

  for(int i = 0; i < M; i++) {
    cout<<dp[els.size() - 1][i]<<"\n";
  }

  cout.flush();
}