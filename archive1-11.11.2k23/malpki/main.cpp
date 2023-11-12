#include <bits/stdc++.h>
typedef int ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct M {
  ll depth;
  ll left;
  ll right;
};

vec<M> malpki;
vec<ll> zrzucone;

// graf[from][to];
vec<vec<bool>> graf;

void dfs_depth(ll n, ll depth) {
  if (malpki[n].depth != -1) {
    return ;
  }
  malpki[n].depth = depth;
  for (ll to = 1; to < graf.size(); to++) {
    if(graf[n][to] && malpki[to].depth == -1) {
      dfs_depth(to, depth + 1);
    }
    if(graf[to][n] && malpki[to].depth == -1) {
      dfs_depth(to, depth + 1);
    }
  } 
}

void dfs_throw(ll n, ll sec) {
  for (ll to = 0; to < graf.size(); to++) {
    if(graf[n][to] && zrzucone[to] == -1) {
      zrzucone[to] = sec;
      dfs_throw(to, sec);
    }
  }
}

bool ishold(ll n) {
  for (ll i = 1; i < graf.size(); i++) {
    if(malpki[i].depth < malpki[n].depth && (graf[n][i] || graf[i][n])) {
      return true;
    }
  }
  return false;
}

void release(ll from, ll to, ll sec) {
  graf[from][to] = false;
  if(malpki[from].depth > malpki[to].depth) {
    if (ishold(from)) {
      return;
    }
    zrzucone[from] = sec;
    dfs_throw(from, sec);
  } else {
    if (ishold(to)) {
      return;
    }
    zrzucone[to] = sec;
    dfs_throw(to, sec);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n, m;
  std::cin>>n>>m;
  malpki.push_back({-1, -1});
  zrzucone = vec<ll>(n + 1, -1);
  graf = vec<vec<bool>>(n + 1, vec<bool>(n + 1, 0));

  ll m_count = 1;
  while (n--) {
    ll l, r;
    std::cin>>l>>r;
    malpki.push_back({-1, l, r});
    graf[m_count][l + (l == -1)] = true;
    graf[m_count][r + (r == -1)] = true;
    m_count++;
  }

  dfs_depth(1, 1);
  ll sec = 0;
  while (m--) {
    ll monke, hand;
    std::cin>>monke>>hand;
    M curr_monke = malpki[monke];
    
    if(hand == 1) {
      //left
      release(monke, curr_monke.left, sec);
    } else {
      //right
      release(monke, curr_monke.right, sec);
    }

    sec++;
  }

  for (ll i = 1; i < zrzucone.size(); i++) {
    std::cout<<zrzucone[i]<<"\n";
  }
  std::cout.flush();
}
