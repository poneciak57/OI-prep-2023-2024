#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD = 1000992299;

const ll pows_count = 1e6 + 7;
ll ten_pows[pows_count];

const ll factorials_count = 3e4 + 7;
ll factorials[factorials_count];

void init_pows() {
  for(ll i = 0, pow = 1; i < pows_count; i++) {
    ten_pows[i] = pow;
    pow = (pow * 10) % MOD;
  }
}

void init_factorials() {
  for(ll i = 0, factorial = 1; i < factorials_count; i++, factorial = (factorial*i) % MOD) {
    factorials[i] = factorial;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  str s;
  std::cin>>s;

  init_pows();
  init_factorials();

  // for(int i = 0; i < 20; i++) {
  //   std::cout<<factorials[i]<<" ";
  // }

  // get hash of input
  ll hash = 0;
  for(int i = s.size() - 1, j = 0; i >= 0; i--, j++) {
    int n = s[i] - 48;
    hash = (hash + (n * ten_pows[j])) % MOD;
  }
  if(hash == 0) {
    hash = 1;
  }

  for(int i = 1; i < factorials_count; i++) {
    if(factorials[i] == hash) {
      std::cout<<i;
      break;
    }
  }

  // std::cout<<"fact #11448: "<<factorials[11448]<<"\n";
  // std::cout<<"fact #21008: "<<factorials[21008]<<"\n";
  std::cout.flush();
}
