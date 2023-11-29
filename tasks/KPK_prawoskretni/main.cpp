#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int HASH_MUL = 102;
const int MAX_HASH = HASH_MUL * HASH_MUL + HASH_MUL;

struct Pos {
  int x;
  int y;
};

vec<Pos> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

// [y][x];
vec<vec<bool>> graph;

int get_right_dir(int cur_dir); // gives right dir modifier
int hash(Pos pos); // gives node hash
Pos dehash(int h);
int hash_dir(Pos pos, int dir); // gives node hash with dir
std::pair<Pos, int> dehash_dir(int h);
bool in_bounds(Pos pos);

void bfs(Pos from, Pos to) {
  int to_hash = hash(to);
  int from_hash = hash(from);
  vec<vec<int>> d(MAX_HASH, vec<int>(4, INT_MAX));
  d[from_hash][0] = 0;
  d[from_hash][1] = 0;
  d[from_hash][2] = 0;
  d[from_hash][3] = 0;
  vec<vec<int>> p(MAX_HASH, vec<int>(4, -1));

  std::queue<std::pair<Pos, int>> q;
  q.push({from, 0});
  q.push({from, 1});
  q.push({from, 2});
  q.push({from, 3});

  while(!q.empty()) {
    auto [pos, dir] = q.front();
    q.pop();
    int pos_hash = hash(pos);

    int new_dist = d[pos_hash][dir] + 1;
    int h_dir_cur = hash_dir(pos, dir);

    if (pos_hash == to_hash) {
      vec<Pos> prevs;
      prevs.push_back(pos);
      auto [p_pos, p_dir] = dehash_dir(p[pos_hash][dir]);
      prevs.push_back(p_pos);
      while(hash(p_pos) != from_hash) {
        auto [p_pos2, p_dir2] = dehash_dir(p[hash(p_pos)][p_dir]);
        p_pos = p_pos2;
        p_dir = p_dir2;
        prevs.push_back(p_pos);
      }
      std::cout<<prevs.size()<<"\n";
      for(int i = prevs.size() - 1; i >= 0; i--) {
        std::cout<<prevs[i].y<<" "<<prevs[i].x<<"\n";
      }
      return;
    }

    Pos cur_dir = dirs[dir];
    Pos pos_front = {pos.x + cur_dir.x, pos.y + cur_dir.y};
    int front_hash = hash(pos_front);
    if(in_bounds(pos_front) && !graph[pos_front.y][pos_front.x] && new_dist < d[front_hash][dir]) {
      d[front_hash][dir] = new_dist;
      p[front_hash][dir] = h_dir_cur;
      q.push({pos_front, dir});
    }

    int r_dir = get_right_dir(dir);
    Pos right_dir = dirs[r_dir];
    Pos pos_right = {pos.x + right_dir.x, pos.y + right_dir.y};
    int right_hash = hash(pos_right);
    if(in_bounds(pos_right) && !graph[pos_right.y][pos_right.x] && new_dist < d[right_hash][r_dir]) {
      d[right_hash][r_dir] = new_dist;
      p[right_hash][r_dir] = h_dir_cur;
      q.push({pos_right, r_dir});
    }
  }

  std::cout<<"NIE";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m;
  std::cin>>n>>m;
  graph = vec<vec<bool>>(n + 1, vec<bool>(m + 1, false));
  for(int y = 1; y <= n; y++) {
    for(int x = 1; x <= m; x++) {
      char c;
      std::cin>>c;
      graph[y][x] = c=='1';
    }
  }

  Pos start, end;
  std::cin>>start.y>>start.x>>end.y>>end.x;

  bfs(start, end);

  std::cout.flush();
}

int get_right_dir(int cur_dir) {
  // dirs are in specific order that lets us do this
  return (cur_dir + 1) % 4;
}

int hash(Pos pos) {
  return HASH_MUL * pos.x + pos.y;
}

int hash_dir(Pos pos, int dir) {
  return HASH_MUL*HASH_MUL*dir + HASH_MUL * pos.x + pos.y;
}

std::pair<Pos, int> dehash_dir(int h) {
  return {
    {(h % (HASH_MUL*HASH_MUL))/HASH_MUL, h % HASH_MUL},
    h / (HASH_MUL*HASH_MUL)
  };
}

Pos dehash(int h) {
  return {h / HASH_MUL, h % HASH_MUL};
}

bool in_bounds(Pos pos) {
  return pos.y > 0 && pos.y < graph.size() && pos.x > 0 && pos.x < graph[0].size();
}