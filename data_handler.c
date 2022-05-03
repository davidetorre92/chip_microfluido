#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "data_handler.h"
#include "cell_costants.h"
#define MAXBUFFER_SIZE 512
char *parse_config_file(int argc, char *argv[])
{
    char *filename;
    bool filename_flag = false;
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-c")==0 && i != argc-1)
        {
            filename = (char*)malloc(sizeof(char**)*MAXBUFFER_SIZE);
            strcpy(filename, argv[i+1]);
            filename_flag = true;
            break;
        }
    }
    if(!filename_flag)
    {
        fprintf(stdout, "Usage: %s -c config file path\n",argv[0]);
        exit(1);
    }
    return filename;
}

FILE *Fopen(char *filename, char *cmd)
{

    FILE *fp = fopen(filename, cmd);
    if(fp == NULL)
    {
        fprintf(stderr, "Unable to open %s. Aborting...\n", filename);
        exit(EXIT_FAILURE);
    }
    return fp;

}

double read_data(FILE* fp, char *keyword, int ind, bool turnback, double dft)
{
    const char *DELIMITER = "=";
    char line[MAXBUFFER_SIZE];
    double data;
    char data_key[MAXBUFFER_SIZE];
    bool found=false;
    if(ind>=0)
    {
        sprintf(data_key, "%s %d", keyword, ind);
    } else
    {
        strcpy(data_key, keyword);
    }
    if(turnback)
    { 
        rewind(fp);
    }
    while(fgets(line, MAXBUFFER_SIZE, fp) != NULL)
    {
        char *token = strtok(line, DELIMITER);
        if(strcmp(data_key, token) == 0)
        {
            token = strtok(NULL, DELIMITER);
            data = atof(token);
            found = true;
            break;
        }
    }
    if(!found)
    {
        if(!turnback)
        {
            read_data(fp, keyword, ind, true, dft);
        }
        fprintf(stdout, "Warning: %s not found, returning %lf\n",data_key, dft);
        data = dft;
    }
    return data;
}

char* read_text(FILE* fp, char *keyword, bool mandatory, char *dft)
{
    const char *DELIMITER = "=";
    char line[MAXBUFFER_SIZE];
    char *data = (char*)malloc(sizeof(char**)*MAXBUFFER_SIZE);
    bool found=false;
    
    rewind(fp);

    while(fgets(line, MAXBUFFER_SIZE, fp) != NULL)
    {
        char *token = strtok(line, DELIMITER);
        if(strcmp(keyword, token) == 0)
        {
            token = strtok(NULL, DELIMITER);
            strcpy(data, token);
            found = true;
            data[strcspn(data, "\n")] = 0; 
            break;
        }
    }
    if(!found && mandatory)
    {
        fprintf(stderr, "Error: mandatory field\n%s\n not found in configuration file. Exiting\n",keyword);
        exit(1);
    }
    if(!found && !mandatory)
    {
        fprintf(STREAM, "Warning: %s not found, setting it to its default value: %s\n", keyword, dft);
        data = strcpy(data, dft);
    }
    return data;
}
