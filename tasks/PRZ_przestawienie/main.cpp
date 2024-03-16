#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

using namespace std;
typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

int n, m;
const int LIMM = 1e5 + 7;

vec<int> graph[LIMM];
int odw[LIMM], mt[LIMM], ski[LIMM];

bool DFS(int v) {
  if(odw[v]) return false;
  odw[v] = 1;
  for(auto e : graph[v]) {
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

  cin>>n>>m;
  for(int i = 0; i < n; i++) {
    for(int j = 0, tmp; j < m; j++) {
      cin>>tmp;
      graph[i].push_back(tmp);
    }
  }

  vec<vec<int>> ans_mat(n, vec<int>(m));

  for(int col = 0; col < m; col++) {
    for(int i = 0; i < LIMM; i++) mt[i] = -1;
    for(int i = 0; i < LIMM; i++) ski[i] = 0;

    int ans = 0;
    while(true) {
      for(int i = 0; i < LIMM; i++) odw[i] = 0;
      bool ok = false;
      for(int i = 0; i < n; i++) {
        if(!ski[i] && DFS(i)) {
          ski[i] = 1;
          ok = true;
          ans++;
          break;
        }
      }

      if(!ok) break;
    }

    if(ans < n) {
      cout<<"Nie";
      return 0;
    }
    for(int i = 0; i < LIMM; i++) {
      if(mt[i] != -1) {
        ans_mat[mt[i]][col] = i;
        graph[mt[i]].erase(find(graph[mt[i]].begin(), graph[mt[i]].end(), i));
      }
    }
  }

  cout<<"Tak\n";
  for(auto row : ans_mat) {
    for(auto w : row) cout<<w<<" ";
    cout<<"\n";
  }

  cout.flush();
}