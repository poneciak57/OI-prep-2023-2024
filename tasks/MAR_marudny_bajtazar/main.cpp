#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LOG = 18;

str s;
vec<unordered_map<str, int>> existing(LOG);

void delete_existing(int ind) {
  for(int i = 1; i < LOG; i++) {
    for(int j = 0; j < i; j++) {
      if(ind - j + i > s.size() || (ind - j) < 0) continue;
      str t = s.substr(ind - j, i);
      existing[i][t]--;
      // cout<<"Deleting: "<<t<<"\n";
      if(existing[i][t] <= 0) {
        // cout<<"Erasing!\n";
        existing[i].erase(t);
      }
    }
  }
}

int add_existing(int ind) {
  for(int i = 1; i < LOG; i++) {
    for(int j = 0; j < i; j++) {
      if(ind - j + i > s.size() || (ind - j) < 0) continue;
      existing[i][s.substr(ind - j, i)]++;
      // cout<<"Adding: "<<s.substr(ind - j, i)<<"\n";
    }
  }
  for(int i = 1; i < LOG; i++) {
    if(existing[i].size() < (1 << i)) return i;
  }
}

int add_initial() {
  for(int i = 0; i < s.size(); i++) {
    for(int j = 1; j < LOG && i + j <= s.size(); j++) {
      existing[j][s.substr(i, j)]++;
    }
  }
  for(int i = 1; i < LOG; i++) {
    if(existing[i].size() < (1 << i)) return i;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;
  cin>>s;

  cout<<add_initial()<<"\n";
  for(int i = 0; i < m; i++) {
    int ind;
    cin>>ind;
    delete_existing(ind - 1);
    if(s[ind - 1] == '1') s[ind - 1] = '0';
    else s[ind - 1] = '1';
    // cout<<"s: "<<s<<"\n";
    cout<<add_existing(ind - 1)<<"\n";
  }

  // for(int i = 0; i < 7; i++) {
  //   cout<<i<<": \n";
  //   for(auto [k, c] : existing[i]) {
  //     cout<<k<<" -> "<<c<<"\n";
  //   }
  // }


  cout.flush();
}
