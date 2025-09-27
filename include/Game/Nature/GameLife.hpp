#pragma once

#include "Tools/Color.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"
#include "imgui.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <span>
#include <string>
#include <vector>
#include <random>

class GameOfLife {
public:
    std::vector<std::vector<int>> grid;
    int cellSize = 8;  // 减小细胞大小，确保可见
    int width = 0;
    int height = 0;
    bool isRunning = true;  // 默认运行
    int generation = 0;

    GameOfLife() {
        resizeGrid();
        randomize(0.3f);  // 默认随机化
    }

    void resizeGrid() {
        auto& canvas = Canvas::getInstance();
        width = canvas.GetWindowW() / cellSize;
        height = canvas.GetWindowH() / cellSize;
        
        grid.resize(height, std::vector<int>(width, 0));
        generation = 0;
        
    }

    void randomize(float aliveProbability = 0.3f) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x] = dis(gen) < aliveProbability ? 1 : 0;
            }
        }
        generation = 0;
    }

    void clear() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x] = 0;
            }
        }
        generation = 0;
    }

    void generate() {
        if (!isRunning || width == 0 || height == 0) return;

        std::vector<std::vector<int>> nextGrid = grid;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int neighbors = countNeighbors(x, y);
                
                if (grid[y][x] == 1) {
                    nextGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    nextGrid[y][x] = (neighbors == 3) ? 1 : 0;
                }
            }
        }
        
        grid = nextGrid;
        generation++;
    }

    int countNeighbors(int x, int y) {
        int count = 0;
        
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                
                int nx = (x + dx + width) % width;
                int ny = (y + dy + height) % height;
                
                count += grid[ny][nx];
            }
        }
        return count;
    }

    void display() {
        auto& painter = Painter::getInstance();
        auto& canvas = Canvas::getInstance();
        
        // 先绘制背景
        painter.DrawRect(0, 0, canvas.GetWindowW(), canvas.GetWindowH(), White);
        
        // 绘制细胞
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == 1) {
                    painter.DrawRect(x * cellSize, y * cellSize, cellSize, cellSize, Black);
                }
        
            }
        }
        
        // 绘制网格线（可选，帮助调试）
        // painter.SetColor(Gray);
        // for (int x = 0; x <= width; x++) {
        //     painter.DrawLine(x * cellSize, 0, x * cellSize, height * cellSize);
        // }
        // for (int y = 0; y <= height; y++) {
        //     painter.DrawLine(0, y * cellSize, width * cellSize, y * cellSize);
        // }
    }

    void handleMouse(int mouseX, int mouseY, bool mousePressed, bool erase = false) {
        if (!mousePressed) return;
        
        int cellX = mouseX / cellSize;
        int cellY = mouseY / cellSize;
        
        if (cellX >= 0 && cellX < width && cellY >= 0 && cellY < height) {
            grid[cellY][cellX] = erase ? 0 : 1;
        }
    }

    void printGridState() {
        int aliveCount = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                aliveCount += grid[y][x];
            }
        }
    }

    static void drawControls(GameOfLife& gol) {
        ImGui::Begin("Game of Life Controls");
        
        ImGui::Text("Status: %s", gol.isRunning ? "Running" : "Paused");
        ImGui::Text("Generation: %d", gol.generation);
        ImGui::Text("Grid: %d x %d", gol.width, gol.height);
        
        if (ImGui::Button(gol.isRunning ? "Pause" : "Run")) {
            gol.isRunning = !gol.isRunning;
        }
        ImGui::SameLine();
        if (ImGui::Button("Step")) {
            gol.generate();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            gol.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Randomize")) {
            gol.randomize(0.3f);
        }
        
        static float probability = 0.3f;
        if (ImGui::SliderFloat("Alive Probability", &probability, 0.1f, 0.5f)) {
            gol.randomize(probability);
        }
        
        if (ImGui::Button("Print Debug Info")) {
            gol.printGridState();
        }
        
        ImGui::End();
    }
};