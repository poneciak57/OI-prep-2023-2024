#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Rel {
  ll dest{0};
  ll weight;
};

struct Node {
  Rel parrent;
  vec<Rel> rels;
};

ll n, k;
vec<Node> tree;
vec<ll> up;
// {weight, leaf}
vec<pair<ll, ll>> max_down;

struct QEntry {
  ll cur;
  ll cw;
  ll leaf;
};


void prep(ll node, ll upw) {
  up[node] = upw;

  ll max_d = 0;
  ll leaf = node;
  for(auto rel : tree[node].rels) {
    if(rel.dest != tree[node].parrent.dest) {
      // determing the parrent of each node
      tree[rel.dest].parrent = {node, rel.weight};
      prep(rel.dest, upw + rel.weight);
      ll md = max_down[rel.dest].first + rel.weight;
      if(md > max_d) {
        max_d = md;
        leaf = max_down[rel.dest].second;
      } 
    }
  }
  max_down[node] = {max_d, leaf};
}

struct Higher {
  bool operator()(QEntry e1, QEntry e2) {
    return e1.cw < e2.cw;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>k;
  tree = vec<Node>(n + 1);
  ll all_paths_sum = 0;

  for(ll i = 1; i < n; i++) {
    ll a, b, w;
    cin>>a>>b>>w;
    all_paths_sum += w;
    tree[a].rels.push_back({b, w});
    tree[b].rels.push_back({a, w});
  }
  up = vec<ll>(n + 1, 0);
  max_down = vec<pair<ll, ll>>(n + 1, {-1, -1});
  prep(1, 0);

  // {node, best_path, leaf}
  // priority_queue<QEntry, vec<QEntry>, Higher> pq;
  vec<QEntry> pq(n);
  for(ll i = 1; i <= n; i++) {
    pq[i - 1] = {
      i,
      (-1*up[tree[i].parrent.dest] + tree[i].parrent.weight + max_down[i].first), 
      max_down[i].second
    };
    // cout<<i<<": "<<(-1*up[tree[i].parrent.dest] + tree[i].parrent.weight + max_down[i].first)<<"\n";
    // pq.push({i ,(-1*up[tree[i].parrent.dest] + tree[i].parrent.weight + max_down[i].first), max_down[i].second});
  }
  sort(pq.begin(), pq.end(), [](QEntry &e1, QEntry &e2) {
    return e1.cw > e2.cw;
  });
  ll sum = 0;
  vec<bool> v(n + 1, false);
  ll j = 0;
  for(ll i = 0; i < k; i++) {
    if(j >= n) break;
    auto [node, path_w, leaf] = pq[j];
    j++;
    
    if(v[node]) {
      i--;
      continue;
    } else if(path_w <= 0) break;

    sum += path_w;
    ll cur = leaf;
    while(v[cur] == false && cur != 0) {
      v[cur] = true;
      cur = tree[cur].parrent.dest;
    }
  }

  cout<<2*all_paths_sum - sum;

  cout.flush();
}
