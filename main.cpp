/* Program 4: Billboard Analysis
   Analyze, quantify, and summerize billboard top 50 chart data 
   from three different periods ranging from 1960 to 2020. 

   Author: Jennifer Le
   Date: 3/16/2022
   Class: CS 141, Spring 2022, UIC. Tues 9am Lab
   System: Mac using Visual Studio Code
*/
#include <iostream>      // for cout and cin statements
#include <fstream>       // for file input and output
#include <string>        // for string operations 
#include <vector>        // for vector operations
#include <sstream>       // for stringstrem
#include <algorithm>     // for count()
#include <cctype>        // for tolower()
using namespace std;

struct Billboard {
   vector<string> date;    
   vector<int> rank;
   vector<string> song;
   vector<string> artist;
   vector<int> lastWeek;
   vector<int> peakRank; 
   vector<int> weeksOnBoard;
};

// first, function opens and reads csv file, and stores data into a vector
// second, function populates top50Songs members withe the data using index
void readFileAndPopulateObject(string csvFile, Billboard& top50Songs) {
   fstream inStream;
   inStream.open(csvFile);     // opens file
   
   vector<string> allData;     // contains all data points of csv file              
   string row;                
   string word;                // element in the vector allData e.g "John Lennon"

   while (inStream) {
      getline(inStream, row);
      stringstream s(row);
      while(getline(s, word, ',')) {    // input from a single row, stops when it reaches a comma
         allData.push_back(word);          
      }
   }  inStream.close();                 // closes file 

   // populate Billboard object top50Songs's memebers using the index 
   for (int index = 7; index < allData.size(); index++) {            // starts at 7 to omit first row of csv file            
      if (allData.at(index) == "") {allData.at(index) = "0"; }       // default for if a data point is empty
      if (index % 7 == 0) { top50Songs.date.push_back(allData.at(index)); }
      if (index % 7 == 1) { int intRank = stoi(allData.at(index)); top50Songs.rank.push_back(intRank); }
      if (index % 7 == 2) { top50Songs.song.push_back(allData.at(index)); }
      if (index % 7 == 3) { top50Songs.artist.push_back(allData.at(index)); }
      if (index % 7 == 4) { int intLastWeek = stoi(allData.at(index)); top50Songs.lastWeek.push_back(intLastWeek); }
      if (index % 7 == 5) { int intPeakRank = stoi(allData.at(index)); top50Songs.peakRank.push_back(intPeakRank); }
      if (index % 7 == 6) { int intWeeksOnBoard = stoi(allData.at(index)); top50Songs.weeksOnBoard.push_back(intWeeksOnBoard); }
   } 
}

// displays program header and fileOption menu, displaying the three time periods
void displayFileOptions() {
   cout << "Program 4: BillBoard Analysis \n"
      << "CS 141, Spring 2022, UIC \n \n"
      << "This program will analyze weekly Billboard data spanning from 1960 - 2020.\n\n"
      << "Select file option:\n"
      << "   1. To analyze charts top 50: 1960 - 1980 data file\n"
      << "   2. To analyze charts top 50: 1981 - 2000 data file\n"
      << "   3. To analyze charts top 50: 2001 - 2020 data file\n"
      << "Your choice --> ";
}

// displays menuOptions 1 through 5 and describes them
void displayMenuOptions() {
   cout << "\n\nSelect a menu option: \n"
      << "   1. Display overall information about the data\n"
      << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n"
      << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n"
      << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n"
      << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n"
      << "   6. Exit\n"
      << "Your choice --> ";
}

// used to check if inputed decade or year is in the right range depending of the csv file option
bool rangeError(int fileOption, int decadeOrYear, char characterDandY) {
   if (characterDandY == 'Y' || characterDandY == 'y') {
      if (fileOption == 1) {if (decadeOrYear < 1960 || decadeOrYear > 1980) {return true; } else {return false;} }
      if (fileOption == 2) {if (decadeOrYear < 1981 || decadeOrYear > 2000) {return true; } else {return false;} }
      if (fileOption == 3) {if (decadeOrYear < 2001 || decadeOrYear > 2020) {return true; } else {return false;} }
   }
   // range is slightly different for decade
   if (characterDandY == 'D' || characterDandY == 'd') {     
      if (fileOption == 1) {if (decadeOrYear < 1960 || decadeOrYear > 1980) {return true; } else {return false;} }
      if (fileOption == 2) {if (decadeOrYear < 1980 || decadeOrYear > 2000) {return true; } else {return false;} }
      if (fileOption == 3) {if (decadeOrYear < 2000 || decadeOrYear > 2020) {return true; } else {return false;} }
   }
}

