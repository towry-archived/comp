#include <stack>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cctype>

// Check if char c is a operator
bool 
isOp(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
            break;
        default:
            return false;
            break;
    }
}

// check if op a is precedence than op b
// op: +, -, *, /
bool 
precedence(char a, char b) {
    if (a == '+' || a == '-') {
        if (b == '*' || b == '/') {
            return false;
        }
    }
    return true;
}


// conver a infix notation to postfix notation
std::string
postfix(std::string& infix) {
    std::stack<char> stack;	// used to store temp stuff
    std::string pf; 	// as a return
    stack.push('('); 	// push a left paren

    int i = 0, l = infix.size();
    for (; i < l; i++) {
        const char curr = infix[i];

        // if is a space, just ignore it.
        if (isspace(curr)) {
            continue;
        }

        else if ('(' == curr) {
            stack.push(curr);
        }

        // if is a digit, append it to postfix.
        else if (isdigit(curr)) {
            pf.push_back(curr);
        }

        // if is a op, check the precedence.
        else if (isOp(curr)) {
            while (!stack.empty() &&
                    isOp(stack.top()) &&
                    precedence(stack.top(), curr)) {
                // so suppose the expression is
                // 3+9-2, after append 3 to the postfix
                // we need push + onto the stack. when it comes
                // to -, we compare the precedence between + and
                // -.
                pf.push_back(stack.top());
                stack.pop();
            }
            // after the while loop, do not foget the curr.
            stack.push(curr);
        }

        else if (curr == ')') {
            while (!stack.empty() &&
                    '(' != stack.top()) {
                pf.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                throw std::runtime_error("missing paren");
            }
            stack.pop();
        }

        else {
            std::stringstream s_error;
            s_error << "invalid input: " << curr;
            throw std::runtime_error(s_error.str());
        }
    }

    while (!stack.empty() &&
            '(' != stack.top()) {
        pf.push_back(stack.top());
        stack.pop();
    }
    if (stack.empty()) {
        throw std::runtime_error("missing paren");
    }
    stack.pop();

    while (!stack.empty()) {
        pf.push_back(stack.top());
        stack.pop();
    }

    return pf;
}

int
main() {
    std::string s;
    std::cout << "Please input a string:" << "\n";
    std::getline(std::cin, s);
    std::string pf;
    pf = postfix(s);
    std::cout << pf << "\n";
    return(0);
}
