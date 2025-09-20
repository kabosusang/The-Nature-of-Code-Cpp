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
    static uint32_t index_;
    const static std::vector<std::string_view> nodes_vector;
    const static std::vector<std::string_view> nodes_force;
    const static std::vector<std::string_view> angles_force;
public:
    Walker walker_{};
    Mover mover_{};
    void selectNode();
public:
    Vector mouse_{};
    bool mousePressed_{false};
    uint32_t frameCount_{};
};