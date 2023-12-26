#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Res {
  ll k_wins{-1};
  ll n_wins;
  ll p_wins;
};

const ll MOD = 1e9 + 7;

unordered_map<ll, ll> fermats;

inline ll powm(ll a, ll n);
inline ll multm(ll a, ll b);
inline ll divm(ll a, ll b);

// [k][n][p]
vec<vec<vec<Res>>> dp(201, vec<vec<Res>>(201, vec<Res>(201)));

Res oblicz(int k, int n, int p) {
  if(dp[k][n][p].k_wins != -1) return dp[k][n][p];
  if(k == 0) return {0, 1, 0};
  if(p == 0) return {1, 0, 0};
  if(n == 0) return {0, 0, 1};

  int sum{ k + n + p };

  // omega zdarzen efektywnych
  ll omega{ sum * (sum - 1) - (k * (k - 1)) - (n * (n - 1)) - (p * (p - 1)) };
  if(!fermats[omega]) fermats[omega] = powm(omega, MOD - 2);
  omega = fermats[omega];
  ll kpA = (2 * k * p * omega) % MOD, knA = (2 * k * n * omega) % MOD, pnA = (2 * p * n * omega) % MOD;
  Res kp_res = oblicz(k - 1, n, p);
  Res kn_res = oblicz(k, n - 1, p);
  Res pn_res = oblicz(k, n, p - 1);

  Res res = {
    (multm(kp_res.k_wins, kpA) + multm(kn_res.k_wins, knA) + multm(pn_res.k_wins, pnA)) % MOD,
    (multm(kp_res.n_wins, kpA) + multm(kn_res.n_wins, knA) + multm(pn_res.n_wins, pnA)) % MOD,
    (multm(kp_res.p_wins, kpA) + multm(kn_res.p_wins, knA) + multm(pn_res.p_wins, pnA)) % MOD,
  };

  dp[k][n][p] = res;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int k, n, p;
  cin>>k>>n>>p;
  int zero_count = (k == 0) + (n == 0) + (p == 0);
  if(zero_count >= 2) {
    if(k == 0) cout<<0; else cout<<1;
    cout<<" ";
    if(n == 0) cout<<0; else cout<<1;
    cout<<" ";
    if(p == 0) cout<<0; else cout<<1;
    // cout<<" ";
  } else {
    Res odp = oblicz(k, n, p);
    cout<<odp.k_wins<<" "<<odp.n_wins<<" "<<odp.p_wins;
  }

  cout.flush();
}


inline ll powm(ll a, ll n) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
    a = (a * a) % MOD;
    n /= 2;
  }
  return w;
}

inline ll multm(ll a, ll b) {
  return (a * b) % MOD;
}

inline ll divm(ll a, ll b) {
  return multm(a, b);
}