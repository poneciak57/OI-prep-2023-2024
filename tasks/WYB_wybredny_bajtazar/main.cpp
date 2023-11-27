#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<int> base_filtr = {0, 1, 2, 3, 4};

struct Node {
  ll age{-1};
  vec<int> counts{{0, 0, 0, 0, 0}};
  vec<int> base_count{{0, 0, 0, 0, 0}};
  vec<int> filtr{base_filtr};
};

ll n, m, true_n, tmp;
str s;

vec<Node> seg_tree;

void print_tree();
void create_tree();
ll get_count(ll node, char c, vec<int> &filter);
void propagate_filters(ll filter_age, vec<int> &filter, ll age, vec<int> &node_filter);

void update_counts(ll cur) {
  cur /= 2;
  while(cur > 0) {
    for(int j = 0; j < 5; j++) {
      seg_tree[cur].counts[j] = seg_tree[cur*2].counts[j] + seg_tree[cur*2 + 1].counts[j];
    }
    cur /= 2;
  }
}

ll modify(ll cur, char from, char to, vec<int> filter, ll filter_age, ll count, ll age) {
  propagate_filters(filter_age, filter, seg_tree[cur].age, seg_tree[cur].filtr);
  filter_age = std::max(filter_age, seg_tree[cur].age);
  if(count <= 0) {
    vec<int> new_counts(5, 0);
    for(int i = 0; i < 5; i++) {
      new_counts[filter[i]] += seg_tree[cur].counts[seg_tree[cur].filtr[i]];
    }
    seg_tree[cur].filtr = filter;
    seg_tree[cur].age = filter_age;
    seg_tree[cur].counts = new_counts;
    update_counts(cur);
    return 0;
  }
  // std::cout<<"cur: "<<cur<<" count: "<<count<<" get_count: "<<get_count(cur, from, filter)<<"\n";
  ll loc_count = get_count(cur, from, filter);
  if(loc_count > count) {
    seg_tree[cur].counts = seg_tree[cur].base_count;
    seg_tree[cur].filtr = base_filtr;
    seg_tree[cur].age = -1;
    // we need to get all from left or count from left
    ll count_left = modify(cur*2, from, to, filter, filter_age, count, age);
    // we need to get none from right or the rest 
    modify(cur*2 + 1, from, to, filter, filter_age, count - count_left, age);
  } else {
    // std::cout<<"here cur: "<<cur<<"\n";
    // here it means that count in cur is equal to count, theres no chance its lower
    // we need to apply filter here and propagate
    // propagate_filters(age, filter, seg_tree[cur]);
    vec<int> new_filter = base_filtr;
    vec<int> new_counts(5, 0);
    new_filter[from - 'a'] = to - 'a';
    propagate_filters(filter_age, filter, age, new_filter);

    for(int i = 0; i < 5; i++) {
      new_counts[filter[i]] += seg_tree[cur].counts[seg_tree[cur].filtr[i]];
    }
    seg_tree[cur].counts = new_counts;
    seg_tree[cur].filtr = filter;
    seg_tree[cur].age = age;
    update_counts(cur);
  }
  return loc_count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;
  std::cin>>s;

  create_tree();
  // print_tree();

  for(int i = 1; i <= m; i++) {
    ll count;
    char from, to;
    std::cin>>count>>from>>to;
    modify(1, from, to, base_filtr, -1, count, i);

    // print_tree();

  }

  // print_tree();
  for(int i = true_n; i < (true_n + n); i++) {
    auto filter = seg_tree[i].filtr;
    ll filter_age = seg_tree[i].age;
    ll cur = i/2;
    while(cur > 0) {
      propagate_filters(filter_age, filter, seg_tree[cur].age, seg_tree[cur].filtr);
      cur /= 2;
    }
    std::cout<<(char)(filter[s[i - true_n] - 'a'] + 'a');
  }

  std::cout.flush();
}

void propagate_filters(ll filter_age,  vec<int> &filter, ll age, vec<int> &node_filter) {

  if(age == -1){
    return;
  }

  vec<int> new_filtr(5);
  // vec<int> new_counts(5, 0);

  if(filter_age < age) {
    for(int i = 0; i < 5; i++) {
      new_filtr[i] = node_filter[filter[i]];
    }
  } else {
    for(int i = 0; i < 5; i++) {
      new_filtr[i] = filter[node_filter[i]];
      
    }
  }
  filter = new_filtr;
}

ll get_count(ll node, char c, vec<int> &filter) {
  ll count = 0;
  for(int i = 0; i < 5; i++) {
    if(filter[i] == (c - 'a')) {
      count += seg_tree[node].counts[i];
    }
  }
  return count;
}

void create_tree() {
  ll log_n = log2(n);
  true_n = 1 << log_n;
  if(true_n < n) {
    true_n *= 2;
  }

  seg_tree = vec<Node>(2*true_n);

  for(int i = true_n; i < true_n + n; i++) {
    seg_tree[i].counts[s[i - true_n] - 'a'] = 1;
    seg_tree[i].base_count[s[i - true_n] - 'a'] = 1;
  }

  for(int i = true_n - 1; i > 0; i--) {
    for(int j = 0; j < 5; j++) {
      seg_tree[i].counts[j] = seg_tree[i*2].counts[j] + seg_tree[i*2 + 1].counts[j];
    }
    seg_tree[i].base_count = seg_tree[i].counts;
  }
}


void print_tree() {
  ll previ = 1;
  ll i = 2;
  while (previ < 2*true_n)
  {
    for(int j = 0; j < (true_n - (i - previ))*15/2; j++) {
      std::cout<<" ";
    }
    for(int j = previ; j < i; j++) {
      std::cout<<"["<<seg_tree[j].counts[0]<<", "<<seg_tree[j].counts[1]<<", "<<seg_tree[j].counts[2]<<", "<<seg_tree[j].counts[3]<<", "<<seg_tree[j].counts[4]<<"] ";
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