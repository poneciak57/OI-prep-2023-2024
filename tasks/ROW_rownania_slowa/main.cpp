#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Rel {
  ll node_id;
  ll slot_id;
};

struct Slot {
  bool visited{false};
  vec<Rel> rels;
};

struct Node {
  vec<Slot> slots;
};

// 0, 1, a, b, c, d, e ...
vec<Node> graph(28);
vec<int> sizes(28, 0);

// {node_id, slot_id}
std::queue<std::pair<int, int>> qleft;
std::queue<std::pair<int, int>> qright;

vec<int> res;

int get_node_id(char c) {
  if(c == '0' || c == '1') return c - '0';
  return c - 'a' + 2;
}

// {node_id, slot_id}
void dfs(std::pair<int, int> cur) {
  if(graph[cur.first].slots[cur.second].visited) {
    return;
  }
  graph[cur.first].slots[cur.second].visited = true;
  for(auto &[node_id, slot_id] : graph[cur.first].slots[cur.second].rels) {
    dfs({node_id, slot_id});
  }
}

void multiply() {
  ll reminder = 0;
  for(int i = 0; i < res.size(); i++) {
    res[i] = res[i]*2 + reminder;
    reminder = 0;
    if(res[i] >= 10) {
      res[i] %= 10;
      reminder = 1;
    }
  }
  if(reminder == 1) {
    res.push_back(1);
  }
}

void print_res() {
  for(int i = res.size() - 1; i >= 0; i--) {
    std::cout<<res[i];
  }
  std::cout<<"\n";
}

void clear(std::queue<std::pair<int, int>> &q) {
  std::queue<std::pair<int, int>> empty;
  std::swap(q, empty);
}
void print_graph();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll q, n, l, r, tmp;
  std::cin>>q;

  while(q--) {
    res.clear();
    res.push_back(1);
    clear(qleft);
    clear(qright);
    graph = vec<Node>(28);
    sizes = vec<int>(28, 1);
    graph[0].slots = vec<Slot>(1); 
    graph[1].slots = vec<Slot>(1); 
    std::cin>>n;
    for(int i = 2; i < n + 2; i++) {
      std::cin>>tmp;
      sizes[i] = tmp;
      graph[i].slots = vec<Slot>(tmp);
    }
    str s1, s2;
    int l1, l2;
    std::cin>>l1>>s1>>l2>>s2;

    for(int i = 0; i < l1; i++) {
      ll nid = get_node_id(s1[i]);
      for(int j = 0; j < sizes[nid]; j++) {
        qleft.push({nid, j});
      }
    }

    for(int i = 0; i < l2; i++) {
      ll nid = get_node_id(s2[i]);
      for(int j = 0; j < sizes[nid]; j++) {
        qright.push({nid, j});
      }
    }

    // if sizes does not match
    if(qleft.size() != qright.size()) {
      std::cout<<0<<"\n";
      continue;
    }
    
    while(!qleft.empty()) {
      auto [ln, ls] = qleft.front();
      auto [rn, rs] = qright.front();

      graph[ln].slots[ls].rels.push_back({rn, rs});
      graph[rn].slots[rs].rels.push_back({ln, ls});

      qleft.pop();
      qright.pop();
    }

    dfs({0, 0});
    if(graph[1].slots[0].visited) {
      // that means the 1 is connected to 0
      std::cout<<0<<"\n";
      continue;
    }
    dfs({1, 0});

    for(int i = 2; i < graph.size(); i++) {
      for(int j = 0; j < graph[i].slots.size(); j++) {
        if(!graph[i].slots[j].visited) {
          dfs({i, j});
          multiply();
        }
      }
    }
    print_res();
    // print_graph();
  }

  std::cout.flush();
}

void print_graph() {
  for(int i = 0; i < 2; i++) {
    std::cout<<"letter: "<<(char)('0' + i)<<"\n";
    for(int j = 0; j < graph[i].slots.size(); j++) {
      std::cout<<"slot #"<<j+1<<": [ ";
      for(auto &[node_id, slot_id] : graph[i].slots[j].rels) {
        std::cout<<"{"<<(char)('a' + node_id)<<","<<slot_id+1<<"} ";
      }
      std::cout<<"]\n";
    }
  } 
  for(int i = 2; i < graph.size(); i++) {
    std::cout<<"letter: "<<(char)('a' + i - 2)<<"\n";
    for(int j = 0; j < graph[i].slots.size(); j++) {
      std::cout<<"slot #"<<j+1<<": [ ";
      for(auto &[node_id, slot_id] : graph[i].slots[j].rels) {
        std::cout<<"{"<<(char)('a' + node_id)<<","<<slot_id+1<<"} ";
      }
      std::cout<<"]\n";
    }
  } 
}