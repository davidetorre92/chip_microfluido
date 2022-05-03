#ifndef __BLOCKMAPS_H__
#define __BLOCKMAPS_H__

#ifdef __cplusplus
#define BLOCKMAPS_LINKAGE "C"
#else
#define BLOCKMAPS_LINKAGE
#endif

void make_the_block_map(tile** blockmap, sector *s, double tile_size);
#endif
