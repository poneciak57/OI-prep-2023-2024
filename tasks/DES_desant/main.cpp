#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll n, m;
// {a, b}, a -> gotowy, b -> nie gotowy
vec<pair<ll,ll>> moves;
ll tab;

void print_bits(ll num) {
	for(ll i = 0; i < n; i++) {
		if(num & (1LL << i)) cout<<1;
		else cout<<0;
	}
	cout<<"\n";
}

ll make_moves(ll end) {
  set<ll> anses;
  anses.insert(end);
  for(ll i = moves.size() - 1; i >= 0; i--) {
    auto [a, b] = moves[i];
	// swap(a, b); // odwracamy operacje
	vec<ll> to_ins;
  vec<ll> to_erase;
  for(auto v : anses) {
    ll apos = v & (1LL << a);
		ll bpos = v & (1LL << b);
		if(bpos && !apos) {
			// dodajemy opcje
			v &= ~(1LL << b);
			v |= (1LL << a);
			to_ins.push_back(v);
		} else if(apos && !bpos) {
      to_erase.push_back(v);
		}
  }
  for(auto te : to_erase) anses.erase(te);
	for(auto ti : to_ins) anses.insert(ti);
  }
  return anses.size();
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin >> n >> m;

  moves = vec<pair<ll,ll>>(m);

  for(int i = 0; i < m; i++) {
    ll a, b;
    cin>>a>>b; --a; --b;
    moves[i] = {a, b};
  }


  for(ll i = 1LL; i <= n; i++) {
    tab = (1LL << i) - 1LL;
	ll sum = 0;
	// cout<<"i: "<<i<<"\n";
    for(ll j = 0; j < (n - i + 1); j++) {
      ll tmp = tab << j;
	//   print_bits(tmp);
      sum += make_moves(tmp);
    //   anses.insert(res);
    }
    cout<<sum % 2<<" ";
  }

  cout.flush();
}