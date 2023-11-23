#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

int need_to_be_used[1000007];
int used[1000007];
int not_passed;
bool is_not_complited[1000007];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;
  not_passed = m;
  
  vec<int> l(m);
  for(int i = 0, tmp; i < m; i++) {
    std::cin>>tmp;
    l[i] = tmp;
  }

  for(int i = 0, tmp; i < m; i++) {
    std::cin>>tmp;
    need_to_be_used[tmp] = l[i];
    is_not_complited[tmp] = true;
  }

  std::queue<int> q;
  int c = 0;
  for(int i = 0, cur; i < n; i++) {
    std::cin>>cur;
    used[cur]++;
    q.push(cur);
    if(!is_not_complited[cur]) {
      is_not_complited[cur] = true;
      not_passed++;
      while(used[cur] != need_to_be_used[cur]) {
        int top = q.front();
        q.pop();
        used[top]--;
        if(used[top] != need_to_be_used[top]) {
          is_not_complited[top] = true;
          if(used[top] == (need_to_be_used[top] - 1)) {
            not_passed++;
          }
        } else {
          is_not_complited[top] = false;
          not_passed--;
        }
      } 
    } else {
      if(used[cur] == need_to_be_used[cur]) {
        is_not_complited[cur] = false;
        not_passed--;
      }
    }

    if(not_passed == 0) {
      c++;
      int top = q.front();
      q.pop();
      used[top]--;
      is_not_complited[top] = true;
      not_passed = 1;
    }
  }

  std::cout<<c;

  std::cout.flush();
}
