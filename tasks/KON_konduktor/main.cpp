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

struct Segment {
  int ind;
  vec<int> ranges;
};

vec<Range> ranges;

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

    while(n--) {
      int from, to;
      cin>>from>>to;
      ranges.push_back({from, to});
    }

    sort(ranges.begin(), ranges.end(), [](Range &r1, Range &r2) { return r1.to < r2.to; });

    int last_from = -1;
    int last_to = -1;
    int last_ind = -1;

    // usuwanie przedziałów które obejmują w całości mniejsze przedziały
    for(int i = 0; i < ranges.size(); i++) {
      auto &[from, to] = ranges[i];
      if(from >= last_to) {
        last_to = to;
        last_from = from;
        last_ind = i;
      } else if(from <= last_from && last_ind != i) {
        ranges.erase(ranges.begin() + i);
        i--;
      }
    }

    last_to = -1;
    vec<Segment> segments;
    // podzielenie tras na segmenty w zaleznosci od wybranych tras
    // ilosc wybranych tras to pierwsza odpowiedz
    for(int i = 0; i < ranges.size(); i++) {
      auto &[from, to] = ranges[i];
      if(from >= last_to) {
        segments.push_back({i});
      } else {
        segments.back().ranges.push_back(i);
      }
    }




  }

  cout.flush();
}
