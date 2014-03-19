//
//  file_operations.h
//  LinkedList
//
//  Created by Sarvesh Ghautham on 2/22/14.
//

#ifndef LinkedList_file_operations_h
#define LinkedList_file_operations_h

#include "main.h"
#include "list.h"

int file_open(FILE **, char *, char *);
long file_read(FILE **, char *, int, char *);
void file_close (FILE **);

#endif
