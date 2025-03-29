
#include<iostream>
#include<string>
using namespace std;

class Skill {
    private:
     int SkillId;
     string SkillName;
     string SkillDescription;

    public:
     Skill(int id, string n, string d) {
        SkillId = id;
        SkillName = n;
        SkillDescription = d;
     }

     string GetSkillName() {
        return SkillName;
     }

     void ShowSkillDetails() {
        cout << "Skill Id is: " << SkillId << endl;
        cout << "Skill Name is: " << SkillName << endl;
        cout << "Skill Description is: " << SkillDescription << endl;
     }

     void UpdateSkilldescription(string newSkillDescription) {
        cout << "Skill description for " << SkillName << " updated successfully " << endl;
        SkillDescription = newSkillDescription;
     }
};

class Sports {
    private:
        int SportId;
        string SportName;
        string SportDescription;
        string RequiredSkill[5];  

    public:
        int SkillCount;

        Sports(int id, string n, string d) {
            SportId = id;
            SportName = n;
            SportDescription = d;
            SkillCount = 0;  
        }

        string GetSportsName() {
            return SportName;
        }

        int GetSportsId() {
            return SportId;
        }

        void addskill(Skill s) {
            if (SkillCount < 5) {
                RequiredSkill[SkillCount++] = s.GetSkillName();
                cout << "Skill " << s.GetSkillName() << " added successfully in " << SportName << endl;
            } else {
                cout << "There is no more space for skills" << endl;
            }
        }

        void removeskill(Skill& s) {
            if (SkillCount == 0) {
                cout << "No skill to remove" << endl;
            } else {
                for (int i = 0; i < SkillCount; i++) {
                    if (s.GetSkillName() == RequiredSkill[i]) {
                        for (int j = i; j < SkillCount - 1; j++) {
                            RequiredSkill[j] = RequiredSkill[j + 1];
                        }
                        SkillCount--;
                        cout << "Skill " << s.GetSkillName() << " removed successfully from " << SportName << endl;
                        return;
                    }
                }
                cout << "Skill not found!" << endl;
            }
        }
};

class Student;

class Mentor {
    private:
        int MentorId;
        string MentorName;
        string SportsExpertise[3];
        int MaxLearners;
        string AssignedLearners[3];

    public:
        int learnercount;

        Mentor(int id, string n, Sports sp1, Sports sp2, Sports sp3) {
            MentorId = id;
            MentorName = n;
            learnercount = 0;
            MaxLearners = 3;
            SportsExpertise[0] = sp1.GetSportsName();
            SportsExpertise[1] = sp2.GetSportsName();
            SportsExpertise[2] = sp3.GetSportsName();
        }

        string GetMentorName() {
            return MentorName;
        }

        string* GetSportExpertise() {
            return SportsExpertise;
        }

        bool AssignLearners(Student &s);

        void RemoveLearner(Student &s);

        void provideguidline() {
            if (learnercount == 0) {
                cout << "No learners are currently assigned." << endl;
            } else {
                for (int i = 0; i < learnercount; i++) {
                    cout << "Student " << AssignedLearners[i] << " should practice their skills regularly and complete the assigned tasks." << endl;
                }
            }
        }
};

class Student {
    private:
        int StudentId;
        string StudentName;
        int StudentAge;
        Mentor* MentorAssigned;
        string StudentSportsInterest[2];

    public:
        int SportsCount;

        Student(int id, string n, int a, Sports sp1, Sports sp2) {
            StudentId = id;
            StudentName = n;
            StudentAge = a;
            SportsCount = 2;
            StudentSportsInterest[0] = sp1.GetSportsName();
            StudentSportsInterest[1] = sp2.GetSportsName();
        }

        string GetStudentName() {
            return StudentName;
        }

        void RegisterForMentorship(Mentor &m) {
            for (int i = 0; i < SportsCount; i++) {
                for (int j = 0; j < 3; j++) {
                    if (StudentSportsInterest[i] == m.GetSportExpertise()[j]) {
                        MentorAssigned = &m;
                        if (m.AssignLearners(*this)) {
                            cout << "Student " << StudentName << " was assigned under mentorship of " << m.GetMentorName() << endl;
                        } else {
                            cout << "Mentor has no available slots" << endl;
                        }
                        return;
                    }
                }
            }
            cout << "Mentor not efficient according to your expertise" << endl;
        }

        void ViewMentorDetails() {
            if (MentorAssigned != nullptr) {
                cout << "Name of mentor is " << MentorAssigned->GetMentorName() << endl;
                cout << "Sports expertise of mentor is: " << endl;
                for (int i = 0; i < 3; i++) {
                    cout << MentorAssigned->GetSportExpertise()[i] << " | ";
                }
                cout << endl;
            } else {
                cout << "No mentor assigned" << endl;
            }
        }

