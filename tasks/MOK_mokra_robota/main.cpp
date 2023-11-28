#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

// max is 49
const int MAX_AMMOUNT = 50;

// list of hashes of tries 
// hash is b1*1 + b2*50 + b3*2500 + b4*125000;
vec<bool> was(7000000, false);

struct Buckets {
  int steps;
  int hash;
  vec<int> amounts;
};

// list of max amounts of buckets
Buckets max_buckets;
int wanted_hash;

int bfs() {
  std::queue<Buckets> q;

  int hash = 0;
  int mult = 1;
  for(auto a : max_buckets.amounts) {
    hash += a * mult;
    mult *= MAX_AMMOUNT;
  }
  max_buckets.hash = hash;
  max_buckets.steps = 0;
  q.push(max_buckets);

  while(!q.empty()) {
    auto buck = q.front();
    q.pop();

    if(was[buck.hash]) continue;
    if(buck.hash == wanted_hash) return buck.steps;

    was[buck.hash] = true;

    buck.steps++;

    // wylewanie calej wody
    for(int i = 0, mult = 1; i < buck.amounts.size(); i++, mult *= 50) {
      auto tmp = buck;
      tmp.hash -= tmp.amounts[i] * mult;
      tmp.amounts[i] = 0;
      if(!was[tmp.hash]) {
        q.push(tmp);
      }
    }

    // przelewanie z jednego do drugiego
    for(int i = 0, multi = 1; i < buck.amounts.size(); i++, multi *= 50) {
      auto tmp = buck;
      int amount_snap = tmp.amounts[i];
      tmp.hash -= tmp.amounts[i] * multi;
      tmp.amounts[i] = 0;
      for(int j = 0, multj = 1; j < buck.amounts.size(); j++, multj *= 50) {
        if(j != i) {
          auto tmp2 = tmp;
          if((amount_snap + tmp.amounts[j]) <= max_buckets.amounts[j]) {
            // if can fully empty
            tmp2.hash += amount_snap * multj;
            tmp2.amounts[j] += amount_snap;
          } else {
            // if cant we can just fill the next
            int diff = max_buckets.amounts[j] - tmp.amounts[j];
            tmp2.hash += diff * multj; // adding diff to j
            tmp2.hash += (amount_snap - diff) * multi; // adding back i
            tmp2.amounts[i] = amount_snap - diff;
            tmp2.amounts[j] = max_buckets.amounts[j];
          }
          if(!was[tmp2.hash]) {
            q.push(tmp2);
          }
        }
      }
    }

  }

  return -1;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  max_buckets.amounts = vec<int>(n);
  max_buckets.steps = 0;
  for(int i = 0, t; i < n; i++) {
    std::cin>>t;
    max_buckets.amounts[i] = t;
  }

  wanted_hash = 0;
  for(int i = 0, t, mult = 1; i < n; i++, mult*=50) {
    std::cin>>t;
    wanted_hash += t * mult;
  }

  int res = bfs();
  if (res == -1) {
    std::cout<<"NIE";
  } else {
    std::cout<<res;
  }

  std::cout.flush();
}
