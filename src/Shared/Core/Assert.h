//
// Created by tv on 08.10.23.
//

//From VLib

#pragma once

#include"Logging.h"
#include<csignal>

//From VLib

#ifdef NDEBUG
#define CAFEASSERT(...)
//[[assume(__VA_ARGS__)]];

#else
#define CAFEASSERT(...) CAFEINFO("Testing assumption: " #__VA_ARGS__)\
        {                 \
            if(!(__VA_ARGS__)){  \
                CAFECRASH((std::string("Assertion (" #__VA_ARGS__ ") failed on line ") + SRCLOC).c_str() );\
                std::raise(SIGINT);\
            }                 \
        }

#endif