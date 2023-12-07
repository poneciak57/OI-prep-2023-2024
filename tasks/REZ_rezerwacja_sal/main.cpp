#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Lecture {
  int from;
  int to;
};

vec<Lecture> tab;
vec<int> times;

int bin_search(int from) {
  int b = -1, e = tab.size();
  int m;
  while(b + 1 < e) {
    m = (b + e)/2;
    if(tab[m].to > from) {
      e = m;
    } else {
      b = m;
    }
  } 
  return times[b];
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  std::cin>>n;

  tab.push_back({0, 0});

  while (n--)
  {
    int from, to;
    cin>>from>>to;
    tab.push_back({from, to});
  }

  sort(tab.begin(), tab.end(), [](Lecture &l1, Lecture &l2){ return l1.to < l2.to; });

  times = vec<int>(tab.size(), 0);

  int ov_max = 0;
  for(int i = 1; i < tab.size(); i++) {
    int max_prev = bin_search(tab[i].from);
    times[i] = max(tab[i].to - tab[i].from + max_prev, times[i - 1]);
    ov_max = max(times[i], ov_max);
  }
  std::cout<<ov_max;

  cout.flush();
}
