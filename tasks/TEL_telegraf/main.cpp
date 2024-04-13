#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n;
vec<bool> iic; // is in cycle
vec<pair<int,ll>> graph;
vec<vec<pair<int,ll>>> tgraph;
vec<int> state;
vec<bool> vis;

ll sum = 0;
// jesli 1 cykl i 0 drzew zwroc 0
int cycle_count = 0;
int tree_count = 0;

int dfs_cycle(int v, int s) {
  if(state[v] == s) return v;
  if(state[v] != -1) return -1; // juz tu bylismy
  state[v] = s;
  return dfs_cycle(graph[v].first, s);
}

pair<ll,ll> sum_tree(int v, int prev) {
  ll mv = 0;
  for(auto [e, c] : tgraph[v]) {
    if(e == prev) continue;
    ll tv = sum_tree(e, prev).first;
    mv = max(mv, tv);
    sum += tv;
  }
  sum -= mv;
  return {graph[v].second, mv};
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  iic = vec<bool>(n, false);
  state = vec<int>(n, -1);
  graph = vec<pair<int,ll>>(n);
  tgraph = vec<vec<pair<int,ll>>>(n);

  // vec<ll> tab(n);

  for(int i = 0; i < n; i++) {
    ll dest, cost;
    cin>>dest>>cost; --dest;
    // tab[i] = cost;
    graph[i] = {dest, cost};
    tgraph[dest].push_back({i, cost});
  }

  // for(int i = 0; i < (1 << 10); i++) {
  //   ll s = 0;
  //   for(int j = 0; j < 10; j++) {
  //     if(i & (1 << j)) s += tab[j];
  //   }
  //   if(s == 2396141312LL) {
  //     for(int j = 0; j < 10; j++) {
  //       if(i & (1 << j)) cout<<j<<" ";
  //     }
  //     break;
  //   }
  // }
  // return 0;

  for(int i = 0; i < n; i++) {
    int cycle_start = dfs_cycle(i, i);
    if(cycle_start == -1) continue;
    cycle_count++;
    // cout<<"found cycle\n";
    
    ll local_tree_count = 0;
    ll prev_cost = graph[cycle_start].second;
    ll v = graph[cycle_start].first;
    ll prev_v = cycle_start;
    ll ce = INT_MAX; // cheapest edge
    ll tes = 0; // tree edges sum
    ll lts = INT_MAX; // lowest tree stay
    ll mete = 0; // most expensive tree edge
    ll tpes = 0; // tree previous edges sum
    ll lowest_always = 0; 
    bool taken_prev = false;

    while(!iic[v]) {
      iic[v] = true;
      ce = min(ce, prev_cost);
      if(tgraph[v].size() > 1) {
        tree_count++;
        local_tree_count++;
        tpes += prev_cost;
        ll te = sum_tree(v, prev_v).second;
        if(te < prev_cost) lowest_always += te;
        else {
          lowest_always += prev_cost;
          taken_prev = true;
        }
        // cout<<"v: "<<v<<"\n";
        // cout<<"te: "<<te<<"\n";
        tes += te;
        lts = min(lts, prev_cost - te);
        mete = max(te, mete);
      }
      prev_cost = graph[v].second;
      prev_v = v;
      v = graph[v].first;
    }

    // cout<<"tes: "<<tes<<"\n";
    // cout<<"mete: "<<mete<<"\n";
    // cout<<"ce: "<<ce<<"\n";
    // cout<<"lts: "<<lts<<"\n";
    // cout<<"sum: "<<sum<<"\n";

    ll mins = min({tes + lts, tes + ce, tpes});
    if(taken_prev) mins = min(mins, lowest_always);
    if(local_tree_count == 0) mins = ce;
    sum += mins;
  }
  if(cycle_count == 1 && tree_count == 0) cout<<0;
  else cout<<sum;

  cout.flush();
}