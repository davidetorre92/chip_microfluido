#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cell_costants.h"
#include "cell_structs.h"
#include "sectors.h"
#include <stdbool.h>
#define MAX_SECTOR_BUFFER_SIZE 255

sector* read_sectors(char* filename)
{
    FILE *fp;
    int n_sectors;
   
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Cannot open sector file %s. Aborting...\n", filename);
        exit(EXIT_FAILURE);
    }
    n_sectors = check_parenthesis_consistency(fp, filename);
    sector* s = (sector*)malloc(sizeof(sector)*(n_sectors+1));
    allocate_corners(s, fp);

    return s;
}

void allocate_corners(sector *s, FILE *fp)
{
    int n_corners;
    int i_sector, i_corner;
    bool open_sector_chunk;
    char line[MAX_SECTOR_BUFFER_SIZE], *token, *token_corner;
    rewind(fp);
    
    i_sector = 0;
    n_corners = 0;
    while(fgets(line, MAX_SECTOR_BUFFER_SIZE, fp) != NULL)
    {
        token = strtok(line, "\n");
        if(strcmp(line, "{") == 0)
        {
            n_corners = 0;
            open_sector_chunk = true;
            continue;
        }
        if(strcmp(line, "}") == 0)
        {
            open_sector_chunk = false;
            s[i_sector].n_corners = n_corners;
            s[i_sector].corner = (pos2D*)malloc(sizeof(pos2D) * n_corners);
            i_sector++;
            continue;
        }
        if(open_sector_chunk)
        {
            n_corners++;
        }
    }
    rewind(fp);
    i_sector = 0;
    i_corner = 0;
    while(fgets(line, MAX_SECTOR_BUFFER_SIZE, fp) != NULL)
    {
        token = strtok(line, "\n");
        if(strcmp(line, "{") == 0)
        {
            open_sector_chunk = true;
            continue;
        }
        if(strcmp(line, "}") == 0)
        {
            i_corner = 0;
            i_sector++;
            open_sector_chunk = false;
            continue;
        }
        if(open_sector_chunk)
        {
            token_corner = strtok(token, " ");
            s[i_sector].corner[i_corner].x = atof(token_corner);
            token_corner = strtok(NULL, " ");
            s[i_sector].corner[i_corner].y = atof(token_corner);
            i_corner++;
        }
    }
    s[i_sector].n_corners = 0;
}

int check_parenthesis_consistency(FILE* fp, char *filename)
{
    int n_sectors = 0;
    bool open_sector_chunk = false;
    char line[MAX_SECTOR_BUFFER_SIZE];
    while(fgets(line, MAX_SECTOR_BUFFER_SIZE, fp) != NULL)
    {
        if(strcmp(line, "{") == 0)
        {
            if(open_sector_chunk)
            {
                fprintf(stderr, "Error: \"{\" found before \"}\" in %s. Aborting...\n", filename);
                exit(EXIT_FAILURE);
            }
            open_sector_chunk = true;
        }
        if(strcmp(line, "}") == 0)
        {
            if(open_sector_chunk)
            {
                n_sectors++;
                open_sector_chunk = false;
            } else {
                fprintf(stderr, "Error: \"}\" not matching with \"{\" in %s. Aborting...\n", filename);
                exit(EXIT_FAILURE);
            }
        }
    }
    return n_sectors;
}

void print_sectors(FILE *stream, sector *s)
{
    for(int i = 0; s[i].n_corners != 0; i++)
    {
        fprintf(stream, "Sector #%d:\n", i+1);
        for(int j = 0; j < s[i].n_corners; j++)
        {
            fprintf(stream, "%lf %lf\n", s[i].corner[j].x, s[i].corner[j].y);
        }
    }
}
