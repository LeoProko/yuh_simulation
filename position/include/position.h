#pragma once

struct Position {
    int x;
    int y;
    
    Position() = delete;

    Position(int first, int second);

    Position(const Position& other) = default;
};
