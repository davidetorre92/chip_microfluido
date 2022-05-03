#ifndef __BLOCKMAPS_H__
#define __BLOCKMAPS_H__

#ifdef __cplusplus
#define BLOCKMAPS_LINKAGE "C"
#else
#define BLOCKMAPS_LINKAGE
#endif

blockmap* make_the_block_map(sector *s, double tile_size);
void print_blockmap(FILE* stream, blockmap* bm);

#endif
