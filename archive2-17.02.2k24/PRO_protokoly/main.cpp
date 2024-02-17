#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll k, n, m, l;
  cin>>k>>n>>m>>l;

  ll ilosc_paczek = n/m;

  vec<ll> ans(m + 1);
  ans[0] = 1;
  for(int i = 1; i <= m; i++) {
    ans[i] = ans[i - 1] * k;
    if(i > l) {
      ans[i] -= ans[i - l] * (k - 1);
    } else if(i == l) {
      ans[i] -= ans[i - l] * k;
    }
  }


  ll res = log2(ans.back()) * (double)ilosc_paczek;
  cout<<res;


  cout.flush();
}
