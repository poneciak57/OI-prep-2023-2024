#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct TNode {
  ll cur_max {0};
  ll below_max {0};
};

ll true_n;
ll n, m, z;
vec<TNode> seg_tree;

void create_tree();
ll get_max(ll cur, ll left, ll right, ll lOb, ll rOb) {
  if(left == lOb && right == rOb) {
    return std::max(seg_tree[cur].below_max, seg_tree[cur].cur_max);
  }

  ll mid = (lOb + rOb) / 2;
  if (right <= mid) {
    return std::max(get_max(2*cur, left, right, lOb, mid), seg_tree[cur].cur_max);
  }
  if(left > mid) {
    return std::max(get_max(2*cur + 1, left, right, mid + 1, rOb), seg_tree[cur].cur_max);
  }

  ll left_max = get_max(2*cur, left, mid, lOb, mid);
  ll right_max = get_max(2*cur + 1, mid + 1, right, mid + 1, rOb);

  return std::max(seg_tree[cur].cur_max, std::max(left_max, right_max));
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m>>z;
  create_tree();

  std::cout.flush();
}


void create_tree() {
  ll log_n = log2(n) + 1;
  true_n = 1 << log_n;
  seg_tree = vec<TNode>(2*true_n);
}