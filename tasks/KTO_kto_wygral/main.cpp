#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int algosia[12];
int bajtek[12];

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  for(int i = 0, tmp; i < 18; i++) {
    cin>>tmp;
    algosia[tmp]++;
    algosia[11]+=tmp;
  }

  for(int i = 0, tmp; i < 18; i++) {
    cin>>tmp;
    bajtek[tmp]++;
    bajtek[11]+=tmp;
  }

  int i = 11;
  while(i > 0) {
    if(algosia[i] > bajtek[i]) {
      cout<<"Algosia";
      return 0;
    } else if(bajtek[i] > algosia[i]) {
      cout<<"Bajtek";
      return 0;
    }
    i--;
  }

  cout<<"remis";
  cout.flush();
}