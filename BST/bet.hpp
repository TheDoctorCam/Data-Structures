#ifndef BET_H
#define BET_H
#include <stack>
#include <string>

using std::string;

class BET{
private:
   
    //Node Structure with left and right children
    struct BinaryNode{
        string data;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode() : left{nullptr},right{nullptr}{}
        BinaryNode(const string & s, BinaryNode *l, BinaryNode *r): data{s}, left{l},right{r}{}
    };
    
    
public:
    
    /* Big Three + Default Constructor */
    BET();                      //Default constructor, init root node
    BET(const string postfix);  //Build token seperated postfix tree
    BET(const BET & );          //Deep copy
    ~BET();                     //Destructor, clears all dynamic space
    
    /* Member Functions -- Mutators */
    bool buildFromPostfix(const string postfix); //Return true if tree built successfully
    const BET & operator=(const BET &);          //Assignment operator, makes deep copy
    
    /* Member Functions -- Accessors */
    void printInfixExpression();                //Prints infix expression
    void printPostfixExpression();              //Prints postfix expression
    size_t size();                              //Return number of nodes
    size_t leaf_nodes();                        //Returns number of lead nodes
    bool empty();                               //Returns true if empty
    
    
private:
    /* Private Member Data */
    BinaryNode *root;                           //BN pointer to root node
    
    /* Helper Functions */
    bool isOperator(const string &s);           //Returns true if parameter is operator
    bool isOperand(const string &s);            //Returnrs true if parameter is operand
    int  precedence(const string &s);           //Returns precedence of token
    
    /* Recursive Private Functions */
    void makeEmpty(BinaryNode* &t);             //Delete all nodes in subtree pointed to by t
    void printInfixExpression(BinaryNode *n);   //Print to stdout infix expression
    void printPostfixExpression(BinaryNode *n); //Print to stdout postfix expression
    BinaryNode * clone(BinaryNode *t);          //Clone all nodes in the subtree pointed by t
    size_t size(BinaryNode *t);                 //Return amt nodes in subtree pointed to by t
    size_t leaf_nodes(BinaryNode *t);           //Return amt leaf nodes in subtree pointed by t
};
#endif