// outputs the decade/year message for menuOption 2-4
// takes user input and calls rangeError to make sure there are no errors
void decadeYearMessage(Billboard& top50Songs, int fileOption, char& decadeOrYear, string& decade, string& year, bool& error) {
   while (1 == 1) {  // loop makes sure year or decade choice input is valid
      cout << "Enter D to select a decade or Y to select a year.\nYour choice --> ";
      cin >> decadeOrYear;   

      if (decadeOrYear == 'D' || decadeOrYear == 'd' || decadeOrYear == 'Y' || decadeOrYear == 'y') { 
         break;  // exits loop if character input is valid 
      }
      else {     // restarts loop to get another input if character is invalid
         cout << "Invalid entry. Try again.\n"; continue; 
      } 
   }
   if (decadeOrYear == 'D' || decadeOrYear == 'd') {     // if user chooses decade
      cout << "\nEnter the decade you would like to choose, as a multiple of 10 (e.g. 2010).\n";
      cin >> decade;
      int integerDecade = stoi(decade);
      // if decade isn't within the correct range
      if (rangeError(fileOption, integerDecade, decadeOrYear) == true) {            
         cout << "No songs found in that timeframe. Be sure that the timeframe you" 
            << "enter is within the one covered by the dataset chosen.\n"; 
         error = true; 
      }
      else { error = false; }
   }
   if (decadeOrYear == 'Y' || decadeOrYear == 'y') {    // if user chooses year
      cout << "\nEnter the year you would like to choose (e.g. 2001).\n";
      cin >> year;
      int integerYear = stoi(year);
      // if decade isn't within the correct range
      if (rangeError(fileOption, integerYear, decadeOrYear) == true) {
         cout << "No songs found in that timeframe. Be sure that the timeframe you" 
            << "enter is within the one covered by the dataset chosen.\n"; 
         error = true; 
      }
      else { error = false; }
   }
}

// calculate top50Songs data and output menuOption1 message using that data
void menuOption1(Billboard top50Songs) {
   cout << "Total number of rows: " << top50Songs.song.size() << endl;
   vector<string> uniqueSongs;    // stores unique elements of song vector
   for (int i = 0; i < top50Songs.song.size(); i++){     
      string value = top50Songs.song.at(i);
      if(find(uniqueSongs.begin(), uniqueSongs.end(), value ) == uniqueSongs.end()) {  // if song is not found   
         uniqueSongs.push_back(value);   // song is added to uniqueSongs 
      }
   } cout << "Number of unique songs represented in the dataset: " << uniqueSongs.size();
}

// calculate info using top50Songs and output menuOption2 message using that data
void menuOption2(Billboard top50Songs, char decadeOrYear, string decade, string year) {
   vector<string> number1Songs, number1SongsArtists;   // stores #1 billboard songs with corresponding artist  
   if (decadeOrYear == 'D' || decadeOrYear == 'd') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();  
         // if date is in inputed decade and rank is 1
         if(decade.substr(2, 1) == top50Songs.date.at(i).substr(size - 2, 1) && top50Songs.rank.at(i) == 1) {
            number1Songs.push_back(top50Songs.song.at(i));
            number1SongsArtists.push_back(top50Songs.artist.at(i));
         } 
      }
   }
   if (decadeOrYear == 'Y' || decadeOrYear == 'y') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();
         // if year is in inputed year and rank is 1
         if(year == top50Songs.date.at(i).substr(size - 4, 4) && top50Songs.rank.at(i) == 1) {
            number1Songs.push_back(top50Songs.song.at(i));
            number1SongsArtists.push_back(top50Songs.artist.at(i));
         } 
      }
   }
   int maxCount = 0;   // highest number of #1 song occurances   
   // determines maxCount for a list of #1 songs
   for(int i = 0; i < number1Songs.size(); i++) {
      string value = number1Songs.at(i);
      int userCount = count(number1Songs.begin(), number1Songs.end(), value);
      if (userCount > maxCount) { maxCount = userCount; }   
   }
   vector<string> mostNumber1Song, mostNumber1SongArtist; // for songs that are tied
   // loops through #1 songs again and determins which occur the same amount as maxCount
   for (int i = 0; i < number1Songs.size(); i++) {
      string value2 = number1Songs.at(i);
      int count2 = count(number1Songs.begin(), number1Songs.end(), value2);
      if (count2 == maxCount) {
         mostNumber1Song.push_back(number1Songs.at(i));
         mostNumber1SongArtist.push_back(number1SongsArtists.at(i));
      } 
      // removes songs that are already checked 
      for (int j = 0; j < number1Songs.size(); j++) {
         if (number1Songs.at(j) == value2) {
            number1Songs.erase(number1Songs.begin()+j);
            number1SongsArtists.erase(number1SongsArtists.begin()+j);
         }
      }
   }
   cout << "The song(s) with the most #1 occurrences for selected time period is:\n";
   for (int i = 0; i < mostNumber1Song.size(); i++) {
      cout << "        Song Title: " << mostNumber1Song.at(i) << endl;
      cout << "        Artist: " << mostNumber1SongArtist.at(i) << endl;
      cout << "        # of occurrences: " << maxCount << endl << endl;
   }
}

