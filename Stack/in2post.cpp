#include "stack.h"
#include <algorithm>
#include <string>
#include <iostream> //cin.get();
#include <sstream>
#include <cstdlib> //atof


using namespace cop4530;
using namespace std;


struct input{
    string str;         //stores variable, operand. or operator
    int op_precedence;  //stores order of operations value
    
    input() : str(""), op_precedence(0){} //default constructor
    input(string s): str(s){
        if(!str.empty() ){
            char op = str[0];
            if(op == '+' || op == '-') op_precedence = 1;
            if(op == '*' || op == '/') op_precedence = 2;
            else op_precedence = -1;
        }else op_precedence = -1;
    }
};



//Helper functions
bool isOperator(char s);
bool isOperand(char s);
bool isNumerical( string s);


//Operation Functions
void in2post(std::vector<input> v);
void post2answer(std::vector<input> v);
std::string evaluate(input op1, input op2, input operation);

int main(){
    
    char c;
    std::vector<input> i;
    string exp;
    bool running = true;
    
    while(running){
        std::cout << "Enter infix expression (\"exit\" to quit): ";
        
    
        while(cin.get(c) && running){
            if(exp == "exit"){
                running = false;
                break;
            }
            else{
                if(c == '\n'){
                    i.push_back(exp);
                    in2post(i);
                    exp = "";
                    i.clear();
                    std::cout << "Enter infix expression (\"exit\" to quit): ";
                }
                else if(c == ' '){
                    i.push_back(input(exp));
                    exp = "";
                }
                else if(c == '(' || c == ')'){
                    string x;
                    x+=c;
                    i.push_back(input(x));
                }
                else if(c == '\0'){
                    running = false;
                }
                else{
                    exp+= c;
                }
            }
        }
        running = false;
    }
    
    return (EXIT_SUCCESS);
}

//return true iff C char is supported operator
bool isOperator(string s)
{
    return(s == "+" || s == "-" || s == "/" || s == "*");
}

//returns true iff C char is an operand
bool isOperand(string s)
{
    if(s.length() == 1)
    {
        char c = s[0];
        return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
    }
    return true;
}


//return true iff string s is a number, variable, or operator
bool isNumerical( string s)
{
    for(auto itr = s.begin(); itr != s.end(); ++itr)
    {
        char c = *itr;
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'))  return false;
    }
    return true;
}

void in2post(const std::vector<input> v)
{
    stack<input> operators;
    input last;
    std::vector<input> answer;
    std::cout << "\nThe postfix expression: ";
    
    for(auto itr = v.begin(); itr != v.end(); ++itr)
    {
        input i = *itr;
        if(isOperand(i.str) )
        {
            std::cout << i.str << " ";
            if(i.str.length() > 0) answer.push_back(i.str);
        }
        if(i.str == "(") operators.push(i); //push parenthesis to operator stack
        else if (isOperator(i.str) )
        {
            while(!operators.empty() && operators.top().str != "(" && (operators.top().op_precedence >= i.op_precedence)){
                std::cout << operators.top().str << " ";
                answer.push_back(operators.top().str);
                operators.pop();
            }
            operators.push(i);
        }
        
        else if(i.str == ")" )
        {
            if(isOperator(last.str) ) std::cout << "Last input was operator, error";
            else
            {
                while(!operators.empty() && operators.top().str != "(")
                {
                    std::cout << operators.top().str << " ";
                    answer.push_back(operators.top().str);
                    operators.pop();
                }
                operators.pop();
            }
        }
        last = i;
    }
    
    if(isOperator(last.str) || last.str == "(") std::cout << "The last input was an operator, error";
    else
    {
        while(!operators.empty() )
        {
            if(operators.top().str == "("){ std::cout << "End of input, parenthesis unmatched"; break; }
            std::cout << operators.top().str << " ";
            answer.push_back(operators.top().str);
            operators.pop();
        }
        std::cout << endl;
    }
    post2answer(answer);
}


void post2answer(std::vector<input> v)
{
    stack<string> operand;
    string answer;
    bool variable = false;
    
    for(auto itr = v.begin(); itr != v.end(); ++itr)
    {
        input i = *itr;
        answer += i.str + " ";
        
        if(!variable && isNumerical(i.str) )
        {
            if(isOperand(i.str) ) operand.push(i.str);
            else if(isOperator(i.str) )
            {
                if(operand.size() < 2) std::cout << "Cannot evaluate... less than two operands";
                else
                {
                    input operand1 = operand.top();
                    operand.pop();
                    input operand2 = operand.top();
                    operand.pop();
                    
                    string result = evaluate(operand2, operand1, i.str);
                    operand.push(result);
                }
            }
        }
        else variable = true;
    }
    
    if(!variable)
    {
        if(operand.size() > 1) std::cout << "The stack has one or more operands still in it";
        else if(operand.size() == 1) std::cout << "Postfix evaluation: " << answer << "=" << operand.top() << std::endl;
        else std::cout << "Postfix evaluation: 0" << std::endl;
    }
    
    else
        std::cout << "Postfix evaluation: " << answer << "= " << answer << std::endl;
}


std::string evaluate(input op1, input op2, input operation)
{
    
    std::stringstream ss;
    double left = 0.0, right = 0.0;
    
    //Convert strings to double
    left = atof(op1.str.c_str());
    right = atof(op2.str.c_str());
    
    
    if(operation.str == "*")    left *= right;
    else if(operation.str == "/"){
        if(right != 0)  left /= right;
        else std::cout << "Division by zero not allowed";
    }
    else if(operation.str == "+") left += right;
    else if(operation.str == "-") left -= right;
    else std::cout << "Invalid operator";
    
    ss << left;
    return ss.str();
}