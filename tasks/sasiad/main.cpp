#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int MOD = 53;
vec<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
vec<vec<bool>> is_compliant(MOD, vec<bool>(MOD, false));

void print_mat(vec<vec<int>> &mat) {
  for (auto row : mat) {
    for (auto v : row) {
      std::cout<<v<<" ";
    }
    std::cout<<"\n";
  }
}

bool are_compliant(int a, int b) {
  for (int p : primes) {
    if((a % p == 0 && b % p != 0) || (b % p == 0 && a % p != 0)) {
      return false;
    }
  }
  return true;
}

void prepare_compliants() {
  for (int i = 1; i < MOD; i++) {
    for(int j = i; j < MOD; j++) {
      if(are_compliant(i, j)) {
        is_compliant[i][j] = true;
        is_compliant[j][i] = true;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);


  int n, A;
  std::cin>>n;
  std::cin>>A;

  vec<vec<int>> mat(n, vec<int>(n));
  prepare_compliants(); 

  int count = 0;

  for (int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      A %= MOD;
      mat[i][j] = A;

      if (i > 0 && is_compliant[A][mat[i - 1][j]]) {
        count+=2;
      }
      if (j > 0 && is_compliant[A][mat[i][j - 1]]) {
        count+=2;
      }

      A *= 3;
    } 
  }
 
  std::cout<<count;
  //print_mat(mat);


  std::cout.flush();
}
