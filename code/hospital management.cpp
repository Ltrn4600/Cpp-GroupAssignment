#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>
using namespace std;

const int MAX_ROOMS=50;
const int MAX_HISTORY=200;

class Patient {
    public:
    int id=0,age=0;
    string name,gender,disease,phone;
    Patient* next =NULL;
};

class Doctor {
    public:
    int id=0;
    string name,gender,specialty,phone;
    Doctor* next=NULL;
};

class Appointment {
    public:
    int id=0,patientID=0,doctorID=0;
    string date,time;
    Appointment* next=NULL;
};

class Emergency {
public:
int patientID=0,priority=3;
string reason;
Emergency* next=NULL;
};

class MedicalRecord {
public:
int patientID=0;
string date,diagnosis,treatment;
MedicalRecord* next=NULL;
};

class Medicine {
public:
int id=0,stock=0;
string name;
double price=0.0;
Medicine* next=NULL;
};

class Bill{
public:
int id=0,patientID=0;
double consultation=0.0,medicine=0.0,room=0.0,total=0.0;
Bill* next=NULL;
};

class HospitalSystem{
private:
Patient* patientHead=NULL;
Doctor* doctorHead=NULL;
Appointment* appointmentFront=NULL;
Appointment* appointmentRear=NULL;
Emergency* emergencyHead=NULL;
MedicalRecord* recordHead=NULL;
Medicine* medicineHead=NULL;
Bill* billHead=NULL;

string history[MAX_HISTORY];
int historyTop=-1;
int rooms[MAX_ROOMS+1]={};

static string readLine(const string& prompt){
    string value;
    cout<<prompt;
    getline(cin>>ws,value);
    return value;
}

static int inputInt(const string& prompt){
    string line;
    int value;
    while(true){
        cout<<prompt;
        if(!getline(cin,line)) return 0;
        stringstream ss(line);
        char extra;
        if(ss>>value&&!(ss>>extra)) return value;
        cout<<"Invalid integer.Please Try again!"<<endl;
    }
}

static double InputDouble(const string& prompt){
    string line;
    double value;
    while(true){
        cout<<prompt;
        if(!getline(cin,line)) return 0;
        stringstream ss(line);
        char extra;
        if(ss>>value&&!(ss>>extra)) return value;
        cout<<"Invalid integer.Please Try again!"<<endl;
    }
}

void pushHistory(const string& action){
    if(historyTop>=MAX_HISTORY-1){
        cout<<"History stack is full!"<<endl;
        return ;
    }
    history[++historyTop]=action;
}

Patient* findPatient(int id) const {
    for (Patient* p= patientHead; p; p=p->next)
    if(p->id==id) return p;
    return NULL;
}

Doctor* findDoctor(int id) const {
    for(Doctor* d=doctorHead; d; d=d->next)
    if(d->id==id) return d;
    return NULL;
}

Medicine* findMedicine(int id) const {
    for(Medicine* m =medicineHead; m ; m=m->next)
    if(m->id==id) return m;
    return NULL;
}

void addPatient(){
    int id=inputInt("Enter patient ID (Positive Integer):");
    if(id<0) {
        cout<<"PID must be a positive integer."<<endl;
        return;
    }
    if(findPatient(id)) {
        cout<<"Patient ID already exists."<<endl;
        return;
    }

    Patient* p=new Patient;
    p->id=id;
    p->name=readLine("Enter patient name: ");
    if(p->name.empty()){
        cout<<"Name cannot be empty!"<<endl;
        delete p;
        return ;
    }

     if(p->age<=0 ||p->age >200){
        cout<<"Invalid age!"<<endl;
        delete p;
        return ;
    }

    if(p->gender.empty()){
        cout<<"Gender cannot be empty!"<<endl;
        delete p;
        return ;
    }

    if(p->disease.empty()){
        cout<<"Disease/Condition cannot be empty!"<<endl;
        delete p;
        return ;
    }

    p->phone=readLine("Enter phone number: ");
    if(p->phone.empty()){
        cout<<"Phone number cannot be empty!"<<endl;
        delete p;
        return ;
    }

    p->next=patientHead;
    patientHead=p;
    pushHistory("Added patient");
    cout<<"Patient added successfully!"<<endl;
}

void displayPatients() const {
    cout<<"\n======== PATIENTS ========\n";
    if(!patientHead) {
        cout<<"No patients."<<endl;
    return ;
    }

    for(Patient* p=patientHead;p;p=p->next){
        cout<<"ID: "<<p->id<<"\nName: "<<p->name
            <<"\nAge: "<<p->age<<"\nGender: "<<p->gender
            <<"\nDisease: "<<p->disease<<"\nPhone: "<<p->phone
            <<"\n--------------------------------\n";
    }
}

void searchPatient() const {
    int id=inputInt("Enter patient ID: ");
    Patient* p=findPatient(id);
    if(!p){
        cout<<"Patient not found!\n";
        return;
    }

    cout<<"\nPatient Found\nID: "<<p->id<<"\nName: "<<p->name
            <<"\nAge: "<<p->age<<"\nGender: "<<p->gender
            <<"\nDisease: "<<p->disease<<"\nPhone: "<<p->phone<<endl;
}

void updatePatient(){
    int id=inputInt("Enter Patient ID:");
    Patient* p=findPatient(id);
    if(!p) {
        cout<<"Patient not found!"<<endl;
        return;
    }

    p->name=readLine("New name: ");
    p->age=inputInt("New age: ");
    p->gender=readLine("New gender: ");
    p->disease=readLine("New disease: ");
    p->phone=readLine("New phone: ");
    pushHistory("Updated patient");
    cout<<"Patient updated.\n";
}

void deletePatient(){
    int id=inputInt("Enter Patient ID: ");
    Patient *current=patientHead,*previous=NULL;
    while(current&&current->id!=id){
        previous=current;
        current=current->next;
    }
    if(!current){
        cout<<"Patient not found!"<<endl;
        return;
    }
    if(!previous) patientHead=current->next;
    else previous->next=current->next;

    for(int i=1;i<=MAX_ROOMS;++i)
        if(rooms[i]==id) rooms[i]=0;
    delete current;
    pushHistory("Deleted patient");
    cout<<"Patient Deleted!"<<endl;
}

void addDoctor(){
    int id=inputInt("Doctor Id (positive integer):");
    if(id<=0){
        cout<<"DID must be a positive integer!"<<endl;
        return;
    }
    if(findDoctor(id)) {
        cout<<"Doctor ID already exists!"<<endl;
        return;
    }
    Doctor* d=new Doctor;
    d->id=id;

    d->name=readLine("Doctor name: ");
    if(d->name.empty()){
        cout<<"Doctor name cannot be empty!"<<endl;
        delete d;
        return;
    }

    d->specialty=readLine("Specialty: ");
     if(d->specialty.empty()){
        cout<<"Specialty cannot be empty!"<<endl;
        delete d;
        return;
    }

    d->phone=readLine("Phone: ");
      if(d->phone.empty()){
        cout<<"Phone cannot be empty!"<<endl;
        delete d;
        return;
    }

    d->next=doctorHead;
    doctorHead=d;
    pushHistory("Added doctor");
    cout<<"Doctor added."<<endl;
}

void searchDoctorMenu() const {
    int id=inputInt("Doc tor ID: ");
    Doctor*d =findDoctor(id);
    if(!d){
        cout<<"Doctor not found!"<<endl;
        return;
    }
    cout <<"ID: "<<d->id<<" | Name: "<<d->name<<" | Specialty: "
         <<d->specialty<<" | Phone: "<<d->phone<<"\n";
}

void displayDoctors() const {
    cout<<"\n======== DOCTORS ========\n";
    if (!doctorHead) {
        cout<<"No Doctors!"<<endl;
        return;
    }
    for(Doctor*d=doctorHead;d;d=d->next)
    cout<<"ID:"<<d->id<<" | Name: "<<d->name<<" | Specialty: "
        <<d->specialty<<" | Phone: "<<d->phone<<endl;
}

bool appointmentIDExists(int id) const {
    for(Appointment* a=appointmentFront;a;a=a->next)
    if(a->id==id) return true;
    return false;
}

void enqueueAppointment(){
    int aid=inputInt("Appointment ID(AID): ");
    if (aid<=0) {
        cout<<"AID must be a positive integer!"<<endl;
        return;
    }
    if(appointmentIDExists(aid)){
        cout<<"AID already exists!"<<endl;
        return;
    }

    int pid=inputInt("Patient ID(PID)");
    Patient* patient=findPatient(pid);
    if(!patient){
        cout<<"PID does not exist.Register the patient first!"<<endl;
        return;
    }

    int did=inputInt("Doctor ID(DID)");
    Doctor* doctor=findDoctor(did);
    if(!doctor){
        cout<<"DID does not exist.Register the doctor first!"<<endl;
        return;
    }

    string date=readLine("Date (YYYY-MM-DD): ");
    string time=readLine("Time (HH:MM): ");
    if (date.empty() || time.empty()){
        cout<<"Date and time cannot be empty!"<<endl;
        return;
    }

    //Rejects both patient double-booking and doctor schedule conflicts
    for(Appointment* existing=appointmentFront;existing;existing=existing->next){
        if(existing->date==date&&existing->time==time){
            if(existing->patientID==pid){
                cout<<"Conflict:This patient already has an appointment at that date/time!";
                return;
            }
            if(existing->doctorID==did){
                cout<<"Conflict:This doctor already booked at that date/time!";
                return;
            }
        }
    }

    Appointment* a=new Appointment;
    a->id=aid;
    a->patientID=pid;
    a->doctorID=did;
    a->date=date;
    a->time=time;
    a->next=NULL;

    if(!appointmentRear){
        appointmentFront=appointmentRear=a;
    }
    else {
        appointmentRear->next=a;
        appointmentRear=a;
    }
    pushHistory("Created appointment/Added to Queue");
    cout<<"Appointed created and added to FIFO queue.\n"
        <<"AID: "<<aid<<" | PID: "<<pid<<" ("<<patient->name<< ")"
        <<" | DID: "<<did<<" ("<<doctor->name<< ")"
        <<" | "<<date<<" "<<time<<endl;
}

void dequeueAppointment(){
    if(!appointmentFront){
        cout<<"Appointment queue is empty."<<endl;
        return;
    }
    Appointment* a=appointmentFront;
    appointmentFront=appointmentFront->next;
    if(!appointmentFront) appointmentRear=NULL;
    Patient* p =findPatient(a->patientID);
    Doctor* d=findDoctor(a->doctorID);
    cout<<"Processing next appointment FIFO)\n"
        <<"AID: "<<a->id<<"\nPID: "<<a->patientID
        <<(p ? " | Patient: " + p->name : " | Patient record unavailable") //
        <<"\nDID: "<<a->doctorID
        <<(d ? " | Doctor: " + d->name : " | Doctor record unavailable")
        <<"\nDate: "<<a->date<<"\nTime: "<<a->time<<endl;
    delete a;
    pushHistory("Processed Appointment!");
    }

