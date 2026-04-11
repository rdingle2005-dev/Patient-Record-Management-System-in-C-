//PatientList.h
#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include "Node.h"
#include <string>
#include <vector>

class PatientList {
private:
    Node* head;

    std::string toLowerCase(const std::string& str) const;
    bool lessCaseInsensitive(const std::string& a, const std::string& b) const;

    bool isLeapYear(int year) const;
    int daysInMonth(int month, int year) const;

public:
    PatientList();
    ~PatientList();

    void clear();

    bool isValidDate(const std::string& date) const;
    bool hasAppointmentConflict(const std::string& appointmentDate, int ignoreId = -1) const;

    void addPatient(const std::string& name, int id, int age, const std::string& appointmentDate);
    Patient* findPatientByIdBinary(int id);
    bool deletePatient(int id);
    bool updatePatient(int id, const std::string& newName, int newAge, const std::string& newAppointmentDate);

    void displayAllPatients() const;
    void insertionSortByName();

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif
