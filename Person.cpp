//Person.cpp
#include "Person.h"

Person::Person() : name(""), id(0) {}

Person::Person(const std::string& n, int i) : name(n), id(i) {}

void Person::setName(const std::string& n) {
    name = n;
}

void Person::setId(int i) {
    id = i;
}

std::string Person::getName() const {
    return name;
}

int Person::getId() const {
    return id;
}
