#ifndef __CELLS_H__
#define __CELLS_H__

#ifdef __cplusplus
#define CELLS_LINKAGE "C"
#else
#define CELLS_LINKAGE
#endif

struct pos2D* make_neighbors(char* mode, pos2D center);

#endif
