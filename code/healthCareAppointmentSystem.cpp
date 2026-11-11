#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class Person
{
protected:
    string id;
    string name;

public:
    Person(string id, string name)
        : id(id), name(name)
    {
        // initializer list
    }

    string getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    virtual void displayInfo() const
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
    }
};

class Patient : public Person
{ // Patient inherit Person
private:
    string ailment; // 病理

public:
    Patient(string id, string name, string ailment)
        : Person(id, name), ailment(ailment) {}
    // initialize person and patient

    string getAilment() const
    {
        return ailment;
    }

    void displayInfo() const override
    {
        cout << "Patient ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Ailment: " << ailment << endl;
    }
};

class Doctor : public Person
{
private:
    vector<string> supportedAilments;

public:
    Doctor(string id, string name, vector<string> ailments)
        : Person(id, name), supportedAilments(ailments) {}
    // initialize person and doctor

    bool canHandle(string ailment) const
    {
        for (const string &supported : supportedAilments)
        {
            if (supported == ailment)
            {
                return true;
            }
        }

        return false;
    }

    void displayInfo() const override
    {
        cout << "Doctor ID: " << id << endl;
        cout << "Doctor Name: " << name << endl;
        cout << "Supported Ailments: ";

        for (size_t i = 0; i < supportedAilments.size(); i++)
        {
            cout << supportedAilments[i];

            if (i + 1 < supportedAilments.size())
            {
                cout << ", ";
            }
            // output all supported ailments
        }
        cout << endl;
    }

    vector<string> getSupportedAilments() const
    {
        return supportedAilments;
    }
};

class Appointment
{
private:
    string appointmentID;
    string patientID;
    string doctorID;
    string status;

public:
    Appointment(string id, string patientID, string doctorID)
        : appointmentID(id), patientID(patientID), doctorID(doctorID), status("Waiting") {}
    // initialization for appointment system

    string getPatientID() const
    {
        return patientID;
    }

    string getDoctorID() const
    {
        return doctorID;
    }

    string getStatus() const
    {
        return status;
    }

    bool setStatus(string newStatus)
    {
        if (status == "Waiting" && newStatus == "Called")
        {
            status = newStatus;
            return true;
        }

        if (status == "Called" && newStatus == "Completed")
        {
            status = newStatus;
            return true;
        }

        return false;
    }

    void displayInfo() const
    {
        cout << "Appointment ID: " << appointmentID << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Status: " << status << endl;
    }
};

class ClinicSystem
{
private:
    vector<Patient> patient;
    vector<Appointment> appointment;
    vector<Doctor> doctor;
    int nextPatientID = 1;
    int nextAppointmentID = 1;

public:
    // built-in doctors' data
    ClinicSystem()
    {
        doctor.push_back(
            Doctor("D001", "Doctor Ali", {"Fever", "Cough", "Headache", "Stomach", "Other"}));

        doctor.push_back(
            Doctor("D002", "Doctor Lee", {"Fever", "Skin", "Headache", "Allergy"}));

        // 3 Ailments
        doctor.push_back(
            Doctor("D003", "Doctor Tan", {"Stomach", "Cough", "Skin"}));

        doctor.push_back(
            Doctor("D004", "Doctor Lim", {"Headache", "Allergy", "Fever"}));
    }

    // generate ailment options according supported ailments
    vector<string> getAilmentOptions()
    {
        vector<string> options;

        for (const Doctor &doctor : doctor)
        {
            for (const string &ailment : doctor.getSupportedAilments())
            {

                // Avoid duplicate ailment options
                if (find(options.begin(), options.end(), ailment) == options.end())
                {
                    options.push_back(ailment);
                }
            }
        }

        return options;
    }

