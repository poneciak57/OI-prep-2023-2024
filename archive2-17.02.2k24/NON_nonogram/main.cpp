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

int n, m;
vec<int> cols;
vec<int> rows;
vec<vec<bool>> ret;

struct Higher {
  bool operator()(pair<int,int> &p1, pair<int,int> &p2) {
    return p1.first < p2.first;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;

  cols = vec<int>(m);
  rows = vec<int>(n);
  ret = vec<vec<bool>>(n, vec<bool>(m, false));

  for(int i = 0; i < n; i++) cin>>rows[i];
  for(int i = 0; i < m; i++) cin>>cols[i];

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      char c;
      cin>>c;
      if(c == '-') {
        ret[i][j] = true;
        cols[j]++;
        rows[i]++;
      }
    }
  }

  // {v, col_ind}
  priority_queue<pair<int,int>, vec<pair<int,int>>, Higher> pq;
  for(int i = 0; i < m; i++) {
    if(cols[i] == 0) continue;
    if(cols[i] < 0) {
      cout<<"NIE\n";
      return 0;
    } 
    pq.push({cols[i], i});
  }
  for(int i = 0; i < n; i++) {
    queue<pair<int, int>> q;
    int done = 0;
    while(!pq.empty() && done < rows[i]) {
      auto [v, col_id] = pq.top();
      pq.pop();
      if(v - 1 > 0) q.push({v - 1, col_id});
      done++;
      ret[i][col_id] = !ret[i][col_id];
    }
    if(done < rows[i]) {
      cout<<"NIE";
      return 0;
    }
    while(!q.empty()) {
      pq.push(q.front());
      q.pop();
    }
  }
  if(!pq.empty()) {
    cout<<"NIE";
    return 0;
  }
  cout<<"TAK\n";
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(ret[i][j]) cout<<"#";
      else cout<<".";
    }
    cout<<"\n";
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