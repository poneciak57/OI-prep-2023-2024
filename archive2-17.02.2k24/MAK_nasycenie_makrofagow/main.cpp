#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n;
vec<vec<int>> modifications;

void perform_for_temp(int starting_temp) {
  // [stopien][temperatura] = {minimum, modyfikacja}
  vec<vec<pair<int, int>>> mat(n + 1, vec<pair<int, int>>(50, {INT_MAX, 10}));
  mat[0][starting_temp] = {0, 0};

  // idac po stopniach
  for(int i = 1; i <= n; i++) {
    // dla kazdej modyfikacji szukamy minimum
    for(int mod : modifications[i]) {
      for(int j = 15; j <= 34; j++) {
        if(mat[i - 1][j - mod].second != 10) {
          if(mat[i][j].first > (mat[i - 1][j - mod].first + std::abs(mod))) {
            mat[i][j] = {(mat[i - 1][j - mod].first + std::abs(mod)), mod};
          }
        }
      }
    }
  }

  int min_v = INT_MAX;
  int min_temp = -1;
  for(int i = 15; i <= 34; i++) {
    if(mat[n][i].first < min_v) {
      min_v = mat[n][i].first;
      min_temp = i;
    }
  }

  if(min_temp == -1) {
    cout<<"NIE\n";  
    return;
  }

  vec<int> ans;
  int curr = min_temp;
  for(int i = n; i > 0; i--) {
    ans.push_back(mat[i][min_temp].second);
    min_temp -= mat[i][min_temp].second;
  }
  for(int i = ans.size() - 1; i >= 0; i--) {
    cout<<ans[i]<<" ";
  }
  cout<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  modifications = vec<vec<int>>(n + 1);

  str line;
  getline(cin, line);

  int i = 1;
  while(getline(cin, line)) {
    stringstream line_stream(line);
    int mod;
    while(line_stream>>mod) {
      modifications[i].push_back(mod);
    }
    i++;
  }

  for(int i = 15; i <= 34; i++) {
    perform_for_temp(i);
  }

  cout.flush();
}
