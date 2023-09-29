#include <bits/stdc++.h>
typedef int ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct M {
  ll left;
  ll right;
};

vec<M> malpki;
vec<ll> zrzucone;

// graf[from][to];
vec<vec<bool>> graf;


// return true if monkey `m` has way to root
void throw_all_disconected(ll sec) {
  vec<bool> v = vec<bool>(malpki.size(), false);
  ll n = 1;
  std::queue<ll> queue;
  queue.push(n);
  v[n] = true;
  while(!queue.empty()) {
    n = queue.front();
    queue.pop();
    for (ll i = 1; i < graf.size(); i++) {
      if(!v[i] && graf[i][n]) {
        queue.push(i);
        v[i] = true;
      }
    }
    for (ll i = 1; i < graf.size(); i++) {
      if(!v[i] && graf[n][i]) {
        queue.push(i);
        v[i] = true;
      }
    }
  } 
  for (ll i = 1; i < v.size(); i++) {
    if(v[i] == false) {
      zrzucone[i] = sec;
    }
  }
}

// adds monkey to monkeys and adds relation for that monkey in graf
void add_monkey(ll m, ll l, ll r) {
    malpki.push_back({l, r});
    if(l != -1) {
     graf[m][l] = 1;
    }
    if(r != -1) {
      graf[m][r] = 1;
    }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n, m;
  std::cin>>n>>m;
  malpki.push_back({-1, -1});
  zrzucone = vec<ll>(n+1, -1);
  graf = vec<vec<bool>>(n+1, vec<bool>(n+1, 0));

  ll m_count = 1;
  while (n--) {
    ll l, r;
    std::cin>>l>>r;
    add_monkey(m_count, l, r);
    m_count++;
  }

  ll sec = 0;
  while (m--) {
    ll monke, hand;
    std::cin>>monke>>hand;
    M curr_monke = malpki[monke];
    
    if(hand == 1) {
      //left
      if(zrzucone[curr_monke.left] == -1) {
        graf[monke][curr_monke.left] = false;
        throw_all_disconected(sec);
      }
    } else {
      //right
      if(zrzucone[curr_monke.right] == -1) {
        graf[monke][curr_monke.right] = false;
        throw_all_disconected(sec);
      }
    }


    sec++;
  }

  for (ll i = 1; i < zrzucone.size(); i++) {
    std::cout<<zrzucone[i]<<"\n";
  }
  std::cout.flush();
}
