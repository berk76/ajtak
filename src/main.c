/*
*       main.h
*
*       This file is part of Ajtak game.
*       https://github.com/veteransofelit/ajtak
*       
*       Ajtak is free software; you can redistribute it and/or modify
*       it under the terms of the GNU General Public License as published by
*       the Free Software Foundation; either version 3 of the License, or
*       (at your option) any later version. <http://www.gnu.org/licenses/>
*
*       (c) 14.7.2015
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "map.h"


char items[BLEN];
char name[] = "   ---===*** Ajtak ***===---";
int croom = 1;


static void getOptions(OPTION **o, int *size, char *opts);
static void myprint(char *s);
static void insert_item(char c);


int main(void) {
        char buff[BLEN];
        OPTION *o;
        int size, i, c, choice;
        items[0] = '\0';

        while (1) {
                printf("\n\n%s\n\n", name);
                myprint(map[croom].description);
                
                printf("\n\n\n%s", "Muzes:\n");
                
                /* print options */
                getOptions(&o, &size, map[croom].ways);
                buff[0] = '\0';
                for (i = 0; i < size; i++) {
                        if ((o[i].has_to_have_item == '\0' && o[i].can_get_item == '\0') 
                                || (o[i].has_to_have_item == '\0' && strchr(items, o[i].can_get_item) == NULL)
                                || (o[i].has_to_have_item != '\0' && strchr(items, o[i].has_to_have_item) != NULL)
                         ) {
                                strncat(buff, o[i].description, BLEN);
                                strncat(buff, " ", BLEN);
                        }
                }

                myprint(buff);
                printf("\n\n>");

                /* get choice */
                choice = 0;
                while (choice <= 0) {
                        c = getchar();
                        for (i = 0; i < size; i++) {
                                if (strchr(o[i].key, c) != NULL) {
                                        choice = o[i].room;
                                        if (o[i].can_get_item != '\0') {
                                                insert_item(o[i].can_get_item);        
                                        }
                                        break;
                                }
                        }
                }
                
                free((void *) o);
                croom = choice; 
        }
        return 0;
}


void getOptions(OPTION **o, int *size, char *opts) {
        char buff[BLEN], *p;
        int x, y;

        *size = 0;
        p = opts;
        while (*p != '\0') {
                if (*p == ';') (*size)++;
                p++;
        }

        *o = (OPTION *) malloc(sizeof(OPTION) * (*size));
        if (*o == NULL) {
                printf("FATAL: Cannot allocate memory\n");
                exit(0);
        }

        x = 0;
        y = 0;
        buff[0] = '\0';
        p = opts;

        while (*p != '\0') {

                if (*p == ';') {
                        (*o)[y].can_get_item = *buff;
                        x = 0;
                        y++;
                        buff[0] = '\0';
                        p++;
                        continue;
                }

                if (*p == ',') {
                        switch (x) {
                                case 0: strcpy((*o)[y].description, buff);
                                        break;
                                case 1: strcpy((*o)[y].key, buff);
                                        break;
                                case 2: (*o)[y].room = atoi(buff);
                                        break;
                                case 3: (*o)[y].has_to_have_item = *buff;
                                        break; 
                        }
                        x++;
                        buff[0] = '\0';
                        p++;
                        continue;
                }

                if (strlen(buff) + 1 == BLEN) {
                        p++;
                        continue;
                }

                buff[strlen(buff) + 1] = '\0';
                buff[strlen(buff)] = *p; 
                p++;
        }

        return;
}


void myprint(char *s) {
        int i;
        char *p, *p1;

        i = 0;
        p = s;
        p1 = p;

        while (*p != '\0') {
                
                p = p1;
                while (*p1 != '\0' && (strchr(" \n", *p1) == NULL)) {
                        p1++;
                        i++;
                }
                
                if (i >= SCREEN_WIDTH - 1) {
                        putchar('\n');
                        i = p1 - p;
                }
                
                if (*p1 == '\n') {
                        i = p1 - p;
                }

                while (p <= p1 && *p != '\0') {
                        putchar(*p);
                        p++;
                }
                p1++;
                i++;
        }
}


void insert_item(char c) {
        char *p;
        if (strchr(items, c) == NULL) {
                if (strlen(items) + 1 < BLEN) {
                        p = items + strlen(items);
                        *p = c;
                        p++;
                        *p = '\0';
                } 
        }
}
