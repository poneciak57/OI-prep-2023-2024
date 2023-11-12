#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll num;
    std::cin>>num;

    ll i = 1;
    ll max = 1;

    for (ll i = 2; i*i<=num; i++) {
        if(num % i == 0) {
            if(i % 2 == 1) {
                max = std::max(i ,max);
            }
            ll second = num/i;
            if(second % 2 == 1) {
                max = std::max(second ,max);
            }
        }
    }
    std::cout<<max;

    std::cout.flush();
}