#include <bits/stdc++.h>
#include <string>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll M[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

ll NWD(ll a, ll b)
{
  if(b == 0) return a;
  return NWD(b, a % b);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll q;
  std::cin>>q;
  while (q--) {
    str n;
    std::cin>>n;
    n = n.substr(n.find(".") + 1);
    ll n_caped = std::stoi(n);
    ll nwd = NWD(n_caped, M[n.length()]);
    if(n_caped == 0) {
      std::cout<<0<<"\n";
    } else {
      std::cout<<n_caped/nwd<<"/"<<M[n.length()]/nwd<<"\n";
    }
  }
  
  std::cout.flush();
}
