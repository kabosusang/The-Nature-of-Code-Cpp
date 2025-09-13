#pragma once
#include "Walker.hpp"
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

struct Draw{
    void draw();
    void present();

public:
    static std::vector<std::string_view> nodes;
    static uint32_t index_;
    
    Walker walker_{};
    void selectNode();
};