//
// Created by Steven on 10/7/2017.
//

#ifndef SHORTESTPATHPROBLEM_CIRCLE_H
#define SHORTESTPATHPROBLEM_CIRCLE_H

#include <SDL2/SDL_render.h>

typedef struct SDL_Circ {
    int x, y;
    int r;
} SDL_Circ;

void SDL_RenderDrawCircle(SDL_Renderer *renderer, SDL_Circ circ);


#endif //SHORTESTPATHPROBLEM_CIRCLE_H
