#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll n, k;
    std::cin>>n>>k;

    ll t;
    vec<ll> gasienica;
    while(n--) {
        std::cin>>t;
        gasienica.push_back(t);
    }

    ll b = 0,e = 0;
    ll roze = gasienica[0] == 1;
    ll kapustki = gasienica[0] == 0;
    ll min_kapustki = LLONG_MAX;
    while ((e+1) < gasienica.size())
    {
        if (roze < k) {
            e++;
            roze += gasienica[e] == 1;
            kapustki += gasienica[e] == 0;
        } else {
            if (roze == k) {
                min_kapustki = std::min(min_kapustki, kapustki);
            }
            roze -= gasienica[b] == 1;
            kapustki -= gasienica[b] == 0;
            b++;
        }
    }
    if(min_kapustki == LLONG_MAX) {
        std::cout<<"NIE";
    } else {
        std::cout<<min_kapustki;
    }


    std::cout.flush();
}