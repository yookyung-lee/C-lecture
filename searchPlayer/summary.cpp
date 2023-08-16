//Yookyung Lee G21036602
//Assessment 2, summary Exercise (CO1409 Programming) 
//a football player tracking program

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//a struct to include player data
struct Player 
{
	string name;
	string team;
	int score;
	int yellowCards;
	int redCards;
};

//messages for the menu that allows users to navigate the application
void displayMenu() 
{
	cout << "< Football Player Tracking Program >" << endl;
	cout << "1. Display all player data" << endl;
	cout << "2. Search for a player" << endl;
	cout << "3. Insert new player records" << endl;
	cout << "4. Display all team data" << endl;
	cout << "5. Exit" << endl;
}

// Function to display all information of the players
//use a vector as a parmeter, display all names, the team, the number of goals, yellow and red cards
void displayAllPlayers(vector<Player>& players) 
{
	cout << endl;

	for (auto& player : players) 
	{
		cout << "Name: " << player.name << "\tTeam: " << player.team << "\tGoals Scored: " << player.score;
		cout<< "\t\tYellow Cards: " << player.yellowCards << "\t\tRed Cards: " << player.redCards << endl;
	}
}


//the function to search for a player by name and display their statistics
void searchPlayer( vector<Player>& players) 
{
	string inputName;
	cout << "Enter player name you want to search: ";
	cin >> inputName;

	if (islower(inputName[0]) ) //if userinput is mitchell, make it Mitchell to be correctly found
	{
		inputName[0] = toupper(inputName[0]); //mitchell->Mitchell 
	}

	bool found = false; //declare and initialize the bool variable
	for (int i = 0; i < players.size(); i++)  //in the vector 'players'
	{ 
		if (players[i].name == inputName) 
		{ //if the name that the user want to find is found
			cout << endl << "< The player's information > " << endl; //display statistics
			cout << "Name: " << players[i].name << endl;
			cout << "Team: " << players[i].team << endl;
			cout << "The number of Goals: " << players[i].score << endl;
			cout << "The number of Yellow Cards: " << players[i].yellowCards << endl;
			cout << "The number of Red Cards: " << players[i].redCards << endl << endl;
			found = true; //successfully found
			break; //break the loop
		}
	}

	if (!found) 
	{ //if there is no record 
		cout << "Player not found!!" << endl;
	}
}

//to insert new player records
void insertPlayer(vector<Player>& players) 
{
	Player newPlayer;
	cout << "Enter player name: ";
	cin >> newPlayer.name;
	cout << "Enter team name: ";
	cin >> newPlayer.team;
	cout << "Enter goals scored: ";
	cin >> newPlayer.score;
	cout << "Enter number of yellow cards: ";
	cin >> newPlayer.yellowCards;
	cout << "Enter number of red cards: ";
	cin >> newPlayer.redCards;
	players.push_back(newPlayer);

	cout << endl<< "The new record is successfully added." << endl;
}



// Function to display the total number of goals, yellow cards and red cards for each team
void displayTeamData(vector<Player>& players) 
{	
	vector<string> teams; //create new vector to include team statistics

	for (auto& player : players) //for all player in the vector 'players'
	{
		if (find(teams.begin(), teams.end(), player.team) == teams.end()) //from begin to end, find the player.team. If it can't be found, its value is equal to teams.end()
		{
			teams.push_back(player.team); //add the player.team into the vector 'teams'
		}
	}

	for (auto& team : teams) //for all team in the vector 'teams'
	{
		int totalScore = 0, totalYellowCards = 0, totalRedCards = 0; //initialize all total variables
		
		for (auto& player : players) //for all player in the vector 'players'
		{
			if (player.team == team) //if there is a team that player plays
			{
				totalScore += player.score; //add score, the number of yellow cards and red cards into the total variables
				totalYellowCards += player.yellowCards;
				totalRedCards += player.redCards;
			}
		}
		cout << "Team: " << team << "\tTotal Goals Scored: " << totalScore << "\tTotal Yellow Cards: ";
		cout<< totalYellowCards << "\tTotal Red Cards: " << totalRedCards << endl;
	}
}


int main()
{
	int menuInput; //the menu's number which the user will enter.
	const int tableSize = 4; //the size of the vector table

	//Create and initialise an appropriate data structure to hold the information
	vector <Player> players =
	{
		{"Mitchell","UCLan",4,1,0},
		{"Jobs","Apple",8,0,0},
		{"Edwards","Jaguar",0,2,4},
		{"Dan","UCLan",2,1,0}
	};

	displayMenu(); //display the menu to choose
	cout << endl<< "Enter the number: "; //notice
	cin >> menuInput; //get the user's input

	//If a user enters an option which is not available
	while (cin.fail() || menuInput < 1 || menuInput>5) 
	{
		cin.clear();          // Make cin ready again       
		cin.ignore(80, '\n'); // after the error

		//Ask the user once more        
		cout << "Invalid input. Please enter the number again: ";
		cin >> menuInput; //get user input again
	}

	//call the function according to the user's choice
	switch (menuInput) 
	{
	case 1: //"1. Display all player data"
		displayAllPlayers(players);
		break;
	case 2: // "2. Search for a player"
		searchPlayer(players);
		break;
	case 3: //"3. Insert new player records"
		insertPlayer(players); //insert a new player record and display it.
		displayAllPlayers(players); //to show that the record is successfully inserted.
		break;
	case 4: // "4. Display all team data"
		displayTeamData(players);
		break;
	case 5: //"5. Exit" 
		cout << "Thank you.";
		exit(1); //close the program
	}

	return 0;
}
