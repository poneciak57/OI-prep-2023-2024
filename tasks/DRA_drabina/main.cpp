#include <bits/stdc++.h>
#include <iostream>

typedef int ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const long long mod = 1073741824; // 2^30
const int ans_count = 1000001; // 10^6 + 7
const int pows_count = 31;
vec<ll> answers(ans_count, 1);

long long pows[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824};
void generate_answers() {
  for (ll i = 2; i < ans_count; i++) {
    answers[i] = (answers[i - 1] + answers[i - 2]) % mod;
  }
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll z;
  std::cin>>z;
  
  generate_answers();

  while (z--) {
    ll s, p;
    std::cin>>s>>p;
    std::cout<<answers[s]%pows[p]<<"\n";
  }

  std::cout.flush();
}
