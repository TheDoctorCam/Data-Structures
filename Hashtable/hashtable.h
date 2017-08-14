/*******************************************
    Coder: Cameron Stacy
    Course: COP4530
    Project: Hash Table
 ******************************************/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<list>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
#include<algorithm>
#include <fstream>


namespace cop4530{
    template <typename K, typename V>
    class HashTable{
    public:
        /* Constructor + Destructor */
        HashTable(size_t size = 101);                   //Creates hash table with currentSize of prime_below()
        ~HashTable();                                   //Delete all elements of hash table
        
        /* Accessors */
        bool contains(const K & k);                     //True if key K is in hash table
        bool match(const std::pair<K,V>&kv) const;      //True if key-value pair is in hash table
        void dump();                                    //Display all entries using private makeEmpty()
        
        /* Mutators */
        bool insert(const std::pair<K,V>&kv);           //Add key-value kv to hash table if not duplicate
        bool insert(std::pair<K,V>&& kv);               //Move semantics of insert
        bool remove(const K & k);                       //Delete key k and it's value if it's in the hash table
        void clear();                                   //Delete all elements in hash table
        bool load(const char *filename);                //Load the contents of filename into hash table
        bool write_to_file(const char *filename);       //Writes all elements in hash table into filename
        
        /* Helper Function */
        size_t hashSize();                              //Returns currentSize (passserver)
        size_t primeSize();                             //Retuns the size of prime number prime_num
        
    private:
        
        /* Size constants */
        static const unsigned int max_prime = 1301081;
        static const unsigned int default_capacity = 11;
        
        /* Member Data */
        std::vector <std::list <std::pair<K,V>> > hashTable;    //hashTable as vector of list pairs
        size_t prime_num;
        size_t currentSize;
        
        /* Helper Functions */
        void makeEmpty();                               //Delete all elements in hash table.
        void rehash();                                  //Rehash when size greater than vector size
        size_t myhash(const K &k);                      //Return index where k is stored
        unsigned long prime_below (unsigned long);
        void setPrimes(std::vector<unsigned long>&);    //prime_below() helper function
    };
#include "hashtable.hpp"
}
#endif


