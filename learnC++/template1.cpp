#include <utility> // for std::pair
#include <iostream>
using namespace std;

int main()
{
    std::pair<int, int> p1{1, 2}; // explicitly specify class template std::pair<int, int> (C++11 onward)
    std::pair p2{1, 2};           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    cout << std::get<0>(p2) << endl;
    return 0;
}