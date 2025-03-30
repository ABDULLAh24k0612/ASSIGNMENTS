#include <iostream>
#include <string>
using namespace std;

class TransportationService {
    private:
        int maxUsers;
        int currUsers;
    
    public:
        TransportationService(){
        maxUsers = 500;
        currUsers = 0;
        }
    
        bool checkAvailability() {
            return currUsers < maxUsers;
        }
    
        void addStudent() {
            if (checkAvailability()) {
                currUsers++;
            }
        }
    
        int getCurrentStudents()const{
            return currUsers;
        }
};

class Stop {
    private:
        string stopName;
    
    public:
        Stop(string name){
            stopName = name;
        }
    
        string getStopName()const{
            return stopName;
        }
};

class Card {
    private:
        string assignedTo;
        bool active;
    
    public:
        Card(string studentId){
            assignedTo = studentId;
            active = false;
        }
    
        bool getCardStatus()const{
             return active;
        }
    
        void activateCard() {
            active = true;
            cout << "Card for User " << assignedTo << " is now active." << endl;
        }
};

class User{
    protected:
    string userId;
    string name;
    bool feeStatus;
    bool attendance;
    Card* card;
    Stop* currStop;
    TransportationService* ts;
    public:
    User(string id, string n) : userId(id), name(n), feeStatus(false), attendance(false), card(nullptr), currStop(nullptr), ts(nullptr){}
    string getStudentId() const{
        return userId; 
    }
    string getName() const{ 
        return name; 
    }
    bool getFeeStatus() const{
        return feeStatus; 
    }
    bool getAttendance() const{
        return attendance; 
    }
    void setFeeStatus(bool status){
    feeStatus = status;
    }
    void setAttendance(bool status){
        attendance = status; 
        }
        void registerForTransport(TransportationService& service) {
            if (service.checkAvailability() && feeStatus) {
                card = new Card(userId);
                card->activateCard();
                cout << endl << name << " has registered for the transportation service." << endl;
            }
            else if(!feeStatus){
                cout << endl << name << " has not paid the fee yet. Cannot register.\n";
            }
             else {
                cout << endl << "Transportation service is full. Cannot register " << name << "." << endl;
            }
        }
    
        void tapCard() {
            if(card && card->getCardStatus()) {
                attendance = true;
                cout << endl << name << " has tapped the card. Attendance recorded." << endl;
            } 
            else{
                cout<< endl << "Card is inactive. Please pay the semester fee." << endl;
            }
        }
        void assignStop(Stop* stop){
            if(!card){
                cout<<"\nFee not paid... Cannot assign stop.\n";
                return;
            }
            currStop = stop;
            cout<<"\nUser " << name << " is assigned to " << stop->getStopName() <<".\n";
        }
        ~User(){
            delete card;
        }
};


class Student : public User{
    int Semesterfee;
public:

Student(string id, string n) : User(id, n){
    Semesterfee = 40000;
}

    void paySemesterFee(int fee) {
        if(fee >= Semesterfee){
            feeStatus = true; 
            cout << endl << name << " has paid the semester fee." << endl;
    }
    else{
        cout<<"The payment is not enough.\n";
    }
}

};

class Teacher : public User{
    int monthlyFee;
public:

Teacher(string id, string n) : User(id, n){
    monthlyFee = 7000;
}

    void payMonthlyFee(int fee) {
        if(fee >= monthlyFee){
            feeStatus = true;
            cout << endl << name << " has paid the fee for the month." << endl;
        }
        else{
            cout<<"The payment is not enough.\n";
        }
    }

};
class Staff : public User{
    int monthlyFee;
public:
Staff(string id, string n) : User(id, n){
    monthlyFee = 5000;
}

void payMonthlyFee(int fee) {
    if(fee >= monthlyFee){
        feeStatus = true;
        cout << endl << name << " has paid the fee for the month." << endl;
    }
    else{
        cout<<"The payment is not enough.\n";
    }
}
};



class BusRoutes {
private:
    int routeNumber;
    Stop* stops[10];
    int currStops;
    int maxStops;

public:
    BusRoutes(int num){
        routeNumber = num;
        currStops = 0;
        maxStops = 10;
        
    }

    void addStop(Stop* stop);
    void displayStops();
    bool operator ==(const BusRoutes &b){
        if(currStops != b.currStops) return false;
        for(int i = 0 ; i < currStops ; i++){
            if(this->stops[i] != b.stops[i]) return false;
        }
        return true;
    }
};

void BusRoutes :: addStop(Stop* stop) {
    if(currStops < maxStops){
        stops[currStops] = stop;
        currStops += 1;
    }
    cout << "\nStop " << stop->getStopName() << " added to route " << routeNumber << "." << endl;
}

void BusRoutes :: displayStops() {
    cout << "\nStops on route " << routeNumber << ":" << endl;
    for (int i = 0 ; i < currStops ; i++) {
        cout << "- " << stops[i]->getStopName() << endl;
    }
}


int main() {

    TransportationService service;

    Student student1("S001", "Ali");
    Student student2("S002", "Bilal");
    Teacher teacher1("T101", "Mr. Ahmad");
    Staff staff1("SF202", "Ms. Sara");

    student1.paySemesterFee(42000);
    student1.registerForTransport(service);

    teacher1.payMonthlyFee(7000);
    teacher1.registerForTransport(service);

    
    student2.registerForTransport(service);
    staff1.registerForTransport(service);


    student1.tapCard();
    teacher1.tapCard();
    student2.tapCard();  
    staff1.tapCard();    


    Stop stop1("Jauhar");
    Stop stop2("Gulshan-e-Iqbal");
    Stop stop3("DHA");


    student1.assignStop(&stop1);
    student2.assignStop(&stop2);
    teacher1.assignStop(&stop3);
    staff1.assignStop(&stop1);

    BusRoutes route1(1);
    BusRoutes route2(2);

    route1.addStop(&stop1);
    route1.addStop(&stop2);

    route2.addStop(&stop1);
    route2.addStop(&stop2);

    route1.displayStops();
    route2.displayStops();

    if (route1 == route2) {
        cout << "Route 1 and Route 2 are the same.\n";
    } else {
        cout << "Route 1 and Route 2 are different.\n";
    }

    return 0;
}
