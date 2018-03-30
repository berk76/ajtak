/*
*       map.h
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

#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

char *name = "   ---===*** Ajtak ***===---";

ROOM map[] = {
        {0, "R.I.P.", 
            ""
            },
        {1, "Sedis u sveho pracovniho stolu a ospale koukas do monitoru. Naproti pres stul bezi vetrak. Venku je 30 stupnu.", 
            "Jit na (k)kafe.,Kk,2,,,;"
            "Jit na (z)achod.,Zz,3,,,;"
            "Jit si neco koupit do (a)utomatu na sklad.,Aa,7,,,;"
            "Prohledat (s)uplik.,Ss,5,,,;"
            "Jit pokecat s (B)oukym.,Bb,8,h,,;"
            },
        {2, "Jsi v kuchynce a popijis kafe z kavovaru AdrianoDesign. V umyvadle je hromada spinaveho nadobi. V rohu jsou zamcene dvere.",
            "Jit na (z)patky k pocitaci.,Zz,1,,,;"
            "Precist si (i)nternert na mobilu.,Ii,4,,,;"
            "(O)demknout dvere a vejit.,Oo,6,k,,;"
            },
        {3, "Jsi na zachode.",
            "Jit na (z)patky k pocitaci.,Zz,1,,,;"
            },
        {4, "Ctes si zpravicky:\n\n* V Recku parlament hlasuje o prijeti podminek pujcky\n\n* Masarykovo nadrazi je uzavreno, protoze vlak nedobrzdil.",
            "(V)ypmout mobil a schovat ho do kapsy.,Vv,2,,,;"
            },
        {5, "V supliku je bordel.", 
            "(V)zit klic.,Vv,1,,k,V tom bordelu jsi nasel klic.;"
            "(Z)avrit suplik.,Zz,1,,,;"
            },
        {6, "Jsi v uklidove komre. Je tu sero ale vidis kbelik, nejake hadry a dve kostata.", 
            "Jit (z)patky a zamknout.,Zz,2,,,;"
            },
        {7, "Stojis u automatu a premyslis co si koupit.",
            "Koupit (h)oralku za osm.,Hh,1,,h,;"
            "Koupit (c)oca-colu za patnact.,Cc,1,,c,;"
            "Koupit (m)inonku za deset.,Mm,1,,m,;"
            "Jit (z)patky.,Zz,1,,,;"
            },
        {8, "Stojis v kanclu u Boukyho, je tu trochu zatuchlo... Bouky nadava na webove sluzby a neni s nim rec.",
            "Vzit Boukyho na (c)igo.,Cc,9,,,;"
            "Jit (z)patky.,Zz,1,,,;"
            },
        {9, "Postavas s Boukym pred vchodem do budovy a poslouchas jak si stezuje na Blahu a na Sparktech. ",
            "Jit (z)patky.,Zz,1,,,;"
            }
};

#endif
