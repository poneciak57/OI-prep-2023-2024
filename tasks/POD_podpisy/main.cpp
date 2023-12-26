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

  int n;
  cin>>n;
  vec<vec<int>> graph(n + 1);
  // {node, dowodca}
  queue<pair<int,int>> q;
  // [node][dowodca]
  vec<vec<bool>> v(n + 1, vec<bool>(n + 1, false)); // czy juz zalatwione polecenie dla dowodcy
  vec<int> c(n + 1, 0); // ilosc dowodcow z ktorych ma polecenia

  for(int i = 1; i <= n; i++) {
    int m, t;
    cin>>m;
    if(m == 0) {
      q.push({i, i});
    }
    while(m--) {
      cin>>t;
      graph[t].push_back(i);
    }
  }

  while(!q.empty()) {
    auto [node, lid] = q.front();
    q.pop();

    for(auto rel : graph[node]) {
      if(!v[rel][lid]) {
        c[rel]++;
        v[rel][lid] = true;
        q.push({rel, lid});
      }
    }
  }

  bool found = false;
  for(int i = 1; i <= n; i++) {
    if(c[i] == 1) {
      cout<<i<<"\n";
      found = true;
    }
  }

  if(!found) {
    cout<<"BRAK";
  }

  cout.flush();
}
