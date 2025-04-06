#include<iostream>
using namespace std;

 int hashpassword(string password){
     int hash=5381;
     int hashpass=0;
     for(int i=0;i<password.length();i++){
           hashpass+=(hash*33 + password[i]);   
     }
     return hashpass;
 }




class user{
  protected:
  string name;
  string role;
  int id;
  bool permission[5];
  string email;
  string password;
  int hashpass;
  public:
  user(){}
  user(string name ,int id,string email,string password,bool perm[]){
       this->name=name;
       this->id=id;
       this->email=email;
       this->password=password;
       for(int i=0;i<5;i++){
        permission[i]=perm[i];
       }

       hashpass=hashpassword(password);
  }

  
  void verifyPass(string password){  
      int check=hashpassword(password);
      if(check==hashpass){
        cout<<"password matched"<<endl;
      }
      else{
        cout<<"password not match"<<endl;
      }
  }
virtual void display(){
  cout << "name :" << name << endl;
  cout << "id :" << id << endl;
  cout << "email:" << email << endl;
}

  bool haspermission(string action){
    string Action[5] = {"submit assignment", "view projects", "manage students", "assign projects", "full lab access"};
           for(int i=0;i<5;i++){
             if(action==Action[i]){
              return permission[i];
             }
            }
            return  false;
    }

            virtual void performAction(string action) {
                cout << "Action '" << action << "' is not defined for this user." << endl;
                  }
    friend void authenticateAndPerformAction(user* user, string action);



  };

class student : public user{
       protected:
      int* assignment;
      int count;
      public:
      student(){}
      student(string name, int id, string email, string password,bool perm[])
        : user(name, id, email, password, perm), count(0), assignment(nullptr) {}


      void assignAssignment(){
           int* temp=new int[count + 1];
           for(int i=0;i< count;i++){
              temp[i]=assignment[i];
           }

           delete[] assignment;
           assignment=temp;
           count++;
      }

      ~student() {
        delete[] assignment;  
    }

     void submitAssignment(int index){
      if( index <= count  && index >= 1){
           assignment[index-1]=1;
           cout<<"assignment submitted"<<endl;
      }
      else{
        cout<<"Invalid assignment"<<endl;;
      }

     }

     string getname(){
      return name;
     }

     void display() override{
      user::display();
     }

     void performAction(string action) {
        if(action=="submit assignment"){
          submitAssignment(1);
        }
        else{
          cout<<"student cannot perform this action"<<endl;
        }
        }
};

class TA : public student{
  private:
  int project[2];
  int projectCount;
  student students[10];
  int studentcount;
  public:
  TA(string name, int id, string email, string password, bool perm[]):student(name, id, email, password, perm), projectCount(0), studentcount(0){}

  void managestudent(student s){
    if( studentcount < 10){
      students[studentcount]=s;
      studentcount++;
      cout<<"student :"<<s.getname()<<"assign to TA :"<<name<<endl;
    }
    else {
      cout<<"no space for student"<<endl;
    }
  }

  void display() override{
    user::display();
   }

    int getProjectcount(){
      return projectCount;
    }
   void setProject(int index){
      project[index]=1;
   }

   void setProjectcount(){
                 projectCount++;        
      }

      void performAction(string action) {
        if(action=="manage students"){
          student tempStudent("Irfan", 102, "irfan@example.com", "irfanPass", new bool[5]{true, false, false, false, false});
          managestudent(tempStudent);
        }
        else{
          cout << "Professor does not perform this action." << endl;
        }
        }

};

class professor : public user{
public:
professor(string name, int id, string email, string password, bool perm[]): user(name, id, email, password, perm) {}

void display() override{
  user::display();
 }
void assignProject(TA *ta,string ProjectName){
  if(ta->getProjectcount() < 2){
     cout<<"Project: "<<ProjectName<<" assigned to the TA"<<ta->getname()<<endl;
     ta->setProject(ta->getProjectcount());
     ta->setProjectcount();
  }
 else{
   cout<<"there is not more space for project"<<endl;
 }
}

void performAction(string action) override {
    if (action == "assign projects") {
        TA tempTA("Ali", 202, "ali@gmail.com", "aliPass", new bool[5]{true, true, true, false, false});
        assignProject(&tempTA, "Cybersecurity Project");
    } else {
        cout << "Professor does not perform this action." << endl;
    }
  }
};

void authenticateAndPerformAction(user* usr, string action){
    if (usr->haspermission(action)) {
        cout << "Action '" << action << "' is ALLOWED!" << endl;
          usr->performAction(action);
      } else{
         cout << "Access Denied for '" << action << "'!" << endl;
         }

        }


int main() {
    bool studentPermissions[5] = {true, false, false, false, false};
    bool taPermissions[5] = {true, true, true, false, false};
    bool professorPermissions[5] = {false, false, false, true, true};
    
    student s1("abdullah", 101, "abdullah@gmail.com", "password123", studentPermissions);
    TA ta1("Ali", 201, "ali@gmail.com", "secureTA", taPermissions);
    professor p1("Faisal", 301, "faisal@gmail.com", "profpass", professorPermissions);

    s1.assignAssignment();

    authenticateAndPerformAction(&s1, "submit assignment");
    authenticateAndPerformAction(&ta1, "manage students");
    authenticateAndPerformAction(&p1, "assign projects");
    
    return 0;
}