    // Core system-distribute doctor according to ailment selected
    string findDoctor(const string &ailment)
    {
        string selectedDoctor = "";
        int shortestQueue = -1;

        // Search for suitable doctors
        for (const Doctor &doctor : doctor)
        {
            if (!doctor.canHandle(ailment))
                continue;

            int queueSize = 0;

            // Count waiting appointments
            for (const Appointment &appointment : appointment)
            {
                if (appointment.getDoctorID() == doctor.getID() && appointment.getStatus() == "Waiting")
                {
                    queueSize++;
                }
            }

            // Select the doctor with the shortest queue
            if (selectedDoctor == "" || queueSize < shortestQueue || (queueSize == shortestQueue && doctor.getID() < selectedDoctor))
            {
                selectedDoctor = doctor.getID();
                shortestQueue = queueSize;
            }
        }

        // Fallback doctor for unmatched ailments
        if (selectedDoctor == "" && ailment != "Other")
        {
            return findDoctor("Other");
        }

        return selectedDoctor;
    }

    // Patient registration logic

    bool addPatient()
    {
        string name;
        int choice;

        vector<string> options = getAilmentOptions();

        if (options.empty())
        {
            cout << "No available ailments!" << endl;
            return false;
        }

        while (true)
        {
            cout << "\n======= PATIENT REGISTRATION =======" << endl;

            // Enter patient name
            cout << "Enter Patient Name: ";
            if (!getline(cin, name))
                return false;

            // Check empty name
            if (name.find_first_not_of(" \t") == string::npos)
            {
                cout << "Invalid name!" << endl;
                continue;
            }

            // Display ailment options
            cout << "\nSelect Ailment:" << endl;

            for (int i = 0; i < static_cast<int>(options.size()); i++)
            {
                cout << i + 1 << ". " << options[i] << endl;
            }

            cout << "Enter choice: ";
            cin >> choice;

            // Check invalid input
            if (cin.fail())
            {
                if (cin.eof())
                    return false;

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            // Check choice range
            if (choice < 1 || choice > static_cast<int>(options.size()))
            {
                cout << "Invalid choice!" << endl;
                continue;
            }

            string ailment = options[choice - 1];

            // Generate Patient ID
            string id = "P";

            if (nextPatientID < 10)
                id += "00";
            else if (nextPatientID < 100)
                id += "0";

            id += to_string(nextPatientID);

            // Check duplicate ID
            bool duplicate = false;

            for (const Patient &p : patient)
            {
                if (p.getID() == id)
                {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate)
            {
                cout << "Duplicate Patient ID!" << endl;
                return false;
            }

            // Save patient
            patient.push_back(Patient(id, name, ailment));

            nextPatientID++;

            cout << "\nPatient registered successfully!" << endl;
            cout << "Patient ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Ailment: " << ailment << endl;

            return true;
        }
    }

    bool createAppointment(string patientID)
    {
        for (const Patient &p : patient)
        {
            if (p.getID() == patientID)
            {
                // Automatically assign a doctor
                string doctorID = findDoctor(p.getAilment());

                if (doctorID == "")
                {
                    cout << "No suitable doctor found!" << endl;
                    return false;
                }

                // Generate Appointment ID
                string id = "A" + to_string(nextAppointmentID);

                // Save appointment
                appointment.push_back(Appointment(id, patientID, doctorID));

                nextAppointmentID++;

                cout << "\nAppointment created successfully!" << endl;
                cout << "Appointment ID: " << id << endl;
                for (const Doctor &d : doctor)
                {
                    if (d.getID() == doctorID)
                    {
                        cout << "Assigned Doctor: " << d.getID() << " - " << d.getName() << endl;
                        break;
                    }
                }

                return true;
            }
        }

        cout << "Patient not found!" << endl;
        return false;
    }

    void viewQueue(string doctorID)
    {
        int count = 0;

        cout << "\n======= DOCTOR QUEUE =======" << endl;
        cout << "Doctor ID: " << doctorID << endl;

        for (const Appointment &a : appointment)
        {
            if (a.getDoctorID() == doctorID && a.getStatus() == "Waiting")
            {
                count++;

                cout << "\nQueue No: " << count << endl;
                cout << "Patient ID: " << a.getPatientID() << endl;
            }
        }

        cout << "\nTotal Waiting: " << count << endl;

        if (count == 0)
        {
            cout << "No patients waiting." << endl;
        }
    }

    bool callNextPatient(string doctorID)
    {
        // Complete the previously called patient
        for (Appointment &a : appointment)
        {
            if (a.getDoctorID() == doctorID && a.getStatus() == "Called")
            {
                a.setStatus("Completed");
                break;
            }
        }

        // Find the next waiting patient
        for (Appointment &a : appointment)
        {
            if (a.getDoctorID() == doctorID && a.getStatus() == "Waiting")
            {
                a.setStatus("Called");

                cout << "\nCalling next patient!" << endl;
                cout << "Doctor ID: " << doctorID << endl;
                cout << "Patient ID: " << a.getPatientID() << endl;

                return true;
            }
        }

        cout << "No patients waiting." << endl;
        return false;
    }

    // Menu part

    void patientMenu()
    {
        int choice;

        do
        {
            cout << "\n======= PATIENT SYSTEM =======" << endl;
            cout << "1. Register / Make Appointment" << endl;
            cout << "2. View Queue" << endl;
            cout << "0. Back" << endl;
            cout << "Enter choice: ";

            if (!(cin >> choice))
            {
                if (cin.eof())
                    return;

                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input!" << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            switch (choice)
            {
            case 1:
                if (addPatient())
                {
                    string patientID = patient.back().getID();
                    createAppointment(patientID);
                }
                break;

            case 2:
            {
                string patientID;
                bool found = false;

                cout << "Enter Patient ID: ";
                getline(cin, patientID);

                for (const Appointment &a : appointment)
                {
                    if (a.getPatientID() == patientID && a.getStatus() != "Completed")
                    {
                        viewQueue(a.getDoctorID());
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "No active appointment found." << endl;

                break;
            }

            case 0:
                break;

            default:
                cout << "Invalid choice!" << endl;
            }

        } while (choice != 0);
    }

    void doctorMenu()
    {
        string doctorID;
        bool found = false;

        cout << "\n======= SELECT DOCTOR =======" << endl;

        // Display predefined doctors
        for (const Doctor &d : doctor)
        {
            cout << d.getID() << " - " << d.getName() << endl;
        }

        cout << "Enter Doctor ID: ";
        cin >> doctorID;
        cin.ignore(1000, '\n');

        // Validate Doctor ID
        for (const Doctor &d : doctor)
        {
            if (d.getID() == doctorID)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Invalid Doctor ID!" << endl;
            return;
        }

        int choice;

        do
        {
            cout << "\n======= DOCTOR SYSTEM =======" << endl;
            cout << "Current Doctor: " << doctorID << endl;
            cout << "1. View Queue" << endl;
            cout << "2. Call Next Patient" << endl;
            cout << "0. Back" << endl;
            cout << "Enter choice: ";

            if (!(cin >> choice))
            {
                if (cin.eof())
                    return;

                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input!" << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            switch (choice)
            {
            case 1:
                viewQueue(doctorID);
                break;

            case 2:
                callNextPatient(doctorID);
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice!" << endl;
            }

        } while (choice != 0);
    }

    void run()
    {
        int choice = 0;

        do
        {
            cout << "\n======= CLINIC MANAGEMENT SYSTEM =======" << endl;
            cout << "1. Patient System" << endl;
            cout << "2. Doctor System" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter choice: ";

            cin >> choice;

            if (cin.fail())
            {
                if (cin.eof())
                {
                    return;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            switch (choice)
            {
            case 1:
                patientMenu();
                break;

            case 2:
                doctorMenu();
                break;

            case 0:
                cout << "Exiting system..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
            }

        } while (choice != 0);
    }
};

// ===========Main==============
int main()
{
    ClinicSystem clinic;
    clinic.run();

    return 0;
}