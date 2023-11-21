#include <bits/stdc++.h>

typedef unsigned int ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


const int letters = 26;
const ll MOD = 123456789;

// [przed][po]
bool pairs[letters][letters];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, k;
  std::cin>>n>>k;

  while (k--) {
    char f, s;
    std::cin>>f>>s;
    pairs[f - 97][s - 97] = true;
  }

  vec<vec<ll>> solves(letters, vec<ll>(n + 1, 1));
  vec<ll> sums(n + 1);
  sums[1] = 26;

  for (ll len = 2; len <= n; len++) {
    ll sum = 0;
    for (ll letter = 0; letter < letters; letter++) {
      int len_minus = len - 1;
      ll prev = sums[len_minus];
      for (ll prev_let = 0; prev_let < letters; prev_let++) {
        if(pairs[prev_let][letter]) {
          prev = prev + MOD - solves[prev_let][len_minus];
        } 
      }
      prev = prev % MOD;
      solves[letter][len] = prev;
      sum = (sum + prev) % MOD;
    }
    sums[len] = sum;
  }
  std::cout<<sums[n];

  std::cout.flush();
}
