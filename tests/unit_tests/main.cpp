#include <catch2/catch_test_macros.hpp>
#include "Derivatives.h"

using namespace std;

using X = Var<0>;
using Y = Var<1>;

constexpr array<double, 2> x0 = { 3.0, 6.0 };

TEST_CASE("Derivative of a square", "[derivatives]")
{
    using X_2 = Product<X, X>;
    using DX_2 = X_2::Derivative<0>;
    STATIC_REQUIRE(DX_2::eval(x0) == 6.0);
}

TEST_CASE("Derivative of a variable", "[derivatives]")
{
    using DY = Y::Derivative<0>;
    STATIC_REQUIRE(DY::eval(x0) == 0);
}

TEST_CASE("Derivative of a sum", "[derivatives]")
{
    using X_2 = Product<X, X>;

    using F = Sum<X_2, Product<Const<2.0>, X>>;
    using DF_dx = F::Derivative<0>;
    using DF_dy = F::Derivative<1>;

    STATIC_REQUIRE(DF_dx::eval(x0) == 8);
    STATIC_REQUIRE(DF_dy::eval(x0) == 0);
}

TEST_CASE("Derivative of a subtraction", "[derivatives]")
{
    using X_2 = Product<X, X>;
    using Y_2 = Product<Y, Y>;

    using F = Sub<X_2, Y_2>;
    using DF_dx = F::Derivative<0>;
    using DF_dy = F::Derivative<1>;

    STATIC_REQUIRE(DF_dx::eval(x0) == 6);
    STATIC_REQUIRE(DF_dy::eval(x0) == -12);
}
