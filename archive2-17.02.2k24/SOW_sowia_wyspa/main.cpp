#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int M = 4 * 1000;
struct Sowa {
  int i;
  int j;
};


int n, m, m2;
vec<bitset<M>> shapes(M);
vec<Sowa> owls;
vec<vec<bool>> mat_vec;
bitset<M> mat;
vec<vec<char>> ret;
vec<pair<int,int>> moves = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

inline int get_pos(int i, int j) {
  return i * m2 + j;
}

inline int shift_to_shape(int pos, int initial_pos) {
  return pos - initial_pos + get_pos(n, m);
}

void get_shape(int sid, int sx, int sy) {
  queue<pair<int,int>> q;
  q.push({sx, sy});
  int ipos = get_pos(sx, sy);

  while(!q.empty()) {
    auto [x, y] = q.front();
    int cur = get_pos(x, y);
    int shifted = shift_to_shape(cur, ipos);
    q.pop();

    if(shapes[sid][shifted]) continue;
    shapes[sid][shifted] = true;

    for(auto [xm, ym] : moves) {
      xm += x;
      ym += y;
      if(!mat_vec[xm][ym] || shapes[sid][shift_to_shape(get_pos(xm, ym), ipos)]) continue;
      q.push({xm, ym});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  m2 = 2*m;
  ret = vec<vec<char>>(n + 1, vec<char>(m + 1, '.'));
  mat_vec = vec<vec<bool>>(n + 2, vec<bool>(m + 2, false));
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      char c;
      cin>>c;
      mat_vec[i][j] = c == 'S';
    }
  }
  
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(mat_vec[i][j]) {
        owls.push_back({i, j});
        get_shape(owls.size() - 1, i, j);
      }
    }
  }

  for(int i = 0; i < owls.size(); i++) {
    ret[owls[i].i][owls[i].j] = 'S';
    for(int j = 0; j < owls.size(); j++) {
      if(i == j) continue;
      if((shapes[j] & shapes[i]) == shapes[i]) {
        ret[owls[i].i][owls[i].j] = 'x';
        break;
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cout<<ret[i][j];
    }
    cout<<"\n";
  }

}
