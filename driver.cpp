#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO
    srand(time(0));
    fstream inFile;
    inFile.open(argv[1]);

    if(argc != 3 || !inFile.is_open()){ 
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return 0;
    }

    string fileLine;
    MovieHashTable * newHTab = new MovieHashTable(stoi(argv[2]));
    DirectorSkipList * newDSL = new DirectorSkipList();
    getline(inFile, fileLine);

    //read input file, generating hashtable and skiplist along the way
    while(!inFile.eof()){
        getline(inFile, fileLine);
        if(fileLine != ""){
            MovieNode * tempMN = parseMovieLine(fileLine);
            if(tempMN != NULL){
                newHTab->insert(tempMN->title, tempMN);
                newDSL->insert(tempMN->director, tempMN);
            }
        }
    }
    cout << "Number of collisions: " << newHTab->getCollisions() << endl;

    string menuSelStr;
    int menuSelect;
    MovieNode * tempMNptr;
    string movieTitle;

    do{
        display_menu();
        cout << "Enter an option: ";
        getline(cin, menuSelStr);
        menuSelect = stoi(menuSelStr);
        switch(menuSelect){
            case 1:// Printing the director of a movie
            {
                cout << "Enter the movie's name: ";
                getline(cin, movieTitle);
                tempMNptr = newHTab->search(movieTitle);
                if(tempMNptr == NULL){
                    cout << "Looks like that movie is not in our catalog. Please try a different movie." << endl;
                }
                else{
                    cout << "The director of " << tempMNptr->title << " is " << tempMNptr->director << endl;
                }
            }
            break;

            case 2://number of movies by a director
            {
                cout << "Enter director name: ";
                string direcName;
                getline(cin, direcName);
                DirectorSLNode * searchReturn = newDSL->search(direcName);
                if(searchReturn == NULL){
                    cout << "Looks like that director is not in our catalog. Please try a different movie." << endl;
                }
                else{
                    if(searchReturn->director != direcName && searchReturn->next[0]->director == direcName){//chaining resolution
                        searchReturn = searchReturn->next[0];
                        cout << searchReturn->director << " directed " << searchReturn->movies.size() << " movies." << endl;
                    }
                    else{
                        cout << "Looks like that director is not in our catalog. Please try a different movie." << endl;
                    }
                }
            }
            break;

            case 3://find the description of a movie
            {
                cout << "Enter the movie's name: ";
                getline(cin, movieTitle);
                tempMNptr = newHTab->search(movieTitle);
                if(tempMNptr == NULL){
                    cout << "Looks like that movie is not in our catalog. Please try a different movie." << endl;
                }
                else{
                    cout << "Summary: \"" << tempMNptr->description << "\"" << endl;
                }
            }
            break;

            case 4://list the movies by a director
            {
                cout << "Enter director name: ";
                string direcName;
                getline(cin, direcName);
                DirectorSLNode * searchReturn = newDSL->search(direcName);
                if(searchReturn == NULL){
                    cout << "Looks like that director is not in our catalog. Please try a different movie." << endl;
                }
                else{
                    if(searchReturn->director != direcName && searchReturn->next[0]->director == direcName){//print out all the movies by the director
                        searchReturn = searchReturn->next[0];
                        cout << searchReturn->director << " directed the following movies:" << endl;
                        for(int i = 0; i < searchReturn->movies.size(); i ++){
                            cout << "\t\t" << i << ": " << searchReturn->movies[i]->title << endl;
                        }
                    }
                    else{
                        cout << "Looks like that director is not in our catalog. Please try a different movie." << endl;
                    }
                }
            }
            break;

            case 5:
            {
                cout << "Quitting ... " << endl;
            }
            break;

            default:
            {
                cout << "Whoops! Looks like what you entered is not an option. Please enter a valid input" << endl;
            }
            break;
        }
    }
    while(menuSelect != 5);

    return 0;
}

/**
 * @brief Function to parse a CSV line into a MovieNode object 
 * 
 * @param line (string) - A comma separated line containing 12 values
 * @return MovieNode* - A pointer to the created MovieNode object, NULL if line is invalid
 */
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
// Implemented directly in main
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO
}

// Function to display the menu options
void display_menu() {
    // TODO
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
}
