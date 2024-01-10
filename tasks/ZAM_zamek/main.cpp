#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


struct Node {
  int x1;
  int y1;
  int x2;
  int y2;

  /**
   * D - default
   * B - blocked
   * P - begining
   * S - treasure
  */
  char state;

  vec<int> rels;
};

struct TN {
  int v;
  unordered_map<int, bool> below;
};

vec<Node> graph;


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int w, h, n, m;
  cin>>w>>h>>n>>m;

  cout.flush();
}
