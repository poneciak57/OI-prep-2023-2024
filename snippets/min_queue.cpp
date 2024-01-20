#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct MinQueue {
  // {v, how_many_before}
  typedef pair<int, int> Entry;
  deque<Entry> dq;
  Entry default_min = {INT_MAX, -1};
  
  Entry get_min() {
    if(dq.empty()) return default_min;
    return dq.front();
  }

  void push(int v) {
    int c = 0;
    while(!dq.empty() && dq.back().first >= v) {
      c += dq.back().second + 1;
      dq.pop_back();
    }
    dq.push_back({v, c});
  }

  void pop() {
    dq.front().second--;
    if(dq.front().second == -1) {
        dq.pop_front();
    }
  }
};