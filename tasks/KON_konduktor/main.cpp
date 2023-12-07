#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Range {
  int from;
  int to;
};

vec<Range> ranges;
vec<Range> ranges_final;

// szuka pierwszego indeksu przedziału ktory kończy się później niż dane from
int BS(int from) {
  int b = -1, e = ranges.size();
  int m;
  while(b + 1 < e) {
    int m = (b + e) / 2;
    if(ranges[m].to <= from) {
      b = m;
    } else {
      e = m;
    }
  }
  return e;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int z;
  cin>>z;

  while(z--) {
    int m, n;
    cin>>m>>n;
    ranges.clear();
    ranges_final.clear();
    while(n--) {
      int from, to;
      cin>>from>>to;
      ranges.push_back({from, to});
    }

    sort(ranges.begin(), ranges.end(), [](Range &r1, Range &r2) { return r1.to < r2.to; });

    // usuwanie przedziałów które obejmują w całości mniejsze przedziały
    // może być dość wolne w niektórych przypadkach
    for(int i = 0; i < ranges.size(); i++) {
      bool is_ok = true;
      for(int j = BS(ranges[i].from); j < i; j++) {
        if(ranges[i].from >= ranges[j].from) {
          is_ok = false;
          break;
        }
      }
      if(is_ok) {
        ranges_final.push_back(ranges[i]);
      }
    }
  }

  cout.flush();
}
