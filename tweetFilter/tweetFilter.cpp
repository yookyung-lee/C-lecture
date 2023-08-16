//Yookyung Lee G21036602
//Assessment 2, Tweet filter (CO1409 Programming)

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//the function to convert string to lower case characters
string ToLower(string myString) 
{
	string lowerString;
	for (auto c : myString) //for all characters in the mystring
	{
		lowerString += tolower(c); //make all characters lower case
	}
	return lowerString; //return the string which is all in lower case
}

//the function to display how many times each banned word has been found in ‘tweets1.txt’ on the screen.        
void countData(ifstream& infile, vector<string> bannedWords)
{
	string line, tweetWord;
	infile >> noskipws;

	if (!infile.is_open()) //if the file can't be opened
	{
		cout << "file can't be opened" << endl; //error message
	}

	//perform a comparsion between the words from 'banned.txt' and 'tweets1.txt'.
	for (int index=0; index<bannedWords.size(); index++)
	{
		string bannedWord = bannedWords[index]; //storing each banned word into the string by using index 
		int banCount = 0; //reset count every bannedWords
	
		//to search for a banned word
		while (getline(infile, line)) //to read a text file line by line
		{
			stringstream tweetLine(line);
			while (tweetLine >> tweetWord) //then read it word by word within each line
			{
				if (tweetWord==bannedWord) //if the banned word is found
				{
					banCount++; //increase the count of the banned word
				}
			}
		}
		//display how many times each banned word has been found in 'tweets1.txt' on the screen.
		cout << "\'" << bannedWord << "\' found " << banCount << " times" << endl; 

		infile.close();  //close and reopen the file to count other banned words
		infile.open("tweets1.txt");
	}
	cout << endl<<endl;

}
	
//read the text and compare them with the 'bannedWords' vector
string filterText(string text, vector<string> bannedWords)
{
	const string filter = "***"; //the banned word->"***"
	const int nextOccurence = 3;

	for (string bannedWord:bannedWords) //for all bannedwords in the vector 'bannedWords'
	{
		string noCapText = ToLower(text); //make all letters to lower cases
		size_t pos = noCapText.find(bannedWord); //finds the position of the 'bannedWord'
		while (pos != string::npos) //bannedword found. (if the bannedword is not found in nocaptext, pos will be set to string::npos.)
		{
			text.replace(pos, bannedWord.length(), filter); //change bannedWord to *** 
			pos = text.find(bannedWord, pos + nextOccurence); //to find the next occurrence
		}
	}
	return text; //return the text after filtering
}

//to write the filtered text to separate output files 
//divided the functions for readability
void filterFile(ifstream &inFile, ofstream &outFile, vector<string> bannedWords)
{
	if (inFile.is_open() && outFile.is_open()) //if input and output file is all opened
	{
		string line;
		while (getline(inFile, line)) //read the file line by line
		{
			string filteredLine = filterText(line, bannedWords); //filtering the text line by line
			outFile << filteredLine << endl; //store every line to the outFile
		}
		inFile.close(); //close all file
		outFile.close();
	}
}

int main()
{
	//declare ifstream to read contents
	ifstream bannedFileStream("banned.txt");
	ifstream tweets1Stream("tweets1.txt");
	ifstream tweets2Stream("tweets2.txt");
	ifstream tweets3Stream("tweets3.txt");
	ifstream tweets4Stream("tweets4.txt");

	//declare ofstream to write contents
	ofstream tweets1FilteredStream("tweets1Filtered.txt");
	ofstream tweets2FilteredStream("tweets2Filtered.txt");
	ofstream tweets3FilteredStream("tweets3Filtered.txt");
	ofstream tweets4FilteredStream("tweets4Filtered.txt");

	if (!bannedFileStream.is_open()) //if the file can't be opened
	{ 
		cout << "Error: could not open banned.txt"<< endl; //error message
		exit(1);
	}

	vector<string> bannedWords; //start with an empty list
	string bannedWord; //a word in the "banned.txt"
	while (bannedFileStream >> bannedWord) //extract all word in the file "banned.txt"
	{
		bannedWords.push_back(bannedWord); //store all word into the vector
	}
	bannedFileStream.close(); //close the file

	//calling functions
	//Display how many times each of the banned words (including inside other words) has been found in each of the files.
	countData(tweets1Stream, bannedWords); 	

	filterFile(tweets1Stream, tweets1FilteredStream, bannedWords);
	filterFile(tweets2Stream, tweets2FilteredStream, bannedWords);
	filterFile(tweets3Stream, tweets3FilteredStream, bannedWords);
	filterFile(tweets4Stream, tweets4FilteredStream, bannedWords);
	
	return 0;
}

