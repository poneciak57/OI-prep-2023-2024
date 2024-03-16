#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

// liczymy dla 5

int M = 5;
int n = 5;
int BASE = 1 * 2 * 3 * 4 * 5;

ll mult_ft(ll from, ll to) {
	ll wyn = 1;
	for(ll i = from; i <= to; i++) wyn *= i;
	return wyn;
}

ll combs_heura(int on_right) {
	ll frow = mult_ft(1, n - on_right - 1) * mult_ft(1, on_right);
	M = (n - on_right - 1);
	BASE = mult_ft(1, M);
	return frow * mult_ft(on_right + 2, n) / BASE;
}

ll count(int diff) {
	ll wyn = BASE;

	ll mult_top = 1;
	ll mult_bot = 1;
	for(int i = 1; i <= M; i++) {
		mult_bot *= i;
		mult_top *= i + diff;
		ll cur_w = mult_top * BASE / mult_bot;
		wyn += cur_w;
	}
	return wyn;
}

ll heura(int diff) {
	return mult_ft(diff + 2, diff + M + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// for(int i = 0; i < 500; i++) {
	// 	if(divm(i, 120, MOD1) == 233333338) {
	// 		cout<<i<<"\n";
	// 	}
	// }
	cout<<divm(364, 120, MOD1)<<"\n";

	cout<<combs_heura(4)<<"\n";
	cout<<combs_heura(3)<<"\n";
	cout<<combs_heura(2)<<"\n";
	cout<<combs_heura(1)<<"\n";
	cout<<combs_heura(0)<<"\n";

	// for(int i = 1; i < 100; i++) {
	// 	if(count(i) != heura(i)) {
	// 		cout<<"ERROR";
	// 		return 0;
	// 	}
	// 	// cout<<i<<" -> c: "<<count(i)<<" h: "<<heura(i)<<"\n";
	// }

	// cout<<"wszystkie testy zaliczone :)";
	cout.flush();
	return 0;
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