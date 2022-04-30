#ifndef __CELL_STRUCT_H__
#define __CELL_STRUCT_H__

#ifdef __cplusplus
#define CELL_STRUCT_LINKAGE "C"
#else
#define CELL_STRUCT_LINKAGE
#endif

typedef struct pos2D{
    double x;
    double y;
} pos2D;

typedef struct sector{
    int n_corners;
    struct pos2D* corner;
} sector;

typedef struct cell{
    struct pos2D r;
    unsigned int id;
    unsigned int sector_id;
    unsigned int tilemap_id;
    struct cell* neighbors;
} cell;

typedef struct cell_list{
    struct cell c;
    struct cell_list *next;
} cell_list;

typedef struct tile{
    struct pos2D r;
    unsigned int id;
    struct cell_list cells_in_tile;
} tile;

typedef struct blockmap{
    double tile_size;
    unsigned int ntilex, ntiley;
    pos2D corners[2];
    tile* tilemap;
}

#endif
