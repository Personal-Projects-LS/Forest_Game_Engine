#pragma once

static int progress;

class Progression {
public:
    static void start() {
        progress = 0;
    }

    static void advance() {
        progress += 1;
    }

    static int getProgress() {
        return progress;
    }
};


