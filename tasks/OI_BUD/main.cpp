#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

int n, m;
vec<vec<bool>> mat;

bool can_we(int l) {
  int h_row = -2, h_from = -2, h_to = -2;
  int v_col = -2, v_from = -2, v_to = -2;
  int count = 0, c = 0;

  for (int i = 0; i < n; i++) {
    c = 0;
    for(int j = 0; j < n; j++) {
      if(!mat[i][j]) {
        c++;
      } else {
        if((c/m >= l)) {
          return true;
        }
        if (c >= l) {
          count++;
          h_row = i;
          h_to = j;
          h_from = j - c;
        }
        c = 0;
      }
      
    }
  }
  if(count >= m) {
    return true;
  }

  count = 0;
  for (int i = 0; i < n; i++) {
    c = 0;
    for(int j = 0; j < n; j++) {
      if(!mat[j][i]) {
        c++;
      } else {
        if((c/m >= l)) {
          return true;
        }
        if (c >= l) {
          count++;
          v_col = i;
          v_to = j;
          v_from = j - c;
        }
        c = 0;
      }
      
    }
  }

  if(count >= m) {
    return true;
  }

  if(v_col == -2 || h_row == -2) {
    return false;
  }

  // if they are crosing
  if (h_row <= v_to && h_row >= v_from && v_col <= h_to && v_col >= h_from) {
    int h_cut_max = std::max(h_to - v_col - 1, v_col - h_from);
    int v_cut_max = std::max(v_to - h_row - 1, h_row - v_from); 

    if(l == 1) {
      return false;
    }

    if(((h_cut_max + 1 < l) || v_cut_max < l) && (h_cut_max < l || (v_cut_max + 1) < l)) {
      return false;
    }
    return true;
  } else {
    return true;
  }
}

// Zadanie BUD Kacper Poneta
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;
  n += 1;
  mat = vec<vec<bool>>(n, vec<bool>(n, true));

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      char t;
      std::cin>>t;
      mat[i][j] = (t == 'X');
    }
  }


  int b = 0;
  int e = n;
  int mm;
  while(b + 1 < e) {
    mm = (b + e)/2;
    if(can_we(mm)) {
      b = mm;
    } else {
      e = mm;
    }
  }
  std::cout<<b;


  std::cout.flush();
}
