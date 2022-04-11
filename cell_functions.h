#ifndef __CELL_FUNCTIONS_H__
#define __CELL_FUNCTIONS_H__

#ifdef __cplusplus
#define CELL_FUNCTIONS_LINKAGE "C"
#else
#define CELL_FUNCTIONS_LINKAGE
#endif

sector* read_sectors(char* filename);
void print_sectors(FILE *stream, sector* s);
#endif
