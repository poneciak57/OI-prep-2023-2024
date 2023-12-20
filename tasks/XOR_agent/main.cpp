#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef unsigned long long ull;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Record {
  ull val;
  bool done{false};
  unordered_map<ull, ull> options;
};

int n, m;
ull k;
vec<vec<Record>> mat;

ull ans(ull cur_xor, int x, int y) {
  if(mat[y][x].done) {
    if(mat[y][x].options.find(cur_xor) != mat[y][x].options.end()) return mat[y][x].options[cur_xor];
    return 0;
  }
  cur_xor = cur_xor xor mat[y][x].val;

  if(y == mat.size() - 1) return ans(cur_xor, x + 1, y);
  if(x == mat[0].size() - 1) return ans(cur_xor, x, y + 1);

  return ans(cur_xor, x + 1, y) + ans(cur_xor, x, y + 1);
}

void take_options(int x_from, int y_from, int x_to, int y_to) {
  mat[y_to][x_to].done = true;
  for(auto &[xor_res, count] : mat[y_from][x_from].options) {
    mat[y_to][x_to].options[xor_res xor mat[y_to][x_to].val] += count;
  }
}

void preparation() {
  mat[n - 1][m - 1].options[mat[n - 1][m - 1].val xor k]++;
  mat[n - 1][m - 1].done = true;
  if(!(n >= 2 && m >= 2)) return; 

  // first col from right and first row from bottom
  for(int i = n - 2; i >= 0; i--) {
    take_options(m - 1, i + 1, m - 1, i);
  }
  for(int i = m - 2; i >= 0; i--) {
    take_options(i + 1, n - 1, i, n - 1);
  }

  for(int i = n - 2; i >= 1; i--) {
    for(int j = m - 2; j >= (n - 1 - i); j--) {
      take_options(j + 1, i, j, i);
      take_options(j, i + 1, j, i);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>k;
  mat = vec<vec<Record>>(n, vec<Record>(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin>>mat[i][j].val;
    }
  }
  preparation();
  cout<<ans(0, 0, 0);

  cout.flush();
}
