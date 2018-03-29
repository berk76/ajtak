#include <stdio.h>


/* way */
typedef struct {
        char *description;
        char *key;
        int room;
        char has_to_have_item;
        char can_get_item;
} OPTION;


/* room */
typedef struct {
        int id;                         /* room id */
        char *description;              /* room description */
        char *ways;                     /* list of ways from room */
        OPTION *o;
} ROOM;


ROOM map[] = {
        {0, "R.I.P.", "", {{"test", "test", 1, 'a', 'a'},{"test", "test", 1, 'a', 'a'}}}
        };


int main(void) {
        return 0;
}