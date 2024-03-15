# SkipList-HashTable
A data structure that uses a skip list to store the directors of famous movies, and a hash table to store data about famous movies. Each node in the skip list stores a vector containing pointers to all the "movie nodes" in the hash table for which the given director directed the film.
 
# Compilation Instructions (Linux)
1. <g++ driver.cpp DirectorSkipList.cpp MovieHashTable.cpp -o dsl_exec>
2. <./dsl_exec [Argument 2] [Argument 3]>, where:
    - Argument 2: The name of a .csv file that has been properly formatted. IMDB-small.csv, IMDB-Movie-Data.csv, and IMDB-collision-tester.csv are all valid.
    - Argument 3: The size of hash table you would like to create. It is recommended that the hash table be greater than at least 1/2 the number of entries in the .csv file.
3. Follow the menu instructions to search through the data in the Skip List- Hashtable data structure.

# Known Issues
1. CLI option selection menu cannot process non-numerical inputs due to use of stoi() function. Need to add error handling.