#pragma once
#include "Vector.hpp"
#include "base/Painter.hpp"


#include <array>
#include <cmath>
#include <stack>

#define PI 3.14159
#define TWO_PI 2 * PI

constexpr float radians(float f) {
	return TWO_PI * (f / 360);
}
 
constexpr float degrees(float radians) {
	return radians * (180.0f / PI);
}

inline float atan(float x,float y){
    return std::atan2(x,y);
}

inline Vector PolatoCorrd(float r,float theta){
    return {r * std::cos(theta),r * std::sin(theta)};
}


class ProcessingStyleTransform {
private:
    using Matrix3x3 = std::array<std::array<float, 3>, 3>;
    
    Matrix3x3 currentMatrix;
    std::stack<Matrix3x3> matrixStack;

    static constexpr Matrix3x3 identityMatrix() {
        return {{
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }};
    }

    static Matrix3x3 createRotationMatrix(float angle) {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return {{
            {cosA, -sinA, 0.0f},
            {sinA,  cosA, 0.0f},
            {0.0f,  0.0f, 1.0f}
        }};
    }

    static Matrix3x3 createTranslationMatrix(float tx, float ty) {
        return {{
            {1.0f, 0.0f, tx},
            {0.0f, 1.0f, ty},
            {0.0f, 0.0f, 1.0f}
        }};
    }

    static Matrix3x3 multiplyMatrices(const Matrix3x3& a, const Matrix3x3& b) {
        Matrix3x3 result = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

public:
    ProcessingStyleTransform() : currentMatrix(identityMatrix()) {}

    void resetMatrix() {
        currentMatrix = identityMatrix();
    }

    void rotate(float angle) {
        currentMatrix = multiplyMatrices(currentMatrix, createRotationMatrix(angle));
    }

    void translate(float tx, float ty) {
        currentMatrix = multiplyMatrices(currentMatrix, createTranslationMatrix(tx, ty));
    }

    void pushMatrix() {
        matrixStack.push(currentMatrix);
    }

    void popMatrix() {
        if (!matrixStack.empty()) {
            currentMatrix = matrixStack.top();
            matrixStack.pop();
        }
    }

    void transformPoint(float& x, float& y) const {
        float newX = currentMatrix[0][0] * x + currentMatrix[0][1] * y + currentMatrix[0][2];
        float newY = currentMatrix[1][0] * x + currentMatrix[1][1] * y + currentMatrix[1][2];
        x = newX;
        y = newY;
    }
};


inline ProcessingStyleTransform g_transform;

inline void drawLine(float x1, float y1, float x2, float y2) {
    g_transform.transformPoint(x1, y1);
    g_transform.transformPoint(x2, y2);
    auto& painter = Painter::getInstance();
    painter.DrawLine({x1,y1}, {x2,y2},White);
}

inline void drawEllipse(float x, float y, float width, float height) {
    float centerX = x;
    float centerY = y;
    g_transform.transformPoint(centerX, centerY);
    auto& painter = Painter::getInstance();
    painter.DrawCircle(centerX, centerY, 16);
}




