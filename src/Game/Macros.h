//
// Created by tv on 03.11.23.
//

#pragma once

#define ENSURE_OFFSET(class, field, offset) static_assert(offsetof(class,field) == offset)

#define GVARBIND(name, addr, ...) using name ## _TYPE = __VA_ARGS__;\
inline name ## _TYPE & name = *( name ## _TYPE *)0x ## addr;
#define GVARBINDUNK(addr, type) VARBIND(DAT_ ## addr, addr, type)
#define FUNCBIND(name, addr, ...) using name ## _DEF = __VA_ARGS__; \
    const name ## _DEF name = (name ## _DEF) 0x ## addr;
#define FUNCBINDUNK(addr, signature) FUNCBIND(FUN_ ## addr,addr,signature)

#define ISINBOUNDS(addr) (0x10000000 < ((uint32_t) addr) && ((uint32_t) addr) < 0x48000000)

#define B(firstpart, secondpart) \
    "\n lis 13, " # firstpart             \
    "\n ori 13, 13, " # secondpart            \
    "\n mtctr 13"                         \
    "\n bctr \n"
