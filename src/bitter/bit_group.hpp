#include "sum.hpp"

namespace bitter
{
template<typename... GROUP>
class bit_group
{

public:

    bit_group()
    {

    }

    template <unsigned pos, unsigned... sizes>
    unsigned get()
    {
        return getImpl<pos, 0>();
    }

private:
    template <unsigned pos, unsigned b4, unsigned size, unsigned... sizes>
    unsigned getImpl()
    {
        assert(pos <= sizeof...(sizes));
        if (pos == 0)
        {
            if (size == 1)
            {
                return (this.store & (1u << b4)) != 0;
            }
            return (this.store >> b4) & ((1u  << size) - 1);
        }
        return getImpl<pos - (pos ? 1 : 0), b4 + (pos ? size : 0)>();
    }

private:
    bit_reader m_reader;

};
}
