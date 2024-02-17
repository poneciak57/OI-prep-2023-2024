#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Rel {
  int dest;
  ll weight; // square of distance
};

struct Node {
  ll x;
  ll y;
  vec<Rel> rels;
};

int n;
vec<Node> graph;

ll prims() {
  // {dist, node}
  typedef pair<ll, int> QEntry;
  priority_queue<QEntry, vec<QEntry>, greater<QEntry>> pq;
  vec<bool> v(n + 1); // dist to the node
  int done = 0;
  ll max_dist = 0;
  pq.push({0, 0});

  while(!pq.empty()) {
    auto [dist, node] = pq.top();
    pq.pop();

    if(v[node]) continue;
    v[node] = true;
    done++;
    max_dist = max(max_dist, dist);
    if(done == n + 1) break;

    for(auto rel : graph[node].rels) {
      if(!v[rel.dest]) {
        pq.push({rel.weight, rel.dest});
      }
    }

  }
  return max_dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  graph = vec<Node>(n + 1);

  graph[0] = {0, 0};
  for(ll i = 1, x, y; i <= n; i++) {
    cin>>x>>y;
    graph[i] = {x, y};
  }

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j <= n; j++) {
      ll x_d = abs(graph[i].x - graph[j].x);
      ll y_d = abs(graph[i].y - graph[j].y);
      ll weight = x_d * x_d + y_d * y_d;
      graph[i].rels.push_back({j, weight});
      graph[j].rels.push_back({i, weight});
    }
  }

  // cout<<prims()<<"\n";
  cout<<fixed<<setprecision(5)<<sqrt(prims())<<"\n";


  cout.flush();
}
