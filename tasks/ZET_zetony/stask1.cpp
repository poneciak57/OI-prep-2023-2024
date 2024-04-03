#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int t, n, m, N;

vec<int> seg_tree;
void init() {
  N = 1;
  while(N < n) N *= 2;
  seg_tree = vec<int>(2 * N, 0);
}
void inc(int v) {
  v += N;
  while(v > 0) {
    seg_tree[v]++;
    v /= 2;
  }
}
int sum(int cur, int left, int right, int lOb, int rOb) {
  if(left == lOb && right == rOb) return seg_tree[cur];
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return sum(cur * 2, left, right, lOb, mid);
  if(left > mid) return sum(cur * 2 + 1, left, right, mid + 1, rOb);
  return sum(cur * 2, left, mid, lOb, mid) + sum(cur * 2 + 1, mid + 1, right, mid + 1, rOb);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>t;
  while(t--) {
    cin>>n;
    for(int i = 1, u, v; i < n; i++) cin>>u>>v;
    cin>>m;

    bool ok = true;
    vec<pair<int,int>> moves;
    while(m--) {
      // a -> b
      int a, b;
      cin>>a>>b; --a; --b;
      moves.push_back({a, b});
    }
    init();
    sort(moves.begin(), moves.end());
    int lastb = -1;
    for(auto [a, b] : moves) {
      if(b > a) {
        if(lastb >= b) ok = false;
        lastb = b;
        inc(b);
      } else {
        if(a <= lastb) ok = false;
        int s = sum(1, b + 1, a + 1, 1, N);
        inc(b);
        if(s > 0) ok = false;
      }
    }



    if(!ok) cout<<"Nie\n";
    else cout<<"Tak\n";
  }
  

  cout.flush();
}