#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll det(llPair A, llPair B, llPair C) {
  return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
}

int n, q, c = 0;
vec<llPair> hull;

bool is_inside(llPair p) {
  if(det(hull[0], hull[n - 1], p) > 0 || det(hull[0], hull[1], p) < 0) return false;

  int b = 1, e = n - 1, m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(det(hull[0], hull[m], p) > 0) b = m;
    else e = m;
  }
  if(det(hull[b], hull[e], p) < 0 || det(hull[b], hull[0], p) > 0) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>q;
  hull = vec<llPair>(n);
  for(int i = 0; i < n; i++) cin>>hull[i].first>>hull[i].second;
  while(q--) {
    int x, y;
    cin>>x>>y;
    c += is_inside({x, y});
  }
  cout<<c;

  cout.flush();
}