    void displayAppointments() const {
        cout<<"\n======== APPOINTMENT QUEUE/RECORDS ========\n";
        if(!appointmentFront) {
            cout<<"Queue is empty!"<<endl;
            return;
        }
        int position=1;
        for(Appointment* a=appointmentFront;a;a=a->next,++position){
            Patient* p =findPatient(a->patientID);
            Doctor* d =findDoctor(a->doctorID);
            cout<<position<<"AID: "<<a->id<<" | PID:"<<a->patientID
                <<(p ? " (" +p->name + ")" : "(record unavailable)")
                <<" | DID: "<<a->doctorID
                <<(d ? " (" +d->name + ")" : "(record unavailable)")
                <<" | "<<a->date<<" "<<a->time<<endl;
        }
    }

    void addEmergency(){
        Emergency* e=new Emergency;
        e->patientID=inputInt("Patient ID: ");
        if(!findPatient(e->patientID)){
            cout<<"Patient not found!";
            delete e;
            return ;
        }
        do {
            e->priority=inputInt("Priority (1=Critical, 2=Serious, 3=Normal): ");
            if (e->priority < 1 || e->priority > 3) cout << "Choose 1, 2, or 3.\n";
        } while (e->priority < 1 || e->priority > 3);
        e->reason=readLine("Emergency reason: ");

        //Lower priority number is more urgent;equal priorities remains FIFO
        if(!emergencyHead || e->priority < emergencyHead->priority){
            e->next=emergencyHead;
            emergencyHead=0;
        }
        else {
            Emergency* cur=emergencyHead;
            while(cur->next&&cur->next->priority <= e->priority) cur=cur->next;
            e->next=cur->next;
            cur->next=0;
        }
        pushHistory("Added emergency patient");
        cout<<"Emergency patient added!"<<endl;
    }

