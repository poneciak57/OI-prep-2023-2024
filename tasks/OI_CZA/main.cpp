#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD1 = 1000992299;
const ll MOD2 = 1e9 + 7;
// const ll MOD1 = 479001599;
// const ll MOD2 = 433494437;
// const ll MOD1 = 1000000000007;

const int POWS_COUNT = 1e6 + 7;
ll pows1[POWS_COUNT];
ll pows2[POWS_COUNT];

// [hash][13] is set to index when we already visited the hash
std::unordered_map<ll, std::unordered_map<char, int>> suffixes;

void prepare_pows();
ll hash1(str s);
ll hash2(str s);

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  prepare_pows();

  // n - text lenght
  // k - prefix size
  // a - print start
  // b - print end
  ll n, k, a, b;
  std::cin>>n>>k>>a>>b;

  str s = "";

  ll ni = 0;
  for(char c;ni < k; ni++) {
    std::cin>>c;
    s += c;
  }

  ll chash = hash1(s);
  ll chash2 = hash2(s);
  ll main_hash = chash * chash2;

  // now starting from the first suffix we are hashing the next suffixes
  for(char c; ni < n; ni++) {

    std::cin>>c;
    s += c;

    ll hash_without_first = divm((chash - (s[ni - k] - 'a' + 1) + MOD1) % MOD1, pows1[1], MOD1);
    ll hashed_current_letter = multm(s[ni] - 'a' + 1, pows1[k-1], MOD1);
    chash = (hash_without_first + hashed_current_letter) % MOD1;

    ll hash_without_first2 = divm((chash2 - (s[ni - k] - 'a' + 1) + MOD2) % MOD2, pows2[1], MOD2);
    ll hashed_current_letter2 = multm(s[ni] - 'a' + 1, pows2[k-1], MOD2);
    chash2 = (hash_without_first2 + hashed_current_letter2) % MOD2;
    
    suffixes[main_hash][c]++;
    main_hash = chash * chash2;
  }

  while(ni < b) {
    
    int maxc = 0;
    char c = 'a';

    // here add cycles and checking for cycles

    if(suffixes.find(main_hash) != suffixes.end()) {
      std::unordered_map<char, int> &suffs = suffixes[main_hash];
      if(suffs[13] != NULL) {
        // found cycle
        ll print_pos = std::max(a, (ll)s.length() + 1);
        ll prefix_start = suffs[13];
        ll loop_lenght = ni - prefix_start;
        ll print_pos_in_prefix = (print_pos - prefix_start - 1) % loop_lenght;

        while (print_pos <= b)
        {
          std::cout<<s[prefix_start + print_pos_in_prefix];
          print_pos_in_prefix++;
          print_pos_in_prefix %= loop_lenght;
          print_pos++;
        }
        
        break;
      }
      for(auto &[ch, count] : suffs) {
        if(count > maxc || (count == maxc && ch < c)) {
          maxc = count;
          c = ch;
        }
      }
    }
    suffixes[main_hash][13] = ni;
    s+=c;

    ll hash_without_first = divm((chash - (s[ni - k] - 'a' + 1) + MOD1) % MOD1, pows1[1], MOD1);
    ll hashed_current_letter = multm(s[ni] - 'a' + 1, pows1[k-1], MOD1);
    chash = (hash_without_first + hashed_current_letter) % MOD1;
    
    ll hash_without_first2 = divm((chash2 - (s[ni - k] - 'a' + 1) + MOD2) % MOD2, pows2[1], MOD2);
    ll hashed_current_letter2 = multm(s[ni] - 'a' + 1, pows2[k-1], MOD2);
    chash2 = (hash_without_first2 + hashed_current_letter2) % MOD2;

    main_hash = chash * chash2;
    ni++;
    if(ni >= a) {
      std::cout<<c;
    }
  } 



  std::cout.flush();
}


void prepare_pows() {
  for(ll i = 0, pow = 1; i < POWS_COUNT; i++, pow = (pow * 27)%MOD1) {
    pows1[i] = pow;
  }
  for(ll i = 0, pow = 1; i < POWS_COUNT; i++, pow = (pow * 27)%MOD2) {
    pows2[i] = pow;
  }
}

ll hash1(str s) {
  ll hash = 0;
  for(int i = 0; i < s.size(); i++) {
    hash = (hash + (s[i] - 'a' + 1) * pows1[i]) % MOD1;
  }
  return hash;
} 

ll hash2(str s) {
  ll hash = 0;
  for(int i = 0; i < s.size(); i++) {
    hash = (hash + (s[i] - 'a' + 1) * pows2[i]) % MOD2;
  }
  return hash;
} 

ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}