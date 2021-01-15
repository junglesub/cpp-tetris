#include <iostream>

int main(){
    int a = 20;
    int & b = a;
    int & c = b;
    // int a = 20;
    // int * b = &a;

    std::cout << b << c;

    return 0;
}