    void processEmergency() {
        if(!emergencyHead){
            cout<<"Emergency Queue empty!"<<endl;
            return;
        }
        Emergency* e = emergencyHead;
        emergencyHead = emergencyHead->next;
        cout<< "Processing emergency patient\nPatient ID: " << e->patientID
            << "\nPriority: " << e->priority << "\nReason: " << e->reason << '\n';
        delete e;
        pushHistory("Processed emergency patient");
    } 

    void displayEmergencies() const {
        cout<<"\n======== EMERGENCY QUEUE ========\n";
        if (!emergencyHead){
            cout<<"No emergency patients!"<<endl;
            return ;
        }
        for (Emergency* e=emergencyHead;e;e=e->next)
            cout<< "Patient: " << e->patientID << " | Priority: "
                << e->priority << " | " << e->reason << '\n';
    }

    void addMedicalRecord(){
        MedicalRecord* r=new MedicalRecord;
        r->patientID=inputInt("Patient ID: ");
        if(!findPatient(r->patientID)){
            cout<<"Patient not found!"<<endl;
            delete r;
            return;
        }
        r->date=readLine("Date: ");
        r->diagnosis=readLine("Diagnosis: ");
        r->treatment=readLine("Treatment: ");
        r->next=recordHead;
        recordHead=r;
        pushHistory("Added medical record");
        cout<<"Medical Record added!"<<endl;
    }

