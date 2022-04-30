#ifndef __SECTORS_H__
#define __SECTORS_H__

#ifdef __cplusplus
#define SECTORS_LINKAGE "C"
#else
#define SECTORS_LINKAGE
#endif

sector* read_sectors(char* filename);
void print_sectors(FILE *stream, sector* s);
int check_parenthesis_consistency(FILE *fp, char *filename);
void allocate_corners(sector *s, FILE *fp);

#endif
