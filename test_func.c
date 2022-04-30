#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell_structs.h"
#include "sectors.h"
#include "data_handler.h"
#include "blockmaps.h"
int main(int argc, char *argv[])
{
    sector* s;
    blockmap* bm;
    char *config_filename;
    config_filename = parse_config_file(argc, argv);
    FILE *cpt = Fopen(config_filename, "r");
    char *sector_filename;

    sector_filename = read_text(cpt,"Sectors file", true);
    s = read_sectors(sector_filename);
    print_sectors(stdout, s);
    make_the_block_map(&bm, s, tile_size);
    for(int i = 0; i < bm.ntilex * bm.ntiley; i++)
    {
        fprintf(stdout, "%d:\t%lf\t%lf\n", i, bm->tilemap[i].x, bm->tilemap[i].y);
    }

    free(config_filename);
    free(sector_filename);
    free(s);
    free(bm->tilemap);
    free(bm);
    return 0;
}
