#include <iostream>

namespace constants
{
    constexpr double gravity{9.8};
}

// This function can calculate the instant velocity for any gravity value (more useful)
double instantVelocity(int time, double gravity)
{
    return gravity * time;
}

int main()
{
    std::cout << instantVelocity(5, constants::gravity); // pass our constant to the function as a parameter
}