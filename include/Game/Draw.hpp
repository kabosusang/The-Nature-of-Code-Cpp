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
    void draw(float deltaTime);
    void present();
    void pollevent(SDL_Event& event);
public:
    static uint32_t index_;
    const static std::vector<std::string_view> nodes_vector;
    const static std::vector<std::string_view> nodes_force;
    const static std::vector<std::string_view> nodes_angle;
    const static std::vector<std::string_view> nodes_partivle;
    const static std::vector<std::string_view> nodes_box2d;
    const static std::vector<std::string_view> nodes_vehicle;
    const static std::vector<std::string_view> nodes_automata;



    public:
    Walker walker_{};
    Mover mover_{};
    void selectNode(float deltaTime);
public:
    Vector mouse_{};
    bool mousePressed_{false};
    bool blankPressed_{false};
    bool mouseClick_{false};
    uint64_t frameCount_{};
};