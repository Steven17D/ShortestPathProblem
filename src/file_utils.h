//
// Created by Steven on 10/7/2017.
//

#ifndef SHORTESTPATHPROBLEM_FILE_UTILS_H
#define SHORTESTPATHPROBLEM_FILE_UTILS_H

#include <windef.h>
#include <stdio.h>
#include "properties.h"

BOOL OpenFileDialog(char *fileName);

BOOL GetWorldMapFileName(int argc, char **argv, const char *file_name);

BOOL InitWorldMap(FILE *world_map_file, short world_map[MAX_DIMENSION][MAX_DIMENSION]);


#endif //SHORTESTPATHPROBLEM_FILE_UTILS_H
