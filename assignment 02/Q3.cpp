#include<iostream>
using namespace std;

class Vehicle{
   protected:
        int vehicleID;
        double speed;
        double capacity;
        double energyefficiency;
        static int activedelieveries;
    public:
        Vehicle(int vehicleID,double speed,double capacity,double energyefficiency):
        vehicleID(vehicleID),speed(speed),capacity(capacity),energyefficiency(energyefficiency){
            activedelieveries++; 
        }


        static int getactivedelieveries(){
            return activedelieveries;
        }
        virtual void calculateroute()=0;

        virtual void estimatetime()=0;

        virtual void command(string action,int packageID)=0;

        virtual void command(string action,int packageID,string urgentlvl)=0;


        friend Vehicle* operator==(Vehicle &v1,Vehicle &v2);


        virtual ~Vehicle() { 
            activedelieveries--;
         }
         int getid(){
            return vehicleID;
         }

         int getspeed(){
            return speed;
         }

};

    Vehicle* operator==(Vehicle &v1,Vehicle &v2){
        double efficiency1=v1.speed + v1.capacity + v1.energyefficiency;
        double efficiency2=v2.speed + v2.capacity + v2.energyefficiency;
        if( efficiency1 > efficiency2){
            cout<<"vehicle ("<<v1.vehicleID<<") is better for delivery compare to "<<v2.vehicleID<<endl;
        }
        else if( efficiency2 > efficiency1){
            cout<<"vechile ("<<v2.vehicleID<<") is better for delivery compare to "<<v1.vehicleID<<endl;
        }
        else{
            cout<<"both vehicle ("<<v1.vehicleID<<") and vehicle ("<<v2.vehicleID<<") have same efficieny"<<endl;          
    }
}

class RamzanTimeship:public Vehicle{
    public:
    RamzanTimeship(int vehicleID,double speed,double capacity,double energyefficiency):
    Vehicle(vehicleID,speed,capacity,energyefficiency){}

        void calculateroute() override{
            cout<<" TimeShip: "<<vehicleID<<"verifies historical consistency"<<endl;
        }
        void estimatetime() override{
            cout<<" TimeShip: "<<vehicleID<<"Consistency Before proceeding"<<endl;
        }

        void command(string action, int packageID) override { 
            cout << "RamzanTimeShip: Delivering package " << packageID << " through time travel."<<endl; 
            }
        
           void command(string action, int packageID, string urgencyLevel) override { 
            cout << "RamzanTimeShip: Ensuring historical accuracy for package " << packageID <<"For "<<urgencyLevel<< endl; 
           }
        
};

class RamzanDrone:public Vehicle{
    public:
    RamzanDrone(int vehicleID,double speed,double capacity,double energyefficiency):
    Vehicle(vehicleID,speed,capacity,energyefficiency){}

        void calculateroute() override{
            cout<<" Drone: "<<vehicleID<<"calculates an aerial route"<<endl;
        }
        void estimatetime() override{
            cout<<" Drone: "<<vehicleID<<"High Speed Delievery"<<endl;
        }

        void command(string action,int packageID)override{
            cout << "RamzanDrone: Delivering package " << packageID << " via aerial route."<<endl; 
            }
        
            void command(string action,int packageID,string urgentlvl) override{
            cout << "RamzanDrone: High-speed delivery of package " << packageID << " for " << urgentlvl << endl; 
            }

};

class RamzanHyperPod:public Vehicle{
    public:
    RamzanHyperPod(int vehicleID,double speed,double capacity,double energyefficiency):
    Vehicle(vehicleID,speed,capacity,energyefficiency){}

        void calculateroute() override{
            cout<<" HyperPod: "<<vehicleID<<"navigates an underground tunnel network"<<endl;
        }
        void estimatetime() override{
            cout<<" HyperPod: "<<vehicleID<<"efficient bulk delivery"<<endl;
        }

        void command(string action, int packageID) override { 
            cout << "RamzanTimeShip: Delivering package " << packageID << " through time travel."<<endl; 
            }
        
           void command(string action, int packageID, string urgencyLevel) override { 
            cout << "RamzanTimeShip: Ensuring historical accuracy for package " << packageID << endl; 
           }
};

int Vehicle::activedelieveries=0; 

int main() {
    RamzanDrone D(100,200,1500,800);
    RamzanTimeship T(101,120,1200,2000);
    RamzanHyperPod H(102,150,1000,1000);


    Vehicle *v1 = &D;
    Vehicle *v2 = &T;
    Vehicle *v3 = &H;

    cout << "---- Route Calculation ----" << endl;
    v1->calculateroute();
    v2->calculateroute();
    v3->calculateroute();
    cout << endl;

    cout << " Delievery " << endl;
    v1->estimatetime();
    v2->estimatetime();
    v3->estimatetime();
    cout << endl;

    cout << " Delivery Commands " << endl;
    v1->command("Deliver", 101);
    v2->command("Deliver", 102);
    v3->command("Deliver", 103);
    cout << endl;


    cout << " Urgent Delivery Commands" << endl;
    v1->command("Deliver", 201, "Iftar");
    v2->command("Deliver", 202, "Sehri");
    v3->command("Deliver", 203, "High Priority");
    cout << endl;

    cout << " Efficiency Comparison" << endl;
    *v1 == *v2;
    *v2 == *v3;
    *v1 == *v3;
    cout << endl;

  
    cout << "Total Deliveries Made: " << Vehicle::getactivedelieveries() << endl;

    return 0;
}

