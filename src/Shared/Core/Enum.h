//
// Created by tv on 08.10.23.
//

//From VLib

#pragma once

#include<string>
#include"cpplib.h"

#define ENUMNAMECASE(enumname, casename) \
    enumname :: casename,

#define ENUMCASERETURN(enumname, casename) \
    case(enumname :: casename):     \
        return #casename;

//NO enum class because iu
#define CAFEENUM(name, ...) \
    enum class name{    \
        __VA_ARGS__\
    };                   \
    static name all##name[] = { \
        CPP_FOREACH(ENUMNAMECASE,name,__VA_ARGS__)                  \
    };                     \
    \
    inline const char* toString(name enumopt){ \
        switch(enumopt){ \
            CPP_FOREACH(ENUMCASERETURN,name,__VA_ARGS__) \
            default:     \
                return "Invalid";\
        }                     \
    }
