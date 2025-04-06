#include <iostream>
#include <string>
#include <memory>
using namespace std;


class Ghost
{
protected:
    string workerName;
    int scareLevel;

public:
    Ghost() {}
    Ghost(string name, int SL) : workerName(name), scareLevel(SL) {}
    virtual ~Ghost() {}
    virtual void haunt() const{
        cout << "Generic ghostly presence... [Scare Level: " << scareLevel << "]\n";
    }

    friend ostream &operator<<(ostream &os, const Ghost &g)
    {
        os << "Ghost played by: " << g.workerName << ", Scare Level: " << g.scareLevel << endl;
        return os;
    }

    virtual Ghost *operator+(const Ghost &other) const
    {
        string newName = workerName + " & " + other.workerName;
        int newRating = scareLevel + other.scareLevel;
        return new Ghost(newName, newRating);
    }
    int getScareLevel() const
    {
        return scareLevel;
    }
};

class Poltergeist : virtual public Ghost
{
public:
    Poltergeist(string name, int SL) : Ghost(name, SL) {}

    void haunt() const override
    {
        cout << "The Poltergeist moves objects violently! [Scare Level: " << scareLevel << "]\n";
    }
};

class Banshee : virtual public Ghost
{
public:
    Banshee(string name, int SL) : Ghost(name, SL) {}

    void haunt() const override
    {
        cout << "The Banshee screams loudly! [Scare Level: " << scareLevel << "]\n";
    }
};

class ShadowGhost : virtual public Ghost
{
public:
    ShadowGhost(string name, int SL) : Ghost(name, SL) {}

    void haunt() const override
    {
        cout << "The Shadow Ghost whispers creepily! [Scare Level: " << scareLevel << "]\n";
    }
};

class ShadowPoltergeist : public ShadowGhost, public Poltergeist
{
public:
    ShadowPoltergeist(string name, int level)
        : Ghost(name, level), ShadowGhost(name, level), Poltergeist(name, level) {}

    void haunt() const override
    {
        ShadowGhost::haunt();
        Poltergeist::haunt();
    }
};

class BansheePoltergeist : public Banshee, public Poltergeist
{
public:
    BansheePoltergeist(string name, int level)
        : Ghost(name, level), Banshee(name, level), Poltergeist(name, level) {}

    void haunt() const override
    {
        Banshee::haunt();
        Poltergeist::haunt();
    }
};

class ShadowBanshee : public ShadowGhost, public Banshee
{
public:
    ShadowBanshee(string name, int level)
        : Ghost(name, level), ShadowGhost(name, level), Banshee(name, level) {}

    void haunt() const override
    {
        ShadowGhost::haunt();
        Banshee::haunt();
    }
};

class Visitor
{
    string name;
    string bravery;

public:
    Visitor() {}
    Visitor(string name, string bravery) : name(name), bravery(bravery) {}
    void reactToGhost(const Ghost &g) const
    {
        int scare = g.getScareLevel();

        if (bravery == "Cowardly")
        {
            if (scare > 4)
                cout << name << " screams then runs away!\n";
            else if (scare <= 1)
                cout << name << " laughs and taunts the ghost!\n";
            else
                cout << name << " speaks shakily and hesitates!\n";
        }
        else if (bravery == "Average")
        {
            if (scare > 7)
                cout << name << " screams then runs away!\n";
            else if (scare <= 5)
                cout << name << " laughs and taunts the ghost!\n";
            else
                cout << name << " speaks shakily and hesitates!\n";
        }
        else if (bravery == "Fearless")
        {
            if (scare > 10)
                cout << name << " screams then runs away!\n";
            else if (scare <= 8)
                cout << name << " laughs and taunts the ghost!\n";
            else
                cout << name << " speaks shakily and hesitates!\n";
        }
        else
        {
            cout << name << " has an unknown bravery type!\n";
        }
    }
};

class HauntedHouse
{
    string name;
    Ghost *ghosts[10];
    int currGhosts;

public:
    HauntedHouse(string name) : name(name), currGhosts(0) {}
    ~HauntedHouse()
    {
        for (int i = 0; i < currGhosts; ++i)
        {
            delete ghosts[i];
        }
    }
    void addHouse(Ghost *g)
    {
        if (currGhosts < 10)
        {
            ghosts[currGhosts] = g;
            currGhosts += 1;
            cout << "Ghost Added.\n";
        }
        else
        {
            cout << "Cannot add anymore ghosts.\n";
        }
    }

    string getName() const
    {
        return name;
    }
    Ghost *getGhosts(int index) const
    {
        return ghosts[index];
    }
    int getCurrGhosts() const
    {
        return currGhosts;
    }
};

void visit(const Visitor *v, int num, const HauntedHouse &house)
{
    cout << "\n Visitors are entering " << house.getName() << "...\n"
         << endl;

    for (int i = 0; i < house.getCurrGhosts(); i++)
    {
        Ghost *g = house.getGhosts(i);
        g->haunt();
        for (int j = 0; j < num; j++)
        {
            v[j].reactToGhost(*g);
        }
        cout << endl;
    }
}

int main()
{

    HauntedHouse house1("Hilltop Horror");
    HauntedHouse house2("Shadow Manor");

    house1.addHouse(new Poltergeist("Ali", 6));
    house1.addHouse(new Banshee("Sara", 8));
    house1.addHouse(new ShadowGhost("Irfan", 4));
    house1.addHouse(new ShadowPoltergeist("Bilal", 7));

    house2.addHouse(new BansheePoltergeist("Hassan", 9));
    house2.addHouse(new ShadowBanshee("Farhan", 5));

    int numVisitors = 4;
    Visitor visitors[numVisitors] = {
        Visitor("Abdullah", "Cowardly"),
        Visitor("Talha", "Average"),
        Visitor("Rameel", "Fearless"),
        Visitor("Rafay", "Average")};

    visit(visitors, numVisitors, house1);
    visit(visitors, numVisitors, house2);

    return 0;
}
