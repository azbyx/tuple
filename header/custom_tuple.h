#ifndef CUSTOM_TUPLE_H_INCLUDED
#define CUSTOM_TUPLE_H_INCLUDED
#include <utility>


template<typename... Args>
struct custom_tuple;


namespace tmp{
    template<size_t Is, typename Head, typename... Args>
    struct getter
    {
        static decltype(auto) get(const custom_tuple<Head, Args...>& t)
        {
            return getter<Is - 1, Args...>::get(t);
        }
    };

    template<typename Head, typename... Args>
    struct getter<0, Head, Args...>
    {
        static decltype(auto) get(const custom_tuple<Head, Args...>& t)
        {
            return t.value;
        }
    };
}//namespace tmp{

template<size_t Is, typename Head, typename... Args>
decltype(auto) custom_get(const custom_tuple<Head, Args...>& t)
{
    return tmp::getter<Is, Head, Args...>::get(t);
}

template<typename H, typename... Tail>
struct custom_tuple<H, Tail...> : custom_tuple<Tail...>{

    using value_t = H;

    custom_tuple(H val, Tail... tail)
            : custom_tuple<Tail...>(tail...), value(val){}

    template<typename... Args>
    custom_tuple(const custom_tuple<Args...>& other):
            custom_tuple(other, std::make_index_sequence<sizeof...(Args)>{}){}

    template<typename... Args>
    void operator=(const custom_tuple<Args...>& other)
    {
        assign_tuple(*this, other, std::make_index_sequence<sizeof...(Args)>{});
    }

    template<typename T1, typename T2, size_t ... Indices>
	void assign_tuple(T1& th, const T2& other, std::index_sequence<Indices...>){
        ((custom_get<Indices>(th) = custom_get<Indices>(other)), ...);
	}

    template<typename Tuple, size_t ... Indices>
	custom_tuple(Tuple&& other, std::index_sequence<Indices...>):
        custom_tuple(custom_get<Indices>(std::forward<Tuple>(other))...){}

public:
    value_t value = H();
};

template<>
struct custom_tuple<>{};


template <typename... Args>
auto make_custom_tuple(Args&&... args);

template <typename... Args>
auto custom_tie(Args&... args);

#include "custom_tuple.impl"

#endif // CUSTOM_TUPLE_H_INCLUDED
