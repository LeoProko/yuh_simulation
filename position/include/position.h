#pragma once

struct Position {
    int x;
    int y;
    
    Position() = delete;

    Position(int first, int second);

    friend bool operator<(const Position& first, const Position& second);

    friend bool operator==(const Position& first, const Position& second);
};
