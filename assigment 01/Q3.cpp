#include<iostream>
using namespace std;

class Vehicle;

class User{
    private:
        int userAge;
        int userID;
        string userContact;
        string userLicense;
    public:
        
        User(int id, int age, string contact, string license){
            userID = id;
            userAge = age;
            userContact = contact;
            userLicense = license;
        }
        void modifyUserDetails(int age, string contact, string license){
            if(age > 0){
                userAge = age;
            }
            else{
                cout << "Error: Invalid age entered." << endl;
            }
            userContact = contact;
            userLicense = license;
        }
        string fetchLicense(){
            return userLicense;
        }
        void displayUserInfo(){
            cout << "User ID: " << userID << " || Age: " << userAge << " || Contact: " << userContact << " || License Type: " << userLicense << endl;
        }

        void leaseVehicle(Vehicle *v, int duration);
       

};

class  Vehicle
{
private:
    string vehicleModel;
    float rentCost;
    string requiredLicense;
public:
    Vehicle(string model, float cost, string licenseReq){
        vehicleModel = model;
        rentCost = cost;
        requiredLicense = licenseReq;
    }

    string fetchRequiredLicense(){
        return requiredLicense;
    }
    string fetchModel(){
        return vehicleModel;
    }
    float fetchRentCost(){
        return rentCost;
    }

    void displayVehicleDetails(){
        cout << "Vehicle Model: " << vehicleModel << " || Rental Price per Day: " << rentCost << " || Required License: " << requiredLicense << endl;
    }
};

void User::leaseVehicle(Vehicle *v, int duration) {
    if (userLicense == v->fetchRequiredLicense() || userLicense == "Full" || v->fetchRequiredLicense() == "Learner") {
        cout << "Success! You have leased: " << v->fetchModel() << endl;
        cout << "Total Rental Cost: " << v->fetchRentCost() * duration << " units." << endl;
    } else {
        cout << "Lease unsuccessful! You do not meet the license requirements for: " << v->fetchModel() << endl;
    }
}

class RentalService{
    private:
        Vehicle** fleet;
        int totalVehicles;
    public:
        RentalService(Vehicle* v[]) {
            totalVehicles = 5;
            fleet = new Vehicle*[totalVehicles];
            for(int i = 0; i < totalVehicles; i++) {
                fleet[i] = v[i];
            }
        }
        void enrollUser(User &user){
            cout << "User successfully enrolled." << endl;
            user.displayUserInfo();
        }

        void showAvailableVehicles(Vehicle* v[], User &user) {
            cout << "Vehicles available based on your license category:" << endl;
            if(user.fetchLicense() == "Learner") {
                for(int i = 0; i < totalVehicles; i++) {
                    if(v[i]->fetchRequiredLicense() == "Learner") {
                        v[i]->displayVehicleDetails();
                        cout << "--------------------------------------------------------------" << endl;
                    }
                }
            }
            else if(user.fetchLicense() == "Intermediate") {
                for(int i = 0; i < totalVehicles; i++) {
                    if(v[i]->fetchRequiredLicense() == "Learner" || v[i]->fetchRequiredLicense() == "Intermediate") {
                        v[i]->displayVehicleDetails();
                        cout << "--------------------------------------------------------------" << endl;
                    }
                }
            }
            else {
                for(int i = 0; i < totalVehicles; i++) {
                    v[i]->displayVehicleDetails();
                    cout << "--------------------------------------------------------------" << endl;
                }
            }
        }
        
        void addNewVehicle(string model, float price, string license) {
            Vehicle** temp = new Vehicle*[totalVehicles + 1];
            for (int i = 0; i < totalVehicles; i++) {
                temp[i] = fleet[i];
            }
            temp[totalVehicles] = new Vehicle(model, price, license);
            totalVehicles++;
            delete[] fleet;
            fleet = temp;
            cout << "Vehicle successfully added: " << model << endl;
        }

        Vehicle* fetchVehicle(int index) {
            if (index >= 0 && index < totalVehicles) {
                return fleet[index];
            }
            return nullptr;
        }
    
        int fetchTotalVehicles(){
            return totalVehicles;
        }

        ~RentalService(){
            for(int i = 0; i < totalVehicles; i++){
                delete fleet[i];
            }
            delete[] fleet;
        }
};

int main() {
    Vehicle* v1 = new Vehicle("Nissan", 550.0, "Intermediate");
    Vehicle* v2 = new Vehicle("Hyundai", 750.0, "Learner");
    Vehicle* v3 = new Vehicle("BMW", 3200.0, "Full");
    Vehicle* v4 = new Vehicle("Chevrolet", 3600.0, "Learner");
    Vehicle* v5 = new Vehicle("Tesla", 5200.0, "Full");

    Vehicle* vehicleList[] = {v1, v2, v3, v4, v5};

    User user1(100, 25, "03301234567", "Intermediate");
    User user2(101, 30, "03301224577", "Full");
    User user3(102, 19, "03301235930", "Learner");

    RentalService garage(vehicleList);

    cout << "Enrolling User 1..." << endl;
    garage.enrollUser(user1);

    cout << "Displaying vehicles available for User 1..." << endl;
    garage.showAvailableVehicles(vehicleList, user1);

    cout << "User 1 attempting to lease a vehicle..." << endl;
    user1.leaseVehicle(v4, 10);

    cout << endl << "Adding a new vehicle to the fleet..." << endl;
    garage.addNewVehicle("Range Rover", 4500.0, "Intermediate");

    cout << "Showing the newly added vehicle..." << endl;
    Vehicle* newVehicle = garage.fetchVehicle(garage.fetchTotalVehicles() - 1);
    if (newVehicle) {
        newVehicle->displayVehicleDetails();
    } else {
        cout << "Error: Could not retrieve details of the added vehicle." << endl;
    }

    return 0;
}

