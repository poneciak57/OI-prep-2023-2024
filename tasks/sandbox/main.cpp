#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1000000007;
const ll MOD2 = 1000992299;

vec<llPair> fib_hashes;
// vec<llPair> fib_sums; 
vec<llPair> pows;

void prepare_pows() {
  pows = vec<llPair>(5007);
  ll num1 = 1;
  ll num2 = 1;
  for(int i = 0; i < 5007; i++) {
    pows[i] = {num1, num2};
    num1 = (num1 * 10) % MOD1;
    num2 = (num2 * 10) % MOD2;
  }
}

void prepare_fibs() {
  fib_hashes = vec<llPair>(100000);
  fib_hashes[0] = {1, 1};
  fib_hashes[1] = {1, 1};
  for(int i = 2; i < fib_hashes.size(); i++) { 
    fib_hashes[i] = {
      (fib_hashes[i - 1].first + fib_hashes[i - 2].first) % MOD1,
      (fib_hashes[i - 1].second + fib_hashes[i - 2].second) % MOD2
    };
    // for(int j = 1; j < i; j++) {
    //   fib_sums.push_back({
    //     (fib_hashes[j].first + fib_hashes[i].first) % MOD1,
    //     (fib_hashes[j].second + fib_hashes[i].second) % MOD2
    //   });
    // }
  }
}

bool BS(ll hash1, ll hash2) {
  int b = -1, e = fib_hashes.size(), m;

  while(b + 1 < e) {
    m = (b + e) / 2;

    if(fib_hashes[m].first >= hash1) {
      e = m;
    } else {
      b = m;
    }
  }

  while(e < fib_hashes.size() && fib_hashes[e].first == hash1) {
    if(fib_hashes[e].second == hash2) {
      return true;
    }
    e++;
  }
  return false;
}



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  prepare_fibs();
  prepare_pows();
  
  str s;
  cin>>s;

  ll hash1 = 0;
  ll hash2 = 0;

  // hashing input
  for(int i = 0; i < s.size(); i++) {
    hash1 = (hash1 + (s[i] - '0') * pows[s.size() - 1 - i].first) % MOD1;
    hash2 = (hash2 + (s[i] - '0') * pows[s.size() - 1 - i].second) % MOD2;
  }

  bool found = false;
  sort(fib_hashes.begin(), fib_hashes.end(), [](llPair &p1, llPair &p2) { return p1.first < p2. first; });


  for(int i = 1; i < fib_hashes.size(); i++) {
    ll nhash1 = (hash1 - fib_hashes[i].first + MOD1) % MOD1;
    ll nhash2 = (hash2 - fib_hashes[i].second + MOD2) % MOD2;
    if(BS(nhash1, nhash2)) {
      found = true;
      break;
    }
  }


  if(found) {
    cout<<"TAK";
  } else {
    cout<<"NIE";
  }

  std::cout.flush();
}
