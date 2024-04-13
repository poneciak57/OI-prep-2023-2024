#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Entry { int qid; int s; int w; };
int n, N, q;
vec<Entry> entries;
vec<int> ans;

set<int> es;
unordered_map<int, int> emp;
vec<int> seg_tree;
void init() {
  int ind = 1;
  for(auto e : es) emp[e] = ind++;
  N = 1;
  while(N < ind) N *= 2;
  seg_tree = vec<int>(2 * N, 0);
}
void change(int v, int mod) {
  v += N - 1;
  while(v > 0) {
    seg_tree[v] += mod;
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
void print_tree() {
  for(int i = 1; i < 2*N; i++) {
    cout<<seg_tree[i]<<" ";
  }
  cout<<"\n";
  for(auto [k, v] : emp) {
    cout<<k<<": "<<seg_tree[v + N - 1]<<" ";
  }
  cout<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>q;
  while(n--) {
    int s, w;
    cin>>s>>w;
    es.insert(s);
    entries.push_back({-1, s, w});
  }
  ans = vec<int>(q);
  for(int i = 0; i < q; i++) {
    int s, w;
    cin>>s>>w;
    es.insert(s);
    entries.push_back({i, s, w});
  }
  init();
  sort(entries.begin(), entries.end(), [](Entry e1, Entry e2) {
    return (e1.w < e2.w)
      || (e1.w == e2.w && e1.s > e2.s)
      || (e1.w == e2.w && e1.s == e2.s && e1.qid < e2.qid);
  });
  multiset<ll> boxes;

  for(auto [qid, s, w] : entries) {
    // std::cout<<"s: "<<s<<" w: "<<w<<" qid: "<<qid<<"\n";
    if(qid == -1) {
      boxes.insert(s);
      change(emp[s], 1);
      auto it = boxes.lower_bound(s);
      if(it != boxes.begin()) {
        --it;
        change(emp[*it], -1);
        boxes.erase(it);
      }
    } else {
      ans[qid] = sum(1, emp[s], N, 1, N);
    }
    // std::cout<<"[ ";
    // for(auto b : boxes) std::cout<<b<<" ";
    // std::cout<<"]\n";
    // print_tree();
  }

  for(int i = 0; i < q; i++) std::cout<<ans[i]<<"\n";

  std::cout.flush();
}