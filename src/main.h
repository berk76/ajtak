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

#ifndef _MAIN_H_
#define _MAIN_H_

#define BLEN 256
#define SCREEN_WIDTH 32


/* way */
typedef struct {
        char description[BLEN];
        char key[BLEN];
        int room;
        char has_to_have_item;
        char can_get_item;
} OPTION;


/* room */
typedef struct {
        int id;                         /* room id */
        char *description;              /* room description */
        char *ways;                     /* list of ways from room */
} ROOM;


#endif
