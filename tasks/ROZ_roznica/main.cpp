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

  int n;
  cin>>n;

  str s;
  cin>>s;

  // uzywam tutaj algorytmu kadane w tym samym czasie dla wszystkich liter
  vec<vec<int>> sums(26, vec<int>(26, 0));
  vec<vec<bool>> can_be(26, vec<bool>(26, false));
  vec<vec<bool>> was(26, vec<bool>(26, false));

  int res = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 26; j++) {
      sums[s[i] - 'a'][j]++;
    }
    for(int j = 0; j < 26; j++) {
      sums[j][s[i] - 'a']--;
      can_be[j][s[i] - 'a'] = true;
      if(sums[j][s[i] - 'a'] < 0) {
        sums[j][s[i] - 'a'] = 0;
        can_be[j][s[i] - 'a'] = false;
        was[j][s[i] - 'a'] = true;
      }
      if(can_be[s[i] - 'a'][j]) res = max(res, sums[s[i] - 'a'][j]);
      else if(was[s[i] - 'a'][j]) res = max(res, sums[s[i] - 'a'][j] - 1);

      if(can_be[j][s[i] - 'a']) res = max(res, sums[j][s[i] - 'a']);
      else if(was[j][s[i] - 'a']) res = max(res, sums[j][s[i] - 'a'] - 1);
    }
  }

  cout<<res;

  cout.flush();
}
