#include "stack.h"  //includes cop4530 namespace and stack definitons
#include <vector>   //vector::push_back, vector::pop_back


/*** Stack Big 5 + Constructor  ***/

//default constructor
template<typename T>
stack<T>::stack()
{
    theSize = -1;
}

//copy constructor
template<typename T>
stack<T>::stack(const stack<T> &s)
{
    theSize = s.theSize;
    _stack = std::move(s._stack);
}

//move constuctor
template<typename T>
stack<T>::stack(stack<T> &&s)
{
    //set lhs member data to rhs
    theSize = s.theSize;
    _stack = s._stack;
    //destroy rhs
    s.theSize = -1;
    s._stack = std::vector<T> ();
}

//move assignment
template<typename T>
stack<T> &stack<T>::operator= (stack<T> &&s)
{
    _stack = std::move(s._stack);
    return *this;
}

//copy assignment
template<typename T>
stack<T> &stack<T>::operator= (const stack<T> &s)
{
    stack<T> temp = s;
    std::swap(*this, temp);
    return *this;
}

//destructor
template<typename T>
stack<T>::~stack()
{
    clear();
    theSize = -1;
}

//end of Big 5 + Constructor


/*** Stack Member Functions ***/



//return true iff stack contains T elements
template<typename T>
bool stack<T>:: empty() const
{
    return (theSize < 0);
}

//calls pop on stack, doesn't call destructor
template<typename T>
void stack<T>:: clear()
{
    while(!empty()) pop();
}

//increase theSize and add const T reference element to top
template<typename T>
void stack<T>:: push (const T & x)
{
    theSize++;
    _stack.push_back(x); //std vector function, adds x after current last element
}

//move semantic of push
template<typename T>
void stack<T>:: push (T && x)
{
    theSize++;
    _stack.push_back(std::move(x));
}

//remove top element, decrement the theSize
template<typename T>
void stack<T>:: pop()
{
    _stack.pop_back();
    theSize--;
}

//returns top T element as modifiable lvalue
template<typename T>
T& stack<T>:: top()
{
    return _stack[theSize];
}

//returns top T element by const reference
template<typename T>
const T& stack<T>:: top() const
{
    return _stack[theSize];
}

//returns the theSize of the stack
template<typename T>
int stack<T>:: size() const
{
    return (_stack.size());
}

//print stack using vector::iterator
template<typename T>
void stack<T>:: print(std::ostream & os, char ofc) const
{
    for(auto itr : _stack) os << itr << ofc;
}

//end of member functions


/*** Stack Global Operator Overloads ***/


/*Stack global operator overloads */

template<typename T>
std::ostream& operator << (std::ostream& os, const stack<T> & x)
{
    x.print(os);
    return os;
}

template<typename T>
bool operator== (const stack<T> s1, const stack<T> s2)
{
    if (s1.size() != s2.size() ) return false;
    else
    {
        stack <T> lhs = s1, rhs = s2;
        while(!lhs.empty() && !rhs.empty() )
        {
            if (lhs.top() != rhs.top() ) return false;
            lhs.pop(); rhs.pop();
        }
    }
    
    return true;
}

template<typename T>
bool operator!= (const stack<T> s1, const stack<T> s2)
{
    return !(s1 == s2);
}

template<typename T>
bool operator <= (const stack<T> s1, const stack<T> s2)
{
    if (s1 == s2) return true;
    else if (s1.size() == s2.size())
    {
        stack<T> rhs = s1, lhs = s2;
        while(!lhs.empty() )
        {
            if(lhs.top() > rhs.top() ) return false;
            lhs.pop(); rhs.pop();
        }
    }
    return true;
}

//end of global operator overloads
//end of stack.hpp