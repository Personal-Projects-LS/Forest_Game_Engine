#pragma once

#include <iostream>

class stb_PointerContainer {
private:
    unsigned char *const data = nullptr;

public:
    stb_PointerContainer(const stb_PointerContainer&) = delete;
    stb_PointerContainer& operator=(const stb_PointerContainer&) = delete;

    explicit stb_PointerContainer(unsigned char *image) noexcept;

    [[nodiscard]] const unsigned char *getData() const noexcept;

    ~stb_PointerContainer();
};
