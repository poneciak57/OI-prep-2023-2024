#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


bool is_fighting_number(ll n) {
    vec<bool> already_checked = vec<bool>(10, false);
    ll num = n;
    ll first = n % 10;
    while (n > 0) {
        ll t = n % 10;
        n /= 10;

        if (t == 0) {
            return false;
        }

        if((already_checked[t] || (t == 1))){
            already_checked[t] = true;
        } else if (t == 2 && first%2 == 0){
            already_checked[2] = true;
        } else if (t == 5 && first%5 == 0){
            already_checked[5] = true;
        } else if (num % t == 0) {
            already_checked[t] = true;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll from, to;
    std::cin>>from>>to;

    ll count = 0;
    for (ll i = from; i<= to; i++) {
        count += is_fighting_number(i);
    }
    std::cout<<count;

    std::cout.flush();
}