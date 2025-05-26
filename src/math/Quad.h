//
// Created by Daniel Laplana Gimeno on 19/1/25.
//

#ifndef AURAGL_QUAD_H
#define AURAGL_QUAD_H

/**
 * Class that define a Quad that act as an square.
 * This square is defined by its x and y positions
 */
struct Quad {
public:
    int x;
    int y;

    inline explicit Quad(int x = 1920, int y = 1080){
        this->x = x;
        this->y = y;
    }
};

#endif //AURAGL_QUAD_H
