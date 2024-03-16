#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll h, w, n;
vec<ll> ds;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>h>>w>>n;
  ds = vec<ll>(n);
  for(int i = 0; i < n; i++) cin>>ds[i];

  if(h % ds[0] != 0 || w % ds[0] != 0) {
    cout<<-1;
    return 0;
  }

  // wartosc ile obrazow potrzeba do upakowania obrazami do gory zakladajac ze dany obraz jest najwiekszym
  vec<ll> dspu(n);

  for(int i = 0; i < n; i++) {
    ll sum = 0;
    ll mod = h;
    ll base = ds[i];
    for(int j = i; j >= 0; j--) {
      sum += (base / ds[j]) * (mod / ds[j]);
      mod = mod % ds[j];
    }
    dspu[i] = sum;
  }

  ll sum = 0;
  ll mod = w;
  for(int i = n - 1; i >= 0; i--) {
    sum += (mod / ds[i]) * dspu[i];
    mod = mod % ds[i];
  }
  cout<<sum;

  cout.flush();
}