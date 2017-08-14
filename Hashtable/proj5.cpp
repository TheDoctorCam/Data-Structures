#include<iostream>
#include"passserver.h"
#include<string>
#include<stdlib.h>

using namespace std;

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

int main(){
    
    int hashCapacity;
    cout << "Enter preferred hash table capacity: ";
    cin >> hashCapacity;
    
    PassServer server(hashCapacity);
    
    cout << hashCapacity;
    
    char menuChoice;
    string username;
    string password;
    string oldPassword;
    char filename[200];
    
    do
    {
        Menu();
        cout << "\n\n";
        cin >> menuChoice;
        
        switch(menuChoice){
                
            case 'l':
                cout << "Enter password file name to load from" << endl;
                cin >> filename;
                server.load(filename);
                break;
                
            case 'a':
                cout << "Enter username: ";
                cin >> username;
                cout<<"Enter password: ";
                cin >> password;
                server.addUser(make_pair(username,password));
                break;
                
            case 'r':
                cout << "Enter username: " << endl;
                cin >> username;
                server.removeUser(username);
                break;
                
            case 'c':
                cout<<"Enter username: " << endl;
                cin >> username;
                cout<<"Enter password: " << endl;
                cin >> oldPassword;
                cout << "Enter new password: " << endl;
                cin >> password;
                server.changePassword(make_pair(username,oldPassword),password);
                break;
                
            case 'f':
                cout << "Enter username:  " << endl;
                cin >> username;
                if(server.find(username) )
                    cout<<"User " << username << " found" << endl;
                else
                    cout<<"User " << username << " not found" << endl;
                break;
                
            case 'd':
                server.dump();
                break; 
                
            case 's':
                cout << "Size of hashtable: " << server.size() << endl;
                break; 
                
            case 'w':
                cout<< "Enter password file name to write to: " << endl;
                cin >> filename;
                server.write_to_file(filename);
                break; 
                
            case 'x':
                exit(1); 
                
            default:
                cout << "*****Error: Invalid entry.  Try again." << endl;
                break;   
        }
        
    }while(menuChoice!= 'x');
    
    return 0;
}