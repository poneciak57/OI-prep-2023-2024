#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// n - rzedy, m - kolumny
int n, m;
vec<vec<char>> img;
struct Info { char color { 'A' }; int waiting { 0 }; bool ok { false }; };
vec<Info> cols;
vec<Info> rows;


int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  img = vec<vec<char>>(n, vec<char>(m));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) cin>>img[i][j];
  }

  cols = vec<Info>(m); // K
  rows = vec<Info>(n); // R

  for(int i = 0; i < n; i++) {
    int lind = m;
    for(int j = 0; j < m; j++) {
      if(cols[j].color != img[i][j] || !cols[j].ok) {
        rows[i].color = img[i][j];
        lind = j + 1;
        break;
      }
    }
    for(int j = lind; j < m; j++) {
      if(rows[i].color != img[i][j]) {
        cols[j].color = img[i][j];
        cols[j].ok = true;
      }
    }
  }

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      rows[i].waiting += (img[i][j] == rows[i].color && img[i][j] != cols[j].color);
    }
  }

  for(int j = 0; j < m; j++) {
    for(int i = 0; i < n; i++) {
      cols[j].waiting += (img[i][j] != rows[i].color && img[i][j] == cols[j].color);
    }
  }

  // for(auto [col, w] : cols) {
  //   std::cout<<"("<<col<<","<<w<<") ";
  // }
  // std::cout<<"\n";
  // for(auto [col, w] : rows) {
  //   std::cout<<"("<<col<<","<<w<<") ";
  // }
  // std::cout<<"\n";

  // t = 1 -> kolumna
  // t = 2 -> rzad
  struct QEntry { int type; int id; };
  queue<QEntry> q;
  for(int i = 0; i < n; i++) if(rows[i].waiting == 0) q.push({2, i});
  for(int i = 0; i < m; i++) if(cols[i].waiting == 0) q.push({1, i});

  std::cout<<n + m<<"\n";
  while(!q.empty()) {
    auto [type, id] = q.front();
    q.pop();
    if(type == 1) {
      std::cout<<"K "<<id + 1<<" "<<cols[id].color<<"\n";
      for(int i = 0; i < n; i++) {
        if(img[i][id] != cols[id].color) {
          rows[i].waiting--;
          if(rows[i].waiting == 0) q.push({2, i});
        }
      }
    } else {
      std::cout<<"R "<<id + 1<<" "<<rows[id].color<<"\n";
      for(int i = 0; i < m; i++) {
        if(img[id][i] != rows[id].color) {
          cols[i].waiting--;
          if(cols[i].waiting == 0) q.push({1, i});
        }
      }
    }
  }

  std::cout.flush();
}