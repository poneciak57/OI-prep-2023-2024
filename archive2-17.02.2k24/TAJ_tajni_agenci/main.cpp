#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Ret { int type; int depth; int v; };
struct Node { int type; int depth; vec<int> rels; };
vec<Node> tree;
vec<pair<int,int>> pairs;
bool ok = true;

Ret dp(int v, int par, int d) {
  // {depth, nid}
  vec<pair<int, int>> elites;
  vec<pair<int, int>> twos;
  vec<pair<int, int>> trees;
  vec<Ret> rets;

  tree[v].depth = d;
  if(tree[v].type == 1) elites.push_back({d, v});
  else if(tree[v].type == 2) twos.push_back({d, v});
  else if(tree[v].type == 3) trees.push_back({d, v});

  for(auto e : tree[v].rels) {
    if(e == par) continue;
    auto [tt, td, tw] = dp(e, v, d + 1);
    if(tt == 1) elites.push_back({td, tw});
    else if(tt == 2) twos.push_back({td, tw});
    else if(tt == 3) trees.push_back({td, tw});
  }

  sort(elites.begin(), elites.end());
  sort(twos.begin(), twos.end());
  sort(trees.begin(), trees.end());

  for(auto [dep, nid] : elites) {
    if(!rets.empty() && rets.back().depth == dep){
      pairs.push_back({rets.back().v, nid});
      rets.pop_back();
    } else rets.push_back({1, dep, nid});
  }

  if(twos.empty()) for(auto [dep, nid] : trees) rets.push_back({3, dep, nid});
  else if(trees.empty()) for(auto [dep, nid] : twos) rets.push_back({2, dep, nid});
  else {
    if(abs((int)twos.size() - (int)trees.size()) > 1) ok = false;
    else {
      int i = 0, j = 0;

      for(; j < twos.size() && i < trees.size(); j++, i++) {
        if(trees[i].first > twos[j].first) pairs.push_back({trees[i].second, twos[j].second});
        else if(i == j) ok = false;
        else {
          if(i > j) {
            rets.push_back({3, trees[i].first, trees[i].second});
            j--;
          } else {
            rets.push_back({2, twos[j].first, twos[j].second});
            i--;
          }
        }
      }
      while(i < trees.size()) {
        rets.push_back({3, trees[i].first, trees[i].second});
        i++;
      }
      while(j < twos.size()) {
        rets.push_back({2, twos[j].first, twos[j].second});
        j++;
      }
    }
  }
  if(rets.size() > 1) ok = false;
  if(rets.empty()) return {0, -1, -1};
  return rets[0];
}



int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;

  tree = vec<Node>(n + 7);
  for(int i = 2, t; i <= n; i++) {
    cin>>t;
    tree[i].type = t;
  }

  for(int i = 1; i < n; i++) {
    int a, b;
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }

  Ret r = dp(1, 1, 0);
  if(r.type == 0 && ok) {
    cout<<"TAK\n";
    for(auto [a, b] : pairs) {
      cout<<a<<" "<<b<<"\n";
    }
  } else { 
    cout<<"NIE";
  }

}
