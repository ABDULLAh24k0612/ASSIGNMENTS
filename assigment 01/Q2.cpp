#include<iostream>
#include<string>
#include<tuple>
using namespace std;

class Robot{
  
    private:

    string RobotName;
    int Hits;

    public:

    Robot(string n){

        RobotName=n;
        Hits=0;
    }

    int GetRobotHits(){
        return Hits;
    }

    string GetRobotName(){
        return RobotName;
    }

    void hitBall(int &ballX, int &ballY, string direction){
        if(direction == "up"){
            ballY += 1;
            Hits += 1;
        }
        else if(direction == "down"){
            ballY -= 1;
            Hits += 1;
        }
        else if(direction == "left"){
            ballX -= 1;
            Hits += 1;
        }
        else if(direction == "right"){
            ballX += 1;
            Hits += 1;
        }
        else{
            cout<<"Invalid direction...Try again!\n";
        }
    }

};

class Ball{

    private:

    int x;
    int y;

    public:

    Ball(){
      x=0;
      y=0;
    }

    int GetX(){
        return x;
    }

    int GetY(){
        return y; 
    }

    void move(int dx, int dy);
    
    tuple<int,int> GetPosition(){
        return make_tuple(x,y);
    }
};

class Goal{
    
        tuple<int,int> GoalPosition;
        public:
        Goal(){
            GoalPosition = make_tuple(3,3);
        }
        bool IsGoalReached(int ballX, int ballY);
    
};

class Team{

    private:

    string TeamName;
    Robot*player;
    bool IsScored;

    public:

    Team(string n){
       TeamName=n;
       IsScored=false;
       player=nullptr;
    }

    void SetPlayer(Robot*p){
       player=p;
    }

    string GetTeamName(){
        return TeamName;
    }

    int GetHitsFromRobot(){
        return player->GetRobotHits();
    }
    void hitBallinRobot(int &x, int &y, string d){
        player->hitBall(x, y, d);
    }
    void setScored(){
        IsScored = true;
    }
    bool hasScored(){
        return IsScored;
    }
};
class Game{
    Team* teamOne;
    Team* teamTwo;
    Ball* gameBallOne;
    Ball* gameBallTwo;
    Goal* gameGoal;
    public:
    Game(){
        teamOne = nullptr;
        teamTwo = nullptr;
        gameBallOne = nullptr;
        gameBallTwo = nullptr;
        gameGoal = nullptr;
    }
    void setTeamOne(Team* t1){
        teamOne = t1;
    }
    void setTeamTwo(Team* t2){
        teamTwo = t2;
    }
    void setBallOne(Ball* b){
        gameBallOne = b;
    }
    void setBallTwo(Ball* b){
        gameBallTwo = b;
    }
    void setGoal(Goal* g){
        gameGoal = g;
    }
    void startGame();
    bool play(Team* team, Ball* b);

};

void Ball :: move(int dx, int dy){
    x = dx;
    y = dy;
    cout << "New ball position: (" << x << "," << y << ")\n";
}

bool Goal::IsGoalReached(int Ballx, int Bally){
    if(make_tuple(Ballx, Bally) == GoalPosition){
        return true;
    }
    return false;
}

void Game::startGame(){
    if(!teamOne || !teamTwo || !gameBallOne || !gameBallTwo || !gameGoal){
        cout<<"Game setup is incomplete.\n";
        return;
    }
    cout<<"Starting the game between " << teamOne->GetTeamName() << " and" << teamTwo->GetTeamName() << endl;

    
    while(true){
        if(!teamOne->hasScored() && play(teamOne, gameBallOne)){
            teamOne->setScored();
        }
        if(!teamTwo->hasScored() && play(teamTwo, gameBallTwo)){
            teamTwo->setScored();
        }
        if(teamOne->hasScored() && teamTwo->hasScored()){
            break;
        }
    }

        int teamOneHits = teamOne->GetHitsFromRobot();
        int teamTwoHits = teamTwo->GetHitsFromRobot();

        if(teamOneHits < teamTwoHits){
            cout<<"Team " << teamOne->GetTeamName() << " has won with " << teamOneHits << " hits.\n";
        }
        else if(teamOneHits > teamTwoHits){
            cout<<"Team " << teamTwo->GetTeamName() << " has won with " << teamTwoHits << " hits.\n";
        }
        else{
            cout<<"It is a tie. Both the teams took " << teamOneHits << " hits to score.\n";
        }
    cout <<"Game Over...Exiting.\n";
}

bool Game::play(Team* team, Ball* b){
    cout<<team->GetTeamName() << " is currently playing.\n";
   
    string direc;
    cout<<"Enter the hit direction: \n";
    cin>>direc;
    int ballX = b->GetX();
    int ballY = b->GetY();
    team->hitBallinRobot(ballX, ballY, direc);
    b->move(ballX, ballY);
    if(gameGoal->IsGoalReached(b->GetX(), b->GetY())){
        cout<<"Goal " << team->GetTeamName() <<" has scored in " << team->GetHitsFromRobot() << " hits.\n";
        return true;
    }
    else{
        return false;
    }
}




int main(){
    Game myGame;

    Team* teamA = new Team("Team A");
    Team* teamB = new Team("Team B");
    Ball* ballA = new Ball();
    Ball* ballB = new Ball();
    Goal* goal = new Goal();

    Robot* robotA = new Robot("Robot A");
    Robot* robotB = new Robot("Robot B");

    teamA->SetPlayer(robotA);
    teamB->SetPlayer(robotB);

    myGame.setTeamOne(teamA);
    myGame.setTeamTwo(teamB);
    myGame.setBallOne(ballA);
    myGame.setBallTwo(ballB);
    myGame.setGoal(goal);

    myGame.startGame();

    delete teamA;
    delete teamB;
    delete ballA;
    delete ballB;
    delete goal;
    delete robotA;
    delete robotB;
    return 0;
}


