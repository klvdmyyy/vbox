// -*- mode: c++; -*-
#pragma once

#include "Core/Types.h"
#include "Core/IO/Writer.h"

#include "GUI/Window.h"

#include <vector>

namespace ERUNTIME_NAMESPACE::GUI {    
    class ConsoleWindow : public Window {
    public:
        ConsoleWindow();

        void Draw() final
        {
            DrawOutput();
            DrawInput();
        }
        
        int InputCallback(void* data_);

    private:
        void DrawOutput();
        void DrawInput();

        IO::Writer& m_writer;

        String m_inputBuffer{};
        std::vector<String> m_history;
        Int32 m_historyIndex = 0;
        bool m_autoScroll = true;
    };
}