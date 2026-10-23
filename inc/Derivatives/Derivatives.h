#pragma once
#include <array>
#include <cmath>
#include <type_traits>

template <double V>
struct Const
{
    template <std::size_t N>
    static constexpr double eval(const std::array<double, N>&) { return V; }

    template <int Wrt>
    using Derivative = Const<0.0>;
};

template <int ID>
struct Var
{
    template <std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return x[ID]; }

    template <int Wrt>
    using Derivative = Const<(Wrt == ID ? 1.0 : 0.0)>;
};

template <typename L, typename R>
struct Sum
{
    template <std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return L::eval(x) + R::eval(x); }

    template <int Wrt>
    using Derivative = Sum<typename L::template Derivative<Wrt>,
    typename R::template Derivative<Wrt>>;
};

template<typename L, typename R>
struct Sub
{
    template<std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return L::eval(x) - R::eval(x); }

    template<int Wrt>
    using Derivative = Sub<typename L::template Derivative<Wrt>,
    typename R::template Derivative<Wrt>>;
};

template <typename L, typename R>
struct Product
{
    template <std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return L::eval(x) * R::eval(x); }

    template <int Wrt>
    using Derivative = Sum<Product<typename L::template Derivative<Wrt>, R>,
    Product<L, typename R::template Derivative<Wrt>>>;
};

template<typename L, typename R>
struct Frac
{
    template <std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return L::eval(x) / R::eval(x); }

    template<int Wrt>
    using Derivative = Frac<Sub<Product<typename L::template Derivative<Wrt>, R>,
    Product<L, typename R::template Derivative<Wrt>>>, Product<R, R>>;
};

template<int ID>
struct Cos;

template<int ID>
struct Sin
{
    template<std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return std::sin(x[ID]); }

    template<int Wrt>
    using Derivative = std::conditional_t<Wrt == ID, Cos<ID>, Const<0.0>>;
};

template<int ID>
struct Cos
{
    template<std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return std::cos(x[ID]); }

    template<int Wrt>
    using Derivative = std::conditional_t<Wrt == ID, Product<Const<-1.0>, Sin<ID>>, Const<0.0>>;
};

template<int ID>
struct Exp
{
    template<std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return std::exp(x[ID]); }

    template<int Wrt>
    using Derivative = std::conditional_t<Wrt == ID, Exp<Wrt>, Const<0.0>>;
};

template<int ID>
struct Ln
{
    template<std::size_t N>
    static constexpr double eval(const std::array<double, N>& x) { return std::log(x[ID]); }

    template<int Wrt>
    using Derivative = std::conditional_t<Wrt == ID, Frac<Const<1.0>, Var<Wrt>>, Const<0.0>>;
};
