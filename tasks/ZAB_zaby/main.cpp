#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int wx, wy;
vec<vec<int>> mat;
vec<pair<int,int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vec<pair<int,int>> moves2 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};


int dijkstra(int sx, int sy, int ex, int ey) {
  vec<vec<int>> d(wy + 2, vec<int>(wx + 2, -1));
  struct QEntry {
    int x;
    int y;
    int dist;
  };
  // to odwrotna kolejka najwiekszy dystans jest na wierzchu (nie taka jak w typowym dijkstrze)
  struct Lower {
    bool operator()(QEntry &qe1, QEntry &qe2) {
      return qe1.dist < qe2.dist;
    }
  };
  priority_queue<QEntry, vec<QEntry>, Lower> pq;
  pq.push({sx, sy, mat[sy][sx]});
  d[sy][sx] = mat[sy][sx];

  while(!pq.empty()) {
    auto [x, y, dist] = pq.top();
    pq.pop();

    if(d[y][x] > dist) continue;
    if(x == ex && y == ey) return dist;

    // cout<<"x: "<<x<<"  y: "<<y<<"\n";

    for(auto m : moves) {
      int nx = x + m.first;
      int ny = y + m.second;
      int ndist = min(mat[ny][nx], dist);
      // cout<<"ndist: "<<ndist<<" d[ny][nx]: "<<d[ny][nx]<<"\n";
      if(ndist <= d[ny][nx] || mat[ny][nx] == INT_MAX) continue;
      d[ny][nx] = ndist;
      pq.push({nx, ny, ndist});
    }
  }


  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>wx>>wy;

  mat = vec<vec<int>>(wy + 2, vec<int>(wx + 2, INT_MAX));
  int sx, sy, ex, ey;
  cin>>sx>>sy>>ex>>ey;
  // sx = wx + 1 - sx;
  sy = wy + 1 - sy;
  // ex = wx + 1 - ex;
  ey = wy + 1 - ey;

  int o;
  cin>>o;

  struct QEntry {
    int x;
    int y;
    int xo;
    int yo;
  };
  queue<QEntry> q;
  while(o--) {
    int tx, ty;
    cin>>tx>>ty;
    // tx = wx + 1 - tx;
    ty = wy + 1 - ty;
    mat[ty][tx] = 0;
    q.push({tx, ty, tx, ty});
  }

  // wyznaczamy najmniejsza odleglosc od kazdego pola do odstraszacza
  while(!q.empty()) {
    auto [ox, oy, xo, yo] = q.front();
    q.pop();

    for(auto m : moves2) {
      int nox = ox + m.first;
      int noy = oy + m.second;
      int xd = abs(nox - xo);
      int yd = abs(noy - yo);
      int dist = xd * xd + yd * yd;
      if(mat[noy][nox] <= dist || nox == 0 || nox > wx || noy == 0 || noy > wy) continue;
      mat[noy][nox] = dist;
      q.push({nox, noy, xo, yo});
    }
  }
  // for(auto y : mat) {
  //   for(auto x : y) {
  //     cout<<x<<" ";
  //   }
  //   cout<<"\n";
  // }


  cout<<dijkstra(sx, sy, ex, ey);
  cout.flush();
}
