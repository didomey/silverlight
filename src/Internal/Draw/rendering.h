#pragma once

#include<gx2/shaders.h>
#include <whb/gfx.h>
#include<string>
#include<Game/DebugTextRenderer.h>

class Renderer {
public:
    Renderer();

    void updateVars(DebugTextRenderer *textRenderer);

    void setTextScale(float size);

    void setTextCursor(glm::vec2 position);

    void drawText(const std::string &text, glm::vec4 color = {1, 1, 1, 1}, unsigned int number = 0);

    void drawTextRainbow(const std::string &text);

    float m_rainbowTimer = 0;


private:
    DebugTextRenderer *m_textRenderer;
};
