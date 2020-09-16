#include <iostream>
#include "../includes/core.hpp"
#include "../includes/number.hpp"
int main(){
    try
    {
        using namespace mcalcu;
        auto one = Integer::from(1);
        auto two = Integer::from(2);
        auto half = Fraction::from(one, two);
        auto irr = Irrational::from(Integer::from(8), half, one->clone());
        irr->simplify();
        std::cout << irr->to_string();
        //test_factor();
    }
    catch (mcalcu::Error& e)
    {
        std::cout << e.what();
    }
    return 0;
}