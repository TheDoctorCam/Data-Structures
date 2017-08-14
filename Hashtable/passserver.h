/*******************************************
 Coder: Cameron Stacy
 Course: COP4530
 Project: Pass Server
 ******************************************/

#include "hashtable.h"
#include<iostream>
#include <crypt.h>
#include <utility>
#include <unistd.h>
#include <string>
#include <cstring>

using std::string;

class PassServer{
public:
    /* Default Constructor + Destructor */
    PassServer(size_t size = 101);                      //Create hash table of size size
    ~PassServer();                                      //Cleared by HashTable class
    bool load(const char *filename);                    //Loads password file into hash table object
    bool addUser(std::pair<string,  string> & kv);      //Add a NEW username and password
    bool addUser(std::pair<string, string> && kv);      //Move semantics of addUser()
    bool removeUser(const string & k);                  //Delete exisiting username k
    bool changePassword(const std::pair<string, string> &p, const string & newpassword);    //Change existing password
    bool find(const string & user);                     //Check if a user exists
    void dump();                                        //Show the structure and contents of HashTable object
    size_t size();                                      //Return the size of HashTable
    bool write_to_file(const char *filename);           //Save username and password into file filename
    
private:
    cop4530::HashTable<string, string> server;          //HashTable object
    string encrypt(const string & str);                 //Encrypt the parameter str and return encrypted
    
};