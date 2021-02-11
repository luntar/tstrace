/*!
 * \file TestThings.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 * 
 * This file can be included an any C++
 * implementation file.  It uses the iostream
 * to print to stdout.
 * 
 * This file contains testing macros
 * 
 */

#ifndef _TESTTHINGS_H
#define _TESTTHINGS_H
#include <iostream>

#define CHECK_TRUE(S)        \
    if ((S) != true)         \
    {                        \
        std::cout << "FAIL"; \
        exit (-1);           \
    }                        \
    (void) 0
    
#define CHECK_FALSE(S)       \
    if ((S) != false)        \
    {                        \
        std::cout << "FAIL"; \
        exit (-1);           \
    }                        \
    (void) 0

#endif // _TESTTHINGS_H 