    void  viewMedicalRecords() const {
        int id=inputInt("Patient ID:");
        bool found=false;
        cout<<"\n======== MEDICAL HISTORY ========\n";
        for(MedicalRecord* r=recordHead;r;r=r->next){
            if(r->patientID==id){
                cout<< "Date: " << r->date << "\nDiagnosis: " << r->diagnosis
                    << "\nTreatment: " << r->treatment << "\n-------------------------\n";
                found = true;
            }
        }
        if(!found) cout<<"No medical records found!"<<endl;
    }

    void addMedicine() {
        int id=inputInt("Medicine ID: ");
        if(findMedicine(id)) {\
            cout<<"Medicine ID already exists!"<<endl;
            return ;
        }
        Medicine* m =new Medicine;
        m->id=id;
        m->name=readLine("Medicine name:");
        m->stock = inputInt("Stock: ");
        m->price = InputDouble("Price: ");
        if (m->stock < 0 || m->price < 0) {
            cout << "Stock and price cannot be negative.\n"; delete m; return;
        }
        m->next=medicineHead;
        medicineHead=m;
        pushHistory("Added Medicine");
        cout<<"Medicine added!"<<endl;
    }

    void displayMedicine() const {
        cout<<"\n======== PHARMACY ========\n";
        if(!medicineHead) {
            cout<<"No medicines!"<<endl;
            return;
        }
        for(Medicine* m=medicineHead;m;m->next)
            cout << "ID: " << m->id << " | Name: " << m->name
                << " | Stock: " << m->stock << " | Price: "
                << fixed << setprecision(2) << m->price << '\n';
    }

    void searchMedicineMenu() const {
        int id=inputInt("Medicine ID: ");
        Medicine* m =findMedicine(id);
        if(!m){
            cout<<"Medicine not found!"<<endl;
            return;
        }
        cout<< "ID: " << m->id << " | Name: " << m->name
            << " | Stock: " << m->stock << " | Price: "
            << fixed << setprecision(2) << m->price <<endl;
    }

    void dispenseMedicine() {
        int id=inputInt("Medicine ID");
        Medicine* m = findMedicine(id);
        if (!m) {
            cout << "Medicine not found."<<endl; 
            return; 
        }

        int quantity = inputInt("Quantity: ");
        if (quantity <= 0 || quantity > m->stock) {
            cout << "Invalid quantity.\n"; 
            return;
        }
        m->stock -= quantity;
        cout << "Medicine dispensed.\nCost: "<<fixed<<setprecision(2)
             << quantity * m->price <<endl;
        pushHistory("Dispensed medicine");
    }

    void createBill() {
        int id=inputInt("Bill ID: ");
        for(Bill* b =billHead;b;b=b->next)
            if(b->id==id) {
                cout<<"Bill ID already exists!"<<endl;
                return;
            }
            Bill* b =new Bill;
            b->consultation=InputDouble("Consultation fee: ");
            b->medicine=InputDouble("Medicine Fee: ");
            b->room=InputDouble("Room Fee: ");

            if (b->consultation < 0 || b->medicine < 0 || b->room < 0) {
            cout<<"Fees cannot be negative."<<endl;
            delete b; 
            return;
        }
        b->total = b->consultation + b->medicine + b->room;
        b->next=billHead;
        billHead=b;
        cout<< "\n========== BILL ==========\nBill ID: " << b->id
            << "\nPatient ID: " << b->patientID << "\nConsultation: " << b->consultation
            << "\nMedicine: " << b->medicine << "\nRoom: " << b->room
            << "\nTOTAL: " << fixed << setprecision(2) << b->total << '\n';
        pushHistory("Generated bill");
    }

