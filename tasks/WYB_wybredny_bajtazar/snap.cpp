#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

/**
 * Problem:
 * Trzeba wykonywac operacje na przedziale w postaci zamiany danej ilosci lampek koloru `a` na kolor `b`
 * 
 * Pomysł:
 * Drzewo przedziałowe z propagacją.
 * - dostajemy operacje zamien l a b
 * - wyszukujemy idac w dół najmniejszego przedziału posiadającego daną ilość lampek o kolorze a
 * - idac w dół nakładamy wszystkie filtry na filtr bazowy podspód mianowicie filtr na górze jest najnowszy zatem na filtr niżej zakładamy nowy
 * - szukając sumy uwzględniamy filtr
 * - gdy znajdziemy wierzchołki modyfikujemy je i propagujemy wszystkie filtry od góry idąc w dół
 * 
 * podczas propagacji trzeba zwrócić uwage na date dwóch filtrów
*/

vec<int> base_filtr = {0, 1, 2, 3, 4};

struct Node {
  ll age{-1};
  vec<int> counts{{0, 0, 0, 0, 0}};
  vec<int> filtr{base_filtr};
};

ll n, m, true_n, tmp;
str s;

vec<Node> seg_tree;

void print_tree();
void create_tree();
void propagate_filters(ll last_age, vec<int> &filtr, Node &to_apply);
ll get_count(ll node, char c);

void update_counts(ll cur) {
  cur /= 2;
  while(cur > 0) {
    for(int j = 0; j < 5; j++) {
      seg_tree[cur].counts[j] = seg_tree[cur*2].counts[j] + seg_tree[cur*2 + 1].counts[j];
    }
    cur /= 2;
  }
}

void propagate_all_filters_to(ll cur) {
  cur /= 2;
  std::stack<ll> to_propagate;
  while(cur > 0) {
    to_propagate.push(cur);
    cur /= 2;
  }

  while(!to_propagate.empty()) {
    ll top = to_propagate.top();
    to_propagate.pop();
    auto &node = seg_tree[top];
    propagate_filters(node.age, node.filtr, seg_tree[top*2]);
    seg_tree[top*2].age = std::max(seg_tree[top*2].age, node.age);
    propagate_filters(node.age, node.filtr, seg_tree[top*2 + 1]);
    seg_tree[top*2 + 1].age = std::max(seg_tree[top*2 + 1].age, node.age);
    node.filtr = base_filtr;
    node.age = -1;
  }
}

void modify(ll cur, char from, char to, ll count, ll age) {
  if(count <= 0) {
    return;
  }
  std::cout<<"cur: "<<cur<<" count: "<<count<<" get_count: "<<get_count(cur, from)<<"\n";
  if(get_count(cur, from) > count) {
    ll count_left = seg_tree[cur*2].counts[from - 'a'];
    // we need to get all from left or count from left
    modify(cur*2, from, to, std::min(count, count_left), age);
    // we need to get none from right or the rest 
    modify(cur*2 + 1, from, to, count - count_left, age);
  } else {
    // std::cout<<"here cur: "<<cur<<"\n";
    // here it means that count in cur is equal to count, theres no chance its lower
    // we need to apply filter here and propagate
    propagate_all_filters_to(cur);
    vec<int> new_filtr = base_filtr;
    new_filtr[from - 'a'] = to - 'a';
    propagate_filters(age, new_filtr, seg_tree[cur]);
    seg_tree[cur].age = age;
    update_counts(cur);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;
  std::cin>>s;

  create_tree();
  print_tree();

  for(int i = 1; i <= 2; i++) {
    ll count;
    char from, to;
    std::cin>>count>>from>>to;
    modify(1, from, to, count, m);

    print_tree();

  }

  // print_tree();
  for(int i = true_n; i < (true_n + n); i++) {
    propagate_all_filters_to(i);
    std::cout<<(char)(seg_tree[i].filtr[s[i - true_n] - 'a'] + 'a');
  }

  std::cout.flush();
}

ll get_count(ll node, char c) {
  ll count = 0;
  for(int i = 0; i < 5; i++) {
    if(seg_tree[node].filtr[i] == (c - 'a')) {
      count += seg_tree[node].counts[i];
    }
  }
  return count;
}

void propagate_filters(ll age, vec<int> &filtr, Node &apply_on) {
  // std::cout<<"prop_filters\n";


  if(age == -1){
    return;
  }

  // std::cout<<"age: "<<age<<" apply_on.age: "<<apply_on.age<<"\n";
  // std::cout<<"filtr: [";
  // for(auto i : filtr) {
  //   std::cout<<i<<" ";
  // }
  // std::cout<<"]\n";

  // std::cout<<"count: [";
  // for(auto i : apply_on.counts) {
  //   std::cout<<i<<" ";
  // }
  // std::cout<<"]\n";

  // std::cout<<"apply_on.filtr: [";
  // for(auto i : apply_on.filtr) {
  //   std::cout<<i<<" ";
  // }
  // std::cout<<"]\n";

  vec<int> new_filtr(5);
  vec<int> new_counts(5, 0);

  if(age < apply_on.age) {
    // apply `to_apply.filter` on `filtr`
    for(int i = 0; i < 5; i++) {
      new_filtr[i] = apply_on.filtr[filtr[i]];
      new_counts[new_filtr[i]] += apply_on.counts[apply_on.filtr[i]];
    }
  } else {
    // apply `filtr` on `to_apply.filter`
    for(int i = 0; i < 5; i++) {
      new_filtr[i] = filtr[apply_on.filtr[i]];
      new_counts[new_filtr[i]] += apply_on.counts[apply_on.filtr[i]];
    }
  }
  apply_on.filtr = new_filtr;
  apply_on.counts = new_counts;

  // std::cout<<"new_count: [";
  // for(auto i : new_counts) {
  //   std::cout<<i<<" ";
  // }
  // std::cout<<"]\n";
  // std::cout<<"new_filtr: [";
  // for(auto i : new_filtr) {
  //   std::cout<<i<<" ";
  // }
  // std::cout<<"]\n";
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
  }

  for(int i = true_n - 1; i > 0; i--) {
    for(int j = 0; j < 5; j++) {
      seg_tree[i].counts[j] = seg_tree[i*2].counts[j] + seg_tree[i*2 + 1].counts[j];
    }
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