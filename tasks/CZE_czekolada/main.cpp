#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Lower {
  bool operator() (int &a, int &b) {
    return a <= b;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m, t;
  std::cin>>n>>m;

  priority_queue<int, vec<int>, Lower> pqx;
  priority_queue<int, vec<int>, Lower> pqy;
  int xsum = 0, ysum = 0;

  for(int i = 1; i < n; i++) {
    std::cin>>t;
    xsum += t;
    pqx.push(t);
  }
  for(int i = 1; i < m; i++) {
    std::cin>>t;
    ysum += t;
    pqy.push(t);
  }

  int xmul = 1;
  int ymul = 1;
  int sum = 0;

  // std::cout<<pqx.top()<<"\n";
  // std::cout<<pqy.top()<<"\n";
  while(!pqx.empty() && !pqy.empty()) {
    int x_first = pqx.top() * (ymul);
    int y_first = pqy.top() * (xmul);
    if(x_first > y_first) {
      sum += pqx.top() * xmul;
      ymul ++;
      xsum -= pqx.top(); 
      pqx.pop();
    } else {
      sum += pqy.top() * ymul;
      xmul ++;
      ysum -= pqy.top(); 
      pqy.pop();
    }
  }

  sum += xsum * xmul;
  sum += ysum * ymul;
  std::cout<<sum;

  cout.flush();
}
