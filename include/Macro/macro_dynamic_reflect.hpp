#ifndef SEREFLECT_MACRO_DYNAMIC_H_
#define SEREFLECT_MACRO_DYNAMIC_H_

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace SeReflection {

class Reflectable {
public:
	std::map<std::string, std::any> properties;
	std::map<std::string, std::function<void(std::any)>> methods;

	template <typename T>
	void setProperty(const std::string& name, T value) {
		properties[name] = value;
	}

	template <typename T>
	T getProperty(const std::string& name) const {
		try {
			return std::any_cast<T>(properties.at(name));
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			throw;
		}
	}

	void invokeMethod(const std::string& name, std::any arg) {
		if (methods.find(name) != methods.end()) {
			methods[name](arg);
		} else {
			std::cerr << "Method not found: " << name << std::endl;
		}
	}
};

class Person_dynamic : public Reflectable {
public:
	Person_dynamic(int id, const std::string& name, const std::string& email) {
		setProperty("id", id);
		setProperty("name", name);
		setProperty("email", email);

		methods["setName"] = [this](std::any arg) {
			try {
				this->name = std::any_cast<std::string>(arg);
				setProperty("name", this->name);
			} catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		};

		methods["printInfo"] = [this](std::any) {
			std::cout << "ID: " << this->id << ", Name: " << this->name << ", Email: " << this->email << std::endl;
		};
	}

private:
	int id;
	std::string name;
	std::string email;
};

/*  Use
    Person_dynamic person(1, "John Doe", "johndoe@example.com");

    // 动态获取属性值
    int id = person.getProperty<int>("id");
    std::string name = person.getProperty<std::string>("name");
    std::string email = person.getProperty<std::string>("email");

    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;

    // 动态调用方法
    person.invokeMethod("setName", std::string("Jane Doe"));
    person.invokeMethod("printInfo", nullptr);
*/






} //namespace SeReflection

#endif