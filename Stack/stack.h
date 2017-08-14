#ifndef DL_STACK_H
#define DL_STACK_H

#include <iostream>
#include <vector>

namespace cop4530{
    
    template<typename T>
    class stack{
    private:
        int theSize;               //amount of T objects in stack
        std::vector<T> _stack;  //vector to function as ADT stack
        
    public:
        /* Big Five + Constructor */
        stack();                    //default constructor
        stack(const stack<T> & s);  //copy constructor
        stack(stack<T> && s);       //move constuctor
        stack<T>& operator= (stack<T> && s);        //move assignment
        stack<T>& operator= (const stack<T> & s);   //copy assignment
        ~stack();   //destructor
        
        /* Member Functions */
        bool empty() const;     //returns true if size -1
        void clear();           //emptys the list but doesn't destroy
        void push(const T &x);   //add x to stack by copy
        void push(T && x);      //add x to stack by move semantic
        void pop();             //removes top element
        T& top();               //returns top element as modifiable lvalue
        const T& top() const;   //returns top element as const lvalue
        int size() const;       //get size
        void print(std::ostream & os, char ofc = ' ') const;   //prints element with space in-between
    };  //end stack private and public member data/functions
    
    /*Stack global operator overloads */
    template<typename T>
    std::ostream& operator << (std::ostream& os, const stack<T> & x);
    
    template<typename T>
    bool operator == (const stack<T> s1, const stack<T> s2);
    
    template<typename T>
    bool operator != (const stack<T> s1, const stack<T> s2);
    
    template<typename T>
    bool operator <= (const stack<T> s1, const stack<T> s2);
    
    
#include "stack.hpp"    //implementation file
    } // end namespace 4530
    
    
    
#endif
