//
//  file_operations.c
//  LinkedList
//
//  Created by Sarvesh Ghautham on 2/22/14.
//

#include "file_operations.h"

int file_open(FILE **fp, char *file_name, char *mode)
{
    *fp = fopen(file_name, mode);
    if (*fp == NULL)
    {
        perror("fopen");
        return 0;
    }
    
    return 1;
}

long file_read(FILE **fp, char *file_name, int list_id, char *line_read)
{
    int list_length = 0;
    int list_id_from_file=0;
    
    if (file_open(fp, file_name, "r"))
    {    
        while (1)
        {
            fgets(line_read, MAX_NODES_IN_LIST, *fp);
            list_id_from_file = line_read[0] - '0';
            if (list_id_from_file == list_id)
                break;
            list_length += strlen(line_read);
            //printf("Line: %s\n", line_read);
        }
        file_close(fp);
        return list_length;
    }
    return 0;
}

void file_close (FILE **fp)
{
    fclose(*fp);
}