#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


const ll MOVE = 1e6;
struct Line {
  ll a, b;
  ll operator()(ll x) { return a * (x - MOVE) + b; };
};
const ll NINF = (1e9 + 57) * -1;
int N, n;
vec<Line> seg_tree;
void init() {
  N = 1 << 21;
  seg_tree = vec<Line>(N * 2, {0, NINF});
}
void add(int cur, int left, int right, Line line) {
  int mid = (left + right) / 2;
  if(line(mid) > seg_tree[cur](mid)) swap(seg_tree[cur], line);
  if(left == right) return;
  if(line(left) > seg_tree[cur](left)) add(cur * 2, left, mid, line);
  if(line(right) > seg_tree[cur](right)) add(cur * 2 + 1, mid + 1, right, line);
}
ll get_max(int x) {
  x += MOVE;
  int v = x + N - 1;
  ll maxv = NINF;
  while(v > 0) {
    maxv = max(seg_tree[v](x), maxv);
    v /= 2;
  }
  return maxv;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll sum = 0;
  vec<ll> psums; // [1; n]
  vec<ll> vals;
  cin>>n;
  psums = vec<ll>(n + 2, 0);
  vals = vec<ll>(n + 1);
  for(int i = 1; i <= n; i++) {
    ll tmp;
    cin>>tmp;
    sum += tmp * i;
    vals[i] = tmp;
    psums[i] = tmp;
  }
  for(int i = 1; i <= n; i++) psums[i] += psums[i - 1];

  ll maxv = 0;
  init();
  for(int i = n; i >= 1; i--) {
    ll maxline = get_max(vals[i]) + psums[i] - vals[i] * i;
    maxv = max(maxv, maxline);
    add(1, 1, N, {i, psums[i] * -1LL});
  }
  init();
  for(int i = 1; i <= n; i++) {
    ll maxline = get_max(vals[i]) + psums[i - 1] - vals[i] * i;
    maxv = max(maxv, maxline);
    add(1, 1, N, {i, psums[i - 1] * -1LL});
  }

  cout<<sum + maxv;

  cout.flush();
}