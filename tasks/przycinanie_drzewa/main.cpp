#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<bool> tree;
ll count = 0;

void dfs(ll n) {
  if(n < tree.size() && tree[n]) {
    count++;
    dfs(n*2);
    dfs(n*2 + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll h, n;
  std::cin>>h>>n;
  
  tree = vec<bool>(1<<h, true);
  
  while (n--) {
    ll t;
    std::cin>>t;
    tree[t] = false;
  }

  dfs(1);
  std::cout<<count;

  std::cout.flush();
}
