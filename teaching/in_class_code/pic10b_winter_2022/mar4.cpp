#include <iostream>

template<typename T>
struct Foo{
    static constexpr int i = 0;
    struct Bar{};
    using str = std::string;
};

template<typename T>
void baz(const Foo<T>& f){
    typename Foo<T>::str s = "hello";
    typename Foo<T>::Bar b;
    int j = Foo<T>::i;
}

void bazz(const Foo<int>& f){
    Foo<int>::str s = "hello";
    Foo<int>::Bar b;
    int j = Foo<int>::i;
}

int main()
{
   Foo<int> d;
   baz(d);
   bazz(d);

    return 0;
}
