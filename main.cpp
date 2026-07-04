#include "sweeper_array_gen.h"
#include <iostream>
#include <iomanip> // For std::setw to properly format console grid layout

int main() {
    // Define game specifications (Standard Beginner Board: 9x9 with 10 mines)
    int height = 9;
    int width = 9;
    int mines = 10;

    std::cout << "Initializing MineSweeperGenerator (" << height << "x" << width << ", Mines: " << mines << ")..." << std::endl;
    MineSweeperGenerator generator(height, width, mines);

    std::cout << "Generating random board on the heap..." << std::endl;
    // Catch the returned heap-allocated vector using a unique_ptr
    std::unique_ptr<std::vector<std::uint8_t>> board = generator.generateBoard();

    std::cout << "\n--- Generated Underlying Board Grid (Validation Test) ---\n" << std::endl;
    
    // Constant definitions identical to the bitmasks for verification
    const std::uint8_t MASK_MINE_COUNT = 0x0F;
    const std::uint8_t IS_MINE = 9;

    // Outer and Inner loops to display the 1D vector like a 2D matrix
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            
            int index = r * width + c;
            
            // Isolate the core value from any hidden player action states using the bitwise AND
            std::uint8_t cellValue = (*board)[index] & MASK_MINE_COUNT;

            if (cellValue == IS_MINE) {
                std::cout << std::setw(3) << "*"; // Display mines as asterisks
            } 
            else if (cellValue == 0) {
                std::cout << std::setw(3) << "."; // Display empty zones cleanly as dots
            } 
            else {
                std::cout << std::setw(3) << (int)cellValue; // Explicit cast to int to print numeric text instead of ASCII char
            }
        }
        std::cout << std::endl; // Break line at the end of each matrix row
    }

    std::cout << "\n---------------------------------------------------------" << std::endl;
    std::cout << "Test completed successfully! Heap memory will now auto-deallocate." << std::endl;

    return 0;
}