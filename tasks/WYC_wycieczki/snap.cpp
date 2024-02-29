#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LOG = 41;
int n, m, N;
unsigned long long k;
vec<vec<ll>> pows[LOG];
ll sums[LOG];

ll get_sum(vec<vec<ll>> &mat, vec<vec<ll>> &pow) {
  ll sum = 0;
  for(int i = 0; i <= n; i++) sum += pow[i][0] - mat[i][0];
  return sum;
}

void prep_pows(vec<vec<ll>> &mat) {
  vec<vec<ll>> cur_pow = mat;
  vec<vec<ll>> tmp(N + 1, vec<ll>(N + 1, 0));
  
  for(unsigned long long i = 0; i < LOG; i++) {
    for(int x = 0; x <= N; x++) {
      for(int y = 0; y <= N; y++) {
        tmp[x][y] = 0;
        for(int z = 0; z <= N; z++) {
          tmp[x][y] += cur_pow[x][z] * cur_pow[z][y];
        }
      }
    }
    cur_pow = tmp;
    pows[i] = cur_pow;
    sums[i] = get_sum(mat, pows[i]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>k;
  N = 3 * n;
  // [from][to]
  vec<vec<ll>> mat(N + 1, vec<ll>(N + 1, 0));
  for(int i = 0; i <= n; i++) mat[i][0] = 1;
  for(int i = 1; i <= n; i++) {
    mat[i][i + n]++;
    mat[i + n][i + 2 * n]++;
  }

  while(m--) {
    int a, b, c;
    cin>>a>>b>>c;
    if(c == 1) mat[a][b]++;
    else if(c == 2) mat[a + n][b]++;
    else mat[a + 2 * n][b]++;
    
  }
  prep_pows(mat);

  int i = LOG - 1;
  vec<vec<ll>> res;
  while(sums[i] >= k) i--;
  res = pows[i];
  ll len = (1LL << i);
  for(;i >= 0; i--) {
    vec<vec<ll>> nres(N + 1, vec<ll>(m + 1));
    for(int x = 0; x <= N; x++) {
      for(int y = 0; y <= N; y++) {
        nres[x][y] = 0;
        for(int z = 0; z <= N; z++) {
          nres[x][y] += res[x][z] * nres[z][y];
        }
      }
    }
    ll sum = get_sum(mat, nres);
    if(sum < k) {
      len += (1LL << i);
      res = nres;
    }
  }
  cout<<len+1;
  // ll b = 0, e = k + 7, m;
  // while(b + 1 < e) {
  //   m = (b + e) / 2;
  //   if(mat_pow(mat, m) >= k) e = m;
  //   else b = m; 
  // }
  // if(e > k) std::cout<<-1;
  // else std::cout<<e;

  std::cout.flush();
}
