#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

vec<int> tab;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, q;
  cin>>n>>q;
  tab = vec<int>(n);

  for(int i = 0; i < n; i++) cin>>tab[i];

  if(n > 2000) {
    priority_queue<int> pq;
    for(auto t : tab) pq.push(t);
    while(q--) {
      int s, t, p;
      cin>>s>>t>>p;
      pq.push(p);
      cout<<pq.top()<<"\n";
      pq.pop();
    }
    return 0;
  }

  while(q--) {
    int s, t, p;
    cin>>s>>t>>p; --s; --t;

    for(int i = s; i != t; i = (i + 1) % n) {
      if(tab[i] > p) swap(tab[i], p);
      // cout<<"i: "<<i<<" p: "<<p<<"\n";
    }
    if(tab[t] > p) swap(tab[t], p);
    cout<<p<<"\n";
  }


  

  cout.flush();
}