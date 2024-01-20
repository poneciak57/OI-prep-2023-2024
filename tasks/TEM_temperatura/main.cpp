#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

struct MaxQueue {
  int size = 0;
  deque<pair<int,int>> dq;

  int get_max() {
    if(dq.empty()) return -1e9;
    return dq.front().first;
  }

  void push(int v) {
    int c = 0;
    while(!dq.empty() && dq.back().first <= v) {
      c += dq.back().second + 1;
      dq.pop_back();
    }
    dq.push_back({v, c});
    size++;
  }

  void pop() {
    dq.front().second--;
    size--;
    if(dq.front().second < 0) {
      dq.pop_front();
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n;
  cin>>n;

  MaxQueue mq;
  int max_res = 0;
  
  while(n--) {
    int from, to;
    cin>>from>>to;
    while(mq.get_max() > to) {
      mq.pop();
    }
    mq.push(from);
    max_res = max(max_res, mq.size);
  }

  cout<<max_res;

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}