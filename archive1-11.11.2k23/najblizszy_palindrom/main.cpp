#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

bool is_palindrom(ll n) {
    vec<ll> nums;
    while (n > 0) {
        nums.push_back(n%10);
        n /= 10;
    }
    for (int i = 0; i<nums.size()/2; i++) {
        if(nums[i] != nums[nums.size() - i - 1]) {
            return false;
        }
    }
    return true;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll liczba;
    std::cin>>liczba;

    while(!is_palindrom(liczba)) {
        liczba++;
    }

    std::cout<<liczba;


    std::cout.flush();
}