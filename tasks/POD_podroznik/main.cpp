#include <bits/stdc++.h>
#define LL_INF 1000000000000000007LL

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll n, m, b, c;

vec<vec<pair<int, int>>> graph;
vec<ll> d;

void dijkstra(int s) {
  priority_queue<pair<ll, ll>, vec<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
  pq.push({0, s});
  d[s] = 0;
  while(!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();

    if(d[v] < dist) continue;

    for(auto [e, w] : graph[v]) {
      int nd = min(dist + w, LL_INF);
      if(d[e] > nd) {
        d[e] = nd;
        pq.push({nd, e});
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>b>>c;
  graph = vec<vec<pair<int,int>>>(n + 1);
  d = vec<ll>(n + 1, INT_MAX);
  while(m--) {
    int f, t, w;
    cin>>f>>t>>w;
    graph[f].push_back({t, w});
    graph[t].push_back({f, w});
  }
  dijkstra(1);

  vec<ll> tab;
  for(int i = 1; i <= n; i++) tab.push_back(d[i]);
  sort(tab.begin(), tab.end());

  int i = 0;
  int ans = 0;
  while(b > 0 && i < n) {
    b -= min(tab[i] * 2, c);
    // cout<<b<<"\n";
    ans++;
    i++;
  } 
  if(b < 0) ans--;
  cout<<ans;

    
  cout.flush();
}
