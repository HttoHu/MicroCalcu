#include <iostream>
#include "../includes/core.hpp"
#include "../includes/number.hpp"
int main(){
    try
    {
        using namespace mcalcu;
        auto a = Integer::from(123);
        auto b = Integer::from(246);
        auto c = Fraction::from(a, b);
        auto d = Fraction::from(b, a);
        d = d * c -d;
        std::cout << d->to_string();
    }
    catch (mcalcu::Error& e)
    {
        std::cout << e.what();
    }
    return 0;
}