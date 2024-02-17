#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Lower {
  bool operator()(pair<int, int> p1, pair<int, int> p2) {
    return p1.first < p2.first;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, s;
  cin>>n>>s;

  vec<vec<int>> nums(s);
  for(int i = 1; i <= n; i++) {
    int tmp;
    std::cin>>tmp;
    tmp = (tmp + 1) % s;
    nums[tmp].push_back(i);
  }

  // {count, num}
  priority_queue<pair<int, int>, vec<pair<int, int>>, Lower> pq;

  for(int i = 1; i < nums.size(); i++) {
    if(nums[i].size() > 0) {
      pq.push({nums[i].size(), i});
    }
  }

  int c = 0;
  int cur_mod = 0;
  while(!pq.empty()) {
    auto [count, node] = pq.top();
    pq.pop();

    if((cur_mod + node) % s != (s - 1)) {
      cur_mod = (cur_mod + node) % s;
      nums[0].push_back(nums[node][count-1]);
      if(count - 1 > 0) {
        pq.push({count - 1, node});
      }
    } else {
      if(!pq.empty()) {
        auto [ncount, nnode] = pq.top();
        pq.pop();
        cur_mod = (cur_mod + nnode) % s;
        nums[0].push_back(nums[nnode][ncount-1]);
        if(ncount - 1 > 0) {
          pq.push({ncount - 1, nnode});
        }
        pq.push({count, node});

      } else {
        c += (count != 1);
        cur_mod = 0;
        nums[0].push_back(nums[node][count-1]);

        if(count - 1 > 0) {
          pq.push({count - 1, node});
        }
      }
    }
  }

  std::cout<<c<<"\n";
  for(auto n : nums[0]) {
    std::cout<<n<<" ";
  }

  cout.flush();
}
