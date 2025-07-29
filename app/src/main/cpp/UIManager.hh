#ifndef UIMANAGER_HH
#define UIMANAGER_HH

#include <raymob.h>
#include <raymath.h>

using namespace std;

class UIManager {
public:
    UIManager();

    void Render(const int screenWidth, const int screenHeight, const float deltaTime);

protected:

private:
    void Render_MainMenu(const int screenWidth, const int screenHeight, const float deltaTime);
    void Render_Playing(const int screenWidth, const int screenHeight, const float deltaTime);
    void Render_PlayerDead(const int screenWidth, const int screenHeight, const float deltaTime);
};

#endif