#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


struct Node {
  ll mods{0};
  ll sum_below{0};
};

ll n;
ll true_n;
ll tree_height;
vec<Node> seg_tree;

void create_tree();
void print_tree();
ll count_below(ll cur);

void update_up(ll cur);
void add_on_segment(ll cur, ll left, ll right, ll lOb, ll rOb, ll mod) {
  if(left == lOb && right == rOb) {
    seg_tree[cur].mods += mod;
    seg_tree[cur].sum_below += mod * count_below(cur);
    return update_up(cur/2);
  }

  ll mid = (lOb + rOb)/2;
  if(right <= mid) {
    return add_on_segment(2 * cur, left, right, lOb, mid, mod);
  }
  if(left > mid) {
    return add_on_segment(2 * cur + 1, left, right, mid + 1, rOb, mod);
  }

  add_on_segment(2 * cur, left, mid, lOb, mid, mod);
  add_on_segment(2 * cur + 1, mid + 1, right, mid + 1, rOb, mod);
  return;
}

ll sum_segment(ll cur, ll left, ll right, ll lOb, ll rOb, ll mod) {
  if(left == lOb && right == rOb) {
    return seg_tree[cur].sum_below + mod * count_below(cur);
  }

  mod += seg_tree[cur].mods;

  ll mid = (lOb + rOb)/2;
  if(right <= mid) {
    return sum_segment(2 * cur, left, right, lOb, mid, mod);
  }
  if(left > mid) {
    return sum_segment(2 * cur + 1, left, right, mid + 1, rOb, mod);
  }

  ll leftPart = sum_segment(2 * cur, left, mid, lOb, mid, mod);
  ll rightPart = sum_segment(2 * cur + 1, mid + 1, right, mid + 1, rOb, mod);

  return leftPart + rightPart;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll q;
  std::cin>>n>>q;
  create_tree();

  // std::cout<<count_below(3)<<"\n";
  // std::cout<<count_below(1)<<"\n";
  // std::cout<<count_below(4)<<"\n";

  while(q--) {
    char c;
    ll a, b, k;
    std::cin>>c;
    if(c == 'W') {
      std::cin>>a>>b>>k;
      add_on_segment(1, a, b, 1, true_n, k);
    } else {
      std::cin>>a>>b;
      std::cout<<sum_segment(1, a, b, 1, true_n, 0)<<"\n";
    }
  }

  std::cout.flush();
}

ll count_below(ll cur) {
  return 1 << (tree_height - (ll)log2(cur));
}

void update_up(ll cur) {
  ll count = count_below(cur);
  while(cur > 0) {
    seg_tree[cur].sum_below = count * seg_tree[cur].mods + seg_tree[cur * 2].sum_below + seg_tree[cur * 2 + 1].sum_below;
    cur/=2;
    count*=2;
  }
}

void create_tree() {
  tree_height = log2(n); 
  true_n = 1 << tree_height;
  if(true_n != n) {
    true_n *= 2;
    tree_height++;
  }
  seg_tree = vec<Node>(2*true_n);
}

void print_tree() {
  ll previ = 1;
  ll i = 2;
  while (previ < 2*true_n)
  {
    for(int j = 0; j < (true_n - (i - previ))*10/2; j++) {
      std::cout<<" ";
    }
    for(int j = previ; j < i; j++) {
      std::cout<<"{ "<<seg_tree[j].sum_below<<", "<<seg_tree[j].mods<<" }  ";
    }
    
    std::cout<<"\n";
    previ *= 2;
    i *= 2;
  }
  for(int j = 0; j < true_n; j++) {
    std::cout<<"    "<<j+1<<"     ";
  } 
}