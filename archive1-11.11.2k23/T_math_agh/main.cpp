#include <bits/stdc++.h>
#include <cmath>
#include <string>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll aproach1(ll n) {
  if(n % 2 == 0) {
    if(n % 3 == 0) {
      return ((n - 1) * (n - 2)/2 - 1 - (n/2 - 2) * 3)/6; 
    } else {
      return ((n - 1) * (n - 2)/2 - (n/2 - 1) * 3)/6;
    }
  } else {
    if(n % 3 == 0) {
      return ((n - 1) * (n - 2)/2 - 1 - ((n - 1)/2 - 1) * 3)/6;
    } else {
      return ((n - 1) * (n - 2)/2 - ((n - 1)/2) * 3)/6;
    }
  }
}

ll aproach2(ll n) {
  ll sum = 0;
  for (ll i = 1; i <= (n/3 - 1); i++) {
    sum += ((n - i - 1)/2) - i;
  }
  return sum;
}

ll brute(ll n) {
    ll count = 0;

    // Zakładamy, że liczby są dodatnie
    for (ll i = 1; i <= n - 3; i++) {
        for (ll j = 1; j <= n - i; j++) {
            ll k = n - i - j;
            
            if (k > 0 && i != j && j != k && i != k) {
                count++;
            }
        }
    }

    return count/6;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll to;
  std::cin>>to;
  
  ll len = 10;
  for (ll i = 1; i < to; i++) {
    ll a1 = aproach1(i);
    ll brut = brute(i);
    std::cout<<i<<":\t\t"<<a1<<"\t"<<brut<<"\n";
  }

  std::cout.flush();
}
