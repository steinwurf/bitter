namespace bitter
{
    template <unsigned...> struct sum;
    template <unsigned size> struct sum<size>
    {
            enum {value = size};
    };

    template <unsigned size, unsigned... size> struct sum<size, sizes...>
    {
        enum { value = size + sum<sizes...>::value };
    };
}
