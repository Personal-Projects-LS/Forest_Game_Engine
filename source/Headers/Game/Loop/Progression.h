#pragma once

static int progress;
static bool won;

class Progression {
public:
    static void start() {
        progress = 0;
        won = false;
    }

    static void advance() {
        progress += 1;
    }

    static int getProgress() {
        return progress;
    }

    static void hasWon() {
        won = true;
    }

    static bool getWon() {
        return won;
    }
};


