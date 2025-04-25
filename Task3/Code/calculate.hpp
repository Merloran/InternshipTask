#pragma once

template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation)
{
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};

template <class BinaryOp, class ValueType>
    requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp &f)
{
    ValueType current = value;
    // I would say that n times would be f(f(f(x, x), x), x), but I did as it was in example
    for (int32_t i = 0; i < n - 1; ++i)
    {
        current = f(current, value);
    }
    return current;
}

struct Int
{
    int val;

    Int(int v) : val(v) {}

    static Int identity()
    {
        return { 0 };
    }
};

inline Int f(const Int first, const Int second)
{
    return { first.val ^ second.val };
}

inline Int g(const Int first, const Int second)
{
    return { first.val << second.val };
}