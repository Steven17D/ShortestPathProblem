//
// Created by StevenD on 10/21/2017.
//

#include <time.h>
#include "../depth_first_search.h"

int main() {
    srand(time(NULL));
    short world_map[MAX_DIMENSION][MAX_DIMENSION];
    UINT x; for (x = 0; x < MAX_DIMENSION; ++x) {
        UINT y; for (y = 0; y < MAX_DIMENSION; ++y) {
            world_map[x][y] = (short) (rand() % 1000);
        }
    }
#ifdef DIAGONAL
    world_map[1][1] = 0;
    world_map[2][0] = 0;
    world_map[3][1] = 0;
    world_map[3][2] = 0;
#else
    world_map[0][1] = 0;
    world_map[0][2] = 0;
    world_map[1][2] = 0;
    world_map[2][2] = 0;
    world_map[2][3] = 0;
#endif

    Graph* graph = Graph_Create(world_map);
    Path result = NULL;
    DepthFirstSearch(graph, &result);

#ifdef DIAGONAL
    assert(Stack_Size_PNode(result) == 6);

    assert(Stack_PeekAt_PNode(result, 0)->position.x == 0);
    assert(Stack_PeekAt_PNode(result, 0)->position.y == 0);

    assert(Stack_PeekAt_PNode(result, 1)->position.x == 1);
    assert(Stack_PeekAt_PNode(result, 1)->position.y == 1);

    assert(Stack_PeekAt_PNode(result, 2)->position.x == 2);
    assert(Stack_PeekAt_PNode(result, 2)->position.y == 0);

    assert(Stack_PeekAt_PNode(result, 3)->position.x == 3);
    assert(Stack_PeekAt_PNode(result, 3)->position.y == 1);

    assert(Stack_PeekAt_PNode(result, 4)->position.x == 3);
    assert(Stack_PeekAt_PNode(result, 4)->position.y == 2);

    assert(Stack_PeekAt_PNode(result, 5)->position.x == 3);
    assert(Stack_PeekAt_PNode(result, 5)->position.y == 3);
#else
    assert(Stack_Size_PNode(result) == 7);

    assert(Stack_PeekAt_PNode(result, 0)->position.x == 0);
    assert(Stack_PeekAt_PNode(result, 0)->position.y == 0);

    assert(Stack_PeekAt_PNode(result, 1)->position.x == 0);
    assert(Stack_PeekAt_PNode(result, 1)->position.y == 1);

    assert(Stack_PeekAt_PNode(result, 2)->position.x == 0);
    assert(Stack_PeekAt_PNode(result, 2)->position.y == 2);

    assert(Stack_PeekAt_PNode(result, 3)->position.x == 1);
    assert(Stack_PeekAt_PNode(result, 3)->position.y == 2);

    assert(Stack_PeekAt_PNode(result, 4)->position.x == 2);
    assert(Stack_PeekAt_PNode(result, 4)->position.y == 2);

    assert(Stack_PeekAt_PNode(result, 5)->position.x == 2);
    assert(Stack_PeekAt_PNode(result, 5)->position.y == 3);

    assert(Stack_PeekAt_PNode(result, 6)->position.x == 3);
    assert(Stack_PeekAt_PNode(result, 6)->position.y == 3);
#endif

    Stack_Destroy_PNode(result);
    Graph_Destroy(graph);

    return 0;
}