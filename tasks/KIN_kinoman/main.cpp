#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  ll sum{0};
  ll max_pref{0};
};

struct Movie {
  int coolnes;
  std::deque<int> occured;
};

int n, m, true_n, tmp;

vec<Node> seg_tree;
vec<int> days;
vec<Movie> movies;

void print_tree();
void create_tree();

void update_value(ll cur, ll val) {
  cur += true_n;
  seg_tree[cur].max_pref = val;
  seg_tree[cur].sum = val;

  cur /= 2;
  while(cur > 0) {
    seg_tree[cur].sum = seg_tree[cur*2].sum + seg_tree[cur*2 + 1].sum;
    seg_tree[cur].max_pref = std::max(seg_tree[cur*2].max_pref, seg_tree[cur*2].sum + seg_tree[cur*2 + 1].max_pref);
    cur /= 2;
  }
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  days = vec<int>(n);
  for(int i = 0; i < n; i++) {
    std::cin>>tmp;
    days[i] = tmp;
  }

  movies = vec<Movie>(m + 1);
  for(int i = 1; i <= m; i++) {
    std::cin>>tmp;
    movies[i].coolnes = tmp;
  }

  create_tree();
  // print_tree();

  ll cmax = seg_tree[1].max_pref;
  for(int i = 0; i < n; i++) {
    auto &movie = movies[days[i]];
    ll f_occur = movie.occured.front();
    // std::cout<<"f_occur: "<<f_occur<<" movie: "<<days[i]<<"\n";
    movie.occured.pop_front();
    update_value(f_occur, 0);
    if(movie.occured.size()) {
      ll s_occur = movie.occured.front();
      // std::cout<<"s_occur: "<<s_occur<<" movie: "<<days[i]<<"\n";
      movie.occured.pop_front();
      update_value(s_occur, movie.coolnes);
      if(movie.occured.size()) {
        update_value(movie.occured.front(), movie.coolnes * -1);
      }
      movie.occured.push_front(s_occur);
    }
    cmax = std::max(cmax, seg_tree[1].max_pref);
    // print_tree();
  }

  std::cout<<cmax;
  std::cout.flush();
}


void create_tree() {
  ll log_n = log2(n);
  true_n = 1 << log_n;
  if(true_n < n) {
    true_n *= 2;
  }

  seg_tree = vec<Node>(2*true_n);
  for(int i = true_n; i < (true_n + n); i++) {
    auto &movie = movies[days[i - true_n]];
    if(movie.occured.size() == 0) {
      seg_tree[i].max_pref = movie.coolnes;
    } else if (movie.occured.size() == 1) {
      seg_tree[i].max_pref = movie.coolnes * -1;
    } else {
      seg_tree[i].max_pref = 0;
    }
    seg_tree[i].sum = seg_tree[i].max_pref;

    movie.occured.push_back(i - true_n);
  }

  for(int i = true_n - 1; i > 0; i--) {
    seg_tree[i].sum = seg_tree[i*2].sum + seg_tree[i*2 + 1].sum;
    seg_tree[i].max_pref = std::max(seg_tree[i*2].max_pref, seg_tree[i*2].sum + seg_tree[i*2 + 1].max_pref);
  }
}

void print_tree() {
  ll previ = 1;
  ll i = 2;
  while (previ < 2*true_n)
  {
    for(int j = 0; j < (true_n - (i - previ))*10/2; j++) {
      std::cout<<" ";
    }
    for(int j = previ; j < i; j++) {
      std::cout<<"{ "<<seg_tree[j].sum<<", "<<seg_tree[j].max_pref<<" }  ";
    }
    
    std::cout<<"\n";
    previ *= 2;
    i *= 2;
  }
  for(int j = 0; j < true_n; j++) {
    std::cout<<"    "<<j+1<<"     ";
  } 
  std::cout<<"\n";
}