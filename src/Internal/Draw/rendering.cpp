#include"rendering.h"
#include "Shared/Core/Logging.h"
#include "Game/Filetypes/Sarc.h"
#include "Shared/colorconvert.h"
#include<gx2/shaders.h>
#include<gx2/draw.h>
#include<coreinit/filesystem.h>
#include<fmt/core.h>
#include<glm/vec4.hpp>
#include<glm/vec2.hpp>
#include<glm/gtx/string_cast.hpp>
#include<unordered_map>


typedef void (*TextRenderFunc)(DebugTextRenderer *unk1, const char *text, unsigned int unk2);

static TextRenderFunc renderText = (TextRenderFunc) 0x028cc450;

Renderer::Renderer() {
}

void Renderer::updateVars(DebugTextRenderer *textRenderer) {
    m_textRenderer = textRenderer;

    m_textRenderer->m_textCursor.x = -625;
    m_textRenderer->m_textCursor.y = 350;

    m_rainbowTimer += 0.3333 / 60;

    if (m_rainbowTimer > 1)
        m_rainbowTimer -= 1;
}

void Renderer::drawText(const std::string &text, glm::vec4 color, unsigned int number) {
    //TODO: implement text rendering

    m_textRenderer->m_color = color;

    renderText(m_textRenderer, text.c_str(), number);
}

void Renderer::setTextCursor(glm::vec2 position) {
    m_textRenderer->m_textCursor = position;
}

void Renderer::setTextScale(float size) {
    m_textRenderer->m_textSize = glm::vec2{1.2f, 1.0f} * size;
}

static const std::unordered_map<Log::LogSeverity, glm::vec3> colorBySeverity = {
        {Log::LogSeverity::Info,    {1,   1,    1}},
        {Log::LogSeverity::Error,   {1,   0.25, 0.25}},
        {Log::LogSeverity::Verbose, {0.5, 0.5,  0.5}},
        {Log::LogSeverity::Crash,   {1,   0,    0}},
        {Log::LogSeverity::Warning, {0.9, 0.9,  0}}
};

void Renderer::drawTextRainbow(const std::string &text) {
    glm::vec2 beginCursor = m_textRenderer->m_textCursor;

    unsigned int newlines = 0;

    float coloroffset = 0;

    for (char c: text) {
        if (c == '\n') {
            setTextCursor(beginCursor);
            for (unsigned i = 0; i < newlines; i++)
                drawText("\n");

            newlines++;
        }

        float colorhue = m_rainbowTimer + coloroffset;
        while (colorhue > 1)
            colorhue -= 1;

        auto otherrainbow = hsva2rgba({colorhue, 1, 1, 1});

        drawText(std::string({c}), otherrainbow);

        coloroffset += 0.025f;
    }
}
