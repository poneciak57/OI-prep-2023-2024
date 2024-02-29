#include <bits/stdc++.h>
#define LL_INF 1000000000000000057

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LOG = 61;
int n, m, N;
unsigned long long k;
ll pows[LOG][121][121];
ll cur_pow[121][121];
ll mat[121][121];
ll tmp[121][121];
ll sums[LOG];

ll get_sum(ll (&pow)[121][121]) {
  ll sum = 0;
  for(int i = 0; i <= n; i++) sum = min(sum + pow[i][0] - mat[i][0], LL_INF);
  if(sum < 0) sum = LL_INF;
  return sum;
}

void prep_pows() {
  for(int i = 0; i <= N; i++) for(int j = 0; j <= N; j++) cur_pow[i][j] = mat[i][j];
  for(int i = 0; i <= N; i++) for(int j = 0; j <= N; j++) pows[0][i][j] = mat[i][j];

  for(unsigned long long i = 1; i < LOG; i++) {
    for(int x = 0; x <= N; x++) {
      for(int y = 0; y <= N; y++) {
        pows[i][x][y] = 0;
        for(int z = 0; z <= N; z++) {
          if(cur_pow[x][z] * cur_pow[z][y] < 0) pows[i][x][y] = LL_INF;
          else pows[i][x][y] = min(pows[i][x][y] + cur_pow[x][z] * cur_pow[z][y], LL_INF);
          if(pows[i][x][y] < 0) pows[i][x][y] = LL_INF;
        }
      }
    }
    for(int i = 0; i <= N; i++) for(int j = 0; j <= N; j++) cur_pow[i][j] = pows[i][i][j];
    sums[i] = get_sum(pows[i]);
  }
}


// z jakiegos powodu zbyt wolne
// minowac z INFem bo wartosc wychodzi poza long longa
int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>k;
  N = 3 * n;
  // [from][to]
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
  prep_pows();

  int i = LOG - 1;
  ll res[2][121][121];
  int resi = 0;
  while(sums[i] >= k) i--;
  for(int ii = 0; ii <= N; ii++) for(int j = 0; j <= N; j++) res[0][ii][j] = pows[i][ii][j];
  ll len = (1LL << i);
  for(;i >= 0; i--) {
    for(int x = 0; x <= N; x++) {
      for(int y = 0; y <= N; y++) {
        res[(resi + 1) % 2][x][y] = 0;
        for(int z = 0; z <= N; z++) {
          if(res[resi][x][z] * pows[i][z][y] < 0) res[(resi + 1) % 2][x][y] = LL_INF;
          else res[(resi + 1) % 2][x][y] = min(res[(resi + 1) % 2][x][y] + res[resi][x][z] * pows[i][z][y], LL_INF);
          if(res[(resi + 1) % 2][x][y] < 0) res[(resi + 1) % 2][x][y] = LL_INF;
        }
      }
    }
    ll sum = get_sum(res[(resi + 1) % 2]);
    if(sum < k) {
      len += (1LL << i);
      resi = (resi + 1) % 2;
    }
  }
  if(len > k) cout<<-1;
  else cout<<len;
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
