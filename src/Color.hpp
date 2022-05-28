#pragma once

#include <stdint.h>
#include <algorithm>

class Color
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a = 255;

    template<typename numberT>
    Color operator *(const numberT factor)
    {
        return Color
        {
            static_cast<uint8_t>(std::min(this->r*factor,255.0)),
            static_cast<uint8_t>(std::min(this->g*factor,255.0)),
            static_cast<uint8_t>(std::min(this->b*factor,255.0))
        };
    }

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
    static const Color Transparent;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Magenta;

};

