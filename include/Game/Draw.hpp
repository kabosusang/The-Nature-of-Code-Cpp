#pragma once
#include "Walker.hpp"

struct Draw{
    void draw();
    void present();

private:
    Walker walker_{};
};