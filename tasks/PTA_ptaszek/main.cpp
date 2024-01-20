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
  typedef pair<int, int> Entry;
  // {index_v, v}
  deque<Entry> dq;

  Entry get_max() {
    return dq.front();
  }

  void push(Entry v) {
    while(!dq.empty() && dq.back().first <= v.first ) {
      dq.pop_back();
    }
    dq.push_back(v);
  }

  void pop() {
    dq.pop_front();
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, q, k;
  cin>>n;

  vec<int> d(n);
  vec<int> wyn(n);
  for(int i = 0; i < n; i++) {
    cin>>d[i];
  }

  cin>>q;
  while(q--) {
    cin>>k;
    // kolejka A przechowuje wyniki x
    // kolejka B przechowuje wyniki x + 1
    // gdy kolejka A bedzie pusta x++, swap(A, B)
    MaxQueue A, B;
    A.push({d[0], 0});
    wyn[0] = 0;
    for(int i = 1; i < n; i++) {
      auto max_v = A.get_max();
      if(max_v.first <= d[i]) {
        wyn[i] = wyn[max_v.second] + 1;
        B.push({d[i], i});
      } else {
        wyn[i] = wyn[max_v.second];
        A.push({d[i], i});
      }
      if(max_v.second <= i - k) {
        A.pop();
        if(A.dq.empty()) {
          swap(A, B);
        }
      }
    }
    cout<<wyn[n - 1]<<"\n";
  }

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