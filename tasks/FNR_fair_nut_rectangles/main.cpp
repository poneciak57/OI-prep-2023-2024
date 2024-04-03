#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;


const ll INFF = 1e9 + 57;
const ll NINF = -1e9 - 57LL;
struct Line {
  ll a;
  ll b;
  ll operator()(ll x) { return a * x + b; }
};
int n, N;
struct E { ll x; ll y; ll a; };
vec<E> entries;
vec<ll> inds;
vec<Line> seg_tree;
void init() {
  N = 1;
  while(N < n) N *= 2;
  seg_tree = vec<Line>(N * 2, {NINF, NINF});
  entries = vec<E>(n);
  inds = vec<ll>(N, INFF);
}
void add(int cur, int left, int right, Line line) {
  int mid = (left + right) / 2;
  // cout<<"line: ("<<line.a<<","<<line.b<<")\n";
  // cout<<"["<<left<<","<<right<<"]\n";
  ll vmid = inds[mid - 1], vleft = inds[left - 1], vright = inds[right - 1];
  // cout<<"vmid: "<<vmid<<" vleft: "<<vleft<<" vright: " << vright<<"\n";
  if(seg_tree[cur](vmid) < line(vmid)) swap(seg_tree[cur], line);
  if(left == right) return;
  if(line(vleft) > seg_tree[cur](vleft)) add(cur * 2, left, mid, line);
  if(line(vright) > seg_tree[cur](vright)) add(cur * 2 + 1, mid + 1, right, line);
}
ll get_max(int x, int ind) {
  int v = ind + N;
  ll maxv = NINF;
  while(v > 0) {
    maxv = max(maxv, seg_tree[v](x));
    v /= 2;
  }
  return maxv;
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	std::cout.tie(nullptr);

  cin>>n;
  init();
  for(int i = 0; i < n; i++) {
    cin>>entries[i].x>>entries[i].y>>entries[i].a;
    inds[i] = entries[i].x;
  }
  sort(entries.begin(), entries.end(), [](E e1, E e2) { return e1.x > e2.x; });
  sort(inds.begin(), inds.end());
  ll maxv = NINF;
  for(int i = 0, revi = n - 1; i < n; i++, revi--) {
    auto &e = entries[i];
    ll maxcur = e.y * e.x - e.a;
    maxcur = max(maxcur, maxcur + get_max(e.x, revi));
    maxv = max(maxv, maxcur);
    add(1, 1, N, { -1 * e.y, maxcur});
  }
  std::cout<<maxv;

	std::cout.flush();
	return 0;
}