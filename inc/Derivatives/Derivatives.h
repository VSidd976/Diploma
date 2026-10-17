#pragma once
#include <array>

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
    typename R::template Derrivative<Wrt>>;
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
