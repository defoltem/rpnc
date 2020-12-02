#include <iostream>
#include <vector>
#include <string>
#include <math.h>

const std::string nums = "0123456789"; // list of numbers

int prior(const char &c){ // find out a priority
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else if (c == '(') return 4;
    else if (c == ')') return 5;
    else return -1;
}
int calculations(std::string &str){ 
    std::vector<int> numbers;
    std::string buff = "";
    int per, p1, p2, res;
    for (size_t i = 0; i < str.size(); i++){
    if(nums.find(str.at(i)) != std::string::npos) { // if number...
        buff += str.at(i);
    }
    else if (str.at(i) == '|') {
        per = std::stoi(buff);
        buff = "";
        numbers.push_back(per);
    }  
    else {
        p1 = numbers.back();
        numbers.pop_back();
        p2 = numbers.back();
        numbers.pop_back();
        switch (str.at(i)) // determining future actions
        {
        case '+':
            res = p1 + p2;
            numbers.push_back(res);
            break;
        case '-':
            res = p2 - p1;
            numbers.push_back(res);
            break;
        case '*':
            res = p1 * p2;
            numbers.push_back(res);
            break;
        case '/': 
            res = p2 / p1;
            numbers.push_back(res);
            break;
        case '^':
            res = pow(p2, p1);
            numbers.push_back(res);
            break;
        default:
            break;
            }
        }
    }
    return res;
}
std::string rpn(const std::string &str){
    std::string conv = "";
    std::string buff = "";
    std::vector<char> symbols;
    for (const char c:str){
        if (nums.find(c) != std::string::npos) buff += c;
        else if (symbols.empty()) { 
            if (!buff.empty()) { 
                conv += buff + "|";
                buff = "";
            }
            symbols.push_back(c);
        }
        else if(prior(c) == 5){
            if (!buff.empty()) {
                conv += buff + "|";
                buff = "";
            }
            while(prior(symbols.back()) != 4){
            conv += symbols.back();
            symbols.pop_back();
            }
        }
        else if (prior(c) > prior(symbols.back())) { 
            if (!buff.empty()) { 
                conv += buff + "|";
                buff = "";
            }
            symbols.push_back(c);
        }
        else if (prior(c) <= prior(symbols.back())) {
            if (!buff.empty()) {
                conv += buff + "|";
                buff = "";
            }
            if (symbols.back() == '(') {
                symbols.push_back(c);
                continue; 
            }
            conv += symbols.back();
            symbols.pop_back();
            symbols.push_back(c);
        }
        else if (prior(c) == -1) {
            std::cout << "error\n";
            exit(0);
        }
    }
    if (!buff.empty()) conv += buff + "|";
    while(!symbols.empty()){
        if (symbols.back() == '(') { 
            symbols.pop_back();
            continue;
        }
        conv += symbols.back();
        symbols.pop_back();
    }
    return conv;
}