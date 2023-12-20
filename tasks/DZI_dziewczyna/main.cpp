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

str s;
int n;
ll gcount = 0;
// 
// hash jest konstruowany nastepujaco (pos pozycja w ciagu)
// - 0 = 1 * 2^(pos) 
// - 1 = 2 * 2^(pos) 
// h1 -> hashes from left
// h2 -> hashes from right (reversed) with negation
vec<pair<ll, ll>> pows;
vec<pair<ll, ll>> fermats;
vec<pair<ll, ll>> h1;
vec<pair<ll, ll>> h2;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

void prepare_hash_pref_sums();
bool is_good_range(int b, int e) {
  if(b < 0 || e >= n) return false;
  // cout<<"b: "<<b<<"  e: "<<e<<"\n";
  pair<ll, ll> n_hash;
  if(b > 0) {
    n_hash = {
      divm((h1[e].first - h1[b - 1].first + MOD1) % MOD1, fermats[b].first, MOD1),
      divm((h1[e].second - h1[b - 1].second + MOD2) % MOD2, fermats[b].second, MOD2)
    };
  } else {
    n_hash = {h1[e].first, h1[e].second};
  }

  pair<ll, ll> r_hash;
  if(e < n - 1)  {
    r_hash = {
      divm((h2[b].first - h2[e + 1].first + MOD1) % MOD1, fermats[n - e - 1].first, MOD1),
      divm((h2[b].second - h2[e + 1].second + MOD2) % MOD2, fermats[n - e - 1].second, MOD2)
    };
  } else {
    r_hash = {h2[b].first, h2[b].second};
  }
  // cout<<"nh: "<<n_hash.first<<"\n";
  // cout<<"rh: "<<r_hash.first<<"\n";

  return r_hash.first == n_hash.first && r_hash.second == n_hash.second;
}

// void check_pair(int b, int e) {
//   while(is_good_range(b, e)) {
//     cout<<"["<<b<<","<<e<<"]\n";
//     b--;
//     e++;
//     gcount++;
//   }
// }

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  cin>>s;
  prepare_hash_pref_sums();

  // is_good_range(3, 4);
  // return 0;

  // for(int i = 1; i < n; i++) {
  //   check_pair(i - 1, i);
  // }


  for(int i = 1; i < n; i++) {
    if((s[i] - '0') != !(s[i - 1] - '0')) continue;

    int b = 0, e = n, m;
    while(b + 1 < e) {
      m = (b + e) / 2;
      
      if(is_good_range(i - 1 - m, i + m)) {
        b = m;
      } else {
        e = m;
      }
    }
    gcount += b + 1;
  }

  cout<<gcount;


  cout.flush();
}


void prepare_hash_pref_sums() {
  pows = vec<pair<ll, ll>>(n);
  fermats = vec<pair<ll, ll>>(n);
  pows[0] = {1, 1};
  fermats[0] = {1, 1};
  ll mod1_fermat_mult = powm(3, MOD1 - 2, MOD1);
  ll mod2_fermat_mult = powm(3, MOD2 - 2, MOD2);
  for(int i = 1; i < n; i++) {
    pows[i] = {
      (pows[i - 1].first * 3) % MOD1, 
      (pows[i - 1].second * 3) % MOD2
    };
    fermats[i] = {
      (fermats[i - 1].first * mod1_fermat_mult) % MOD1,
      (fermats[i - 1].second * mod2_fermat_mult) % MOD2
    };
  }

  h1 = vec<pair<ll, ll>>(n);
  pair<ll, ll> prev = {0, 0};
  for(int i = 0; i < n; i++) {
    prev.first = (prev.first + pows[i].first * (s[i] - '0' + 1)) % MOD1;
    prev.second = (prev.second + pows[i].second * (s[i] - '0' + 1)) % MOD2;
    h1[i] = prev;
  }

  h2 = vec<pair<ll, ll>>(n);
  prev = {0, 0};
  for(int i = n - 1; i >= 0; i--) {
    prev.first = (prev.first + pows[n - i - 1].first * (!(s[i] - '0') + 1)) % MOD1;
    prev.second = (prev.second + pows[n - i - 1].second * (!(s[i] - '0') + 1)) % MOD2;
    h2[i] = prev;
  }
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

ll divm(ll a, ll fermat, ll MOD) {
  return multm(a, fermat, MOD);
}