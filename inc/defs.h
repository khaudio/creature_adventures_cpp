#if _DEBUG
#include <iostream>
#include <iomanip>
#endif

#ifndef DEBUG_OUT
#if _DEBUG
#define DEBUG_OUT(x) std::cout << x << '\n';
#else
#define DEUBG_OUT(x)
#endif
#endif

#ifndef DEBUG_ERR
#if _DEBUG
#define DEBUG_ERR(x) std::cerr << x << '\n';
#else
#define DEUBG_ERR(x)
#endif
#endif
