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
  if(n <= 1) {
    std::cout<<0;
    return 0;
  }

  uint t_start, t_end;
  list.push_back({0, 0, 0});
  for(uint i = 1; i <= n; i++) {
    std::cin>>t_start>>t_end;
    list.push_back({i, t_start, t_end});
  }

  std::sort(list.begin(), list.end(), [](const Lecture &l1, const Lecture &l2){ return l1.end < l2.end; });
  list.push_back({0, 0, INT_MAX});

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

  // for(auto p : pl) {
  //   std::cout<<list[p].num<<" ";
  // }
  // std::cout<<"\n";

  int repl = -1;
  bool flag = false;
  vec<llPair> solves;
  int prev_pick_main = INT_MAX;
  int prev_pick_repl = INT_MAX;
  for(int i = pl.size() - 2; i >= 1; i--) {

    if(repl != -1) {
      solves.push_back({list[pl[i]].num, repl});
      continue;
    }

    uint bound_right_main = prev_pick_repl;
    uint bound_right_repl = prev_pick_main;
    // uint bound_left = list[pl[i - 1]].end;

    uint min_bound = std::min(bound_right_main, bound_right_repl);


    int highest_start = list[pl[i - 1]].end;
    int hs_main_id = -1;
    for(int j = pl[i + 1]; j > pl[i - 1]; j--) {
      if(list[j].end <= min_bound && list[j].start >= highest_start) {
        highest_start = list[j].start;
        hs_main_id = j;
      }
    }
    highest_start = list[pl[i - 1]].end;
    int hs_repl_id = -1;
    for(int j = pl[i + 1]; j > pl[i - 1]; j--) {
      if(list[j].end <= bound_right_repl && list[j].start >= highest_start && j != hs_main_id) {
        highest_start = list[j].start;
        hs_repl_id = j;
      }
    }

    // std::cout<<"main: "<<list[hs_main_id].num<<"\n";
    // std::cout<<"repl: "<<list[hs_repl_id].num<<"\n";
    if(hs_main_id == -1 || hs_repl_id == -1) {
      //means we couldnt even find any replacment in given range
      repl = list[pl[i]].num;
      continue;
    }

    prev_pick_main = list[hs_main_id].start;
    prev_pick_repl = list[hs_repl_id].start;
    solves.push_back({list[hs_main_id].num, list[hs_repl_id].num});

  }

  std::cout<<solves.size()<<"\n";
  
  for(auto &[a, b] : solves) {
    std::cout<<a<<" "<<b<<"\n";
  }

  std::cout.flush();
}