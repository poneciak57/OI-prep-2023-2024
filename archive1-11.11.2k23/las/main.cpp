#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct Pos {
  int x;
  int y;
};
vec<vec<ll>> mat;
vec<vec<bool>> visited;
ll n, d;

bool bfs_count(int x, int y, ll max) {
  ll count = 0;
  std::queue<Pos> queue;
  queue.push({x, y});
  visited[x][y] = true;
  while (!queue.empty()) {
    Pos front = queue.front();
    queue.pop(); 
    count++;
    if(front.x != 0 && !visited[front.x - 1][front.y] && mat[front.x - 1][front.y] <= max) {
      visited[front.x - 1][front.y] = true;
      queue.push({front.x - 1, front.y});
    }
    if(front.x != (n - 1) && !visited[front.x + 1][front.y] && mat[front.x + 1][front.y] <= max) {
      visited[front.x + 1][front.y] = true;
      queue.push({front.x + 1, front.y});
    }
    if(front.y != 0 && !visited[front.x][front.y - 1] && mat[front.x][front.y - 1] <= max) {
      visited[front.x][front.y - 1] = true;
      queue.push({front.x, front.y - 1});
    }
    if(front.y != (n - 1) && !visited[front.x][front.y + 1] && mat[front.x][front.y + 1] <= max) {
      visited[front.x][front.y + 1] = true;
      queue.push({front.x, front.y + 1});
    }
  }
  return count >= d;
}

bool is_possible(ll max) {
  visited = vec<vec<bool>>(n, vec<bool>(n, false));
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if(mat[x][y] <= max && !visited[x][y] && bfs_count(x, y, max)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  std::cin>>n>>d;
  
  mat = vec<vec<ll>>(n, vec<ll>(n));
  ll max = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ll h;
      std::cin>>h;
      max = std::max(max, h);
      mat[i][j] = h;
    }
  }

  ll b = 0;
  ll m;
  while (b + 1 < max) {
    m = (b + max)/2;
    if(is_possible(m)) {
      max = m;
    } else {
      b = m;
    }
  }
  std::cout<<max;


  


  
  std::cout.flush();
}
