#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int MAX_SIZE = 1e8;

vec<bool> sito(MAX_SIZE, true);

void make_sito() {
  sito[0] = false;
  sito[1] = false;
  for(int i = 2; i < MAX_SIZE; i++) {
    if(sito[i]) {
      for(int j = i + i; j < MAX_SIZE; j += i) {
        sito[j] = false;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  make_sito();

  

  std::cout.flush();
}
