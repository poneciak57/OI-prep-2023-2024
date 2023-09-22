#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


bool is_fighting_number(vec<int> n, ) {
    vec<bool> already_checked = vec<bool>(10, false);
    
    return true;
}

int to_number(vec<int> l) {
    int i = 0;
    ll result = 0;
    ll mult = 1;
    while (l[i] != -1) {
        result += l[i] * mult;
        i++;
        mult*=10;
    }
    return result;
}

vec<int> from_number(ll num) {
    vec<int> liczba;
    
    while(num > 0) {
        liczba.push_back(num%10);
        num /= 10;
    }
    return liczba;
}

vec<int> increment(vec<int> num) {
    int i = 0;
    while(++num[i] != 10) {
        num[i] = 1;
        i++;
        if(i == num.size()) {
            num.push_back(1);
        }
    }
    return num;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll from, to;
    std::cin>>from>>to;

    vec<int> liczba = from_number(from);

    while(to_number(liczba) < to) {
        increment(liczba);
    }
    
    std::cout.flush();
}