    void displayBills() const {
        cout << "\n========== BILLS ==========\n";
        if (!billHead) {
            cout << "No bills."<<endl; 
            return; 
        }

        for (Bill* b = billHead; b; b = b->next)
            cout<< "Bill ID: " << b->id << " | Patient: " << b->patientID
                << " | Total: " << fixed << setprecision(2) << b->total<<endl;
    }

    void allocateRoom(){
        int room=inputInt("Room number (1-50): ");
        if(room<1 || room>MAX_ROOMS){
            cout<<"Room already occupied!"<<endl;
            return;
        }
        if(rooms[room]!=0){
            cout<<"The room already occupied!"<<endl;
            return;
        }

        int patientID=inputInt("Patient ID: ");
        if (!findPatient(patientID)) {
            cout<<"Patient not found! "<<endl;
            return;
        }

        for(int i=1;i<=MAX_ROOMS;++i){
            if(rooms[i]==patientID) {
                cout<<"Patient already has a room! "<<endl;
                return;
            }
        }
        rooms[room]=patientID;
        cout << "Room " << room << " allocated to patient " << patientID<<endl;
        pushHistory("Allocated room");
    }

    void releaseRoom() {
        int room=inputInt("Room number: ");
        if(room<1 || room>MAX_ROOMS) {
            cout<<"Room number invalid!"<<endl;
            return;
        }

        if(rooms[room]==0){
            cout<<"Room is already empty!"<<endl;
            return;
        }

        rooms[room]=0;
        cout<<"Room released!"<<endl;\
        pushHistory("Released room");
    }

    void displayRooms() const {
        cout << "\n========== ROOMS ==========\n";
        for (int i = 1;i <= MAX_ROOMS;++i) {
            if (rooms[i]== 0) cout << "Room " << i << ": Empty\n";
            else cout << "Room " << i << ": Patient " << rooms[i] << '\n';
        }
    }

    int countPatients() const {
        int count=0;
        for(Patient* p=patientHead;p;p=p->next) ++count;
        return count;
    }

     int countDoctors() const {
        int count=0;
        for(Doctor* d=doctorHead;d;d=d->next) ++count;
        return count;
    }

    // Text files are used for portability; strings with tabs/newlines are not supported.
    void savePatients() const {
        ofstream file("patients.data");
        if (!file) { 
            cout << "Could not open patients.data"<<endl;
            return; 
        }
        for (Patient* p = patientHead; p;p = p->next)
            file<< p->id << '\t' << p->age << '\t' << p->name << '\t'
                << p->gender << '\t' << p->disease << '\t' << p->phone<<endl;
    }

