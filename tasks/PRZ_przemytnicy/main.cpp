#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int MINF = 1e8 + 57;

int n, m;
int minc;
vec<vec<pair<int,int>>> graph;
vec<vec<pair<int,int>>> tgraph;
vec<int> c;
vec<int> d1;

// normal [from][to]
// trams [to][from]
vec<vec<int>> mat;

void dijkstra() {
  priority_queue<pair<int,int>, vec<pair<int,int>>, greater<pair<int,int>>> pq;
  d1 = vec<int>(n, MINF);
  d1[0] = 0;
  pq.push({0, 0});
  while(!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();

    if(d1[v] < d) continue;
    for(auto [e, cost] : graph[v]) {
      int nd = d + cost;
      if(nd < d1[e]) {
        d1[e] = nd;
        pq.push({nd, e});
      }
    }
  }
  for(int i = 0; i < n; i++) c[i] += d1[i];
}

void trans_dijkstra() {
  priority_queue<pair<int,int>, vec<pair<int,int>>, greater<pair<int,int>>> pq;
  d1 = vec<int>(n, MINF);
  d1[0] = 0;
  pq.push({0, 0});
  while(!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();

    if(d1[v] < d) continue;

    for(auto [e, cost] : tgraph[v]) {
      int nd = d + cost;
      if(nd < d1[e]) {
        d1[e] = nd;
        pq.push({nd, e});
      }
    }
  }
  for(int i = 0; i < n; i++) c[i] += d1[i];
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  c = vec<int>(n);
  d1 = vec<int>(n, MINF);
  graph = vec<vec<pair<int,int>>>(n);
  tgraph = vec<vec<pair<int,int>>>(n);
  for(int i = 0; i < n; i++) {
    cin>>c[i];
    c[i] /= 2;  
  }
  minc = c[0];

  cin>>m;
  while(m--) {
    int a, b, cost;
    cin>>a>>b>>cost; --a; --b;
    graph[a].push_back({b, cost});
    tgraph[b].push_back({a, cost});
  }
  dijkstra();
  trans_dijkstra();

  for(int i = 0; i < n; i++) minc = min(minc, c[i]);

  cout<<minc;

  cout.flush();
}