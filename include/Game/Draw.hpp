#pragma once
#include "Game/Utils/Vector.hpp"
#include "Walker.hpp"
#include "Mover.hpp"

#include <cstdarg>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

struct Draw{
    void draw();
    void present();
    void pollevent(SDL_Event& event);
public:
    static std::vector<std::string_view> nodes;
    static uint32_t index_;

    Walker walker_{};
    Mover mover_{};

    void selectNode();
    Vector mouse_{};
};