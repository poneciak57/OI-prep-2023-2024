#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

void print_vec(vec<int> &v) {
  for (auto c : v) {
    std::cout<<c<<" ";
  }
} 

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  str s;
  std::cin>>s;

  int prev = 0;

  // pierwszy zakres jest do smieci bo nie zawiera samogloski
  vec<ll> ranges;

  ll count = -1;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    if(c == 'a' || c == 'e' || c == 'o' || c == 'y' || c == 'i' || c == 'u') {
      if(count == -1) {
        count = 1;
      } else {
        count *= i - prev + 1;
      }
      prev = i;
    }
  }
  count--;

  //print_vec(ranges);
  std::cout<<count;


  std::cout.flush();
}
