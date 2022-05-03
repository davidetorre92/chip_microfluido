#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cell_structs.h"
#include "sectors.h"
#include "blockmaps.h"
#include <stdbool.h>

void make_the_block_map(blockmap** bm, sector *s, double tile_size)
{

    bool first = true;
    double min_x, max_x, min_y, max_y;
    unsigned int ntilex, ntiley;
    unsigned int id = 0;

    for(int i = 0; s[i].n_corners != 0; i++)
    {
        for(int j = 0; j < s[j].n_corners; j++)
        {
            if(first == true)
            {
                min_x = s[i].corner[j].x;
                min_y = s[i].corner[j].y;
                max_x = s[i].corner[j].x;
                max_y = s[i].corner[j].y;
                first = false;
            } else {
                min_x = fmin(min_x, s[i].corner[j].x); 
                min_y = fmin(min_y, s[i].corner[j].y); 
                max_x = fmax(max_x, s[i].corner[j].x); 
                max_y = fmax(max_y, s[i].corner[j].y); 
            }
        }
    } 
    ntilex = (unsigned int)((max_x - min_x)/tile_size + 1);
    ntiley = (unsigned int)((max_y - min_y)/tile_size + 1);
    *bm = (blockmap*)malloc(sizeof(blockmap));
    if(bm == NULL)
    {
        fprintf(stderr, "Unable to allocate memory in make_the_block_map. Aborting...\n");
        exit(1);
    }

    bm->corners[0].x = min_x;
    bm->corners[0].y = min_y;
    bm->corners[1].x = max_x;
    bm->corners[1].y = max_y;
    bm->tile_size = tile_size;
    bm->ntilex = ntilex;
    bm->ntiley = ntiley;
    bm->tilemap = (tile*)malloc(sizeof(tile) * ntilex * ntiley)
    for(int xi = 0; xi < ntilex; xi++)
    {
        for(int yi = 0; yi < ntiley; yi++)
        {
        bm->tilemap[id].r.x = min_x + ntilex * tile_size;
        bm->tilemap[id].r.y = min_y + ntiley * tile_size;
        bm->tilemap[id].id = id;
        bm->tilemap[id].cells_in_tile = NULL;
        id++;
        }
    }
}
