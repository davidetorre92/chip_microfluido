#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cell_structs.h"
#include "cell_costants.h"
#include "sectors.h"
#include "blockmaps.h"
#include <stdbool.h>

blockmap* make_the_block_map(sector *s, double tile_size)
{

    bool first = true;
    double min_x, max_x, min_y, max_y;
    unsigned int ntilex, ntiley;
    unsigned int id = 0;
    blockmap* bm;

    for(int i = 0; s[i].n_corners != 0; i++)
    {
        for(int j = 0; j < s[i].n_corners; j++)
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
    bm = (blockmap*)malloc(sizeof(blockmap));
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
    bm->tilemap = (tile*)malloc(sizeof(tile) * ntilex * ntiley);
    for(int xi = 0; xi < ntilex; xi++)
    {
        for(int yi = 0; yi < ntiley; yi++)
        {
        bm->tilemap[id].r.x = min_x + xi * tile_size;
        bm->tilemap[id].r.y = min_y + yi * tile_size;
        bm->tilemap[id].id = id;
        id++;
        }
    }
    return bm;
}

void print_blockmap(FILE* stream, blockmap* bm)
{
    for(int i = 0; i < bm->ntilex * bm->ntiley; i++)
    {
        fprintf(stream, "%d:\t%lf\t%lf\n", i, bm->tilemap[i].r.x, bm->tilemap[i].r.y);
    }
}
