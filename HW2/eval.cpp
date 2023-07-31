//
//  eval.cpp
//  HW2
//
//  Created by Esmail Mozaffari on 4/30/23.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isValidParens(string infix);


int evaluate(string infix, string& postfix, bool& result)
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
{
    // Initialize postfix and operator stack to empty
    postfix = "";
    stack<char> operatorStack;
    
    // Create version of infix with no whitespaces
    string temp = "";
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] != ' ')
            temp += infix[i];
    }
    infix = temp;       // Update infix with no whitespaces
    
    // Empty infix is invalid
    if (infix.size() == 0)
        return 1;
    
    // Check for parenthesis symmetry
    if (!isValidParens(infix))
        return 1;
    
    // Infix to Postfix //
    for (int i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
            // Operands
            case 'F':
            case 'T':
                // Check char right before
                if (i > 0 && (infix[i-1] == 'T' || infix[i-1] == 'F' || infix[i-1] == ')'))
                    return 1;
                
                postfix += infix[i];
                break;
            
            // Open Parens
            case '(':
                // ( can't be last element in string
                if (i == infix.size() - 1)
                    return 1;
                
                // Check char right before
                if (i > 0 && (infix[i-1] == 'T' || infix[i-1] == 'F' || infix[i-1] == ')'))
                    return 1;
                
                operatorStack.push(infix[i]);
                break;

            // Close Parens
            case ')':
                // ) can't be first element in string
                if (i == 0)
                    return 1;
                
                // Check char right before
                if (i > 0 && (infix[i-1] == '&' || infix[i-1] == '^' || infix[i-1] == '!' || infix[i-1] == '('))
                    return 1;
                
                
                while (operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                
                operatorStack.pop();
                break;
            
            // Unary operator
            case '!':
                // ! can't be last element in string
                if (i == infix.size() - 1)
                    return 1;

                // ! behaves like (
                // Check char right before
                if (i > 0 && (infix[i-1] == 'T' || infix[i-1] == 'F' || infix[i-1] == ')'))
                    return 1;
                
                
                operatorStack.push(infix[i]);
                break;
                
            // Binary Operators
            case '&':
            case '^':
                // & or ^ can't be first or last element in string
                if (i == infix.size() - 1 || i == 0)
                    return 1;
                
                // Check char right before
                if (i > 0 && (infix[i-1] != 'T' && infix[i-1] != 'F' && infix[i-1] != ')'))
                    return 1;
                
                
                // Precedence, greatest to least: ! -> & -> ^      ASCII, greatest to least ^ -> & -> !
                while (!operatorStack.empty() && operatorStack.top() != '(' && infix[i] >= operatorStack.top()) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                
                operatorStack.push(infix[i]);
                break;
                
            // Any other charcater is invalid
            default:
                return 1;
                break;
        }
    }
    
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
//    // Print Infix
//    for (int i = 0; i < infix.size(); i++)
//        cerr << infix[i];
//    cerr << endl;
//
//    // Print Postfix
//    for (int i = 0; i < postfix.size(); i++)
//        cerr << postfix[i];
//    cerr << endl;
    
    
    // Evaluate Postfix //
    stack<char> operandStack;

    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] == 'T' || postfix[i] == 'F')
            operandStack.push(postfix[i]);

        // Negate the operand at top of stack
        else if (postfix[i] == '!') {
            char temp = operandStack.top();
            operandStack.pop();
            // Negate T
            if (temp == 'T')
                operandStack.push('F');
            // Negate F
            else
                operandStack.push('T');
        }
        
        else {
            char operand2 = operandStack.top();
            operandStack.pop();
            char operand1 = operandStack.top();
            operandStack.pop();
            
            switch(postfix[i])
            {
                case '&':
                    if (operand1 == 'T' && operand2 == 'T') {
                        char result = 'T';
                        operandStack.push(result);
                    }
                    else {
                        char result = 'F';
                        operandStack.push(result);
                    }
                    break;
                    
                case '^':
                    if ((operand1 == 'T' && operand2 == 'F') || (operand1 == 'F' && operand2 == 'T')) {
                        char result = 'T';
                        operandStack.push(result);
                    }
                    else {
                        char result = 'F';
                        operandStack.push(result);
                    }
                    break;
            }
        }
    }
    
    if (operandStack.size() != 1)
        return 1;
    
    if (operandStack.top() == 'T')
        result = true;
    // Otherwise the top is 'F'
    else
        result = false;
    
    return 0;
}




bool isValidParens(string infix)
{
    // Create a stack, where we push an open parens everytime we see it in the string
    stack<char> openParens;
    // Iterate through string
    for (int k = 0; k < infix.size(); k++) {
        char c = infix[k];
        switch (c)
        {
            // If we see an open parens, push it
            case '(':
                openParens.push(c);
                break;
                
            // If we see a closed parens, pop the stack
            case ')':
                if (openParens.empty())     // no matching open parens if stack is empty
                    return false;
               
                openParens.pop();
                break;
                
            default:
                break;
        }
    }
    // When we reach the end of string, stack is empty if there was matching close parens for every open parens
    return openParens.empty();
}

