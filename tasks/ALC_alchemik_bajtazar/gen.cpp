#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

const int MIN_N = 5;
const int MAX_N = 15;

void gen_tree(int n) {
    vec<int> par(n + 1);
    for(int i = 2; i <= n; i++) {
      par[i] = rand_range(1, i - 1);
    }

    vec<int> inds(n + 1);
    for(int i = 1; i <= n; i++) inds[i] = i;
    random_shuffle(inds.begin() + 1, inds.end());

    vec<pair<int,int>> E;
    for(int i = 2; i <= n; i++) E.push_back({inds[i], inds[par[i]]});

    for(auto [a, b] : E) {
      cout<<a<<b<<"\n";
    }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n = rand_range(MIN_N, MAX_N);

  cout<<n - 1<<"\n";
  gen_tree(n);
  cout<<n - 1<<"\n";
  gen_tree(n);

  cout.flush();
}