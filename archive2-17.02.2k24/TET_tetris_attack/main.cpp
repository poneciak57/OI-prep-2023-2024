#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  vec<bool> is_in_d(n + 7, false);
  std::stack<int> stack_s;
  std::stack<int> stack_d;

  int ni = 2*n;
  while(ni--) {
    int t;
    std::cin>>t;
    stack_d.push(t);
  }

  while(!stack_d.empty()) {
    stack_s.push(stack_d.top());
    stack_d.pop();
  }

  // while(!stack_s.empty()) {
  //   std::cout<<stack_s.top()<<"\n";
  //   stack_s.pop();
  // }


  vec<int> moves;
  while(!stack_s.empty()) {
    int stop = stack_s.top();
    stack_s.pop();

    if(!is_in_d[stop]) {
      stack_d.push(stop);
      is_in_d[stop] = true;
    } else {
      int j = stack_d.size();
      int dtop = stack_d.top();
      stack_d.pop();
      is_in_d[dtop] = false;

      if(dtop != stop) {
        moves.push_back(j);
        stack_s.push(dtop);
        stack_s.push(stop);
      }

    }
  }

  std::cout<<moves.size()<<"\n";
  for(int m : moves) {
    std::cout<<m<<"\n";
  }

  std::cout.flush();
}
