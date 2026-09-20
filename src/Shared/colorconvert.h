//
// Created by tv on 18.11.23.
//

#pragma once

#include<glm/vec4.hpp>
#include<cmath>
//Calculation to shift up the sine wave to be between 1 and 0
#define SINESHIFTCALC * 0.5f + 0.5f
// a value of 1 makes it washed out
#define SINEEXPONENT 2.0f

inline glm::vec4 hsva2rgba(glm::vec4 hsva) {
    glm::vec4 rgba = {1, 1, 1, hsva.a};
    float hue = hsva[0] * M_PI * 2;


    rgba.r = powf(cosf(hue) SINESHIFTCALC, SINEEXPONENT);
    rgba.g = powf(cosf(hue + (float) M_PI / 0.75f) SINESHIFTCALC, SINEEXPONENT);
    rgba.b = powf(cosf(hue + ((float) M_PI / 0.75f) * 2) SINESHIFTCALC, SINEEXPONENT);

    return rgba;
}