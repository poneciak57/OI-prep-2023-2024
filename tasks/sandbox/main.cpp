#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  int n = 300;
  vec<str> answers;
  for(int i = 0; i < n; i++) {
    str s;
    std::cin>>s;
    vec<bool> is_in_text(26, false);
    bool flag = true;
    for(auto c : s) {
      if(is_in_text[c - 'A']) {
        flag = false;
        break;
      }
      is_in_text[c - 'A'] = true;
    }
    if(flag) {
      answers.push_back(s);
    }
  }

  std::sort(answers.begin(), answers.end());
  std::cout<<answers.size()<<" "<<answers.back();

  std::cout.flush();
}
