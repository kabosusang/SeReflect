#ifndef SEREFLECT_STATIC_H_
#define SEREFLECT_STATIC_H_
#include <tuple>



template <typename T>
struct show_tmpl;


//类型萃取
template <typename T>
struct remove_pointer;

template <typename T>
struct remove_pointer<T*> 
{
    using type = T;
};


//类型萃取 函数指针
template<typename T>
struct function_traits;

template<typename Ret,typename... Args>
struct function_traits<Ret(*)(Args...)>
{
    using return_type = Ret;
    using param = std::tuple<Args...>;
    static constexpr bool is_class = false;
};

//类型萃取 类成员函数
template<typename Ret,typename Class,typename... Param>
struct function_traits<Ret(Class::*)(Param...)>
{
    using return_type = Ret;
    using param = std::tuple<Param...>;
    using class_type = Class;
    static constexpr bool is_class = true;
};

//类型萃取 类成员函数(常量函数)
template<typename Ret,typename Class,typename... Param>
struct function_traits<Ret(Class::*)(Param...)const>
{
    using return_type = Ret;
    using param = std::tuple<Param...>;
    using class_type = Class;
    static constexpr bool is_class = true;
    static constexpr bool is_const = true;
};


//类型萃取 类成员变量
template <typename T>
struct variable_traits;

template<typename Ret,typename Class>
struct function_traits<Ret(Class::*)>
{
    using return_type = Ret;
    using class_type = Class;
    static constexpr bool is_class = true;
};

template <typename T>
struct TypeInfo;

#define BEGIN_CLASS(T)                               \
template <>                                          \
struct TypeInfo<T>{                                  \
    using type = T;                                  \

#define FUNCTIONS(...)  using functions = std::tuple< __VA_ARGS__>;  \

#define END_CLASS() }; \








#endif
