#include <iostream>
#include "../includes/core.hpp"
#include "../includes/number.hpp"
int main(){
    try
    {
        using namespace mcalcu;
        test_factor();
    }
    catch (mcalcu::Error& e)
    {
        std::cout << e.what();
    }
    return 0;
}