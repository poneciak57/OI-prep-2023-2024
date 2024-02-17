#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int MAX_N = 1007;

struct Node {
  int h {-1}; // max height 
  int d {0}; // two leafs max
  int t {0}; // three leafs max
  vec<int> rels;
};

vec<Node> tree;

int hash_edge(int a, int b) {
  return min(a, b) * MAX_N + max(a, b);
}

void get_for(int node, int parent) {
  if(tree[node].h != -1 ) {
    return;
  }
  int ch_count = tree[node].rels.size() - 1;
  if(parent == -1) {
    ch_count += 1;
  }
  if(ch_count == 1) {
    for(auto rel : tree[node].rels) {
      if(rel != parent) {
        get_for(rel, node);
        tree[node].h = tree[rel].h + 1;
        tree[node].d = tree[rel].d + 1;
        tree[node].t = tree[rel].t;
      }
    }
  } else if(ch_count == 2){
    int prev_t, prev_d = 0, prev_h = -1;
    for(auto rel : tree[node].rels) {
      if(rel != parent) {
        get_for(rel, node);
        tree[node].h = max(tree[rel].h + 1, tree[node].h);
        tree[node].d += tree[rel].h;
        if(prev_h != -1) {
          tree[node].t = max({tree[rel].t, prev_t, tree[rel].h + prev_d + 1, prev_h + tree[rel].d + 1});
        }
        prev_t = tree[node].t;
        prev_d = tree[node].d;
        prev_h = tree[node].h;
      }
    }
    tree[node].d++;
  } else {
    for(auto rel : tree[node].rels) {
      get_for(rel, node);
    }
    int h_sum = 0;
    for(int i = 0; i < tree[node].rels.size(); i++) {
      tree[node].t = max(tree[node].t, tree[tree[node].rels[i]].t);
      int m_h = -1;
      h_sum += tree[tree[node].rels[i]].h;
      for(int j = 0; j < tree[node].rels.size(); j++) {
        if(j != i) m_h = max(m_h, tree[tree[node].rels[i]].h);
      }
      tree[node].t = max({tree[node].t, tree[tree[node].rels[i]].t, m_h + 1 + tree[tree[node].rels[i]].d});
    }
    tree[node].t = max(tree[node].t, h_sum + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;

  if(n == 3) {
    cout<<1;
    return 0;
  }
  // hash = trojkat
  unordered_map<int, int> edges;
  tree = vec<Node>(n - 1);

  for(int i = 1; i <= n - 2; i++) {
    int a, b, c;
    cin>>a>>b>>c;

    int ab_h = hash_edge(a, b);
    if(edges[ab_h]) {
      tree[edges[ab_h]].rels.push_back(i);
      tree[i].rels.push_back(edges[ab_h]);
    } else edges[ab_h] = i;

    int ac_h = hash_edge(a, c);
    if(edges[ac_h]) {
      tree[edges[ac_h]].rels.push_back(i);
      tree[i].rels.push_back(edges[ac_h]);
    } else edges[ac_h] = i;

    int bc_h = hash_edge(c, b);
    if(edges[bc_h]) {
      tree[edges[bc_h]].rels.push_back(i);
      tree[i].rels.push_back(edges[bc_h]);
    } else edges[bc_h] = i;
    
  }
  int degree_1_count = 0;
  for(int i = 1; i < tree.size(); i++) {
    if(tree[i].rels.size() == 1) {
      tree[i].h = 1;
      tree[i].d = 0;
      tree[i].t = 0;
      degree_1_count++;
    }
  }

  if(degree_1_count == 2) {
    cout<<n-2;
    return 0;
  }

  for(int i = 1; i < tree.size(); i++) {
    if(tree[i].rels.size() > 1) {
      get_for(i, -1);
      cout<<tree[i].t;
      return 0;
    }
  }


  cout.flush();
}
