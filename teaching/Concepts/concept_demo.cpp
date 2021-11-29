#include<concepts>
#include<type_traits>
#include<iostream>
#include <string>
#include <exception>
#include<vector>

template<typename T>
void always() requires true {}

template<typename T>
requires false
void never() {}

template<typename T>
decltype(auto) neg(T&& t) requires std::is_signed_v<
  std::remove_reference_t<T>> {
    return -t;
  }

template<typename S, typename A>
size_t string_app(S& s, A&& a)
  requires requires(S& s, A&& a){
      s += std::forward<A>(a);
      {s.size()} noexcept -> std::same_as<size_t>;
  } {
      s += std::forward<A>(a);
      return s.size();
  }

template<typename T1, typename T2>
concept can_compare_integrals = requires(T1 t1,T2 t2) {
  {t1<t2} noexcept -> std::convertible_to<bool>;
} && std::integral<T1> && std::integral<T2>;

template<typename T1, typename T2>
constexpr bool integral_less(const T1& t1, const T2& t2)
requires can_compare_integrals<T1,T2> {
  return t1<t2;
}


[[noreturn]] void insult(const std::string& reason){
    throw std::logic_error(reason + ", you monster!");
}

template<typename T>
concept not_const =
  std::is_same_v< T, std::remove_const_t<T> >;

template<typename T, typename S>
decltype(auto) write_to0(T* t, S&& s){
    if(!t){
        insult("writing to null");
    }
    else{
        return *t = std::forward<S>(s);
    }
}

template<typename T, typename S>
decltype(auto) write_to1(T* t, S&& s){
    static_assert(not_const<T>);
    if(!t){
        insult("writing to null");
    }
    else{
        return *t = std::forward<S>(s);
    }
}

template<typename T, typename S>
decltype(auto) write_to2(T* t, S&& s)
  requires not_const<T> {
    if(!t){
        insult("writing to null");
    }
    else{
        return *t = std::forward<S>(s);
    }
}

template<not_const T, typename S>
decltype(auto) write_to3(T* t, S&& s)
{
    if(!t){
        insult("writing to null");
    }
    else{
        return *t = std::forward<S>(s);
    }
}

decltype(auto) write_to4(not_const auto* t, auto&& s)  {
    if(!t){
        insult("writing to null");
    }
    else{
        return *t = std::forward<decltype(s)>(s);
    }
}

template<typename Container>
void print_container(const Container& c) {
    for(const auto& e : c) {
        std::cout << e << '\n';
    }
}

template<typename T>
using ElementType = decltype(* std::begin( std::declval<T>() ) );

template<typename Container>
concept IterableContainerType =
std::input_iterator< decltype( std::begin(std::declval<Container>()))>;

template<typename Printable>
concept PrintableType = requires(Printable&& value){
{ std::declval<std::ostream&>() <<
        std::forward<Printable>(value) }
-> std::same_as<std::ostream&>;
};

template<typename PrintableContainer>
concept PrintableContainerType =
PrintableType< ElementType<PrintableContainer> > &&
IterableContainerType<PrintableContainer>;

void print_container_better(PrintableContainerType auto & p){
    for(const auto& e : p){
        std::cout << e << '\n';
    }
}

template<PrintableType P>
struct Printer {
    P data;
    void print() const {
        std::cout << data;
    }
};

int main(){
    always<int>();
    //never<double>();
    neg(-3);
    //neg(false);

    std::string s{};
    std::cout << string_app(s,'A') << '\n';

    const std::string s2{};
    //std::cout << string_app(s2,"abc") << '\n';

    //integral_less("abc", 8);
    //integral_less(4.255,7);

    const int x = -1;
    //std::cout << write_to0(&x,0);
    //std::cout << write_to1(&x,1);
    //std::cout << write_to2(&x,2);
    //std::cout << write_to3(&x,3);
    //std::cout << write_to4(&x,4);

    //print_container(7);
    //print_container_better(7);

    Printer< std::vector<int> > p;

    return 0;
}
