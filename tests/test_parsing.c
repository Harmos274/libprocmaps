/**
 * @file test_parsing.c
 * @brief Unit tests
 * @author Lilian VERLHAC
 * @version 1.0
 * @date 2020-04-18
 */

#include "../include/procmaps.h"
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

procmaps_row_t *parse_procmaps_line(char *line);

int main(void)
{
    char *mapstr = strdup("00400000-00452000 r-xp 00000000 08:02 173521      /usr/bin/dbus-daemon\n\0");
    char permissions = ((0 | PERMS_READ) | PERMS_EXECUTE) | PERMS_PRIVATE;
    procmaps_row_t *map = parse_procmaps_line(mapstr);

    assert(map != NULL);
    assert(map->addr_begin == 0x00400000);
    assert(map->addr_end == 0x00452000);
    assert(map->perms == permissions);
    assert(map->offset == 0);
    assert(map->dev.major == 8);
    assert(map->dev.minor == 2);
    assert(map->inode == 173521);
    assert(strcmp(map->pathname, "/usr/bin/dbus-daemon") == 0);
    printf("All tests passed :)\n");
    return 0;
}
