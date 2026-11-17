//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


/**
 * The Rogue 20 Project
 * (C) 2026 Alessio Saltarin
 *
 * This software is licensed unser ISC
 * (see LICENSE)
 */

#pragma once

namespace rogue20 {

class Camera {
public:
    void update(float targetX, float targetY, float targetSize);

    float x() const { return x_; }
    float y() const { return y_; }

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
};

}  // namespace rogue20
