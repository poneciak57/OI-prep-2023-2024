#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll n;
    std::cin>>n;

    vec<ll> goscie(n+1);
    vec<bool> is_visited(n+1, false);

    ll i = 1;
    while (n--) {
        ll gosc;
        std::cin>>gosc;
        goscie[i] = gosc;
        i++;
    }

    ll count = 0;
    for(ll i = 1; i<goscie.size(); i++) {
        if(!is_visited[i]) {
            count++;
            ll j = i;
            while(!is_visited[j]) {
                is_visited[j] = true;
                j = goscie[j];
            }
        }
    }
    std::cout<<count;

    std::cout.flush();
}