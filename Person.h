//Person.h
#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    int id;

public:
    Person();
    Person(const std::string& n, int i);

    void setName(const std::string& n);
    void setId(int i);

    std::string getName() const;
    int getId() const;

    virtual void displayInfo() const = 0;
    virtual ~Person() = default;
};

#endif
