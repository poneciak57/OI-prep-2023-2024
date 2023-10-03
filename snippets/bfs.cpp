#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct Node {
  vec<ll> rels;
};

vec<Node> graf;

void bfs(ll n) {
    std::queue<ll> queue;
    vec<bool> visited(graf.size(), false);
    queue.push(n);
    while (!queue.empty()) {
        ll current = queue.front();
        queue.pop();
        visited[current] = true;
        
        for(ll r : graf[current].rels) {
            if(!visited[r]) {
                queue.push(r);
            }
        }
    }
    
}