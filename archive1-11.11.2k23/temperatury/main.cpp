#include <iostream>
#include <vector>
#include <queue>

struct temper
{
    int min;
    int max;
};
struct kolejka
{
    int temp;
    int dzien;
};
std::vector<temper> tab;
std::deque<kolejka> que;
int solve()
{
    int temp_min = -1000000000;
    int licznik = 0;
    int temp_dzien;
    for (int first = 0, last = 0; first < tab.size(); first++)
    {
        temp_dzien = first;
        temp_min = std::max(temp_min, tab[first].min);
        while (!que.empty() && que.front().temp < tab[first].min) {
            temp_dzien = que.front().dzien;
            que.pop_front();
        }
        que.push_front({ tab[first].min,temp_dzien});
        while (!que.empty()&&temp_min > tab[first].max) {
            temp_min = que.back().temp;
            last = que.back().dzien;
            que.pop_back(); 
        }
        licznik = std::max(licznik, first - last + 1);
    }
    return licznik;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int o_min, o_max;
    while (n-- > 0)
    {
        std::cin >> o_min >> o_max;
        tab.push_back({ o_min,o_max });
    }
    std::cout << solve();

}
