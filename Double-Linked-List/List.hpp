//Cameron Stacy COP4530 Summer 2017



#ifndef LIST_HPP
#define LIST_HPP



#include "List.h"   //includes namespace cop4530
#include <utility>  //swap

/********************************
 *                              *
 *  Nested Const Itr Class      *
 *                              *
 ********************************/

//zero parameter constructor
template<typename T>
List<T>::const_iterator::const_iterator()
{
    current = nullptr;
}


//operator * -- returns at pos
template<typename T>
const T & List<T>::const_iterator::operator* () const
{
    return retrieve();      //retrieves element referred when deferenced
}


//prefix increment
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
    current =  current->next;
    return *this;
}

//postfix increment
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++(*this);   //use already defined prefix ++ operator;
    return *temp;
}

//prefix decrement
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

//postfix decrement
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --(*this);
    return *temp;
}

//bool operator == returns true iff calling itr equal to parameter itr
template<typename T>
bool List<T>::const_iterator::operator== (const const_iterator & rhs) const
{
    if(current == rhs.current) return true;
    return false;
}

//bool operator != returns true iff calling itr not equal to parameter itr
template<typename T>
bool List<T>::const_iterator::operator!= (const const_iterator & rhs) const
{
    return !(*this == rhs);
}


//accessor function -- gets current iterators data
template<typename T>
T & List<T>::const_iterator::retrieve() const
{
    return current->data;
}

//protected const iterator, sets pointer to parameter p
template<typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p}
{
    
}

/***** End of const_iterator *****/





/********************************
 *                              *
 *      Nested  Itr Class       *
 *    inherit from const itr    *
 ********************************/


//default constructor... calls parent const iterator constructor
template<typename T>
List<T>::iterator::iterator()
{   }


template<typename T>
T& List<T>::iterator::operator* ()
{
    return const_iterator::retrieve();
}

//calls parent retrieve
template<typename T>
const T & List<T>::iterator::operator* () const
{
    return const_iterator::operator*();
    
}

//prefix increment
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

//postfix increment
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);   //use already defined prefix ++ operator;
    return temp;
}

//prefix decrement
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

//postfix decrement
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator temp = *this;
    --(*this);
    return temp;
}



//protected constructor -- one parameter using parent protected constructor
template<typename T>
List<T>::iterator::iterator(Node *p) : List<T>::const_iterator::const_iterator(p)
{
    
}

/***** End of iterator *****/






/********************************
 *                              *
 *         List Class           *
 *                              *
 ********************************/



/***** List Constructors/Destructors *****/

//default constructor
template<typename T>
List<T>::List()
{
    init();
}

//copy constructor
template<typename T>
List<T>::List(const List & rhs)
{
    init(); //create new node obj
    for(auto &itr : rhs) push_back(itr);
}


//move semantic constructor
template<typename T>
List<T>::List(List && rhs)
{
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    
    rhs.theSize =  0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

//constucts number elements with value -val
template<typename T>
List<T>::List(int num, const T& val)
{
    init();     //creates blank list
    for(int i = 0; i < num; i++)
    {
        this->push_back(val);
    }
}

//constructs with elements [start, end)
template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
    init();
    for(auto itr = start; itr != end; ++itr)
    {
        this->push_back(*start);       //access start iterator pointer
    }
}

//constructs with a copt of each of the elements in the initializer_list
template<typename T>
List<T>::List(std::initializer_list<T> iList)
{
    init();
    for(auto itr : iList)   this->push_back(itr);
}

//destructor
template<typename T>
List<T>::~List()
{
    clear();
    delete head; //delete head/tail markers because they won't be cleaned up in clear()
    delete tail;
}

/***** End of List Constructors/Destructors *****/



/***** overloaded assignment operators *****/

//copy assignment operator
template<typename T>
const List<T> &List<T>::operator= (const List & rhs)
{
    List temp = rhs;    //create copy for swap
    std::swap(*this, temp);
    return *this;
}

//move assingment operator
template<typename T>
List<T> &List<T>::operator= (List && rhs)
{
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}


// sets list to the elements of the initializer_list
template<typename T>
List<T> &List<T>::operator= (std::initializer_list<T> iList)
{
    List temp = iList;
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    std::swap(theSize, temp.theSize);
    return *this;
}

/***** End of overloaded assingment operators *****/





/***** Member Functions *****/


//return number of elements
template<typename T>
int List<T>::size() const
{
    return theSize;
}

//check if the list is empty
template<typename T>
bool List<T>::empty() const
{
    return (theSize != 0);
}

