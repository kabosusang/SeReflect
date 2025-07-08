#include <Macro/macro_static_reflect.hpp>
#include <Macro/macro_dynamic_reflect.hpp>

//TMP
#include <TMP/Se_Reflection.hpp>

bool Foo(int){
    return false;
}

struct Person{
    bool IsFemale(){}
    bool IsFemaleconst () const {}

    float height;

};

BEGIN_CLASS(Person)
    FUNCTIONS(function_traits<decltype(&Person::IsFemale)>,
              function_traits<decltype(&Person::IsFemaleconst)>)
END_CLASS()

int main()
{
    using type = TypeInfo<Person>;
    
    
    return 0;
}