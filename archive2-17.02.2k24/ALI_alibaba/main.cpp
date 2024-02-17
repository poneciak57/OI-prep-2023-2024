#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int MAX_V = 10;
const int MAX_VV = MAX_V*MAX_V;

struct Set {
  int hash;
  int z;
  int s;
  int m;
};


Set end;
vec<std::pair<Set, Set>> options;
vec<bool> was;

int bfs(Set start) {
  std::queue<std::pair<int, Set>> q;
  q.push({0, start});
  while (!q.empty())
  {
    auto [time, cur] = q.front();
    q.pop();

    if(cur.z >= end.z && cur.s >= end.s && cur.m >= end.m) {
      return time;
    }
    time++;
    for(auto [from, to] : options) {
      Set tmp = cur;
      tmp.z -= from.z;
      tmp.s -= from.s;
      tmp.m -= from.m;
      if(tmp.z < 0 || tmp.s < 0 || tmp.m < 0) continue;

      tmp.z += to.z;
      tmp.s += to.s;
      tmp.m += to.m;
      if(tmp.z >= MAX_V || tmp.s >= MAX_V || tmp.m >= MAX_V) continue;
      
      tmp.hash = tmp.z + tmp.s*MAX_V + tmp.m*MAX_VV;

      if(!was[tmp.hash]) q.push({time, tmp});
      was[tmp.hash] = true;
    }
  }
  return -1;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  while(n--) {
    int r;
    Set start;

    options.clear();
    was = vec<bool>(MAX_VV*MAX_V + MAX_VV + MAX_V + 7, false);

    std::cin>>start.z>>start.s>>start.m;
    std::cin>>end.z>>end.s>>end.m;

    start.hash = start.z + start.s*MAX_V + start.m*MAX_VV;
    end.hash = end.z + end.s*MAX_V + end.m*MAX_VV;

    std::cin>>r;
    while(r--) {
      int z1, s1, m1, z2, s2, m2;
      std::cin>>z1>>s1>>m1>>z2>>s2>>m2;
      options.push_back({{-1, z1, s1, m1}, {-1, z2, s2, m2}});
    }
    int res = bfs(start);
    if(res == -1) {
      std::cout<<"NIE\n";
    } else {
      std::cout<<res<<"\n";
    }
  }

  std::cout.flush();
}
