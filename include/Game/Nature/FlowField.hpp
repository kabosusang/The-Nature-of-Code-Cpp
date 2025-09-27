#pragma once

#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

class FlowField {
private:
	std::vector<Vector> field;
	size_t cols, rows; //行 列
	int resolution;
public:	
	FlowField(){
		auto& canvas = Canvas::getInstance();
		resolution = 10;
		cols = canvas.GetWindowW() / resolution;
		rows = canvas.GetWindowH() / resolution;
		field.resize(cols * rows);

		for (auto& vec : field) {
            vec = Vector(Random{0,1}, 0);  // 或者设置默认值
        }
	}

	Vector& at(size_t x, size_t y) { 
        return field[y * cols + x]; 
    }
    
    const Vector& at(size_t x, size_t y) const { 
        return field[y * cols + x]; 
    }

	Vector lookup(Vector lookup){
		int column = std::clamp(static_cast<int>(lookup.x/resolution),0,(int)cols-1);
		int row = std::clamp(static_cast<int>(lookup.y/resolution),0,(int)rows-1);
		return at(column,row);
	}
    
};