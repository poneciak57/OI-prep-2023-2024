#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


vec<bool> mods;

struct QEntry {
  int num;
  str s;
};

str bfs(int n) {
  mods = vec<bool>(n, false);
  std::queue<QEntry> q;
  q.push({1 % n ,"1"});
  while(!q.empty()) {
    auto cur = q.front();
    q.pop();

    if(cur.num == 0) {
      return cur.s;
    }

    if(mods[cur.num]) continue;
    mods[cur.num] = true;
    q.push({(cur.num * 10) % n, cur.s + '0'});
    q.push({(cur.num * 10 + 1) % n, cur.s + '1'});
  }
  return "BRAK";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int q;
  std::cin>>q;

  int n;
  while(q--) {
    std::cin>>n;
    std::cout<<bfs(n)<<"\n";
  }

  std::cout.flush();
}
