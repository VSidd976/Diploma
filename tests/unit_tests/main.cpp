#include <catch2/catch_test_macros.hpp>
#include "Derivatives.h"

using namespace std;

using X = Var<0>;
using Y = Var<1>;

constexpr array<double, 2> x0 = { 3.0, 6.0 };

TEST_CASE("Derivative of a variable", "[derivatives]")
{
    using DX_dx = X::Derivative<0>;
    using DY_dx = Y::Derivative<0>;

    STATIC_REQUIRE(DX_dx::eval(x0) == 1);
    STATIC_REQUIRE(DY_dx::eval(x0) == 0);
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

TEST_CASE("Derivative of a product", "[derivatives]")
{
    using X_2 = Product<X, X>;
    using XY = Product<X, Y>;

    using DX_2_dx = X_2::Derivative<0>;
    using DXY_dy = XY::Derivative<1>;

    STATIC_REQUIRE(DX_2_dx::eval(x0) == 6.0);
    STATIC_REQUIRE(DXY_dy::eval(x0) == 3.0);
}
