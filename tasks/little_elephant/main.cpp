#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Q {
  int start;
  int end;
  int ind;
  int ans;
};

int freq[100007];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m;
  std::cin>>n>>m;
  int sqrt_n = sqrt(n);
  vec<int> tab(n + 1);

  for(int i = 1, t; i <= n; i++) {
    std::cin>>t;
    tab[i] = t;
  }

  vec<Q> queries;
  for(int i = 0, qs, qe; i < m; i++) {
    std::cin>>qs>>qe;
    queries.push_back({qs, qe, i});
  }

  // sort according to Mo's algorithm
  std::sort(queries.begin(), queries.end(), [&sqrt_n](const Q &q1, const Q &q2) { return (q1.start/sqrt_n) <= (q2.start/sqrt_n) && q1.end < q2.end; });

  int ans = 0;
  int s = queries[0].start;
  int e = queries[0].end;
  for(int i = s; i <= e; i++) {
    if(tab[i] <= 100000) {
      freq[tab[i]]++;
      if(freq[tab[i]] == tab[i]) {
        ans++;
      } else if(freq[tab[i]] == (tab[i]+1)) {
        ans--;
      }
    }
  }
  queries[0].ans = ans;


  for(int i = 1; i < queries.size(); i++) {
    while(s < queries[i].start) {
      if(tab[s] <= 100000) {
        freq[tab[s]]--;
        if(freq[tab[s]] == tab[s]) {
          ans++;
        } else if(freq[tab[s]] == (tab[s] - 1)) {
          ans--;
        }
      }
      s++;
    }
    while(s > queries[i].start) {
      s--;
      if(tab[s] <= 100000) {
        freq[tab[s]]++;
        if(freq[tab[s]] == tab[s]) {
          ans++;
        } else if(freq[tab[s]] == (tab[s] + 1)) {
          ans--;
        }
      }
    }
    while(e > queries[i].end) {
      if(tab[e] <= 100000) {
        freq[tab[e]]--;
        if(freq[tab[e]] == tab[e]) {
          ans++;
        } else if(freq[tab[e]] == (tab[e] - 1)) {
          ans--;
        }
      }
      e--;
    }
    while(e < queries[i].end) {
      e++;
      if(tab[e] <= 100000) {
        freq[tab[e]]++;
        if(freq[tab[e]] == tab[e]) {
          ans++;
        } else if(freq[tab[e]] == (tab[e] + 1)) {
          ans--;
        }
      }
    }
    queries[i].ans = ans;
  }

  std::sort(queries.begin(), queries.end(), [](const Q &q1, const Q &q2){ return q1.ind < q2.ind; });

  for(auto &q : queries) {
    std::cout<<q.ans<<"\n";
  }


  std::cout.flush();
}
