#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cell_costants.h"
#include "cell_structs.h"
#include "sectors.h"
#include "blockmaps.h"
#include "cells.h"

struct pos2D* neighbors_relative_position(char* mode, double grid_cell_size)
{
    int n_neighbors;
    pos2D* relative_positions;
    if(strcmp("QUAD2", mode) == 0)
    {
        n_neighbors = 8;
        relative_positions = (pos2D*)malloc(sizeof(pos2D) * n_neighbors);
        double angle = 0.;
        for(int i = 1; i < 8; i += 2)
        {
            relative_positions[i].x = grid_cell_size * cos(angle);
            relative_positions[i].y = grid_cell_size * sin(angle);
            angle += M_PI * 0.5;
        }
        angle = -M_PI * 0.25;
        for(int i = 0; i < 8; i += 2)
        {
            relative_positions[i].x = grid_cell_size * cos(angle);
            relative_positions[i].y = grid_cell_size * sin(angle);
            angle += M_PI * 0.5;
        }
    }else{
            fprintf(STREAM, "Mode: %s not implemented yet. Aborting...\n", mode);
        }
        return relative_positions;
}
