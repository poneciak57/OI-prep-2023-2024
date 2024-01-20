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

/**
 * Posegregowac przedzialy konce i poczatki bez znaczenia
 * - z przedmiotów stworzyc operacje
 * Odpowiadanie:
 * - sprawdzic binsearchem lower bound poczatku przedzialu i sprawdzic nastepny czy jest w przedziale
 * - 
*/
int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n;
  cin>>n;

  map<int, set<int>> froms;
  // {c, {time, action}} => 1 - add, 2 - delete
  vec<pair<int, pair<int,int>>> actions;

  for(int i = 0; i < n; i++) {
    int c;
    ll from, to;
    cin>>c>>from>>to;
    // inp[i] = {c, from, to};
    actions.push_back({c, {from, 1}});
    actions.push_back({c, {to, 2}});
  }

  sort(actions.begin(), actions.end(), [](pair<int, pair<int,int>> n1, pair<int, pair<int,int>> n2){ return n1.second.first < n2.second.first;});

  multiset<int> t;
  for(auto [c, ac] : actions) {
    auto [time, action] = ac;
    if(action == 2) {
      t.erase(t.find(c));
    } else {
      t.insert(c);
    }
    
    set<int> tmp = {0};
    froms[time] = {0};
    for(auto e : t) {
      for(auto ef : tmp) {
        froms[time].insert(e + ef);
      }
      tmp = froms[time];
    }
  }

  // for(auto [k, v] : froms) {
  //   cout<<k<<" -> "<<"[ ";
  //   for(auto vv : v) {
  //     cout<<vv<<" ";
  //   }
  //   cout<<"]\n";
  // }

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