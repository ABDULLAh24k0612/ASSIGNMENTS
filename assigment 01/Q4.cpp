#include<iostream>
using namespace std;

#define MAX_STUDENTS 50
#define MAX_STOPS 20
#define MAX_BUSES 10

class Student{

    private:

    int StudentId;
    string StudentName;
    double StudentBalance;
    int StudentCardNumber;
    string StudentPickUpStop;
    string StudentDropOffStop;
    bool IsActive;

    public:

    Student(int id,int no,double b,string n,string p, string d){

        StudentId=id;
        StudentCardNumber=no;
        StudentBalance=b;
        StudentName=n;
        StudentPickUpStop=p;
        StudentDropOffStop=d;
        IsActive=0;
    }

    int GetStudentId(){
        return StudentId;
    }
    int GetStudentCardNumber(){
        return StudentCardNumber;
    }
    string GetStudentName(){
        return StudentName;
    }
    string GetStudentPickUpStop(){
        return StudentPickUpStop;
    }

    void PaySemesterFee(double amount){
        if(StudentBalance>amount){
        StudentBalance-=amount;
        IsActive=true;
        cout<<"semester fees has been paid"<<endl;
        }
        else{
            cout<<"not enough balance to pay a fees"<< endl;
         }
        
        }
    void RegisterForTransport(){
         IsActive=true;
         cout<< StudentName<< "has been registered for the transportation"<< endl;
    }
   
    void TapCard(){
        if (IsActive=true) cout << "Attendance recorded for " << StudentName << endl;
            else cout << "Card not active!" << endl;
    }
    void StudentDetails(){
        cout << "Student name"<< StudentName << endl;
        cout << "Student Id"<< StudentId << endl;
        cout << "Student Card Number"<< StudentCardNumber << endl;
        cout << "Student Pick Up"<< StudentPickUpStop << endl;
        cout << "Student Drop Off"<< StudentDropOffStop << endl;
         
    }

};
class BusStop {
    private:
        int stopID;
        string location;
        Student* studentsAtStop[MAX_STUDENTS];
        int studentCount;
    public:
        BusStop(int id, string loc) {
             stopID=id; 
             location=loc;
             studentCount=0;
             }

             string GetLocation(){
                return location;
             }
        void assignStudent(Student* s)  {
             if (studentCount < MAX_STUDENTS) {
                studentsAtStop[studentCount++] = s;
             }
            }
        void getStopDetails() {
             cout << "Stop " << stopID << " at " << location << endl;
             }
    };
    
    class BusRoute {
    private:
        int routeID;
        BusStop* stops[MAX_STOPS];
        int stopCount;
    public:
        BusRoute(int id) { 
            routeID=id;
            stopCount=0;
        }
        void addStop(BusStop* stop) {
             if (stopCount < MAX_STOPS){ 
             stops[stopCount++] = stop; 
             }
            }
        void getRouteDetails() {
             cout << "Route " << routeID << " has " << stopCount << " stops." << endl;
             }
    };
    
    class Bus {
    private:
        int busID;
        string driverName;
        BusRoute* route;
        int capacity;
    public:
        Bus(int id, string driver, int cap) {
            busID=id; 
            driverName=driver;
            capacity=cap;
            route=nullptr; 
            }
        void assignRoute(BusRoute* r) {
             route = r; 
            }
        void getBusDetails() {
             cout << "Bus " << busID << " driven by " << driverName << endl; 
            }
    };
    
    class TransportSystem {
    private:
        Student* students[MAX_STUDENTS];
        Student* attendance[MAX_STUDENTS];
        Bus* buses[MAX_BUSES];
        BusRoute* routes[MAX_STOPS];
        int studentCount, busCount, routeCount,attendanceCount;
    public:
        TransportSystem(){
             studentCount=0;
             busCount=0;
             routeCount=0;
             attendanceCount=0;
            }
        void registerStudent(Student* s) {
             if (studentCount < MAX_STUDENTS){
                 students[studentCount++] = s;

             }
             }
        void assignBusToRoute(Bus* b, BusRoute* r) {
             b->assignRoute(r); 
            }
            void recordAttendance(Student* s, BusStop* b) {
                if (s->GetStudentPickUpStop() == b->GetLocation()) {
                    attendance[attendanceCount++] = s;
                    cout << "Attendance recorded for student: " << s->GetStudentName() << endl;
                } else {
                    cout << "Student is not at the correct stop!" << endl;
                }
            
                cout << "Attendance List: " << endl;
                for (int i = 0; i < attendanceCount; i++) {
                    cout << " - " << attendance[i]->GetStudentName() << endl;
                }
            }
        };
    int main() {
        TransportSystem system;
        Student s1(1, 1001, 500,"John", "Stop A", "Stop B");
        system.registerStudent(&s1);
        s1.PaySemesterFee(200);
        s1.TapCard();
        
        BusRoute route1(101);
        Bus bus1(1, "Mike", 50);
        system.assignBusToRoute(&bus1, &route1);
        return 0;
    }
    


