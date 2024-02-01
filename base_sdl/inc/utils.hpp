#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>

#define PRINT(x) std::cout << x << '\n'
#define ASSERT(x) if(!(x)) {PRINT("ERROR AT LINE: " << __LINE__ << "\nFILE: " __FILE__); *(int*)0=0;}

#endif //UTILS_HPP