#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, N;
vec<int> seg_tree;
vec<int> tab;
unordered_map<ll, int> um;

void init();
void inc(int cur, int left, int right, int lOb, int rOb) {
  if(left == lOb && right == rOb) {
    seg_tree[cur]++;
    return;
  }
  
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return inc(cur * 2, left, right, lOb, mid);
  if(left > mid) return inc(cur * 2 + 1, left, right, mid + 1, rOb);

  inc(cur * 2, left, mid, lOb, mid);
  inc(cur * 2 + 1, mid + 1, right, mid + 1, rOb);
}
void prop_all() {
  for(int i = 1; i <= N; i++) {
    int v = i + N - 1;
    while(v > 0) {
      tab[i] += seg_tree[v];
      v /= 2;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  init();

  for(int i = 0; i < n; i++) {
    ll tmp;
    cin>>tmp;
    um[tmp]++;
  }

  for(auto [k, v] : um) inc(1, 1, v, 1, N);
  prop_all();

  for(int i = 1; i <= n; i++) {
    int j = i;
    int sum = 0;
    while(j <= n) {
      sum += tab[j];
      j += i;
    }
    cout<<sum * i<<" ";
  }

  cout.flush();
}


void init() {
  N = 1;
  while (N < n) N *= 2;
  seg_tree = vec<int>(2 * N, 0);
  tab = vec<int>(N + 1, 0);
}