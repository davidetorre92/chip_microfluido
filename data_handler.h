#ifndef __DATA_HANDLER_H__
#define __DATA_HANDLER_H__

#ifdef __cplusplus
#define DATA_HANDLER_LINKAGE "C"
#else
#define DATA_HANDLER_LINKAGE
#endif
#include <stdbool.h>
char *parse_config_file(int argc, char *argv[]);
double read_data(FILE* fp, char *keyword, int ind, bool turnback);
char* read_text(FILE* fp, char *keyword, bool mandatory);
FILE *Fopen(char *filename, char *cmd);
#define MAXBUFFER_SIZE 512
#endif
