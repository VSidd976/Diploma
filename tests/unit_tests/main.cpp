#include <catch2/catch_test_macros.hpp>
#include "Derivatives.h"
#include <iostream>

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

TEST_CASE("Derivative of a sin", "[derivatives]")
{
    using Sin_X = Sin<0>;
    using Sin_Y = Sin<1>;

    using DSin_X_dx = Sin_X::Derivative<0>;
    using DSin_X_dy = Sin_X::Derivative<1>;

    STATIC_REQUIRE(DSin_X_dx::eval(x0) == cos(3.0));
    STATIC_REQUIRE(DSin_X_dy::eval(x0) == 0);
}

TEST_CASE("Derivative of a cos", "[derivatives]")
{
    using Cos_X = Cos<0>;

    using DCos_X_dx = Cos_X::Derivative<0>;
    using DCos_X_dy = Cos_X::Derivative<1>;

    STATIC_REQUIRE(DCos_X_dx::eval(x0) == -sin(3.0));
    STATIC_REQUIRE(DCos_X_dy::eval(x0) == 0);
}

TEST_CASE("Derivative of an exp", "[derivatives]")
{
    using Exp = Exp<0>;

    using DExp_dx = Exp::Derivative<0>;
    using DExp_dy = Exp::Derivative<1>;

    STATIC_REQUIRE(DExp_dx::eval(x0) == exp(3.0));
    STATIC_REQUIRE(DExp_dy::eval(x0) == 0);
}

TEST_CASE("Derivative of a ln", "[derivatives]")
{
    using Ln = Ln<0>;

    using DLn_dx = Ln::Derivative<0>;
    using DLn_dy = Ln::Derivative<1>;

    STATIC_REQUIRE(DLn_dx::eval(x0) == (1 / 3.0));
    STATIC_REQUIRE(DLn_dy::eval(x0) == 0);
}
