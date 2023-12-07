#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Point {
  ll x;
  ll y;
};

struct Rock {
  Point p;
  vec<int> rels;
};

ll n, start, S;
vec<Rock> rocks;

inline bool can_jump(Point from, Point to) {
  ll xs = abs(from.x - to.x);
  ll ys = abs(from.y - to.y);
  return (xs*xs + ys*ys) <= S*S;
}

inline double get_dist_from_start(Point p) {
  ll ps = abs(rocks[start - 1].p.x - p.x);
  ll ss = abs(rocks[start - 1].p.y - p.y);
  return sqrt(ps*ps + ss*ss);
}

double bfs(int from) {
  queue<int> q;
  vec<bool> v(rocks.size());
  q.push(from);
  v[from] = true;

  double max_dist = S;

  while (!q.empty()) 
  {
    Rock &curr = rocks[q.front()];
    q.pop();

    max_dist = max(get_dist_from_start(curr.p) + S, max_dist);

    for(auto rel : curr.rels) {
      if(!v[rel]) {
        q.push(rel);
        v[rel] = true;
      }
    }
  }
  return max_dist;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  cin>>n>>start>>S;

  rocks = vec<Rock>(n);

  for(int i = 0; i < n; i++) {
    ll x, y;
    cin>>x>>y;
    rocks[i] = {{x, y}};
  }

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if(can_jump(rocks[i].p, rocks[j].p)) {
        rocks[i].rels.push_back(j);
        rocks[j].rels.push_back(i);
      }
    } 
  }

  double res = bfs(start - 1);
  cout<<fixed<<setprecision(3)<<res;
  
  

  std::cout.flush();
}
