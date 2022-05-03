#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell_costants.h"
#include "cell_structs.h"
#include "sectors.h"
#include "blockmaps.h"
#include "cells.h"
#include "data_handler.h"

int main(int argc, char *argv[])
{
    sector* s;
    blockmap* bm;
    
    char *config_filename;
    double tile_size;
    FILE *cpt;
    char *sector_filename;
    char *grid_mode;
    double grid_cell_size;

    config_filename = parse_config_file(argc, argv);
    cpt = Fopen(config_filename, "r");
    sector_filename = read_text(cpt,"Sectors file", true, "");
    tile_size = read_data(cpt, "Tile size", -1, true, DEFAULT_TILE_SIZE);
    grid_cell_size = read_data(cpt, "Grid cell size", -1, true, DEFAULT_GRID_SIZE);
    grid_mode = read_text(cpt, "Grid type", false, DEFAULT_GRID_MODE);
    s = read_sectors(sector_filename);
    bm = make_the_block_map(s, tile_size);
    
    free(config_filename);
    free(sector_filename);
    free(s);
    free(bm->tilemap);
    free(bm);
    free(grid_mode);
    return 0;
}
