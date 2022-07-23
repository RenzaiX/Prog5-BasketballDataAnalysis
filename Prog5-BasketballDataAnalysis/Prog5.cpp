/* ---------------------------------------------
Program 5: March Madness Frenzy

Course: CS 141, Spring 2022. Tues 11am lab
System: Windows using Visual Studio Code
Author: Mykola Turchak
---------------------------------------------
*/

#include <iostream>  // For menu and Output
#include <fstream>   // For file menuut and output
#include <vector>    // menuut file is stored in a vector
#include <cctype>    // Allows using the tolower() function
#include <sstream>   // Allows performing insertion, extraction, and other operations.
#include <algorithm> // defines functions for searching, sorting, counting, manipulating
#include <cstdlib>   //adds absolute value

using namespace std; // So that we don't need to preface cin and cout with std::


// This function displays the menu options for a file.
void displayMenu()
{
    cout << endl << "Select a menu option:" << endl
         << "   1. Display overall information about the data" << endl
         << "   2. Display the path of the winning team to the championship" << endl
         << "   3. Determine which region is expected to win the championship based on a given round" << endl
         << "   4. Identify the best underdog within a given round" << endl
         << "   5. Find the shoo-in and nail-biting games within a given round, or overall" << endl
         << "   6. Compare the actual brackets to your predicted brackets" << endl
         << "   7. Exit " << endl
         << "Your choice --> ";
}



// This is a class of Brackets which represents each row in the CSV File
class Bracket
{
  // Declaring variables that represent the header row in the CSV File

public:
    // Initializing a Constructor which takes a vector of strings
    Bracket(vector<string> row)
    {
        // Assigning each variable to the corresponding column of data in the CSV File
        this->region = row[0];
        this->rank1 = stoi(row[1]);
        this->team1 = row[2];
        this->score1 = stoi(row[3]);
        this->rank2 = stoi(row[4]);
        this->team2 = row[5];
        this->score2 = stoi(row[6]);
        this->winningTeam = row[7];
        this->roundNumber = stoi(row[8]);
        this->gameNumber = stoi(row[9]);
    }
    
    //setters and getters for each variable
    void setRegion(string r){region = r;}
    string getRegion(){return this->region;}

    void setRank1(int r1){rank1 = r1;}
    int getRank1(){return this->rank1;}

    void setTeam1(string t1){team1 = t1;}
    string getTeam1(){return this->team1;}

    void setScore1(int s1){score1 = s1;}
    int getScore1(){return this->score1;}

    void setRank2(int r2){rank2 = r2;}
    int getRank2(){return this->rank2;}

    void setTeam2(string t2){team2 = t2;}
    string getTeam2(){return this->team2;}

    void setScore2(int s2){score2 = s2;}
    int getScore2(){return this->score2;}

    void setWinningTeam(string wT){winningTeam = wT;}
    string getWinningTeam(){return this->winningTeam;}

    void setRoundNumber(int rN){roundNumber = rN;}
    int getRoundNumber(){return this->roundNumber;}

    void setGameNumber(int gN){gameNumber = gN;}
    int getGameNumber(){return this->gameNumber;}


//private data members
private:
    string region;
    int rank1;
    string team1;
    int score1;
    int rank2;
    string team2;
    int score2;
    string winningTeam;
    int roundNumber;
    int gameNumber;

    
}; // end of class



/* This function reads the CSV File and takes the filename as an argument
 * and returns a vector which is an instance of the Bracket class.
 * Source: https://java2blog.com/read-csv-file-in-cpp/
 */
