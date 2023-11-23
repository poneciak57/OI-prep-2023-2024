#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll tree_n;
ll n;
vec<ll> seg_tree;

void create_seg_tree();

void update_point(ll i, ll v) {
  seg_tree[tree_n + i] = v;
  int u = (tree_n + i)/2;
  while(u > 0) {
    seg_tree[u] = seg_tree[2*u] + seg_tree[u*2 + 1];
    u /= 2;
  }
}

// segment question
ll get_sum(ll cur, ll left, ll right, ll lOb, ll rOb) {
  if(left == lOb && right == rOb) {
    return seg_tree[cur];
  }
  ll mid = (rOb + lOb)/2;
  // if whole segment is on the left side
  if(right <= mid) {
    return get_sum(2*cur, left, right, lOb, mid);
  }

  if(left > mid) {
    return get_sum(2*cur + 1, left, right, mid + 1, rOb);
  }

  ll leftPart = get_sum(2*cur, left, mid, lOb, mid);
  ll rightPart = get_sum(2*cur + 1, mid + 1, right, mid + 1, rOb);

  return leftPart + rightPart;
}

void print_tree() {
  int from = 1;
  int to = 2;
  while(from < 2*tree_n) {
    for(int j = from; j < to; j++) {
      std::cout<<seg_tree[j]<<" ";
    }
    from *= 2;
    to *= 2;
    std::cout<<"\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll q;
  std::cin>>n>>q;

  create_seg_tree();
  // std::cout<<"tree print 1\n";
  // print_tree();
  // std::cout<<"[2, 3]: "<<get_sum(1, 2, 3, 1, tree_n)<<"\n";

  // std::cout<<"\ntree print 2\n";
  // update_point(0, 2);
  // print_tree();
  while(q--) {
    char c;
    ll a, b;
    std::cin>>c>>a>>b;

    if(c == 'S') {
      std::cout<<get_sum(1, a, b, 1, tree_n)<<"\n";
    } else {
      update_point(a - 1, b);
    }
  }
  

  std::cout.flush();
}

void create_seg_tree() {
  int log_n = log2(n) + 1;
  tree_n = 1 << log_n;
  seg_tree = vec<ll>(2* tree_n, 0);

  // taking initial data and updating the tree
  for(ll i = 0, inp; i < n; i++) {
    std::cin>>inp;
    seg_tree[tree_n + i] = inp;
  }

  for(int i = tree_n - 1; i >= 1; i--) {
    seg_tree[i] = seg_tree[i * 2] + seg_tree [i * 2 + 1];
  }
}