#ifndef __TILEMAPS_H__
#define __TILEMAPS_H__

#ifdef __cplusplus
#define TILEMAPS_LINKAGE "C"
#else
#define TILEMAPS_LINKAGE
#endif

sector* read_sectors(char* filename);
void print_sectors(FILE *stream, sector* s);
cell_list* construct_grid(sector* s, float cell_size, char *mode);
void put(pos2D r, sector s, cell_list* grid, pos2D *neighbors, int n_neigh);
#endif
