#include <iostream>

int initx(); // forward declaration
int inity(); // forward declaration

int g_y{inity()};
int g_x{initx()}; // g_x is initialized first

int initx()
{
    return g_y; // g_y isn't initialized when this is called
}

int inity()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}
