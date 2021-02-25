#include <iostream>
#include <version.h>

namespace {

template<int P>
struct fact {
    static const int value = P * fact<P-1>::value;
};

template<>
struct fact<0> {
    static const int value = 1;
};

// -------------------------------------------------------------------

template <class T>
struct is_int {
    static const bool value = false;
};

template <>
struct is_int<int> {
    static const bool value = true;
};

// -------------------------------------------------------------------

// template <class T>
// struct remove_const {
//     using type = T;
// };

// template <class T>
// struct remove_const<const T> {
//     using type = T;

// };

// -------------------------------------------------------------------

template <class T>
struct type_is {
    using type = T;
};

template <class T>
struct remove_const : type_is<T> {};

template <class T>
struct remove_const<const T> : type_is<T> {};

// -------------------------------------------------------------------

template <bool C, class T, class F>
struct conditional : type_is<T> {};

template<class T, class F>
struct conditional<false, T, F> : type_is<F> {};

// -------------------------------------------------------------------

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };

// -------------------------------------------------------------------

struct A {
    void foo(int ) { return ; }
};

struct B {
    int foo(int ) { return 2; }
};

template <class T>
struct has_foo {
private:
    static int detect(...);
    
    template <class U>
    static decltype(std::declval<U>().foo(43)) detect(const U&);

public:
    static const bool value = std::is_same<
        void, 
        decltype(
            detect(std::declval<T>())
        )
        >::value;
};

}
// -------------------------------------------------------------------

int main() {
    std::cout << "Print v.0.0." << PROJECT_VERSION_PATCH << std::endl;

    std::cout << fact<7>::value << std::endl;
    std::cout << is_int<double>::value << std::endl;
    std::cout << is_int<int>::value << std::endl;

    remove_const<const int>::type b = 1;
    b = 2;
    std::cout << b << std::endl;
    constexpr bool flag = false;
    conditional<flag, int, double>::type c = 1.21;
    std::cout  << c << std::endl;

    if (has_foo<int>::value) {
        std::cout << "int has foo" << "\n";
    } else {
        std::cout << "int has not foo" << "\n";
    }

    if (has_foo<A>::value) {
        std::cout << "A has foo" << "\n";
    } else {
        std::cout << "A has not foo" << "\n";
    }

    if (has_foo<B>::value) {
        std::cout << "B has foo" << "\n";
    } else {
        std::cout << "B has not foo" << "\n";
    }
}
