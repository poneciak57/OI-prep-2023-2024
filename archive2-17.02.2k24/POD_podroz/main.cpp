#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Rel {
  int dest; // destination node
  int time; // travelling time
  vec<int> times; // times of departure
};  

struct Node {
  vec<Rel> rels;
};

vec<Node> graph;

int dijkstra(int src, int dest, int stime) {
  // {time, node}
  priority_queue<pair<int,int>, vec<pair<int,int>>, greater<pair<int,int>>> pq;
  vec<int> d(graph.size(), INT_MAX);
  pq.push({stime, src});
  d[src] = stime;

  while(!pq.empty()) {
    auto [time, v] = pq.top();
    pq.pop();

    if(d[v] < time) continue;
    if(v == dest) return time;

    // now for each rel we need to choose closest (higher or equal than current) time
    int time_mod = time % 60;
    for(auto rel : graph[v].rels) {
      int ntime = time + rel.time;
      int min_waiting = INT_MAX;
      for(auto t : rel.times) {
        // we are taking minimal waiting time with modulo
        min_waiting = min(min_waiting, (t - time_mod + 60) % 60);
      }

      ntime += min_waiting;
      if(d[rel.dest] > ntime) {
        d[rel.dest] = ntime;
        pq.push({ntime, rel.dest});
      }
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m, src, dest, h, min;
  std::cin>>n>>m>>src>>dest>>h>>min;

  int stime = h * 60 + min;
  
  graph = vec<Node>(n + 1);

  while(m--) {
    int s, c;
    std::cin>>s>>c;

    // reading stations and times for certain line
    vec<int> stations(s);
    vec<int> ttimes(s - 1);
    for(int i = 0, t; i < s; i++) {
      std::cin>>t;
      stations[i] = t;
    }
    for(int i = 1, t; i < s; i++) {
      std::cin>>t;
      ttimes[i - 1] = t;
    }

    // adding times for each interval as Rel to nodes 
    vec<int> times;
    for(int i = 0; i < 60; i += c) {
      times.push_back(i);
    }
    int prev = stations[0];
    for(int i = 1; i < s; i++) {
      graph[prev].rels.push_back({
        stations[i],
        ttimes[i - 1],
        times
      });
      prev = stations[i];
      for(auto &t : times) {
        t = (t + ttimes[i - 1]) % 60;
      }
    }
    // adding the same but backwards 
    times.clear();
    for(int i = 0; i < 60; i += c) {
      times.push_back(i);
    }
    prev = stations.back();
    for(int i = stations.size() - 2; i >= 0; i--) {
      graph[prev].rels.push_back({
        stations[i],
        ttimes[i],
        times
      });
      prev = stations[i];
      for(auto &t : times) {
        t = (t + ttimes[i]) % 60;
      }
    }
  }

  // for(int i = 1; i < graph.size(); i++) {
  //   cout<<"#"<<i<<"\n";
  //   for(auto rel : graph[i].rels) {
  //     cout<<"-> "<<rel.dest<<" t: "<<rel.time<<"  [ ";
  //     for(auto t : rel.times) {
  //       cout<<t<<" ";
  //     }
  //     cout<<"]\n";
  //   }
  // }

  int arr_time = dijkstra(src, dest, stime);
  if(arr_time == -1) {
    cout<<"KARAMBA";
  } else {
    cout<<(arr_time/60) % 24<<" "<<arr_time%60;
  }

  std::cout.flush();
}
