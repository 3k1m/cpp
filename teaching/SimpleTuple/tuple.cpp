#include<iostream>

// this example should be overloaded on const, too (left as exercise)

template<typename ... Types>
struct tuple;

template<typename T, typename ... Types>
struct tuple<T, Types...> : tuple<Types...> {
  T value;
};

template<>
struct tuple<>{ };

template<size_t i, typename T, typename ... Types>
struct tuple_helper {
  constexpr static auto& get( tuple<T, Types...>& t) {
    return tuple_helper<i-1, Types...>::get(
      static_cast< tuple<Types...>& >(t) );
  }
};

// totally legit, partial specialization is awesome
template<typename T, typename ... Types>
struct tuple_helper<0, T, Types...> {
  constexpr static auto& get( tuple<T, Types...>& t) {
    return t.value;
  }
};

template<size_t i, typename T, typename ... Types>
constexpr auto& get( tuple<T, Types...>& t) {
  return tuple_helper<i, T, Types...>::get( t );
}

int main(){
  tuple<int,double> t;
  get<0>(t) = 5;
  get<1>(t) = 3.14;
  ++get<0>(t);
  std::cout << get<0>(t) << '\n' << get<1>(t) << '\n';
    
	
  return 0;
}
