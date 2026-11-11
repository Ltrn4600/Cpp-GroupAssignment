#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
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

    // Patient registration logic
    bool addPatient()
    {
        // 填后删
    }

    void createAppointment()
    {
        // 填后删
    }

    // generate ailment options according supported ailments
    vector<string> getAilmentOptions() const
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

    void viewQueue()
    {
        // 填后删
    }

    bool callNextPatient()
    {
        // 填后删
    }

    // Menu part
    void run()
    {
        // 填后删
    }

    void patientMenu()
    {
        // 填后删
    }

    void DoctorMenu()
    {
        // 填后删
    }
};
// ===========Main==============
int main()
{

    return 0;
};