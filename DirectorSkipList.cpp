#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    // TODO
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = new DirectorSLNode("", levels);
    size = 0;
}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // TODO
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("", levels);
    size = 0;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() {
    // TODO
    DirectorSLNode * destroyer = head;
    DirectorSLNode * destroyerNext = head->next[0];
    delete destroyer;
    destroyer = destroyerNext;
    while(destroyerNext->next[0] != NULL){
        destroyerNext = destroyerNext->next[0];
        delete destroyer;
        destroyer = destroyerNext;
    }
    delete destroyer;
    delete destroyerNext;
    delete head;
}

/**
 * @brief Inserts a movie node into the skip list with the specified director.
 *        First checks if MovieNode* already exists in SkipList. If so, just pushes movie
 *        data into corresponding DirectorSLNode vector. Otherwise Handles insertion of new
 *        DirectorSkipList node with the movie's data by randomly determining height of DSLNode,
 *        determining which pointers will "collide" with the node when inserted, and
 *        reassigning those pointers to point to the inserted node.
 * 
 * @param director (string) - Name of the director to insert
 * @param _movie (MovieNode*) - pointer to node to be inserted
 */
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO
    DirectorSLNode * debug = search(director);
    if(debug != NULL){//two meanings of non-NULL return from search
        if(debug->next[0]->director == director){//director already exists, just add the movie to the director
            debug->next[0]->movies.push_back(_movie);
        }
        else{//the return from search is a DSLNode * to the prev of the new node to be inserted
            DirectorSLNode * insertPtr = head;
            DirectorSLNode* prevArr[levels];
            bool flag = true;
            
            //populating the prevArr needed for skiplist node insertion
            for(int i = levels - 1; i >= 0; i --){
                while(insertPtr->next[i] != NULL && flag){
                    if(insertPtr->next[i]->director < director){
                        insertPtr = insertPtr->next[i];
                    }
                    else{
                        flag = false;
                    }
                }
                flag = true;
                prevArr[i] = insertPtr;
            }

            //randomly generate the "height" of the skiplist node
            int randNumLevels = 1;
            srand(time(0));
            while(randNumLevels < levels && rand() % 2 == 0){
                randNumLevels ++;
            }

            //create a new director node
            DirectorSLNode * newDirec = new DirectorSLNode(director, randNumLevels);
            newDirec->addMovie(_movie);
            
            //reassigning nodes that would collide with the new column to be inserted
            for(int i = 0; i < randNumLevels; i ++){
                DirectorSLNode * temp = prevArr[i]->next[i];
                prevArr[i]->next[i] = newDirec;
                newDirec->next[i] = temp;   
            }
        }
    }
    else if(debug == NULL){//if the director doesn't exist
        DirectorSLNode * insertPtr = head;
        DirectorSLNode* prevArr[levels];
        bool flag = true;
        
        //populating the prevArr needed for skiplist node insertion
        for(int i = levels - 1; i >= 0; i --){
            while(insertPtr->next[i] != NULL && flag){
                if(insertPtr->next[i]->director < director){
                    insertPtr = insertPtr->next[i];
                }
                else{
                    flag = false;
                }
            }
            flag = true;
            prevArr[i] = insertPtr;
        }

        //randomly generate the "height" of the skiplist node
        int randNumLevels = 1;
        srand(time(0));
        while(randNumLevels < levels && rand() % 2 == 0){
            randNumLevels ++;
        }

        //create a new director node
        DirectorSLNode * newDirec = new DirectorSLNode(director, randNumLevels);
        newDirec->addMovie(_movie);
        
        //reassigning nodes that would collide with the new column to be inserted
        for(int i = 0; i < randNumLevels; i ++){
            DirectorSLNode * temp = prevArr[i]->next[i];
            prevArr[i]->next[i] = newDirec;
            newDirec->next[i] = temp;   
        }
    }
}

/**
 * @brief Searches for a node in the skip list with the specified director. Returns NULL
 *        if the director does not exist in the SkipList. Otherwise, returns a non-NULL
 *        pointer to somewhere in the skiplist. DO NOT TRUST THAT THE RETURNED POINTER
 *        IS WHERE INSERTION WILL OCCUR. Search returns the first pointer "collision" it
 *        detects, but this is not necessarily where the node needs to be inserted to 
 *        preserve alphabetization. A non-NULL return can also indicate that the director
 *        doesn't exist, but that they need to be inserted.
 * 
 * @param director (string) - Name of the director to search for
 * @return (DirectorSLNode*) - a pointer to the Director SLNode if found, otherwise NULL 
 */
DirectorSLNode *DirectorSkipList::search(string director) {
    // TODO
    DirectorSLNode * searchPtr = head;
 
    for(int i = levels - 1; i >= 0; i --){
        while(searchPtr->next[i] != NULL){
            if(searchPtr->next[i]->director < director){
                searchPtr = searchPtr->next[i];
            }
            else{
                return searchPtr;
            }
        }
    }

    return NULL;
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    // TODO
}