vector<Bracket> readLine(string fname)
{
  // Create a vector of the Bracket class
  vector<Bracket> content;
  vector<string> row;
  string line, word;
  int i = 0;

  fstream file(fname, ios::in);
  if (file.is_open())
  {

    while (getline(file, line))
    {
      if (i == 0)
      {
        i++;
        continue;
      }
      row.clear();

      stringstream str(line);
      // Seperates each word by a comma (',')
      while (getline(str, word, ','))
      {
        // If the data is missing, put a placeholder of -1
        if (word == "")
        {
          row.push_back("0");
        }
        else
        {
          row.push_back(word);
        }
      }
      // Creating an object of the Bracket class.
      Bracket newEntry = Bracket(row);
      content.push_back(newEntry);
    }
  }
  return content;
}

//function to get team's name based on their region
string getTeamName(vector<Bracket> data, string region, vector <string> teams)
{
    //if team name is in vector and the region is the same as the one being passed to the function, then return team name
    for (int i = 0; i < data.size(); i++)
    {   
        for (int j = 0; j < teams.size(); j++)
        { 
            if (teams.at(j) == data.at(i).getTeam1() && data.at(i).getRegion() == region)
            {
                return teams.at(j);
            }
        }
    }
}


//function to get team's region
string getTeamRegion(vector<Bracket> data, string teamName)
{   
    //if team region is not "Championship" and not "Final Four" then return region associated with the team
    for (int i = 0; i < data.size(); i++)
    {   
        if (teamName == data.at(i).getTeam1() && data.at(i).getRegion() != "Championship" && data.at(i).getRegion() != "Final Four")
            {
                return data.at(i).getRegion();
            }
    }

}


//menu option for questions 3-5
void subMenuOptions(int menu)
{   
    cout << "Enter a round to be evaluated: " << endl;

    //only prints if the menu is requested for menu #5
    if(menu == 5){
        cout << "   Select 1 for round 1" << endl;
    }
    
    cout << "   Select 2 for round 2"  << endl
         << "   Select 3 for round 3 'Sweet 16'"  << endl
         << "   Select 4 for round 4 'Elite 8'"  << endl
         << "   Select 5 for round 5 'Final 4'"  << endl;
        
    //only prints if the menu is requested for menu #4
    if(menu == 4)
    {
        cout << "   Select 6 for round 6 'Championship'" << endl;
    }

    //only prints if the menu is requested for menu #5
    else if(menu == 5)
    {  
        cout << "   Select 6 for round 6 'Championship'" << endl
             << "   Select 7 for the overall tournament" << endl;

    }
    cout << "Your choice --> ";
}


