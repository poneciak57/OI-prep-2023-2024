#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

str s;

int find_first() {

};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int sum = 0;
  while(cin>>s) {
    int c = 0;
    int i = 0;
    
    while(s[i] > 57) {
      i++;
    }
    c += (s[i] - '0') * 10;
    i = s.size() - 1;
    while(s[i] > 57) {
      i--;
    }
    c += (s[i] - '0');
    sum += c;
  }

  std::cout<<sum;

  cout.flush();
}
