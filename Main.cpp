#include "PatientList.h"
#include <iostream>
#include <limits>
#include <string>

int getValidatedInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
        std::cin >> value;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string getLineInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int main() {
    PatientList patientList;
    const std::string filename = "patients.txt";

    if (patientList.loadFromFile(filename)) {
        std::cout << "Patient data loaded from file.\n";
    } else {
        std::cout << "No existing patient file found. Starting fresh.\n";
    }

    int choice;

    do {
        std::cout << "\n===== Patient Appointment System =====\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. Find Patient by ID\n";
        std::cout << "3. Update Patient Information\n";
        std::cout << "4. Delete Patient\n";
        std::cout << "5. Show All Patients\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "8. Exit\n";

        choice = getValidatedInt("Enter your choice: ");

        if (choice == 1) {
            std::string name = getLineInput("Enter patient name: ");
            int id = getValidatedInt("Enter patient ID: ");
            int age = getValidatedInt("Enter patient age: ");
            std::string appointmentDate = getLineInput("Enter appointment date (MM-DD-YYYY): ");

            patientList.addPatient(name, id, age, appointmentDate);
        }
        else if (choice == 2) {
            int id = getValidatedInt("Enter patient ID to find: ");
            Patient* foundPatient = patientList.findPatientByIdBinary(id);

            if (foundPatient != nullptr) {
                std::cout << "\nPatient Found:\n";
                std::cout << "----------------------\n";
                foundPatient->displayInfo();
            } else {
                std::cout << "Patient not found.\n";
            }
        }
        else if (choice == 3) {
            int id = getValidatedInt("Enter patient ID to update: ");
            Patient* foundPatient = patientList.findPatientByIdBinary(id);

            if (foundPatient == nullptr) {
                std::cout << "Patient not found.\n";
                continue;
            }

            std::cout << "\nCurrent Patient Information:\n";
            foundPatient->displayInfo();

            std::string newName = getLineInput("Enter new name: ");
            int newAge = getValidatedInt("Enter new age: ");
            std::string newAppointmentDate = getLineInput("Enter new appointment date (MM-DD-YYYY): ");

            if (patientList.updatePatient(id, newName, newAge, newAppointmentDate)) {
                std::cout << "Patient updated successfully.\n";
            } else {
                std::cout << "Failed to update patient.\n";
            }
        }
        else if (choice == 4) {
            int id = getValidatedInt("Enter patient ID to delete: ");

            if (patientList.deletePatient(id)) {
                std::cout << "Patient deleted successfully.\n";
            } else {
                std::cout << "Patient not found.\n";
            }
        }
        else if (choice == 5) {
            std::cout << "\n===== Patient List (Alphabetical Order) =====\n";
            patientList.displayAllPatients();
        }
        else if (choice == 6) {
            if (patientList.saveToFile(filename)) {
                std::cout << "Patient data saved successfully.\n";
            } else {
                std::cout << "Failed to save patient data.\n";
            }
        }
        else if (choice == 7) {
            if (patientList.loadFromFile(filename)) {
                std::cout << "Patient data loaded successfully.\n";
            } else {
                std::cout << "Failed to load patient data.\n";
            }
        }
        else if (choice == 8) {
            if (patientList.saveToFile(filename)) {
                std::cout << "Data saved before exiting.\n";
            }
            std::cout << "Exiting program...\n";
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
