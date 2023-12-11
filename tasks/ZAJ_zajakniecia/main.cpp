#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, m;

vec<int> t1, t2;

vec<int> prev1;
vec<int> prev2;

void read_inp() {
  prev1 = vec<int>(n + 1, 0);
  prev2 = vec<int>(m + 1, 0);
  t1 = vec<int>(n + 1, 0);
  t2 = vec<int>(m + 1, 0); 
  int tmp;

  for(int i = 1; i <= n; i++) {
    cin>>tmp;
    t1[i] = tmp;
    for(int j = i - 1; j > 0; j--) {
      if(t1[j] == t1[i]) {
        prev1[i] = j;
        break;
      }
    }
  }

  for(int i = 1; i <= m; i++) {
    cin>>tmp;
    t2[i] = tmp;
    for(int j = i - 1; j > 0; j--) {
      if(t2[j] == t2[i]) {
        prev2[i] = j;
        break;
      }
    }
  }
}

int countLCS() {
  vec<vec<int>> LCS(2, vec<int>(m + 1, 0));
  vec<int> memo(m + 1, 0);

  for(int i = 1; i <= n; i++) {
    int imod = i % 2;
    LCS[imod][0] = 0;
    for(int j = 1; j <= m; j++) {
      if(t1[i] == t2[j] && prev1[i] > 0 && prev2[j] > 0) {
        LCS[imod][j] = memo[prev2[j]] + 2;
      } else {
        LCS[imod][j] = 0;
      }
      LCS[i][j] = max({LCS[(imod + 1)% 2][j], LCS[imod][j - 1], LCS[imod][j]});
    }

    for(int j = 1; j <= m; j++) {
      if(t1[i] == t2[j]) {
        memo[j] = LCS[(imod + 1)% 2][j - 1];
      }
    }
  }
  return LCS[n % 2][m];
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;

  read_inp();

  cout<<countLCS();

  cout.flush();
}
