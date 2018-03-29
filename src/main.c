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
*       (c) 14.7.2015 Veterans of ELIT
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "map.h"


char items[BLEN];
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
                
                getOptions(&o, &size, map[croom].ways);

                /* print item descriptions */
                for (i = 0; i < size; i++) {
                        if (o[i].item_description[0] != '\0') {
                                printf("\n");
                                myprint(o[i].item_description);
                        }
                }

                /* print options */
                printf("\n\n\n%s", "Muzes:\n");

                buff[0] = '\0';
                for (i = 0; i < size; i++) {
                        strncat(buff, o[i].description, BLEN);
                        strncat(buff, " ", BLEN);
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

        /* check for size */
        *size = 0;
        p = opts;
        while (*p != '\0') {
                if (*p == ';') 
                        (*size)++;
                p++;
        }

        /* allocate memeory */
        *o = (OPTION *) malloc(sizeof(OPTION) * (*size));
        if (*o == NULL) {
                printf("FATAL: Cannot allocate memory\n");
                exit(0);
        }


        /* parse options */
        x = 0;
        y = 0;
        buff[0] = '\0';
        p = opts;

        while (*p != '\0') {
                if ((*p == ',') || (*p == ';')) {
                        switch (x) {
                                case 0: strcpy((*o)[y].description, buff);
                                        break;
                                case 1: strcpy((*o)[y].key, buff);
                                        break;
                                case 2: (*o)[y].room = atoi(buff);
                                        break;
                                case 3: (*o)[y].has_to_have_item = *buff;
                                        break;
                                case 4: (*o)[y].can_get_item = *buff;
                                        break;
                                case 5: strcpy((*o)[y].item_description, buff);
                                        break; 
                        }

                        switch (*p) {
                                case ',':
                                        x++;
                                        break;
                                case ';':
                                        x = 0;
                                        if (    /* no conditions or */
                                                ((*o)[y].has_to_have_item == '\0') ||
                                                /* you have to have item and you have it actually */
                                                ((*o)[y].has_to_have_item != '\0' && strchr(items, (*o)[y].has_to_have_item) != NULL)
                                           ) {

                                                if (    /* no item or */
                                                        ((*o)[y].can_get_item == '\0') ||
                                                        /* you can have item and you don't have it yet */ 
                                                        ((*o)[y].can_get_item != '\0' && strchr(items, (*o)[y].can_get_item) == NULL)
                                                   ) {
                                                        y++;
                                                }
                                        }
                                        break;
                        }

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

        *size = y;
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
