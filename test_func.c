#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell_structs.h"
#include "cell_functions.h"
#include "data_handler.h"

int main(int argc, char *argv[])
{
    sector* s;
    char *config_filename;
    config_filename = parse_config_file(argc, argv);
    FILE *cpt = Fopen(config_filename, "r");
    char *sector_filename;
    sector_filename = read_text(cpt,"Sectors File", true);
    s = read_sectors(sector_filename);
    print_sectors(stdout, s);
    free(config_filename);
    free(sector_filename);
    free(s);
    return 0;
}
