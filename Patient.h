//Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <iostream>
#include <string>

class Patient : public Person {
private:
    int age;
    std::string appointmentDate; // MM-DD-YYYY

public:
    Patient();
    Patient(const std::string& n, int i, int a, const std::string& apptDate);

    int getAge() const;
    std::string getAppointmentDate() const;

    void setAge(int a);
    void setAppointmentDate(const std::string& apptDate);

    void displayInfo() const override;

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif
