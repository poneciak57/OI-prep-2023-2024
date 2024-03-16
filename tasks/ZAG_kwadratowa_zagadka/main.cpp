#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// rows
int cols[100];
int colss[100];
vec<vec<int>> tab;

vec<int> V[107];
int mt[107], odw[107], ski[107];

bool DFS(int v) {
  if(odw[v]) return false;
  odw[v] = 1;
  for(auto e : V[v]) {
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

  int n;
  cin>>n;
  tab = vec<vec<int>>(n, vec<int>(n));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cols[i * n + j] = j;
      if(j == 0) colss[i * n + j] = 30;
      else colss[i * n + j] = j;
    }
  }

  // {row, col}
  vec<pair<int,int>> zero_col_rels;

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin>>tab[i][j];
      if(cols[tab[i][j]] == 0) zero_col_rels.push_back({tab[i][j], j});
      else V[j].push_back(cols[tab[i][j]]);
    }
  }
  sort(zero_col_rels.begin(), zero_col_rels.end(), [](pair<int,int> p1, pair<int,int> p2) { return p1.first < p2.first; });
  
  vec<vec<int>> nt(n, vec<int>(n));

  for(int j = 0; j < n; j++) {
    V[zero_col_rels[j].second].push_back(0);
    for(int i = 0; i <= n; i++) mt[i] = -1;
    for(int i = 0; i <= n; i++) ski[i] = 0;

    while(true) {
      for(int i = 0; i <= n; i++) odw[i] = 0;

      bool ok = false;
      for(int i = 0; i < n; i++) {
        if(!ski[i] && DFS(i)) {
          ski[i] = 1;
          ok = true;
          break;
        }
      }
      if(!ok) break;
    }

    for(int i = 0; i < n; i++) {
      if(mt[i] != -1) {
        int col = mt[i];
        int mint = INT_MAX;
        for(int ii = 0; ii < n; ii++) {
          if(cols[tab[ii][col]] == i && tab[ii][col] < mint) {
            mint = tab[ii][col];
          }
        }
        nt[j][col] = mint;
        cols[mint] = -1;
        V[mt[i]].erase(find(V[mt[i]].begin(), V[mt[i]].end(), i));
      }
    }
  }

  // for(auto row : nt) {
  //   for(auto w : row) cout<<w<<" ";
  //   cout<<"\n";
  // }
  cout<<n * 3 - 1<<"\n";
  for(int i = 0; i < n; i++) {
    cout<<"R ";
    for(int j = 0; j < n; j++) cout<<nt[j][i]<< " ";
    cout<<"\n";
  }

  for(int i = 0; i < n; i++) sort(nt[i].begin(), nt[i].end(), [&](int i1, int i2) { return colss[i1] < colss[i2]; });

  for(auto row : nt) {
    cout<<"D ";
    for(auto w : row) cout<<w<<" ";
    cout<<"\n";
  }

  // posortowac kolumny po wartosciach

  for(int i = 0; i < n - 1; i++) {
    vec<int> ans;
    for(int j = 0; j < n; j++) ans.push_back(nt[j][i]);
    sort(ans.begin(), ans.end());
    cout<<"R ";
    for(auto a : ans) cout<<a<<" ";
    cout<<"\n";
  }

  cout.flush();
}