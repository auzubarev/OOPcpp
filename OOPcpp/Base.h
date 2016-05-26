#pragma once
#include <string>

class Printable {
public:
	virtual std::string print() const = 0;
protected:
	std::string str(double d) const {
		return std::to_string(d).erase(std::to_string(d).size() - 4);
	}
	std::string str(int i) const {
		return std::to_string(i);
	}
};

class Named : public virtual Printable {
public:
	std::string print() const {
	return "Name: " + name + ";\n";
	}
	Named(std::string _name) : name(_name) {};
private:
	const std::string name;
};