        void UpdateSportsInterest(Sports s) {
            string check;
            int found = 0;
            cout << "Enter sports name you want to update: ";
            cin >> check;
            for (int i = 0; i < 2; i++) {
                if (check == StudentSportsInterest[i]) {
                    StudentSportsInterest[i] = s.GetSportsName();
                    found = 1;
                }
            }
            if (found == 1) {
                cout << "Updated interest" << endl;
                for (int i = 0; i < 2; i++) {
                    cout << StudentSportsInterest[i] << endl;
                }
            } else {
                cout << "Invalid sports name" << endl;
            }
        }
};

bool Mentor::AssignLearners(Student &s) {
    if (learnercount < MaxLearners) {
        AssignedLearners[learnercount++] = s.GetStudentName();
        return true;
    } else {
        return false;
    }
}

void Mentor::RemoveLearner(Student &s) {
    for (int i = 0; i < learnercount; i++) {
        if (s.GetStudentName() == AssignedLearners[i]) {
            for (int j = i; j < learnercount - 1; j++) {
                AssignedLearners[j] = AssignedLearners[j + 1];
            }
            learnercount--;
            cout << "Student removed successfully." << endl;
            return;
        }
    }
    cout << "Student not found in assigned list." << endl;
}

int main() {
    Skill sk[10] = {
        Skill(1, "Agility", "Quick movement."),
        Skill(2, "Coordination", "Precise movements."),
        Skill(3, "Endurance", "Long-lasting effort."),
        Skill(4, "Strength", "High power."),
        Skill(5, "Speed", "Fast acceleration."),
        Skill(6, "Balance", "Stable control."),
        Skill(7, "Technique", "Skillful methods."),
        Skill(8, "Tactical", "Smart strategies."),
        Skill(9, "Communication", "Clear interaction."),
        Skill(10, "Discipline", "Focused practice.")
    };

    Sports sp[6] = {
        Sports(101, "football", "teamwork and perseverance"),
        Sports(102, "cricket", "strategy and endurance"),
        Sports(103, "volleyball", "agility and coordination"),
        Sports(104, "tennis", "precision and focus"),
        Sports(105, "badminton", "speed and reflexes"),
        Sports(106, "hockey", "strength and teamwork")
    };

    Student s[5] = {
        Student(1, "abdullah", 19, sp[4], sp[5]),
        Student(2, "Irfan", 18, sp[0], sp[1]),
        Student(3, "rameel", 18, sp[1], sp[0]),
        Student(4, "talha", 17, sp[3], sp[1]), 
        Student(5, "rafay", 20, sp[2], sp[3])
    };

    Mentor m[2] = {
        Mentor(201, "Ali", sp[4], sp[0], sp[3]),
        Mentor(202, "Saad", sp[5], sp[2], sp[4])
    };

    cout << "Registering mentor 1 for student 1" << endl;
    s[0].RegisterForMentorship(m[0]);
    cout << "Registering mentor 1 for student 2" << endl;
    s[1].RegisterForMentorship(m[0]);
    cout << "Registering mentor 2 for student 3" << endl;
    s[2].RegisterForMentorship(m[1]);
    cout << "Registering mentor 1 for student 4" << endl;
    s[3].RegisterForMentorship(m[0]);
    cout << "Registering mentor 1 for student 5" << endl;
    s[4].RegisterForMentorship(m[0]);

    cout << "View mentor details of student 1" << endl;
    s[0].ViewMentorDetails();
    cout << "View mentor details of student 2" << endl;
    s[1].ViewMentorDetails();
    cout << "View mentor details of student 3" << endl;
    s[2].ViewMentorDetails();
    cout << "View mentor details of student 4" << endl;
    s[3].ViewMentorDetails();
    cout << "View mentor details of student 5" << endl;
    s[4].ViewMentorDetails();

    cout << "Student 3 wants to update sports interest" << endl;
    s[2].UpdateSportsInterest(sp[2]);

    cout << "Registering mentor 2 for student 3" << endl;
    s[2].RegisterForMentorship(m[1]);

    cout << "View mentor details of student 3" << endl;
    s[2].ViewMentorDetails();

    cout << "Student 2 wants to leave mentor 1" << endl;
    m[0].RemoveLearner(s[1]);

    cout << "Mentor 2 provides guidelines to students" << endl;
    m[1].provideguidline();

    cout << "Mentor 2 wants to add skill in badminton" << endl;
    sp[5].addskill(sk[3]);

    cout << "Mentor 1 wants to remove skill from football" << endl;
    sp[0].removeskill(sk[8]);

    cout << "Mentor 1 wants to add skill in football" << endl;
    sp[0].addskill(sk[5]);

    cout << "Update skill description" << endl;
    sk[7].UpdateSkilldescription("Smart decision making");

    return 0;
}

