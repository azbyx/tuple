#ifndef CUSTOM_TUPLE_H_INCLUDED
#define CUSTOM_TUPLE_H_INCLUDED
#include <utility>

template<typename... Args>
struct custom_tuple;


namespace tmp{
    template<size_t Is, typename Head, typename... Args>
    struct getter
    {
        static decltype(auto) get(const custom_tuple<Head, Args...>&);
    };

    template<typename Head, typename... Args>
    struct getter<0, Head, Args...>
    {
        static decltype(auto) get(const custom_tuple<Head, Args...>&);
    };
}//namespace tmp

template<size_t Is, typename Head, typename... Args>
decltype(auto) custom_get(const custom_tuple<Head, Args...>& );

template<typename H, typename... Tail>
struct custom_tuple<H, Tail...> : custom_tuple<Tail...>{

    using value_t = H;

    custom_tuple(H, Tail...);

    template<typename... Args>
    custom_tuple(const custom_tuple<Args...>&);

    template<typename... Args>
    void operator=(const custom_tuple<Args...>&);

    template<typename T1, typename T2, size_t ... Indices>
	void assign_tuple(T1&, const T2&, std::index_sequence<Indices...>);

private:
    template<typename Tuple, size_t ... Indices>
	custom_tuple(Tuple&&, std::index_sequence<Indices...>);

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
