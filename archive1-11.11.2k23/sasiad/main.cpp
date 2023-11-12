#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int MOD = 53;
vec<int> primes = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,1000};
vec<vec<bool>> is_compliant(101, vec<bool>(101, false));

void print_mat(vec<vec<int>> &mat) {
  for (auto row : mat) {
    for (auto v : row) {
      std::cout<<v<<" ";
    }
    std::cout<<"\n";
  }
}

bool are_compliant(int a, int b) {
  int i = 0;
  int max = std::max(a, b);
  while(primes[i] <= max) {
    int p = primes[i];
    if((a % p == 0 && b % p != 0) || (b % p == 0 && a % p != 0)) {
      return false;
    }
    i++;
  }
  return true;
}

void prepare_compliants() {
  for (int i = 1; i < 101; i++) {
    for(int j = i; j < 101; j++) {
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

  vec<vec<int>> mat(n + 2, vec<int>(n + 2, 0));
  prepare_compliants(); 
  
  int count = 0;

  for (int i = 1; i < n + 1; i++) {
    for(int j = 1; j < n + 1; j++) {
      mat[i][j] = A;
      A *= 3;
      A %= MOD;
    } 
  }


  for (int i = 1; i < n + 1; i++) {
    for(int j = 1; j < n + 1; j++) {
      
      if(
        is_compliant[mat[i][j]][mat[i - 1][j]] || 
        is_compliant[mat[i][j]][mat[i][j - 1]] ||
        is_compliant[mat[i][j]][mat[i + 1][j]] ||
        is_compliant[mat[i][j]][mat[i][j + 1]]
        ) {
          count++;
        }
    } 
  }

 
  std::cout<<count;
  //print_mat(mat);


  std::cout.flush();
}
