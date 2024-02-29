#include <bits/stdc++.h>
#include "ckollib.h"
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll card = karta();
  ll missing = 0;
  do {
    missing ^= card;
    card = karta();
  } while(card);
  odpowiedz(missing);
  cout.flush();
}