int main()
{
    // Program 4 description
    cout << "Program 5: March Madness Frenzy" << endl;
    cout << "CS 141, Spring 2022, UIC " << endl;
    cout << " " << endl;
    cout << "This program reads in data from NCAA Basketball Tournaments (aka March " << endl
        << "Madness). It provides overall information regarding the data, allows you to " << endl
        << "see the path taken to the championship, uses rankings of teams to determine " << endl
        << "which region is expected to win at a given round and to find the best underdog " << endl
        << "team, and calculates point differences within the games. You can also compare " << endl
        << "the actual brackets to your own predictions!" << endl << endl;


    //take the input
    string file;
    cout << "Enter the name of the file with the data for the NCAA tournament: ";
    cin >> file;

    bool isrunning = true; // Boolean variable for checking the condition of while loop

    vector<Bracket> data = readLine(file); //main data with all information from file

    // While loop contains the code for the 6 menu options
    while (isrunning)
    {   
        //displays menu options and take input
        displayMenu();
        int menu;
        cin >> menu;

        // Menu Option 1
        if (menu == 1)
        {
            vector <string> teams;
            vector <string> teamRegion;
            //add to the vector teams that have "Final Four" as their region
            for (int i = 0; i < data.size(); i++)
            {
                if(data.at(i).getRegion() == "Final Four" && find(teams.begin(), teams.end(), data.at(i).getTeam1()) == teams.end())
                {
                    teams.push_back(data.at(i).getTeam1());
                    teams.push_back(data.at(i).getTeam2());
                }
            }
            
            //print number of games, and teams in the "Final Four" according to their region
            cout << "Total number of games played in tournament: " << data.size() << endl
                 << "The Final Four contestants are: " << endl;
            for(int i = 0; i< teams.size(); i++){
                 cout << "        " << data.at((i*15) + 3).getRegion() << " region:    " << getTeamName(data, data.at((i*15) + 3).getRegion(), teams) << endl;
            }
                cout << endl;
            

            continue;
        }


        // Menu Option 2
        else if (menu == 2)
        {
            //find the winner of all games
            string winner = data.at(0).getWinningTeam();
            int count = 1;

            //print every game where winner is "winner" in the revers order
            cout << "Path to the championship: " << endl;
            for (int i = data.size() - 1; i >= 0; i--)
            {   
                if(data.at(i).getTeam1() == winner || data.at(i).getTeam2() == winner)
                {
                    cout << "Round " << count << ", Game " << data.at(i).getGameNumber() << ": " << data.at(i).getTeam1() << " vs " << data.at(i).getTeam2() << ". Winner: " << data.at(i).getWinningTeam() << endl;
                    count++;
                }
            }
            continue;
        }

        // Menu Option 3
        else if (menu == 3)
        {   
            //print the subMenuOptions and take the input
            string region;
            int subMenu;
            subMenuOptions(menu);
            cin >> subMenu;

            cout << "Analyzing round " << subMenu << "..." <<endl;
            
            //if the input is within 2 and 4
            if(subMenu >= 2 && subMenu <=4 )
            {   
                int maxRank = 100;
                string teamRegion;
                vector <string> regionVector;
                vector <int> rankVector;

                for (int i = 0; i < data.size(); i++)
                {
                    //Checl if round number is correct and team 1 won, but region doesn't exists
                    if((data.at(i).getRoundNumber() == subMenu) && (data.at(i).getWinningTeam() == data.at(i).getTeam1()) && (find(regionVector.begin(), regionVector.end(), data.at(i).getRegion()) == regionVector.end()))
                    {   
                        //Add values to the vector
                        regionVector.push_back(data.at(i).getRegion());
                        rankVector.push_back(data.at(i).getRank1());
                    }

                    //check if round number is correct, team 1 won, and region already exists in region vector
                    else if((data.at(i).getRoundNumber() == subMenu) && (data.at(i).getWinningTeam() == data.at(i).getTeam1()) && (find(regionVector.begin(), regionVector.end(), data.at(i).getRegion()) != regionVector.end()))
                    {   
                        //Loop through region vecotr. If needed region is found, add value
                        for(int j = 0; j < regionVector.size(); j++)
                        {
                            if(regionVector.at(j) == data.at(i).getRegion() )
                            {
                                rankVector.at(j) += data.at(i).getRank1();
                            }
                        }
                    }

                    //Checl if round number is correct and team 2 won, but region doesn't exists
                    else if((data.at(i).getRoundNumber() == subMenu) && (data.at(i).getWinningTeam() == data.at(i).getTeam2()) && (find(regionVector.begin(), regionVector.end(), data.at(i).getRegion()) == regionVector.end()))
                    {
                        //Add values to the vector
                        regionVector.push_back(data.at(i).getRegion());
                        rankVector.push_back(data.at(i).getRank2());
                    }
                    //Check if round number is correct, team 2 won, and region already exists in region vector
                    else if((data.at(i).getRoundNumber() == subMenu) && (data.at(i).getWinningTeam() == data.at(i).getTeam2()) && (find(regionVector.begin(), regionVector.end(), data.at(i).getRegion()) != regionVector.end()))
                    {
                        //Loop through region vecotr. If needed region is found, add value
                        for(int j = 0; j < regionVector.size(); j++)
                        {
                            if(regionVector.at(j) == data.at(i).getRegion())
                            {
                                rankVector.at(j) += data.at(i).getRank2();
                            }
                        }
                    }
                }

                //Find the smallests value. If value found, change maxRank to that value and look in parralel vector for region name
                for(int i = 0; i<rankVector.size(); i++)
                {   
                    if(maxRank > rankVector.at(i))
                    {
                        maxRank = rankVector.at(i);
                        region = regionVector.at(i);
                    }
                }
            }

            else if(subMenu == 5)
            {   
                string winner;
                int lowestRank = 100;
                
                //loop through rows 3 and 4 (Final Four) and update variable depending on the lowest value of rank for the winning team
                for (int i = 1; i <= 3; i++)
                {
                    //if team 1 won
                    if(data.at(i).getRegion() == "Final Four" && lowestRank > data.at(i).getRank1() && (data.at(i).getWinningTeam() == data.at(i).getTeam1()))
                    {
                        winner = data.at(i).getTeam1();
                        lowestRank = data.at(i).getRank1();
                        region = getTeamRegion(data, winner);
                    }
                    //if team 2 won
                    else if(data.at(i).getRegion() == "Final Four" && lowestRank > data.at(i).getRank2() && (data.at(i).getWinningTeam() == data.at(i).getTeam2()))
                    { 
                        winner = data.at(i).getTeam2();
                        lowestRank = data.at(i).getRank2();
                        region = getTeamRegion(data, winner);
                    }
                }
            }
            //print the region that is expected to win
            cout << endl << "The region expected to win is: " << region << endl;
        }

        else if (menu == 4)
        {
            //print the subMenuOptions and take the input
            int subMenu;
            subMenuOptions(menu);
            cin >> subMenu;

            int highestRank = 0;
            string teamName;

            for (int i = 0; i < data.size(); i++)
            {
                //Checl if round number is correct and team 1 rank is greater than "highestRank"
                if((data.at(i).getRoundNumber() == subMenu) && (data.at(i).getRank1() >  highestRank))
                {
                    highestRank = data.at(i).getRank1();
                    teamName = data.at(i).getTeam1();
                }
                //Checl if round number is correct and team 2 rank is greater than "highestRank"
                if((data.at(i).getRoundNumber() == subMenu) &&(data.at(i).getRank2() >  highestRank))
                {
                    highestRank = data.at(i).getRank2();
                    teamName = data.at(i).getTeam2();
                }
            }
            cout << "The best underdog team is " << teamName << " which has rank " << highestRank << "." << endl;
        }
        // Menu Option 5
        else if (menu == 5)
        {
            //print the subMenuOptions and take the input
            int subMenu;
            subMenuOptions(menu);
            cin >> subMenu;
            
            string analyzing;
            vector <int> round = {0, 0};
            vector <string> title = {"", ""};
            vector<int> difference = {0, 100};
            vector<int> gameNumber = {0, 0};
            vector <string> team1 = {"", ""};
            vector <string> team2 = {"", ""};
            vector <string> winner = {"", ""};

            for (int i = 0; i < data.size(); i++)
            {   
                //if user enters 7, find the match of greatest difference in all rounds
                if(subMenu == 7)
                {
                    analyzing = "the overall tournament";
                    

                    if((difference.at(0) < abs(data.at(i).getScore1() - data.at(i).getScore2()))){
                        
                        title.at(0) = "The shoo-in game was: ";
                        difference.at(0) = abs(data.at(i).getScore1() - data.at(i).getScore2());
                        gameNumber.at(0) = data.at(i).getGameNumber();
                        team1.at(0) = data.at(i).getTeam1();
                        team2.at(0) = data.at(i).getTeam2();
                        winner.at(0) = data.at(i).getWinningTeam();
                        round.at(0) = data.at(i).getRoundNumber();
                    }
                    //if user enters 7, find the match of smallest difference in all rounds
                    if((difference.at(1) > abs(data.at(i).getScore1() - data.at(i).getScore2())))
                    {
                        title.at(1) = "The nail-biting game was: ";
                        difference.at(1) = abs(data.at(i).getScore1() - data.at(i).getScore2());
                        gameNumber.at(1) = data.at(i).getGameNumber();
                        team1.at(1) = data.at(i).getTeam1();
                        team2.at(1) = data.at(i).getTeam2();
                        winner.at(1) = data.at(i).getWinningTeam();
                        round.at(1) = data.at(i).getRoundNumber();
                    }
                }

                //if user enters 1-6, find the match of greatest difference in that rounds
                else if((data.at(i).getRoundNumber() == subMenu))
                {
                    analyzing = "round " + to_string(subMenu);
                    

                    if(difference.at(0) < abs(data.at(i).getScore1() - data.at(i).getScore2()))
                    {   
                        title.at(0) = "The shoo-in game was: ";
                        difference.at(0) = abs(data.at(i).getScore1() - data.at(i).getScore2());
                        gameNumber.at(0) = data.at(i).getGameNumber();
                        team1.at(0) = data.at(i).getTeam1();
                        team2.at(0) = data.at(i).getTeam2();
                        winner.at(0) = data.at(i).getWinningTeam();
                        round.at(0) = data.at(i).getRoundNumber(); 
                    }
                    //if user enters 1-6, find the match of greatest difference in that rounds
                    if(difference.at(1) > abs(data.at(i).getScore1() - data.at(i).getScore2()))
                    {
                        title.at(1) = "The nail-biting game was: ";
                        difference.at(1) = abs(data.at(i).getScore1() - data.at(i).getScore2());
                        gameNumber.at(1) = data.at(i).getGameNumber();
                        team1.at(1) = data.at(i).getTeam1();
                        team2.at(1) = data.at(i).getTeam2();
                        winner.at(1) = data.at(i).getWinningTeam();
                        round.at(1) = data.at(i).getRoundNumber(); 
                    }
                }
            }

            cout << "Analyzing " << analyzing << "..." << endl;

            //create output with all the collected data for shoo-in and nail-bitting games
            for(int i = 0; i < title.size(); i++)
            {
                cout << endl << title.at(i) << endl
                     << "Round " << round.at(i) << ", Game " << gameNumber.at(i) << ": " << team1.at(i) << " vs " << team2.at(i) << ". Winner: " << winner.at(i) << endl
                     << "The difference was " << difference.at(i) << " points." << endl << endl;
            }
        }
        
        // Menu Option 6
        else if (menu == 6)
        {   
            //take in the prediction file
            string predictionFile;
            cout << "Enter the name of the file with your predicted brackets: ";
            cin >> predictionFile;

            vector<Bracket> predictions = readLine(predictionFile); //read the prediction file
            int score = 0;
            int guessedCount = 0;

            for (int i = 0; i < data.size(); i++)
            {   
                //if winning teams are the same, than add value (round number * 5) to score and increment number of correct guesses
                if(data.at(i).getWinningTeam() == predictions.at(i).getWinningTeam())
                {
                    score += data.at(i).getRoundNumber() * 5;
                    guessedCount++;
                }
            }
            //print the results
            cout << "You correctly predicted the winner for " << guessedCount << " games." << endl
                 << "This means that you have a score of " << score << "." << endl;
            
            //print positive or negative text depending if the score is above 250 or not
            if(score > 250)
            { 
                cout << "Great job! You could consider entering your predictions to win money!" << endl;
            }
            else if(score <= 250)
            {
                cout << "You may want to learn more about basketball to improve your predictions next year." << endl;
            }
        }

        // Menu Option 7
        else if (menu == 7)
        {
        // Sets the while loop to false and break out
        isrunning = false;
        cout << "Exiting program..." << endl;
        break;
        }
        // If user input is invalid (not 1-7) then run the loop again
        else
        {
        cout << "Invalid value.  Please re-enter a value from the menu options below." << endl;
        continue;
        }
    }

    return 0;
}