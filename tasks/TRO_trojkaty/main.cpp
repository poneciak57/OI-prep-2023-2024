#include <bits/stdc++.h>
#define LL_INF 10000000000000007

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

  int tmp;
  vec<int> tab;
  while(cin>>tmp) {
    tab.push_back(tmp);
  }

  tab.pop_back();

  sort(tab.begin(), tab.end(), [](int &a, int &b) { return a > b;});

  bool flag = true;
  for(int i = 0; i < tab.size() - 2; i++) {
    if(tab[i] < tab[i + 1] + tab[i + 2]) {
      flag = false;
      cout<<tab[i]<<" "<<tab[i + 1]<<" "<<tab[i + 2]<<"\n";
      break;
    }
  }
  if(flag) {
    cout<<"NIE\n";
  }

  cout.flush();
}
