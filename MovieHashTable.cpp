#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() {
    // TODO
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode* [table_size];
    }

// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) {
    // TODO
    table_size = s;
    table = new MovieNode* [s];
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
// Method of implementation due to chaining used for collision resolution of hash table
MovieHashTable::~MovieHashTable() {
    // TODO
    for(int i = 0; i < table_size; i ++){
        if(table[i] != NULL){
            MovieNode * destroyerNext = table[i]->next;
            MovieNode * destroyer = table[i];
            delete destroyer;
            destroyer = destroyerNext;
            while(destroyerNext != NULL){
                destroyerNext = destroyerNext->next;
                delete destroyer;
                destroyer = destroyerNext;
            }
            delete destroyer;
            delete destroyerNext;
        }
    }
    delete[] table;
    table = NULL;
}

/**
 * @brief Generates an int by summing the ASCII value of every odd character in the movie name (i.e. the 
 *        1th, 3th, ..., kth character of title.) plus the ASCII value of my identikey, caba9156, the 
 *        final sum is then moduloed by table_size.
 * 
 * E.g. hash1("ABCDE") = (B = 66 + (int) "caba9156") + (D = 68 + (int) "caba9156") = n % table_size
 * 
 * @param title (string) - Name of the movie
 * @param table_size (int) - The size of the hash table
 * @return (int) - index of hash table for MovieNode to be inserted at
 */
int hash1(string title, int table_size){
    int hashVal1 = 0;
    string identikey = "caba9156";
    if(title.size() < 2){
        return 0;
    }
    for(int i = 1; i < title.size(); i += 2){
        hashVal1 += (int) ((char) title[i]);
        for(int j = 0; j < 8; j ++){
            hashVal1 += (int) identikey[j];
        }
    }
    return hashVal1 % table_size;
}

/**
 * @brief Generates an int by summing the ASCII value of every even character in the movie name,
 *        modulo table_size, i.e. the 0th, 2th, ..., nth character of title.
 * 
 * E.g. hash2("ABCDE") = (A = 65) + (D = 67) = 132 % table_size
 * 
 * @param title (string) - Name of the movie
 * @param table_size (int) - The size of the hash table
 * @return (int) - index of hash table for MovieNode to be inserted at
 */
int hash2(string title, int table_size){
    int hashVal2 = 0;
    if(title.size() == 1){
        return ((int) ((char) title[0]) % table_size);
    }
    if(title.size() < 1){
        return 0;
    }
    for(int i = 0; i < title.size(); i += 2){
        hashVal2 += (int) ((char) title[i]);
    }
    return hashVal2 % table_size;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
/**
 * @brief Implements double hashing
 * 
 * @param title (string) - Name of the movie. We hash on this value (plus some other stuff)
 * @return (int) - index in hash table that MovieNode is inserted at
 */
int MovieHashTable::hash(string title) {
    // TODO
    return ((hash1(title, table_size) + hash2(title, table_size) + hash2(title, table_size)) % table_size);
    //return 0;
}

/**
 * @brief Inserts a movie node into the hash table with the specified title and increments
 *        for any collisions that occured
 * 
 * @param title (string) - The name of the movie to be inserted into the hash table
 * @param movie (MovieNode*) - Pointer to node to be inserted
 */
void MovieHashTable::insert(string title, MovieNode* movie) {
    // TODO
    int hashIndex = hash(title);
    if (table[hashIndex] != NULL){
        MovieNode * temp = table[hashIndex];
        movie->next = temp;
        setCollisions();
    }    
    table[hashIndex] = movie;
}

/**
 * @brief Searches for a node in the hash table with the specified title
 * 
 * @param title (string) - the name of the movie
 * @return (MovieNode*) - Pointer to the movie if found, NULL otherwise
 */
MovieNode* MovieHashTable::search(string title) {
    // TODO
    MovieNode * validatePtr = table[hash(title)];
    // Because I used chaining for hash table collisions, we have to check that the result of hashing is
    // what we are actually looking for.
    if(validatePtr->title == title){
        return validatePtr;
    }
    // If we do not find the movie we are looking for, iterate down the linked list until we find it or
    // reach the end of the linked list
    else{
        while(validatePtr != NULL){
            if(validatePtr->title == title){
                return validatePtr;
            }
            validatePtr = validatePtr->next;
        }
    }
    return NULL;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
    // TODO
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    // TODO
    n_collisions ++;
}
