#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

vec<ll> buildings;

ll bin_search_max_in_range(ll from, ll to, ll max) {
  ll m;
  while(from + 1 < to) {
    m = (from + to) / 2;
    if(buildings[m] > max) {
      from = m;
    } else {
      to = m;
    }
  }
  return to;
}

ll bin_search_min_in_range(ll from, ll to, ll min) {
  ll m;
  while(from + 1 < to) {
    m = (from + to) / 2;
    if(buildings[m] < min) {
      to = m;
    } else {
      from = m;
    }
  }
  return from;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll m, D, G;
  std::cin>>m>>D>>G;

  buildings.push_back(-1);
  while (m--) {
    ll b;
    std::cin>>b;
    buildings.push_back(b);
  }

  str commands;
  std::cin>>commands;

  ll max_jump = 0;
  ll pos = 1;
  ll initial_pos = 1;
  ll cur_max;
  for (char c : commands) {
    initial_pos = pos;
    if (c == 'g') { //to the left
      cur_max = buildings[pos] + G;
      pos = bin_search_max_in_range(0, pos, cur_max);
      max_jump = std::max(max_jump, initial_pos - pos);
    } else { // to the right
      cur_max = buildings[pos] - D;
      pos = bin_search_min_in_range(pos, buildings.size(), cur_max);
      max_jump = std::max(max_jump, pos - initial_pos);
    }
  }
  std::cout<<pos<<" "<<max_jump;
  std::cout.flush();
}
