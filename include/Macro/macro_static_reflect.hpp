#ifndef SEREFLECT_MACRO_STATIC_H_
#define SEREFLECT_MACRO_STATIC_H_

#include <string>
#include <iostream>
#include <vector>


namespace SeReflection {


//////////////////////////Simple/////////////////////////////////////////
#define REFLECT(...) \
    static std::vector<std::pair<std::string, size_t>> getMemberInfo() { \
        return { __VA_ARGS__ }; \
    }

#define MEMBER_INFO(name) {#name, offsetof(Person_static, name)}


class Person_static{
public:
    int id;
    std::string name;
    std::string email;

    REFLECT(
        MEMBER_INFO(id),
        MEMBER_INFO(name),
        MEMBER_INFO(email)
    )
};

////////////////////////////////////////////////////////////////////////////





}










#endif