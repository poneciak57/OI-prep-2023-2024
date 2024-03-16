#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LIM = 5 * 1e5 + 7;

vec<pair<int,int>> V[LIM];
vec<int> ans;
int mt[LIM], ski[LIM], odw[LIM];

bool DFS(int v) {
  if(odw[v]) return false;
  odw[v] = 1;
  for(auto [e, id] : V[v]) {
    if(mt[e] == -1 || DFS(mt[e])) {
      mt[e] = v;
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int l, r, m;
  cin>>l>>r>>m;

  ans = vec<int>(m);
  int ind = 0;
  while(m--) {
    int a, b;
    cin>>a>>b; --a; --b;
    V[a].push_back({b, ind++});
  }

  int color = 1;
  while(true) {
    for(int i = 0; i < max(r, l); i++) {
      ski[i] = 0;
      mt[i] = -1;
    }

    while(true) {
      for(int i = 0; i < l; i++) odw[i] = 0;

      bool ok = false;
      for(int i = 0; i < l; i++) {
        if(!odw[i] && !ski[i] && DFS(i)) {
          ski[i] = 1;
          ok = true;
          false;
        }
      }

      if(!ok) break;
    }

    bool ok = false;
    for(int i = 0; i < r; i++) {
      if(mt[i] != -1) {
        ok = true;

        int v = mt[i];
        for(int j = 0; j < V[v].size(); j++) {
          if(V[v][j].first == i) {
            ans[V[v][j].second] = color;
            V[v].erase(V[v].begin() + j);
            break;
          }
        }
      }
    }
    if(!ok) break;
    else color++;
  }
  color--;
  cout<<color<<"\n";
  for(auto a : ans) cout<<a<<"\n";

  cout.flush();
}