// calculate info using top50Songs and output menuOption3 message using that data
void menuOption3(Billboard top50Songs, char decadeOrYear, string decade, string year) {
   vector<string> possibleSongs, possibleArtists;
   vector<int> possibleWeeksOnBoard;

   if (decadeOrYear == 'D' || decadeOrYear == 'd') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();
         // if date is in inputed decade
         if(decade.substr(2, 1) == top50Songs.date.at(i).substr(size - 2, 1)) {
            possibleSongs.push_back(top50Songs.song.at(i));
            possibleArtists.push_back(top50Songs.artist.at(i));
            possibleWeeksOnBoard.push_back(top50Songs.weeksOnBoard.at(i));
         } 
      }
   }
   if (decadeOrYear == 'Y' || decadeOrYear == 'y') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();
         // if year is in inputed year
         if(year == top50Songs.date.at(i).substr(size - 4, 4)) {
            possibleSongs.push_back(top50Songs.song.at(i));
            possibleArtists.push_back(top50Songs.artist.at(i));
            possibleWeeksOnBoard.push_back(top50Songs.weeksOnBoard.at(i));
         } 
      }
   }
   int maxWeeksOnBoard = 0;
   string song, artist;
   // determins which song was on the board the longest using weeks-on-board column of csv file
   for (int i = 0; i < possibleSongs.size(); i++) {
      if (possibleWeeksOnBoard.at(i) > maxWeeksOnBoard ) {
         maxWeeksOnBoard = possibleWeeksOnBoard.at(i);
         song = possibleSongs.at(i);
         artist = possibleArtists.at(i);
      }
   }
   cout << "\nThe song with the highest number of weeks on the charts is:\n";
   cout << "      " << song << " by " << artist 
      << " with " << maxWeeksOnBoard << " weeks on the chart.";
}

// calculate info using top50Songs and output menuOption4 message using that data
void menuOption4(Billboard top50Songs, char decadeOrYear, string decade, string year) {
   vector<string> songs, artists, dates; 
   vector<int> ranks, lastWeekRanks;

   if (decadeOrYear == 'D' || decadeOrYear == 'd') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();
         // if date is in inputed decade
         if(decade.substr(2, 1) == top50Songs.date.at(i).substr(size - 2, 1)) {
            songs.push_back(top50Songs.song.at(i));
            artists.push_back(top50Songs.artist.at(i));
            dates.push_back(top50Songs.date.at(i));
            ranks.push_back(top50Songs.rank.at(i));
            lastWeekRanks.push_back(top50Songs.lastWeek.at(i));
         } 
      }
   }
   if (decadeOrYear == 'Y' || decadeOrYear == 'y') {
      for(int i = 0; i < top50Songs.song.size(); i++) {
         int size = top50Songs.date.at(i).size();
         // if year is in inputed year
         if(year == top50Songs.date.at(i).substr(size - 4, 4)) {
            songs.push_back(top50Songs.song.at(i));
            artists.push_back(top50Songs.artist.at(i));
            dates.push_back(top50Songs.date.at(i));
            ranks.push_back(top50Songs.rank.at(i));
            lastWeekRanks.push_back(top50Songs.lastWeek.at(i));
         } 
      }
   }
   int maxRankDifference = 0;  // greatest difference between previous week and current rank of songs
   // determins greatest difference
   for(int i = 0; i < songs.size(); i++){
      int rankDifference = lastWeekRanks.at(i) - ranks.at(i);
      if (rankDifference > maxRankDifference) { maxRankDifference = rankDifference; }
   }
   vector<string> greatestSong, greatestArtist, greatestDate; 
   vector<int> greatestLastWeekRank, greatestRank;
   // loops through songs again and determins which rankDifference mataches maxRankDiffernece
   for(int i = 0; i < songs.size(); i++ ) {
      int rankDifference2 = lastWeekRanks.at(i) - ranks.at(i);
      if (rankDifference2 == maxRankDifference) {
         greatestSong.push_back(songs.at(i));
         greatestArtist.push_back(artists.at(i));
         greatestDate.push_back(dates.at(i));
         greatestLastWeekRank.push_back(lastWeekRanks.at(i));
         greatestRank.push_back(ranks.at(i));
      }
   }
   cout << "The song(s) with the greatest climb from previous week to current week position: \n";
   for (int i = 0; i < greatestSong.size(); i++) {
      cout << "      Song Title: " << greatestSong.at(i) << endl;
      cout << "      Artist: " << greatestArtist.at(i) << endl;
      cout << "      Week of: " << greatestDate.at(i) << endl;
      cout << "      Previous Week Position: " << greatestLastWeekRank.at(i) << endl;
      cout << "      Current Week Position: " << greatestRank.at(i) << endl;
      cout << "      Difference of " << maxRankDifference << " between previous week and current week position\n\n";
   }
}

