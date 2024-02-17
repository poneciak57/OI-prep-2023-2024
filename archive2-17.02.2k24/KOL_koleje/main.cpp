#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct TNode {
  ll people_c {0};
  ll below_max {0};
};

ll true_n;
ll n, m, z;
vec<TNode> seg_tree;

void create_tree();
void print_tree();

ll get_max(ll cur, ll left, ll right, ll lOb, ll rOb, ll modification) {
  if(left == lOb && right == rOb) {
    return seg_tree[cur].below_max + modification;
  }

  modification += seg_tree[cur].people_c;
  ll mid = (lOb + rOb) / 2;
  if (right <= mid) {
    return get_max(2*cur, left, right, lOb, mid, modification);
  }
  if(left > mid) {
    return get_max(2*cur + 1, left, right, mid + 1, rOb, modification);
  }

  ll left_max = get_max(2*cur, left, mid, lOb, mid, modification);
  ll right_max = get_max(2*cur + 1, mid + 1, right, mid + 1, rOb, modification);

  return std::max(left_max, right_max);
}

void update_below_max(ll cur) {
  cur/=2;
  while(cur > 0) {
    seg_tree[cur].below_max = std::max(seg_tree[cur*2].below_max, seg_tree[cur*2 + 1].below_max) + seg_tree[cur].people_c;
    cur /= 2;
  }
}

// adds value on the range to the current max and updates below_max
void update_range(ll cur, ll left, ll right, ll lOb, ll rOb, ll val) {
  if(left == lOb && right == rOb) {
    seg_tree[cur].below_max += val;
    seg_tree[cur].people_c += val;
    update_below_max(cur);
    return;
  }

  ll mid = (lOb + rOb) / 2;
  if (right <= mid) {
    return update_range(2*cur, left, right, lOb, mid, val);
  }
  if(left > mid) {
    return update_range(2*cur + 1, left, right, mid + 1, rOb, val);
  }

  update_range(2*cur, left, mid, lOb, mid, val);
  update_range(2*cur + 1, mid + 1, right, mid + 1, rOb, val);

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m>>z;
  // n = 8;
  create_tree();
  // update_range(1, 3, 5, 1, true_n, 3);
  // update_range(1, 5, 8, 1, true_n, 4);
  // update_range(1, 1, 3, 1, true_n, 2);
  // update_range(1, 4, 7, 1, true_n, 5);
  // print_tree();
  // std::cout<<"\n"<<get_max(1, 1, 5, 1, true_n, 0);

  while(z--) {
    ll p, k, l;
    std::cin>>p>>k>>l;
    if((m - get_max(1, p, k - 1, 1, true_n, 0)) >= l) {
      std::cout<<"T\n";
      update_range(1, p, k - 1, 1, true_n, l);
    } else {
      std::cout<<"N\n";
    }
  }

  // std::cout<<get_max(1, 1, 3, 1, true_n, 0);

  std::cout.flush();
}

void create_tree() {
  ll log_n = log2(n) + 1;
  true_n = 1 << log_n;
  seg_tree = vec<TNode>(2*true_n);
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
      std::cout<<"{ "<<seg_tree[j].below_max<<", "<<seg_tree[j].people_c<<" }  ";
    }
    
    std::cout<<"\n";
    previ *= 2;
    i *= 2;
  }
  for(int j = 0; j < true_n; j++) {
    std::cout<<"    "<<j+1<<"     ";
  } 
}