#pragma once

#include <vector>
#include <string>

// like `trait`
struct Printable {
    virtual void print() const noexcept = 0;
};
