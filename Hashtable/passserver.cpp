#include"passserver.h"
#include<string>
#include<fstream>


PassServer::PassServer(size_t size): server(size) {}
PassServer::~PassServer(){}


bool PassServer::load(const char * filename){
    std::ifstream infile;
    string key, password;
    infile.open(filename);
    
    if (!infile){
        std::cout<<"Wrong file name";
        return false;
    }
    
    while (infile >> key){
        if (infile >> password)
            server.insert(make_pair(key, encrypt(password)));
    }
    return true;
}

bool PassServer::addUser(std::pair<string,  string> & kv){
    
    kv.second = encrypt(kv.second);
    
    if(server.insert(kv)){
        std::cout << "User " << kv.first << " added" << std::endl;
        return true;
    }
}

bool PassServer::addUser(std::pair<string, string> && kv){
    
    kv.second = encrypt(kv.second);
    
    if(server.insert(kv)){
        std::cout << "User " << kv.first << " added" << std::endl;
        return true;
    }
}

bool PassServer::removeUser(const string & k){
    if(!(server.remove(k))){
        std::cout<<"*****Error: User not found. Could not delete user"<< std::endl;
        return false;
    }
    
    server.remove(k);
    std::cout<<"User " << k << " deleted." << std::endl;
    return true;
}


bool PassServer::changePassword(const std::pair<string, string> &p, const string & newpassword){
    
    if((!server.contains(p.first)) || (server.match(make_pair(p.first,encrypt(newpassword))))){
        std::cout << "*****Error: Could not change user password" << std::endl;
        return false;
    }
    
    if(server.match(make_pair(p.first, encrypt(p.second)))){
        server.insert(make_pair(p.first, encrypt(newpassword)));
        std::cout << "Password changed for user denyse" << p.first << std::endl;
        return true;
    }
}

bool PassServer::find(const string & user){
    return server.contains(user);
}

void PassServer::dump(){
    server.dump();
}

size_t PassServer::size(){
    return server.hashSize();
}

bool PassServer::write_to_file(const char *filename){
    return server.write_to_file(filename);
}

string PassServer::encrypt(const string & str){
    char salt[]=  "$1$########";
    char * password = new char [300];
    strcpy(password,crypt(str.c_str(),salt));
    return password; 
}


