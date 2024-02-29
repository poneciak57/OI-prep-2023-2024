#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Sniezka {
  ll l {LL_INF};
  ll r {LL_INF};
};
vec<Sniezka> ski;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll cl = 0, cr = 0, p = 0; // count left, count right, pos
  ll rl = 0, rr = 0; // [rl, rr] -> range
  // {count, {left, right}}
  vec<pair<ll, pair<int,int>>> tab;
  
  int n, q;
  cin>>n>>q;
  ski = vec<Sniezka>(n);
  ll prev;
  cin>>prev;
  for(int i = 1; i < n; i++) {
    ll tmp;
    cin>>tmp;
    tab.push_back({tmp - prev, {i - 1, i}});
    prev = tmp;
  }

  int ind = 0;
  sort(tab.begin(), tab.end());
  
  while(q--) {
    ll tmp;
    cin>>tmp;
    // cout<<"q: "<<tmp<<"\n";
    p += tmp;
    if(p > rr) {
      ll diff = p - rr;
      cr += diff;
      rr = p;
      ll call = cr + cl;
      while(ind < tab.size() && tab[ind].first <= call) {
        auto [left, right] = tab[ind].second;
        // cout<<"right  l: "<<left<<" r: "<<right<<"\n";
        ll c = tab[ind].first;
        ski[right].l = cl;
        ski[left].r = cr - (call - c);
        ind++;
      }
    }
    if(p < rl) {
      ll diff = rl - p;
      cl += diff;
      rl = p;
      ll call = cr + cl;
      while(ind < tab.size() && tab[ind].first <= call) {
        auto [left, right] = tab[ind].second;
        // cout<<"left  l: "<<left<<" r: "<<right<<"\n";
        ll c = tab[ind].first;
        ski[left].r = cr;
        ski[right].l = cl - (call - c);
        ind++;
      }
    }
  }
  for(auto s : ski) {
    cout<<min(s.l, cl) + min(s.r, cr)<<"\n";
  }

  cout.flush();
}
