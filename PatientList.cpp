//PatientList.cpp
#include "PatientList.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

PatientList::PatientList() : head(nullptr) {}

PatientList::~PatientList() {
    clear();
}

void PatientList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

std::string PatientList::toLowerCase(const std::string& str) const {
    std::string lower = str;
    for (char& ch : lower) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return lower;
}

bool PatientList::lessCaseInsensitive(const std::string& a, const std::string& b) const {
    return toLowerCase(a) < toLowerCase(b);
}

bool PatientList::isLeapYear(int year) const {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int PatientList::daysInMonth(int month, int year) const {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

bool PatientList::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[2] != '-' || date[5] != '-') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) {
            continue;
        }
        if (!std::isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int month = std::stoi(date.substr(0, 2));
    int day = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (year < 1900 || year > 2100) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    int maxDay = daysInMonth(month, year);
    if (day < 1 || day > maxDay) {
        return false;
    }

    return true;
}

bool PatientList::hasAppointmentConflict(const std::string& appointmentDate, int ignoreId) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getId() != ignoreId &&
            current->data.getAppointmentDate() == appointmentDate) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void PatientList::addPatient(const std::string& name, int id, int age, const std::string& appointmentDate) {
    if (findPatientByIdBinary(id) != nullptr) {
        std::cout << "A patient with that ID already exists.\n";
        return;
    }

    if (age < 0 || age > 130) {
        std::cout << "Invalid age.\n";
        return;
    }

    if (!isValidDate(appointmentDate)) {
        std::cout << "Invalid date. Use MM-DD-YYYY.\n";
        return;
    }

    if (hasAppointmentConflict(appointmentDate)) {
        std::cout << "Appointment conflict: another patient already has that date.\n";
        return;
    }

    Patient newPatient(name, id, age, appointmentDate);
    Node* newNode = new Node(newPatient);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    insertionSortByName();
    std::cout << "Patient added successfully.\n";
}

Patient* PatientList::findPatientByIdBinary(int id) {
    std::vector<Node*> indexList;
    Node* current = head;

    while (current != nullptr) {
        indexList.push_back(current);
        current = current->next;
    }

    std::sort(indexList.begin(), indexList.end(),
              [](Node* a, Node* b) {
                  return a->data.getId() < b->data.getId();
              });

    int left = 0;
    int right = static_cast<int>(indexList.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midId = indexList[mid]->data.getId();

        if (midId == id) {
            return &(indexList[mid]->data);
        } else if (midId < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nullptr;
}

bool PatientList::deletePatient(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getId() == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.getId() != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

bool PatientList::updatePatient(int id, const std::string& newName, int newAge, const std::string& newAppointmentDate) {
    Patient* patient = findPatientByIdBinary(id);
    if (patient == nullptr) {
        return false;
    }

    if (newAge < 0 || newAge > 130) {
        std::cout << "Invalid age.\n";
        return false;
    }

    if (!isValidDate(newAppointmentDate)) {
        std::cout << "Invalid date. Use MM-DD-YYYY.\n";
        return false;
    }

    if (hasAppointmentConflict(newAppointmentDate, id)) {
        std::cout << "Appointment conflict: another patient already has that date.\n";
        return false;
    }

    patient->setName(newName);
    patient->setAge(newAge);
    patient->setAppointmentDate(newAppointmentDate);

    insertionSortByName();
    return true;
}

void PatientList::displayAllPatients() const {
    if (head == nullptr) {
        std::cout << "No patients in the list.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << '\n';
        current = current->next;
    }
}

void PatientList::insertionSortByName() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;

        if (sorted == nullptr ||
            lessCaseInsensitive(current->data.getName(), sorted->data.getName())) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr &&
                   !lessCaseInsensitive(current->data.getName(), temp->next->data.getName())) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    head = sorted;
}

bool PatientList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        return false;
    }

    Node* current = head;
    while (current != nullptr) {
        outFile << current->data.getName() << ','
                << current->data.getId() << ','
                << current->data.getAge() << ','
                << current->data.getAppointmentDate() << '\n';
        current = current->next;
    }

    return true;
}

bool PatientList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        return false;
    }

    clear();

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string name;
        std::string idStr;
        std::string ageStr;
        std::string appointmentDate;

        std::getline(ss, name, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, appointmentDate);

        if (name.empty() || idStr.empty() || ageStr.empty() || appointmentDate.empty()) {
            continue;
        }

        int id = std::stoi(idStr);
        int age = std::stoi(ageStr);

        if (age < 0 || age > 130 || !isValidDate(appointmentDate) ||
            hasAppointmentConflict(appointmentDate)) {
            continue;
        }

        Patient newPatient(name, id, age, appointmentDate);
        Node* newNode = new Node(newPatient);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    insertionSortByName();
    return true;
}
