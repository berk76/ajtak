/*
*       Textovka.c
*       14.7.2015
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include <spectrum.h>

#define BLEN 30
#define BLEN2 255
#define SCREEN_WIDTH 32

typedef struct {
        int id;
        char *description;
        char *ways;
} ROOM;

typedef struct {
        char description[BLEN];
        char key[BLEN];
        int room;
        char has_to_have_item;
        char can_get_item;
} OPTION;

char items[BLEN];

/* method #1 - heap pointer statically compiled as part of the binary */
long heap;

char name[] = "   ---===*** Ajtak ***===---";

ROOM map[] = {
        {0, "R.I.P.", ""},
        {1, "Sedis u sveho pracovniho stolu a ospale koukas do monitoru. Naproti pres stul bezi vetrak. Venku je 30 stupnu.", 
            "Jit na (k)kafe,Kk,2,,;Jit na (z)achod,Zz,3,,;Prohledat (s)uplik,Ss,5,,;"}, 
        {2, "Jsi v kuchynce a popijis kafe z kavovaru AdrianoDesign. V umyvadle je hromada spinaveho nadobi. V rohu jsou zamcene dvere.",
            "Jit na (z)patky k pocitaci,Zz,1,,;Precist si (i)nternert na mobilu,Ii,4,,;(O)demknout dvere a vejit,Oo,6,k,;"},
        {3, "Jsi na zachode.",
            "Jit na (z)patky k pocitaci,Zz,1,,;"},
        {4, "Ctes si zpravicky:\n\n* V Recku parlament hlasuje o prijeti podminek pujcky\n\n* Masarykovo nadrazi je uzavreno, protoze vlak nedobrzdil.",
            "(V)ypmout mobil a schovat ho do kapsy,Vv,2,,;"},
        {5, "V supliku jsi nasel klic.", 
            "(V)zit klic,Vv,1,,k;(Z)avrit suplik,Zz,1,,;"},
        {6, "Jsi v uklidove komre. Je tu sero ale vidis kbelik, nejake hadry a dve kostata. ", 
            "(J)it zpatky a zamknout,Jj,2,,;"}
        };
        
int croom = 1;

static int getOption(char *opts);
static void myprint(char *s);
static void mystrncat(char * buff, int buflen, char *addition);
static void insert_item(char c);

int main(void)
{
        
        int c;
          
        mallinit();              /* heap cleared to empty */
        //sbrk(30000,2000);        /* add 2000 bytes from addresses 30000-31999 inclusive to the heap */
        sbrk(65000,536);         /* add 536 bytes from addresses 65000-65535 inclusive to the heap  */
        printf("%c%c", 1, 32);   /* 32 characters */
        items[0] = '\0';
        
        while (1) {
                
                printf("%c", 12);
                printf("%s\n\n", name);
                myprint(map[croom].description);
                
                printf("\n\n\n%s", "Muzes:\n");
                croom = getOption(map[croom].ways); 
        }
        return 0;
}

int getOption(char *opts) {
        char buff[BLEN], buff2[BLEN2], *p;
        int size, x, y, c, result;
        OPTION *o;
        
        size = 0;
        p = opts;
        while (*p != '\0') {
                if (*p == ';') size++;
                p++;
        }
        
        o = (OPTION *) malloc(sizeof(OPTION) * size);
        if (o == NULL) {
                printf("FATAL: Cannot allocate memory\n");
                exit(0);
        }
        
        x = 0;
        y = 0;
        buff[0] = '\0';
        p = opts;
        while (*p != '\0') {
                if (*p == ';') {
                        o[y].can_get_item = *buff;
                        x = 0;
                        y++;
                        buff[0] = '\0';
                        p++;
                        continue;
                }
                if (*p == ',') {
                        switch (x) {
                                case 0: strcpy(o[y].description, buff);
                                        break;
                                case 1: strcpy(o[y].key, buff);
                                        break;
                                case 2: o[y].room = atoi(buff);
                                        break;
                                case 3: o[y].has_to_have_item = *buff;
                                        break 
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
        
        buff2[0] = '\0';
        for (y = 0; y < size; y++) {
                if ((o[y].has_to_have_item == '\0' && o[y].can_get_item == '\0') 
                 || (o[y].has_to_have_item == '\0' && strchr(items, o[y].can_get_item) == NULL)
                 || (o[y].has_to_have_item != '\0' && strchr(items, o[y].has_to_have_item) != NULL)
                 ) {
                        mystrncat(buff2, BLEN2, o[y].description);
                        mystrncat(buff2, BLEN2, " ");
                }
        }
        myprint(buff2);
        
        result = 0;
        while (result <= 0) {
                c = getchar();
                for (y = 0; y < size; y++) {
                        if (strchr(o[y].key, c) != NULL) {
                                result = o[y].room;
                                if (o[y].can_get_item != '\0') {
                                        insert_item(o[y].can_get_item);        
                                }
                                break;
                        }
                }
        }
        
        free((void *) o);
        return result;
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


void mystrncat(char * buff, int buflen, char *addition) {
        int result;
        char *p;
        
        result = 0;
        buflen = buflen - strlen(buff);
        p = buff + strlen(buff);
        while (buflen != 0 && *addition != '\0') {
                *p = *addition;
                p++;
                addition++;
                buflen--;                
        }
        *p = '\0';
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
