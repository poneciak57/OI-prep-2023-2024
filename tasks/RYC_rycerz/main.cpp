#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;
template <typename T>
using vec = std::vector<T>;
using namespace std;

int n, m, max_d, k;
struct Rel { int mask {0}; int swords[10]; }; vec<Rel> rels;
vec<vec<pair<int, int>>> graph; // {dest, rel_id}


bool bfs(int last_state) {
  // [state][node]
  vec<bitset<10007>> vis(last_state + 1);
  struct QEntry {int v; int state; int d; }; queue<QEntry> q; q.push({1, 0, 0}); vis[0][1] = true;
  while(!q.empty()) {
    auto [v, s, d] = q.front();
    q.pop();

    if(d >= max_d) continue;

    for(auto [w, e] : graph[v]) {
      int ns = s | rels[e].mask;
      if(vis[ns][w]) continue;
      vis[ns][w] = true;
      q.push({w, ns, d + 1});
    }
  }

  return vis[last_state][n];
}

void update_masks(int sword_id, int val) {
  int mask_reset = 1 << sword_id; mask_reset = ~mask_reset;
  int mask_add = 1 << sword_id;
  for(auto &r : rels) {
    r.mask &= mask_reset;
    if(r.swords[sword_id] >= val) r.mask |= mask_add;
  }
}

vec<int> swords[10];
int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>max_d>>k;
  graph = vec<vec<pair<int,int>>>(n + 1);
  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].push_back({b, rels.size()});
    graph[b].push_back({a, rels.size()});
    rels.push_back({});
    for(int i = 0, tmp; i < k; i++) {
      cin>>tmp; rels.back().swords[i] = tmp;
      swords[i].push_back(tmp);
    }
  }
  for(int i = 0; i < k; i++) sort(swords[i].begin(), swords[i].end());
  
  int state = 0;
  vec<int> ans;
  for(int i = 0; i < k; i++) {
    state += 1 << i;

    // bool stopped = false;
    // for(int j = 0; j < swords[i].size(); j++) {
    //   update_masks(i, swords[i][j]);
    //   if(!bfs(state)) {
    //     ans.push_back(swords[i][j - 1]);
    //     stopped = true;
    //   }
    // }
    // if(!stopped) ans.push_back(swords[i].back());
    int b = 0, e = swords[i].size(), m;
    while(b + 1 < e) {
      m = (b + e) / 2;
      update_masks(i, swords[i][m]);
      if(bfs(state)) b = m;
      else e = m;
    }
    ans.push_back(swords[i][b]);
  }
  for(auto a : ans) cout<<a<<" ";


  cout.flush();
}