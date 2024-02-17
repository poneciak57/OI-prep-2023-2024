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

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  vec<Range> ranges;

  while(n--) {
    int from, to;
    cin>>from>>to;
    ranges.push_back({from, to});
  }

  sort(ranges.begin(), ranges.end(), [](Range &r1, Range &r2) { return r1.from < r2.from; });


  Range curr = {
    ranges.front().from,
    ranges.front().to
  };

  for(auto r : ranges) {
    if(r.from <= curr.to) {
      curr.to = max(curr.to, r.to);
    } else {
      cout<<curr.from<<" "<<curr.to<<"\n";
      curr = r;
    }
  }
  cout<<curr.from<<" "<<curr.to<<"\n";

  cout.flush();
}
