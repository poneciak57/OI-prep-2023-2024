#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

str s1;
str s2;

bool rte(int t1_s, int t1_e, int t2_s, int t2_e) {
  if(t1_s == t1_e) {
    return s1[t1_s] == s2[t2_s];
  }
  int t1_m = (t1_s + t1_e)/2;
  int t2_m = (t2_s + t2_e)/2;

  return (rte(t1_s, t1_m, t2_s, t2_m) && rte(t1_m + 1, t1_e, t2_m + 1, t2_e)) 
    || (rte(t1_s, t1_m, t2_m + 1, t2_e) && rte(t1_m + 1, t1_e, t2_s, t2_m));
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>s1>>s2;
  if(rte(0, s1.size() - 1, 0, s2.size() - 1)) {
    std::cout<<"TAK";
  } else {
    std::cout<<"NIE";
  }

  std::cout.flush();
}
