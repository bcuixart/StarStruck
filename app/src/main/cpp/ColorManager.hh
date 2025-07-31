#ifndef COLORMANAGER_HH
#define COLORMANAGER_HH

#include <iostream>

#include <raymob.h>
#include <raymath.h>

#define BACKGROUND_PALETTES 21
#define ROCKET_PALETTES 2

class ColorManager {
public:
    ColorManager();

    void NextPalette();

    Color GetRocketBaseColor() const;
    Color GetRocketTopColor() const;
    Color GetRocketWindowColor() const;
    Color GetRocketPropeller000Color() const;
    Color GetRocketPropeller001Color() const;
    Color GetRocketPropeller002Color() const;

    Color GetRocketFireColor() const;

    Color GetBackgroundColor() const;
    Color GetCoinColor() const;

    Color GetBGStarColor() const;
    Color GetAsteroid000Color() const;
    Color GetAsteroid001Color() const;

private:

    const Color COLORS_ROCKET[ROCKET_PALETTES] = {
            {213, 167, 247, 255 },
            {189, 129, 237, 255 },
    };

    const Color COLORS_FIRE[ROCKET_PALETTES] = {
            {229, 197, 247, 255},
            {229, 197, 247, 255},
    };

    const Color COLORS_BACKGROUND[BACKGROUND_PALETTES] = {
            {133, 60, 217, 255},
            {55,69,109,255},
            {18,52,95,255},
            {0,63,102,255},
            {22,86,102,255},
            {55,100,102,255},
            {22,97,81,255},
            {37,102,54,255},
            {34,102,27,255},
            {66,102,19,255},
            {88,102,27,255},
            {102,98,13,255},
            {102,83,12,255},
            {102,56,0,255},
            {102,41,0,255},
            {102,27,0,255},
            {102,7,0,255},
            {102,0,51,255},
            {125,43,115,255},
            {99,0,102,255},
            {38,38,38,255},
    };

    const Color COLORS_COIN[BACKGROUND_PALETTES] = {
            {236,176,246,255},
            {129,162,240,255},
            {120,183,240,255},
            {0,147,239,255},
            {53,204,240,255},
            {130,237,240,255},
            {46,240,198,255},
            {46,240,97,255},
            {81,240,63,255},
            {156,240,46,255},
            {206,239,61,255},
            {246,248,0,255},
            {240,194,28,255},
            {240,133,0,255},
            {239,96,0,255},
            {240,63,0,255},
            {239,17,0,255},
            {239,0,119,255},
            {240,102,226,255},
            {232,0,240,255},
            {242,242,242,255},
    };

    const Color COLORS_BGSTARS[BACKGROUND_PALETTES] = {
            {229, 197, 247, 255},
            {106,134,197,255},
            {44,125,231,255},
            {44,125,231,255},
            {43,166,197,255},
            {106,194,197,255},
            {37,197,163,255},
            {37,197,80,255},
            {128,197,37,255},
            {128,197,37,255},
            {170,197,51,255},
            {197,189,37,255},
            {197,160,24,255},
            {197,108,0,255},
            {197,79,0,255},
            {197,53,0,255},
            {197,13,0,255},
            {197,0,99,255},
            {197,85,186,255},
            {191,0,197,255},
            {127,127,127,255},
    };

    const Color COLORS_ASTEROID_000[BACKGROUND_PALETTES] = {
            {190, 130, 237, 255},
            {88,111,163,255},
            {31,88,163,255},
            {0,101,163,255},
            {36,138,163,255},
            {88,161,163,255},
            {31,163,135,255},
            {31,163,66,255},
            {55,163,42,255},
            {106,163,31,255},
            {141,163,42,255},
            {163,157,31,255},
            {163,132,20,255},
            {163,90,0,255},
            {163,55,0,255},
            {163,44,0,255},
            {163,11,0,255},
            {163,0,82,255},
            {163,70,154,255},
            {158,0,163,255},
            {127,127,127,255},
    };

    const Color COLORS_ASTEROID_001[BACKGROUND_PALETTES] = {
            {150, 76, 225, 255},
            {72,90,133,255},
            {25,70,129,255},
            {0,82,133,255},
            {29,112,133,255},
            {72,131,133,255},
            {25,129,107,255},
            {25,133,54,255},
            {44,133,34,255},
            {95,133,45,255},
            {115,133,34,255},
            {133,127,25,255},
            {133,107,16,255},
            {133,73,0,255},
            {133,53,0,255},
            {133,35,0,255},
            {133,9,0,255},
            {133,0,66,255},
            {133,57,125,255},
            {128,0,133,255},
            {89,89,89,255},
    };

    int colorSelectedRocketBase = 0;
    int colorSelectedRocketTop = 1;
    int colorSelectedRocketWindow = 1;
    int colorSelectedRocketPropeller000 = 1;
    int colorSelectedRocketPropeller001 = 1;
    int colorSelectedRocketPropeller002 = 1;
    int colorSelectedRocketFire = 1;

    int colorSelectedBackground = 0;
    int colorSelectedCoin = 0;
    int colorSelectedAsteroid = 0;

};


#endif
