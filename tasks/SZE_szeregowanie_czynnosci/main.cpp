#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Entry {
  ll a;
  ll b;
  int ind;
};

vec<Entry> tab;
vec<int> zeros;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  std::cin>>n;
  
  for(int i = 1; i <= n; i++) {
    double a, b;
    std::cin>>a>>b;
    ll al = a * 1000000;
    ll bl = b * 1000000;

    if(al == 0 && bl == 0) {
      zeros.push_back(i);
    } else {
      tab.push_back({al, bl, i});
    }
  }

  std::sort(tab.begin(), tab.end(), [](Entry &e1, Entry &e2) { return (e1.b*e2.a + e2.b - e2.b*e1.a - e1.b) < 0 ;});
  for(auto e : tab) {
    std::cout<<e.ind<<"\n";
  }

  for(auto z : zeros) {
    std::cout<<z<<"\n";
  }
  

  cout.flush();
}
