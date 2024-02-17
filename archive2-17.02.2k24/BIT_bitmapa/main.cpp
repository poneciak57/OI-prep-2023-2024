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

  int n, m;
  cin>>n>>m;

  vec<pair<int,int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  vec<vec<int>> mat(n + 2, vec<int>(m + 2, -1));
  vec<vec<int>> dists(n + 2, vec<int>(m + 2, -1));
  // [first][second]
  queue<pair<pair<int, int>, int>> q;

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      char c;
      cin>>c;
      if(c == '1') {
        q.push({{i + 1, j + 1}, 0});
        mat[i + 1][j + 1] = 1;
      }
      else mat[i + 1][j + 1] = 0;
    }
  }

  while(!q.empty()) {
    auto [xy, dist] = q.front();
    auto [x, y] = xy;
    q.pop();
    
    if(dists[x][y] == -1) dists[x][y] = dist;
    else continue;
    for(auto m : moves) {
      pair<int, int> npos = {x + m.first, y + m.second};
      if(mat[npos.first][npos.second] != -1) {
        q.push({npos, dist + 1});
      }
    }
  }
  
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cout<<dists[i][j]<<" ";
    }
    cout<<"\n";
  }

  cout.flush();
}
