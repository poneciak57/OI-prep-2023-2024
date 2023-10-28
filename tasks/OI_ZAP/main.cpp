#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned int uint;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Lecture {
  uint num;
  uint start;
  uint end;
  bool is_pl = false;
};

// [0] = {0, 0, 0}
// [n + 1] = {0, INT_MAX, INT_MAX}
vec<Lecture> list;

// possible lectures
// - longest sequence of not overlaping lectures
// [0] = 0 //not lecture just start
// [last] = n + 1 //not lecture just end
vec<int> pl;

// Zadanie ZAP Kacper Poneta
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  uint t_start, t_end;
  list.push_back({0, 0, 0});
  for(uint i = 1; i <= n; i++) {
    std::cin>>t_start>>t_end;
    list.push_back({i, t_start, t_end});
  }

  std::sort(list.begin(), list.end(), [](const Lecture &l1, const Lecture &l2){ return l1.end < l2.end; });
  list.push_back({0, INT_MAX, INT_MAX});

  // for(auto l : list) {
  //   std::cout<<l.num<<" ";
  // }

  uint prev = 0;
  pl.push_back(0);
  for(int i = 1; i <= n; i++) {
    if(list[i].start >= prev) {
      list[i].is_pl = true;
      pl.push_back(i);
      prev = list[i].end;
    }
  }
  pl.push_back(n+1);


  //now for each lecture from pl (except first and last -> these are just bounds) we need to find replacement
  // if one lecture dont have replacement we set repl to that lecture num 
  // and each next lecture can be replaced by it so we skip searching part
  int repl = -1;
  vec<llPair> solves;
  for(int i = 1; i < (pl.size() - 1); i++) {
    // repl exists so we just print the rest of the sequence
    if(repl != -1) {
      solves.push_back({list[pl[i]].num, repl});
      continue;
    }

    uint start_bound_end = list[pl[i - 1]].end;
    uint end_bound_start = list[pl[i + 1]].start;
    uint curr_num = list[pl[i]].num;
    bool found = false;

    for(int j = pl[i + 1]; j > pl[i - 1]; j--) {
      if(!list[j].is_pl && list[j].end <= end_bound_start && list[j].start >= start_bound_end) {
        solves.push_back({curr_num, list[j].num});
        found = true;
        break;
      }
    }
    if(!found) {
      repl = curr_num;
    }
  }

  std::cout<<solves.size()<<"\n";
  
  for(auto &[a, b] : solves) {
    std::cout<<a<<" "<<b<<"\n";
  }

  std::cout.flush();
}
