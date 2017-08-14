#include "bet.hpp"
#include <iostream>
#include <sstream>


/********************************
* Binary Expression Tree Public *
*********************************/

//Default Constructor
BET::BET()
{
    root = new BinaryNode;
}

/*
One-parameter constructor, where parameter "postfix" is string containing a postfix expression.
The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces.
 */
BET::BET(const std::string postfix)
{
    root = new BinaryNode;
    buildFromPostfix(postfix);
}

//Copy Constructor
BET::BET(const BET& rhs): root{nullptr}
{
    root = clone(rhs.root);
}

//Destructor
BET::~BET()
{
    if(!empty() )   makeEmpty(root);
    delete root;
}

/*
 Parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression.
 Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need
 to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is
 encountered.
 */
bool BET::buildFromPostfix(const string postfix)
{
    
    if(postfix.empty() )
    {
        std::cerr << "Error: Empty Postfix Expression" << std::endl;
        return false;
    }
    
    string token;
    std::stringstream ss(postfix);
    std::stack<BinaryNode*> returnStack;
    
    while(ss >> token)
    {
        if(isOperand(token) )
        {
            BinaryNode * temp = new BinaryNode(token, nullptr, nullptr);
            returnStack.push(temp);
        }
        
        else if(isOperator(token) )
        {
            BinaryNode * temp = new BinaryNode(token, returnStack.top(), nullptr);
            returnStack.pop();
            temp->right = returnStack.top();
            returnStack.pop();
            returnStack.push(temp);
        }
    }
    
    root = returnStack.top();
    
    if(returnStack.empty() ){ std::cerr << "Sorry"; return false; }
    
    returnStack.pop();
    
    if (!returnStack.empty()){
        std::cerr << "Error: Please enter a valid postfix expression" << std::endl;
        makeEmpty(root);
        return false;
    }
    return true;
}


//Assignment Operator
const BET & BET::operator=(const BET& rhs)
{
    root = clone(rhs.root);
    return *this;
}

// Public interface printInfix
void BET::printInfixExpression()
{
    if(!empty() )
        printInfixExpression(root);
    else std::cout << "The tree is empty";
    
    std::cout << std::endl; //Output newline and flush output buffer
}

//Public interface printPostfix
void BET::printPostfixExpression()
{
    if(!empty() )
        printPostfixExpression(root);
    else std::cout << "The tree is empty";

    std::cout << std::endl; //Output newline and flush output buffer
}

//Public interface size accessor
size_t BET::size()
{
    return size(root);
}

//Publix interface leaf_node amount accessor
size_t BET::leaf_nodes()
{
    return leaf_nodes(root);
}

//Returns true if empty and in valid state
bool BET::empty()
{
    return (!root->left && !root->right);
}

/**********************************
 * Binary Expression Tree Private *
 **********************************/

//Returns true if string s is operator
bool BET::isOperator(const string &s){
    return (s == "+" || s == "-" || s == "/" || s == "*");
}

//Returns true if string s is operand
bool BET::isOperand(const string &s){
    if(s.length() == 1){
        return((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= '0' && s[0] <= '9') || (s[0] == '_'));
    }
    return true;
}

int BET::precedence(const string &s)
{
    if(s == "*" || s == "/")    return 2;
    if(s == "+" || s == "-")    return 1;
    
    return 0;
}


void BET::makeEmpty(BinaryNode* &t)
{
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

void BET::printInfixExpression(BET::BinaryNode *n)
{
    bool parenthesis = false;
    if(n != nullptr)
    {
        if (!n->left && !n->right)
            std::cout << " " << n->data << " " ;
        
        else
        {
            if(isOperator(n->data) && isOperator(n->right->data) && (precedence(n->data) > precedence(n->right->data)
                || precedence(n->data) == precedence(n->right->data)))
            {
                if(n->data == "*" || n->data == "/")
                {
                    std::cout << "(";
                    parenthesis = true;
                }
            }
            
            printInfixExpression(n->right);
            if (parenthesis)    std::cout << ")";
            parenthesis = false;    //reset
            
            std::cout << " " << n->data << " ";
            if(isOperator(n->data) && isOperator(n->left->data) && (precedence(n->data) > precedence(n->left->data)
                || precedence(n->data) == precedence(n->left->data)))
            {
                std::cout << "(";
                parenthesis = true;
            }
            
            printInfixExpression(n->left);
            if (parenthesis)    std::cout << ")";
        }
    }
}


void BET::printPostfixExpression(BinaryNode *n)
{
    if(size(n) == 0) return;    //function called on empty object
    if(!root->left && !root->right) std::cout << root->data;
    else{
        printPostfixExpression(n->right);
        printPostfixExpression(n->left);
        std::cout << n->data << " ";
    }
}

BET::BinaryNode * BET::clone(BET::BinaryNode* t)
{
    if(t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->data, clone(t->left) ,clone(t->right)};
}

size_t BET::size(BET::BinaryNode *t)
{
    if(t == nullptr)
        return 0;
    else
        return size(t->left) + size(t->right) + 1; //Plus 1 for Root
}

size_t BET::leaf_nodes(BET::BinaryNode *t)
{
    if(t == nullptr)
        return 0;
    else if(!t->left && !t->right)
        return 1;
    else if (!t->right)
        return leaf_nodes(t->left);
    else if (!t->left)
        return leaf_nodes(t->right);
    else return leaf_nodes(t->left) + leaf_nodes(t->right);
}
