#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, m, N;

// {num, count}
vec<pair<int,int>> seg_tree;
vec<vec<int>> counts;

void init();
pair<int, int> merge(pair<int, int> p1, pair<int, int> p2);

pair<int, int> get_candidate(int cur, int left, int right, int lOb, int rOb) {
  if(left == lOb && right == rOb) {
    return seg_tree[cur];
  }

  int mid = (lOb + rOb) / 2;
  if(right <= mid) return get_candidate(cur * 2, left, right, lOb, mid);
  if(left > mid) return get_candidate(cur * 2 + 1, left, right, mid + 1, rOb);

  auto p1 = get_candidate(cur * 2, left, mid, lOb, mid);
  auto p2 = get_candidate(cur * 2 + 1, mid + 1, right, mid + 1, rOb);

  return merge(p1, p2);
}

int get_count(int left, int right, int v) {
  int b = -1, e = counts[v].size() - 1, m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(counts[v][m] >= left) e = m;
    else b = m;
  }
  int lower = e;
  if(counts[v][lower] > right || counts[v][lower] < left) return 0;
  b = 0; e = counts[v].size();
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(counts[v][m] > right) e = m;
    else b = m;
  }
  if(counts[v][b] > right || counts[v][b] < left) return 0;
  return b - lower + 1;
}

int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>n>>m;
  init();

  // cout<<"[3, 7] 3?: "<<get_count(3, 7, 3)<<"\n";
  // cout<<"[1, 4] 1?: "<<get_count(1, 4, 1)<<"\n";
  // cout<<"[4, 6] 3?: "<<get_count(4, 6, 3)<<"\n";

  const int k = 26;
  
  while(m--) {
    int a, b;
    cin>>a>>b;
    // seg tree aproach
    auto p = get_candidate(1, a, b, 1, N);
    if(p.second == 0) {
      cout<<0<<"\n";
      continue;
    }
    int c = get_count(a, b, p.first);
    if(c >= 1 + (b - a + 1) / 2) {
      cout<<p.first<<"\n";
    } else {
      cout<<0<<"\n";
    }

    // randomizer aproach
    // int v = 0;
    // for(int i = 0; i < k; i++) {
    //   int r = rand_range(a, b);
    //   if(get_count(a, b, seg_tree[r + N - 1].first) >= 1 + (b - a + 1) / 2) {
    //     v = seg_tree[r + N - 1].first;
    //     break;
    //   }
    // }
    // cout<<v<<"\n";
  }

  cout.flush();
}

void init() {
  N = 1;
  while(N < n) N *= 2;

  seg_tree = vec<pair<int,int>>(2*N);
  counts = vec<vec<int>>(n + 1);

  for(int i = N; i < n + N; i++) {
    int t;
    cin>>t;
    seg_tree[i] = {t, 1};
    counts[t].push_back(i - N + 1);
  }

  for(int i = N - 1; i >= 1; i--) {
    seg_tree[i] = merge(seg_tree[i * 2], seg_tree[i * 2 + 1]);
  }
}

pair<int, int> merge(pair<int, int> p1, pair<int, int> p2) {
  auto [w1, k1] = p1;
  auto [w2, k2] = p2;
  int w, k;
  if(w1 == w2) {
    w = w1;
    k = k1 + k2;
  } else if(k1 > k2) {
    w = w1;
    k = k1 - k2;
  } else {
    w = w2;
    k = k2 - k1;
  }
  return {w, k};
}