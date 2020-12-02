#include "rpnm.h"
int main(int argc, char* argv[]) {
    std::string exp = "";    
    if (argc == 2) exp = argv[1];
    else {
        std::cout << "wrtie a math expression: ";
        getline(std::cin, exp);
    }
    exp = rpn(exp);
    //std:: cout << exp << '\n';
    std::cout << "answer is = "<< calculations(exp) << '\n';
    return 0;
}