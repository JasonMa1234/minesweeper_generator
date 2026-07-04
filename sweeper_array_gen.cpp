#include "sweeper_array_gen.h"
#include <iostream>
#include <random>
#include <algorithm>

MineSweeperGenerator::MineSweeperGenerator(int h, int w, int mines)
    : height(h), width(w), totalMines(mines) {}

void MineSweeperGenerator::layMines(std::vector<std::uint8_t>& rawGrid) {
    for (int i = 0; i < totalMines; i++) {
        rawGrid[i] = IS_MINE;
    }

    std::random_device rd;
    std:: mt19937 g(rd());
    std:: shuffle(rawGrid.begin(), rawGrid.end(), g);

    const int diffRow[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int diffColumn[] = {-1,  0,  1, -1, 1, -1, 0, 1}; 

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            int curIndex = row * width + column;
            if (rawGrid[curIndex] == IS_MINE) continue;

            int mineCount = 0;

            for (int i = 0; i < 8; i++) {
                int neighborRow = row + diffRow[i];
                int neighborColumn = column + diffColumn[i];

                if (neighborRow >= 0 && neighborRow < height && neighborColumn >= 0 && neighborColumn < width) {
                    int neighborIndex = neighborRow*width + neighborColumn;

                    if (rawGrid[neighborIndex] == IS_MINE) {
                        mineCount++;
                    }
                }
            } 

            rawGrid[curIndex] = mineCount;
        }
    }
}

std::unique_ptr<std::vector<std::uint8_t>> MineSweeperGenerator::generateBoard() {
    auto heapGrid = std::make_unique<std::vector<std::uint8_t>>(height * width, 0);

    layMines(*heapGrid);

    return heapGrid;
}