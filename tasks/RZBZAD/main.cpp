#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

enum Order {
  POST,
  PRE,
  IN
};

int d;
Order ord;

void dfs(ll n, int depth) {
  if(depth > d) return;
  
  if(ord == Order::PRE) std::cout<<n<<" ";
  dfs(n*2, depth + 1);
  if(ord == Order::IN) std::cout<<n<<" ";
  dfs(n*2 + 1, depth + 1);
  if(ord == Order::POST) std::cout<<n<<" ";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>d;
  str s;
  std::cin>>s;

  if(s == "PRE") {
    ord = Order::PRE;
  } else if(s == "IN") {
    ord = Order::IN;
  } else {
    ord = Order::POST;
  }

  dfs(1, 1);

  std::cout.flush();
}
