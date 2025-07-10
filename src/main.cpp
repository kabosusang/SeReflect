#include "TMP/variable_traits.hpp"
#include <Macro/macro_static_reflect.hpp>
#include <Macro/macro_dynamic_reflect.hpp>

//TMP
#include <TMP/Se_Reflection.hpp>
#include <tuple>
#include <type_traits>

bool Foo(int){
    return false;
}

struct Person{
    std::string familyName;
    float height;
    bool isFemale;

    void IntroduceMyself() const {}
    bool IsFemale() const {return false;}

    bool GetMarried(Person& other){
        bool success = other.isFemale != isFemale;
        if (isFemale){
            familyName = "Mrs." + other.familyName;
        }else {
            familyName = "Mr." + other.familyName;
        }
        return success;
    }
};


template <typename RetT,typename... Params>
auto function_pointer_type(RetT(*)(Params...)) ->RetT(*)(Params...);

template <typename RetT,typename Class,typename... Params>
auto function_pointer_type(RetT(Class::*)(Params...)) ->RetT(Class::*)(Params...);

template <typename RetT,typename Class,typename... Params>
auto function_pointer_type(RetT(Class::*)(Params...)const) ->RetT(Class::*)(Params...)const;


template <auto F>
using function_pointer_type_t = decltype(function_pointer_type(F));

// template <auto F>
// using function_traits_t = function_traits<function_pointer_type_t<F>>;



template <typename T>
struct is_function{
    static constexpr bool value = std::is_function_v<T> || std::is_member_function_pointer_v<T>;
};




template<typename T,bool isFunc>
struct basic_filed_traits;

template<typename T>
struct basic_filed_traits<T,true>:public function_traits<T>{
    using traits = function_traits<T>;

    consteval bool is_member() const{
        return traits::is_member;
    }

    consteval bool is_const() const{
        return traits::is_const;
    }

    consteval bool is_function() const{
        return true;
    }

     consteval bool is_variable() const{
        return false;
    }
};


template<typename T>
struct basic_filed_traits<T,false>:public variable_traits<T>{
    using traits = variable_traits<T>;

    consteval bool is_member() const{
        return traits::is_member;
    }

    consteval bool is_const() const{
        return traits::is_const;
    }

    consteval bool is_function() const{
        return false;
    }

     consteval bool is_variable() const{
        return true;
    }
};



template <typename T>
struct filed_traits: public basic_filed_traits<T,is_function<T>::value> {
    consteval filed_traits(T&& pointer) : pointer{pointer}{}
    
    T pointer;
};





template <typename T>
struct TypeInfo;

template<>
struct TypeInfo<Person>{
    // using functions = 
    //     std::tuple<function_traits_t<&Person::IntroduceMyself>>;
};





int main()
{
    using nameType = variable_traits<decltype(&Person::familyName)>;
    using funcType = variable_traits<decltype(&Person::GetMarried)>;


    using type1 = function_pointer_type_t<&Person::GetMarried>;
    using type2 = function_pointer_type_t<&Person::IntroduceMyself>;
    using type3 = function_pointer_type_t<&Person::IsFemale>;

    static_assert(std::is_same_v<type1, bool(Person::*)(Person&)>);
    static_assert(std::is_same_v<type2, void(Person::*)(void)const>);
    static_assert(std::is_same_v<type3, bool(Person::*)(void)const>);


    auto field = filed_traits{&Person::GetMarried};

    std::cout << field.pointer;

}