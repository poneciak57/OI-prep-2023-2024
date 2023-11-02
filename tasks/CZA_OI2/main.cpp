#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD = 1111111111111111111;
const ll d = 256;

ll hash(str &s) {
  ll hx;

  hx = 0;
  for(char c : s) {
    hx = (d*hx + c)%MOD;
  }
  return hx;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, k, a, b;
  std::cin>>n>>k>>a>>b;

  std::map<ll, str> m;

  str s;
  std::cin>>s;
  
  ll h = pow(d, k - 1);

  std::cout<<"h: "<<h<<"\n";

  str pref = s.substr(0, k);
  ll Hp = hash(pref);
  std::cout<<Hp<<"\n";
  m[Hp] = pref;
  ll i = k; 
  while((i + 1) < n) {
    Hp = ((Hp - (s[i - k] * h)) * d + s[i + 1])% MOD; 
    if(Hp < 0) {
      Hp += MOD;
    }
    std::cout<<s.substr(i - k + 1, k)<<" -> "<<Hp<<"\n";
    m[Hp] = s.substr(i - k, k);
    i++;
  }
  
  // for(auto &[hash, pref] : m) {
  //   std::cout<<pref<<" -> "<<hash<<"\n";
  // }
  

  std::cout.flush();
}