//delete all the elements (destructor deletes head and tail
template<typename T>
void List<T>::clear()
{
    while(!empty() ) pop_front();
}

//reverses the order of the elements
template<typename T>
void List<T>::reverse()
{
    if(head == NULL) return;    //no nodes to reverse
    
    std::swap(head,tail);   //swap head and tail nodes to start reverse
    
    Node * tempHead = head; //old tail value
    while(tempHead != NULL)
    {
        std::swap(tempHead->prev, tempHead->next);
        tempHead = tempHead->next;
    }
    
 

}

//returns reference to first node
template<typename T>
T& List<T>:: front()
{
    return *begin();
}

//returns const reference to first node
template<typename T>
const T& List<T>::front() const
{
    return *begin();
}

//returns reference to last node
template<typename T>
T& List<T>::back ()
{
    return *--end();  //return *end would return tail node
}

//returns const reference to last node
template<typename T>
const  T& List<T>::back() const
{
    return *--end();  //return *end would return tail node
}

//prints all elements with delimeter of ofc
template<typename T>
void List<T>::print(std::ostream & os, char ofc) const
{
    for(auto itr = begin(); itr != end(); ++itr)
    {
        os << *itr << ofc;
    }
}



/***** List Insert, move, delete node member functions *****/


//insert node at beginning of list
template<typename T>
void List<T>::push_front(const T & val)
{
    insert(begin(), val);
}

//move semantic insert at beginning of list
template<typename T>
void List<T>::push_front(T && val)
{
    insert(begin(), std::move(val));
}

//insert node at the end of the list
template<typename T>
void List<T>::push_back(const T & val)
{
    insert(end(), val);
}

//move semantic insert node at the end of list
template<typename T>
void List<T>::push_back(T && val)
{
    insert(end(), std::move(val));
}

//delete first node
template<typename T>
void List<T>::pop_front()
{
    erase(begin());
}

//delete last node
template<typename T>
void List<T>::pop_back()
{
    erase(--end());
}

//remove elements with matching value val
template<typename T>
void List<T>::remove(const T & val)
{
    for(auto itr = this->begin(); itr != this->end(); ++itr)
    {
        if(itr.current->data == val)    erase(itr);
    }
}


//removes all elements where predicate is true
template<typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
    for(auto itr = begin(); itr != end(); ++itr)
    {
        if(pred(itr.current->data)) erase(itr);
    }
}



/***** List Iterator Functions *****/

//List Init Function
template<typename T>
void List<T>::init()
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
    
}

//iterator to first node
template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return {this->head->next};
}

//const iterator to first node
template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return this->head->next;
}

//iterator to last node
template<typename T>
typename List<T>::iterator List<T>::end()
{
    return this->tail;
}


//const iterator to last node
template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return this->tail;
}

//inserts val after itr's index
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
    Node * p = itr.current;
    ++theSize;
    //update 4 pointers-- inserted noded prev/next and previous' next and nexts' previous
    return { p->prev = p->prev->next = new Node(std::move(val), p->prev, p) };
}

//move semantic insert after itr's index
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
    Node * p = itr.current;
    ++theSize;
    //update 4 pointers-- inserted noded prev/next and previous' next and nexts' previous
    return { p->prev = p->prev->next = new Node(std::move(val), p->prev, p) };
}

//delete node at itr's position
template<typename T>
typename List<T>::iterator List<T>::erase (iterator itr)
{
    Node * p = itr.current;
    iterator returnValue {p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    
    return returnValue;
}

//erase indexed set of nodes at [start, end)
template<typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end)
{
    for(List<T>::iterator itr = start; itr != end;) itr = erase(itr); //erase until END
    
    return end;
}

/***** end of list iterators *****/

/***** End of Member Functions *****/

/***** End of List *****/




/***** Overloaded Comparison/ostream Operators *****/

//returns true iff lists are equal
template<typename T>
bool operator== (const List<T> &lhs, const List<T> &rhs)
{
    if (lhs.size() == rhs.size())
    {
        for(auto & itr : lhs)
        {
            for(auto & __itr : rhs)
            {
                if(itr != __itr) return false;
            }
        }
        return true; //reached end of both lists without breaking loop
    }
    
    else return false;   //lists aren't same size.. so they can't be equal
}

//returns true iff lists are of different sized
template<typename T>
bool operator!= (const List<T> &lhs, const List<T> & rhs)
{
    return !(lhs == rhs);
};

//enables cout with cascading
template<typename T>
std::ostream& operator << (std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
};


#endif
