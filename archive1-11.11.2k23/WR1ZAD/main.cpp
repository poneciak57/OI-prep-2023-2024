#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int MOD = 1e9 + 7;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, r, nom;
  std::cin>>n>>r;

  vec<int> tab(r + 1, 0);

  tab[0] = 1;

  while(n--) {
    std::cin>>nom;

    for(int i = nom; i <= r; i++) {
      tab[i] = (tab[i] + tab[i - nom]) % MOD;
    }
  }

  if(tab[r] == 0) {
    std::cout<<-1;
  } else {
    std::cout<<tab[r];
  }




  std::cout.flush();
}