    void loadPatients(){
        ifstream file("patients.data");
        if(!file) return ;
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string id,age,name,gender,disease,phone;
            if(!getline(ss,id,'\t') || !getline(ss,age,'\t') ||
                !getline(ss,name,'\t') || getline(ss,gender,'\t') ||
                !getline(ss,disease,'\t') ||!getline(ss,phone)) continue;

                Patient*p=new Patient;
                try {p->id=stoi(id);p->age=stoi(age);}
                catch (...) {delete p;continue;}
                p->name=name;
                p->gender=gender;
                p->disease=disease;
                p->phone=phone;
                if(findPatient(p->id)) {
                    delete p;
                    continue;
                }
                p->next=patientHead;
                patientHead=p;
        }
    }

    void saveDoctors() const {
        ofstream file("doctors.dat");
        if(!file) return;
        for (Doctor*d=doctorHead;d;d=d->next)
            file<<d->id<<'\t'<<d->name<<'\t'<<d->specialty<<'\t'<<d->phone<<endl;
    }

    void loadDoctors(){
        ifstream file("doctors.dat");
        if(!file) return;
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string id,name,specialty,phone;
            if(!getline(ss,id,'\t') || !getline(ss,name,'\t') || 
                !getline(ss,specialty,'\t') || !getline(ss,phone)) continue;

                Doctor* d=new Doctor;
                try {
                    d->id=stoi(id);
                }
                catch(...) {
                    delete d;
                    continue;
                }
                d->name=name;
                d->specialty=specialty;
                d->phone=phone;
                if(findDoctor(d->id)){
                    delete d;
                    continue;
                }
                d->next=doctorHead;
                doctorHead=d;
        }
    }

    void saveMedicines() const {
        ofstream file("medicines.dat");
        if(!file) return;
        for (Medicine*m=medicineHead;m;m=m->next)
            file<<m->id<<'\t'<<m->stock<<'\t'<<setprecision(17)<<m->price<<'\t'<<m->name<<endl;
    }

    void loadMedicines() {
        ifstream file("medicines.dat");
        if(!file) return;
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string id,stock,price,name;
            if (!getline(ss,id,'\t') || !getline(ss,stock,'\t') ||
                !getline(ss,price,'\t') || !getline(ss,name)) continue;

            Medicine* m = new Medicine;
            try { m->id = stoi(id); 
                m->stock = stoi(stock);
                m->price = stod(price); 
            }
            catch (...) { 
                delete m; 
                continue; 
            }
            m->name = name;
            if (findMedicine(m->id)) { delete m; continue; }
            m->next = medicineHead; medicineHead = m;
        }
    }

    void saveAll() const {
        savePatients();
        saveDoctors();
        saveMedicines();
        cout<<"Data saved successfully."<<endl;
    }

    void reports() const {
        int occupied=0;
        double revenue=0.0;
        for(int i=1;i<=MAX_ROOMS;++i) if(rooms[i]!=0) ++occupied;
        for(Bill*b=billHead;b;b=b->next) revenue+=b->total;
        cout<< "\n========== HOSPITAL REPORT ==========\n"
            << "Total patients : "<<countPatients()<<'\n'
            << "Total doctors  : "<<countDoctors()<<'\n'
            << "Occupied rooms : "<<occupied<< " / "<<MAX_ROOMS<<'\n'
            << "Total billing  : "<<fixed<< setprecision(2)<<revenue<<endl;;
    }

    void displayHistory() const {
        if(historyTop<0){
            cout<<"History is empty"<<endl;
            return;
        }
        cout<<"\n======== OPERATION HISTORY ========\n";
        for(int i=historyTop;i>=0;--i){
            cout<<historyTop-i+1<<". "<<history[i]<<endl;
        }
    }

    void peekHistory() const {
        if(historyTop<0) cout<<"History is empty!"<<endl;
        else cout<<"Latest operation: "<<history[historyTop]<<endl;
    }

    void popHistory() {
        if(historyTop<0) cout<<"History is empty!"<<endl;
        else cout <<"Removed:"<<history[historyTop--]<<endl;
    }

    void patientMenu() {
        int choice;
        do {
            cout<<"\n======== PATIENT MANAGEMENT =========\n"
                <<"1.Add Patient\n2.Delete Patient\n3.Search Patient\n"
                <<"4.Update Patient\n5.Display Patient\n0.Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:addDoctor();break;
                case 2:searchDoctorMenu();break;
                case 3:displayDoctors();break;
                case 0:break;
                default:cout<<"Invalid choice1\n";
            }
        } while(choice!=0);
    }

    void doctorMenu(){
        int choice;
        do {
            cout<<"\n======== DOCTOR MANAGEMENT =========\n"
                <<"1.Add Doctor\n2.Search Doctor\n3.Display Doctors\n0.Back\n";
                choice=inputInt("Choice: ");
                switch(choice){
                    case 1:addDoctor();break;
                    case 2:searchDoctorMenu();break;
                    case 3:displayDoctors();break;
                    case 0:break;
                    default:cout<<"Invalid choice!\n";
                }
        } while(choice!=0);
    }

    void appointmentMenu() {
        int choice;
        do {
            cout<<"\n======== APPOINTMENTS =========\n"
                <<"1.Book Appointment\n2.Process Next Appointment\n3.Display Queue\n0.Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:enqueueAppointment();break;
                case 2:dequeueAppointment();break;
                case 3:displayAppointments();break;
                case 0:break;
                default:cout<<"Invalid choice.\n"<<endl;
            }
        } while(choice!=0);
    }

    void emergencyMenu(){
        int choice;
        do {
            cout<<"\n========EMERGENCY ========\n"
                <<"1. Add Emergency Patient\n2. Process Highest Priority\n3. Display Emergency Queue\n0. Back\n";
            choice=inputInt("Choice: ");
            switch (choice){
                case 1: addEmergency();break;
                case 2: processEmergency(); break;
                case 3: displayEmergencies(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void medicalMenu() {
        int choice;
        do {
            cout<<"\n========== MEDICAL RECORDS ==========\n"
                <<"1. Add Medical Record\n2. View Patient History\n0. Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:addMedicalRecord();break;
                case 2:viewMedicalRecords();break;
                case 0:break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }

    void pharmacyMenu(){
        int choice;
        do {
            cout<<"\n========== PHARMACY ==========\n"
                <<"1. Add Medicine\n2. Display Medicines\n3. Search Medicine\n4. Dispense Medicine\n0. Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:addMedicine();break;
                case 2:displayMedicine();break;
                case 3:searchMedicineMenu();break;
                case 4:dispenseMedicine();break;
                case 0:break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }

    void billingMenu() {
        int choice;
        do {
            cout << "\n========== BILLING ==========\n1. Generate Bill\n2. Display Bills\n0. Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:createBill();break;
                case 2:displayBills();break;
                case 0:break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }

    void roomMenu() {
        int choice;
        do {
            cout<<"\n========== ROOM MANAGEMENT ==========\n"
                <<"1. Allocate Room\n2. Release Room\n3. Display Rooms\n0. Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:allocateRoom();break;
                case 2:releaseRoom();break;
                case 3:displayRooms();break;
                case 0:break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }

    void historyMenu() {
        int choice;
        do {
            cout<<"\n========== STACK ==========\n1. Display History\n2. Peek\n3. Pop\n0. Back\n";
            choice=inputInt("Choice: ");
            switch(choice){
                case 1:displayHistory();break;
                case 2:peekHistory();break;
                case 3:popHistory();break;
                case 0:break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }

    void freeAll() {
        while (patientHead) { 
            Patient* t = patientHead; 
            patientHead = patientHead->next;
            delete t;
            }
        
        while (doctorHead){
            Doctor* t=doctorHead;
            doctorHead=doctorHead->next;
            delete t;
        }

        while(appointmentFront){
            Appointment* t=appointmentFront;
            appointmentFront=appointmentFront->next;
            delete t;
        }
        appointmentRear=NULL;

        while(emergencyHead){
            Emergency* t=emergencyHead;
            emergencyHead=emergencyHead->next;
            delete t;
        }

        while(recordHead){
            MedicalRecord *t=recordHead;
            recordHead=recordHead->next;
            delete t;
        }

        while(medicineHead){
            Medicine *t=medicineHead;
            medicineHead=medicineHead->next;
            delete t;
        }

        while(billHead){
            Bill *t=billHead;
            billHead=billHead->next;
            delete t;
        }
    }

public:
    HospitalSystem()=default;
    HospitalSystem(const HospitalSystem&)=delete;
    HospitalSystem& operator=(const HospitalSystem&)=delete;

    ~HospitalSystem() {freeAll(); }

    void run() {
        loadPatients();
        loadDoctors();
        loadMedicines();

        int choice;
        do {
            cout<<"\n============================================\n"
                <<"       HOSPITAL MANAGEMENT SYSTEM\n"
                <<"============================================\n"
                <<"1.  Patient Management\n2.  Doctor Management\n"
                <<"3.  Appointment Queue\n4.  Emergency Priority Queue\n"
                <<"5.  Medical Records\n6.  Pharmacy\n7.  Billing\n"
                <<"8.  Room Management\n9.  Operation History / Stack\n"
                <<"10. Reports\n11. Save Data\n0.  Exit\n"
                <<"============================================\n";
            choice=inputInt("Enter Choice: ");
            switch(choice){
                case 1:patientMenu();break;
                case 2:doctorMenu();break;
                case 3:appointmentMenu();break;
                case 4:emergencyMenu();break;
                case 5:medicalMenu();break;
                case 6:pharmacyMenu();break;
                case 7:billingMenu();break;
                case 8:roomMenu();break;
                case 9:historyMenu();
                case 10:reports();break;
                case 11:saveAll();break;
                case 0:
                    saveAll();
                    cout<<"Exiting Hospital Management System...\n";
                    break;
                default:cout<<"Invalid choice.\n";
            }
        } while(choice!=0);
    }
};

int main(){
    HospitalSystem hospital;
    hospital.run();
    return 0;
}
};

