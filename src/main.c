#include <stdio.h>
#include <SDL2/SDL.h>
#include <afxres.h>
#include <time.h>
#include "graph.h"
#include "circle.h"
#include "file_utils.h"
#include "depth_first_search.h"


BOOL Draw(short world_map[MAX_DIMENSION][MAX_DIMENSION], Stack_PNode* pNode);

void DrawBackground(SDL_Renderer *renderer, short world_map[MAX_DIMENSION][MAX_DIMENSION], Stack_PNode* pNode);

int main(int argc, char* argv[]) {
    char file_name[MAX_PATH] = { '\0' };
    short int world_map[MAX_DIMENSION][MAX_DIMENSION];

    if (!GetWorldMapFileName(argc, argv, file_name)) {
        printf("Failed to open dialog.(0x%x)\n", (unsigned int) CommDlgExtendedError());
        goto exit;
    }

    printf("Opening %s\n", file_name);
    FILE *world_map_file;
    world_map_file = fopen(file_name, "r");
    if (!InitWorldMap(world_map_file, world_map)) {
        goto exit;
    }
    fclose(world_map_file);

    Graph* graph = Graph_Create(world_map);
    Stack_PNode* result = NULL;
    DepthFirstSearch(graph, &result);
    Draw(world_map, result);
    Graph_Destroy(graph);

    exit:
    return 0;
}

BOOL Draw(short world_map[MAX_DIMENSION][MAX_DIMENSION], Stack_PNode* shortest_path) {
    SDL_Window* window = SDL_CreateWindow(
            "World Map",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Setup renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Set render color (background will be rendered in this color)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Clear window
    SDL_RenderClear(renderer);
    // Draw map background
    DrawBackground(renderer, world_map, shortest_path);

    SDL_Event event;
    int SDL_alive = TRUE;
    USHORT fsp = 24;
    ULONG start_time;
    while (SDL_alive) {
        //Init for fps control
        start_time = (ULONG)time(NULL);

        //Events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
                SDL_alive = FALSE;
            }
        }

        //Logic
        // TODO: create generator or thread based logic

        //Rendering
        SDL_RenderPresent(renderer);

        //Delay for fps control
        Sleep((1000 / fsp) - (time(NULL) - start_time));
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void DrawBackground(SDL_Renderer *renderer, short world_map[MAX_DIMENSION][MAX_DIMENSION], Stack_PNode* shortest_path) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

    double padding_coefficient = (double) 0.1;  // + 0.1 is for 10% padding at the end
    double cell_width = window_width / ((double)MAX_DIMENSION + padding_coefficient),
            cell_height = window_height / ((double)MAX_DIMENSION + padding_coefficient);

    double height_padding = cell_height * padding_coefficient,
            width_padding = cell_width * padding_coefficient;

    int cell_body_width = (int) (cell_width * (1 - padding_coefficient)),
            cell_body_height = (int) (cell_height * (1 - padding_coefficient));

    SDL_Rect r;
    int x, y;
    for (x = 0; x < MAX_DIMENSION; ++x) {
        for (y = 0; y < MAX_DIMENSION; ++y) {
            r.x = (int) (width_padding + (cell_width * x));
            r.y = (int) (height_padding + (cell_height * y));
            r.w = cell_body_width;
            r.h = cell_body_height;

            // Set render color to blue ( rect will be rendered in this color )
            unsigned char color = (unsigned char) (255 * ((999 - (double)world_map[x][y]) / 999));
            SDL_SetRenderDrawColor(renderer, color, color, color, 255 );
            // Render rect
            SDL_RenderFillRect(renderer, &r);
        }
    }

    printf("Shortest path: %d", Stack_Size_PNode(shortest_path));
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
    UINT i; for (i = 0; i < (Stack_Size_PNode(shortest_path) - 1); ++i) {
        POINT p1, p2;
        p1.x = Stack_PeekAt_PNode(shortest_path, i)->position.x;
        p1.y = Stack_PeekAt_PNode(shortest_path, i)->position.y;
        p2.x = Stack_PeekAt_PNode(shortest_path, i+1)->position.x;
        p2.y = Stack_PeekAt_PNode(shortest_path, i+1)->position.y;

        SDL_RenderDrawLine(renderer,
//        printf("(%d,%d)->(%d,%d)\n",
                           (int) (width_padding + (cell_width * p1.x) + cell_body_width/2),
                           (int) (height_padding + (cell_height * p1.y) + cell_body_height/2),
                           (int) (width_padding + (cell_width * p2.x) + cell_body_width/2),
                           (int) (height_padding + (cell_height * p2.y) + cell_body_height/2));
    }


    SDL_Circ start_point;
    start_point.x = 0;
    start_point.y = 0;
    start_point.r = 5;
    SDL_Circ end_point;
    end_point.x = window_width;
    end_point.y = window_height;
    end_point.r = 5;

    SDL_RenderDrawCircle(renderer, start_point);
    SDL_RenderDrawCircle(renderer, end_point);
}
