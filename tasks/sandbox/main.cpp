#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

str s;
int n;
int gcount = 0;

inline bool is_good_pair(int a, int b) {
  return s[a] != s[b];
}

void check_pair(int b, int e) {
  while(b >= 0 && e < n && is_good_pair(b, e)) {
    cout<<"["<<b<<","<<e<<"]\n";
    b--;
    e++;
    gcount++;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  cin>>s;

  for(int i = 1; i < n; i++) {
    check_pair(i - 1, i);
  }

  cout<<gcount;


  cout.flush();
}