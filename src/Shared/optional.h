//
// Created by tv on 03.11.23.
//

#pragma once

struct nullopt_t {
};

inline const nullopt_t nullopt = {};

template<typename t>
class optional {
public:
    optional(t val) : m_valid(true), m_value(val) {}

    optional() : m_valid(false), m_value() {}

    operator t() {
        return m_value;
    }

    operator bool() {
        return m_valid;
    }

    bool m_valid;

    t m_value;


};