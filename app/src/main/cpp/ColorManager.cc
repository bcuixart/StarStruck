#include "ColorManager.hh"

ColorManager::ColorManager()
{

}

void ColorManager::NextPalette()
{
    colorSelectedBackground = (colorSelectedBackground + 1) % BACKGROUND_PALETTES;
    colorSelectedCoin = (colorSelectedCoin + 1) % BACKGROUND_PALETTES;
    colorSelectedAsteroid = (colorSelectedAsteroid + 1) % BACKGROUND_PALETTES;
}

Color ColorManager::GetRocketBaseColor() const
{
    return COLORS_ROCKET[colorSelectedRocketBase];
}

Color ColorManager::GetRocketTopColor() const
{
    return COLORS_ROCKET[colorSelectedRocketTop];
}

Color ColorManager::GetRocketWindowColor() const
{
    return COLORS_ROCKET[colorSelectedRocketWindow];
}

Color ColorManager::GetRocketPropeller000Color() const
{
    return COLORS_ROCKET[colorSelectedRocketPropeller000];
}

Color ColorManager::GetRocketPropeller001Color() const
{
    return COLORS_ROCKET[colorSelectedRocketPropeller001];
}

Color ColorManager::GetRocketPropeller002Color() const
{
    return COLORS_ROCKET[colorSelectedRocketPropeller002];
}

Color ColorManager::GetRocketFireColor() const
{
    return COLORS_FIRE[colorSelectedRocketFire];
}

Color ColorManager::GetBackgroundColor() const
{
    return COLORS_BACKGROUND[colorSelectedBackground];
}

Color ColorManager::GetCoinColor() const
{
    return COLORS_COIN[colorSelectedCoin];
}

Color ColorManager::GetBGStarColor() const
{
    return COLORS_BGSTARS[colorSelectedBackground];
}

Color ColorManager::GetAsteroid000Color() const
{
    return COLORS_ASTEROID_000[colorSelectedAsteroid];
}

Color ColorManager::GetAsteroid001Color() const
{
    return COLORS_ASTEROID_001[colorSelectedAsteroid];
}
