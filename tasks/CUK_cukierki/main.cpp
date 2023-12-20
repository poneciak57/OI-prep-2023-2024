#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Range {
  int from;
  int to;
};

vec<Range> rangesss;
// num, count
map<int, int> mapa;

int add_to_rangesss(int num) {
  int b = 0, e = rangesss.size(), m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(rangesss[m].from <= num) {
      b = m;
    } else {
      e = m;
    }
  }
  mapa[num]++;
  if(b >= e) {
    rangesss.push_back({num, num});
  } else if(!(num <= rangesss[b].to && num >= rangesss[b].from)) {
    // cout<<"range[b]: {"<<rangesss[b].from<<","<<rangesss[b].to<<"}\n";
    if(num == rangesss[b].to + 1) {
      rangesss[b].to += 1;
      if(b + 1 < rangesss.size() && num == rangesss[b + 1].from - 1) {
        rangesss[b].to = rangesss[b + 1].to;
        rangesss.erase(rangesss.begin() + b + 1);
      }
    } else if(b + 1 < rangesss.size() && num == rangesss[b + 1].from - 1) {
      rangesss[b + 1].from -= 1;
    } else if(rangesss[b].from == num + 1) {
      rangesss[b].from = num;
    }else {
      if(rangesss[b].from > num) {
        rangesss.insert(rangesss.begin() + b, {num, num});
      } else {
        rangesss.insert(rangesss.begin() + b + 1, {num, num});
        b += 1;
      }
    }
  }

  return rangesss[b].to - rangesss[b].from + 1;
}

pair<int,int> delete_range(int num) {
  int b = 0, e = rangesss.size(), m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    if(rangesss[m].from <= num) {
      b = m;
    } else {
      e = m;
    }
  }
  mapa[num]--;
  if(mapa[num] == 0) {
    // cout<<"range[b]: {"<<rangesss[b].from<<","<<rangesss[b].to<<"}\n";
    int ret = rangesss[b].to - rangesss[b].from + 1;

    bool flag = false;
    if(rangesss[b].to == num) {
      flag = true;
      rangesss[b].to = num - 1;
    }
    if(rangesss[b].from == num) {
      flag = true;
      rangesss[b].from = num + 1;
    }
    if(rangesss[b].to - rangesss[b].from < 0) {
      rangesss.erase(rangesss.begin() + b);
      return {ret, 0};
    }
    if(flag) return {ret, ret - 1};

    rangesss.insert(rangesss.begin() + b + 1, {num + 1, rangesss[b].to});
    rangesss[b].to = num - 1;
    int new_range_max = max(rangesss[b].to - rangesss[b].from + 1, rangesss[b + 1].to - rangesss[b + 1].from + 1);
    return {ret, new_range_max};
  }
  return {0, 0};
}

void print_rangesss() {
  for(auto &[from, to] : rangesss) {
    std::cout<<"{"<<from<<","<<to<<"} ";
  }
  cout<<"\n";
}
void delete_print(int num) {
  auto [a, b] = delete_range(num);
  cout<<a<<","<<b<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);


  // cout<<add_to_rangesss(3)<<"\n";
  // cout<<add_to_rangesss(6)<<"\n";
  // cout<<add_to_rangesss(8)<<"\n";
  // print_rangesss();
  // cout<<add_to_rangesss(9)<<"\n";
  // cout<<add_to_rangesss(7)<<"\n";
  // cout<<add_to_rangesss(2)<<"\n";
  // print_rangesss();

  // delete_print(9);
  // delete_print(2);
  // print_rangesss();
  


  // return 0;





  int n, k;
  cin>>n>>k;

  queue<int> q;
  int min_range = INT_MAX;
  int min_b = -1, min_e = -1;
  for(int i = 1, tmp; i <= n; i++) {
    cin>>tmp;
    q.push(tmp);
    int range = add_to_rangesss(tmp);
    // print_rangesss();

    while(range >= k) {
      if(min_range > q.size()) {
        min_range = q.size();
        min_b = i - q.size() + 1;
        min_e = i;
      }
      // cout<<"delete: "<<q.front()<<endl;
      auto [deleted_r, max_from_it] = delete_range(q.front());
      // print_rangesss();
      // cout<<endl;
      q.pop();
      if(deleted_r == range) {
        range = max_from_it;
      }
    }
  }
  if(min_b == -1) {
    cout<<-1;
  } else {
    cout<<min_range<<"\n";
    cout<<min_b<<" "<<min_e;
  }

  cout.flush();
}