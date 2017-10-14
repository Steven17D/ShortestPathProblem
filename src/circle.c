//
// Created by Steven on 10/7/2017.
//

#include <windef.h>
#include <math.h>
#include "circle.h"

void SDL_RenderDrawCircle(SDL_Renderer *renderer, SDL_Circ circ) {
    int x, y;
    for (x = max(circ.x - circ.r, 0); x < circ.x + circ.r; ++x) {
        for (y = max(circ.y - circ.r, 0); y < circ.y + circ.r; ++y) {
            if (sqrt(pow(x - circ.x, 2) + pow(y - circ.y, 2)) <= circ.r)
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}