// calculate info using top50Songs and output menuOption5 message using that data
void menuOption5(Billboard top50Songs) {
   string artistName, word;
   cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: ";
   getline(cin, word);        // discard previous input
   getline(cin, artistName);  // actuall inpue
      
   char lowercaseChar;
   string lowercaseArtistName;    
   for (int i = 0; i < artistName.size(); i++) {     // lowercases all characters in string
      lowercaseChar = tolower(artistName[i]);
      lowercaseArtistName.push_back(lowercaseChar);  // forms new lowercase string
   }
   
   vector<string> lowercaseArtists;    // vector of all artists with every character lowercased
   string lowercaseWord;
   for (int i = 0; i < top50Songs.artist.size(); i++){    // lowercases all characters in all artists name 
      lowercaseWord = "";
      string word = top50Songs.artist.at(i); 
      for (int j = 0; j < word.size(); j++) {
         lowercaseChar = tolower(word[j]);
         lowercaseWord.push_back(lowercaseChar);
      }
      lowercaseArtists.push_back(lowercaseWord);          // adds lowercased artist name to vector
   }

   vector<string> songs, artists, dates;  // stores info about inputed artists
   // compares inputed artist to list of all artists
   // push back info if artist match
   for (int i = 0; i < lowercaseArtists.size(); i++) {
      if (lowercaseArtists.at(i).find(lowercaseArtistName) != string::npos && top50Songs.rank.at(i) == 1) {
         songs.push_back(top50Songs.song.at(i));
         artists.push_back(top50Songs.artist.at(i));
         dates.push_back(top50Songs.date.at(i));
      }
   }
   if (songs.empty()) { cout << "No matching artists were found.\n"; }
   else {
      cout << "Retrieval of first 10 #1 records found based upon search by artist name:\n";
      if (songs.size() >= 10) {
         for(int i = 0; i < 10; i++ ) {
            cout << i + 1 << ")   Song: " << songs.at(i) << endl; 
            cout << "     Artist: " << artists.at(i) << endl;
            cout << "     Week of: " << dates.at(i) << endl;
            cout << "     Week Position: 1\n\n";
         }
      }
      if (songs.size() < 10) {  // if there is less than 10 #1 records
         for(int i = 0; i < songs.size(); i++ ) {
            cout << i + 1 << ")   Song: " << songs.at(i) << endl; 
            cout << "     Artist: " << artists.at(i) << endl;
            cout << "     Week of: " << dates.at(i) << endl;
            cout << "     Week Position: 1\n\n";
         }
      }
   }
}
//______________________________________________________________________________________________________________
int main() {
   Billboard top50Songs;  
   string decade, year; 
   char decadeOrYear;   // used to choose between decade or year
   bool error;          // true if year or decade is not within range

   displayFileOptions();
   int fileOption;
   cin >> fileOption;

   // read in csv file and populate correct object
   if (fileOption == 1) { readFileAndPopulateObject("charts_top50_1960_1980.csv", top50Songs); }        
   else if (fileOption == 2) { readFileAndPopulateObject("charts_top50_1981_2000.csv", top50Songs); }       
   else if (fileOption == 3) { readFileAndPopulateObject("charts_top50_2001_2020.csv", top50Songs); }     
   else { cout << "\nInvalid value. Exiting Program."; return 0; }

   int menuOption;
   displayMenuOptions();

   cin >> menuOption;
   while (menuOption != 6) {    // while user doesn't exit program

      if (menuOption == 1) { 
         menuOption1(top50Songs);
      }
      else if (menuOption == 2) { 
         decadeYearMessage(top50Songs, fileOption, decadeOrYear, decade, year, error);
         if (error == false) { menuOption2(top50Songs, decadeOrYear, decade, year); }
      }
      else if (menuOption == 3) {
         decadeYearMessage(top50Songs, fileOption, decadeOrYear, decade, year, error); 
         if (error == false) { menuOption3(top50Songs, decadeOrYear, decade, year); }
      }  
      else if (menuOption == 4) { 
         decadeYearMessage(top50Songs, fileOption, decadeOrYear, decade, year, error); 
         if (error == false) { menuOption4(top50Songs, decadeOrYear, decade, year); }
      }  
      else if (menuOption == 5) { 
         menuOption5(top50Songs);
      }  
      else { cout << "\nInvalid value.  Please re-enter a value from the menu options below."; }
      displayMenuOptions();
      cin >> menuOption; continue; // increments and restarts loop 
   }    
   return 0;
}
