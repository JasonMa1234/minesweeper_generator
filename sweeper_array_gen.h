#ifndef SWEEPER_ARRAY_GEN_H
#define SWEEPER_ARRAY_GEN_H

#include <vector>
#include <cstdint>
#include <memory>

class MineSweeperGenerator {
private:
    static constexpr std::uint8_t MASK_MINE_COUNT = 0x0F; // mask for number mines around, ex: int (a & MASK_MINE_COUNT): num mines around
    static constexpr std::uint8_t STATE_REVEALED = 0x10; // mask for whether block is revealed, ex: ((a & STATE_REVEALED) != 0): true if revealed
    static constexpr std::uint8_t STATE_FLAGGED  = 0x20; // mask for whether block is flagged, ex: int ((a & STATE_FLAGGED) != 0): true if flagged
    static constexpr std::uint8_t IS_MINE        = 9; // mask for whether block is mine, ex: int ((a & MASK_MINE_COUNT) == IS_MINE): true if is mine

    int height; 
    int width; 
    int totalMines;
    int firstRow;
    int firstColumn;

    void layMines(std::vector<std::uint8_t>& rawGrid);

public:
    MineSweeperGenerator(int h, int w, int mines, int firstY, int firstX);
    
    std::unique_ptr<std::vector<std::uint8_t>> generateBoard();
};

#endif