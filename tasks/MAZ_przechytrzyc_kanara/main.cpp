#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;
typedef std::pair<int, int> Point;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, k;
vec<vec<int>> mat;
vec<Point> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct QEntry {
  Point p;
  int dist;
};

struct Greater {
  bool operator()(QEntry &qe1, QEntry &qe2) {
    return qe1.dist > qe2.dist;
  }
};

Point add_points(Point p1, Point p2) {
  return {p1.first + p2.first, p1.second + p2.second};
}

int v(Point p) {
  return mat[p.second][p.first];
}

bool dijkstra(Point from, Point to, int mkb) {
  vec<vec<int>> d(n + 2, vec<int>(n + 2, INT_MAX));
  priority_queue<QEntry, vec<QEntry>, Greater> pq;
  pq.push({from, mkb < v(from)});
  d[from.second][from.first] = mkb < v(from);

  // cout<<"dijkstra dla mkb: "<<mkb<<"\n"; 
  while(!pq.empty()) {
    auto [p, dist] = pq.top();
    // cout<<"v(p): "<<v(p)<<"\n";
    pq.pop();

    // jesli doszlismy do konca zwracamy
    if(p.first == to.first && p.second == to.second) return true;

    // jesli doszlismy do wierzcholka mniejszym kosztem
    if(d[p.second][p.first] < dist) continue;

    for(auto m : moves) {
      Point np = add_points(p, m);
      if(v(np) == -1) continue; // jesli wyszlismy poza zakres

      int ndist = dist + (mkb < v(np));
      if(ndist > k) continue; // jesli nie jestesmy w stanie dojsc do wierzcholka z uwagi na kare
      if(ndist < d[np.second][np.first]) { 
        d[np.second][np.first] = ndist;
        pq.push({np, ndist});
      }
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>k;
  mat = vec<vec<int>>(n + 2, vec<int>(n + 2, -1));
  int ax, ay, bx, by;
  cin>>ay>>ax>>by>>bx;

  set<int> secik;
  secik.insert(0);
  for(int i = 1; i <= n; i++) {
    for(int j = 1, tmp; j <= n; j++) {
      cin>>tmp;
      secik.insert(tmp);
      mat[i][j] = tmp;
    }
  }

  vec<int> opcje(secik.begin(), secik.end());
  int b = -1, e = opcje.size(), m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(dijkstra({ax, ay}, {bx, by}, opcje[m])) {
      e = m;
    } else {
      b = m;
    }
  }
  if(e == 0) {
    cout<<"TRIV";
  } else {
    cout<<opcje[e];
  }
  cout.flush();
}
