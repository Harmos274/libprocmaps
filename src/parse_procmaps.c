/**
 * @file parse_procmaps.c
 * @brief Source file for lib procmaps
 * @author Lilian VERLHAC
 * @version 1.0
 * @date 2020-04-18
 */

#include "procmaps.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char make_perms(char const *perms)
{
    unsigned char perm = 0x00;

    if (perms[0] == 'r') {
        perm |= PERMS_READ;
    }
    if (perms[1] == 'w') {
        perm |= PERMS_WRITE;
    }
    if (perms[2] == 'x') {
        perm |= PERMS_EXECUTE;
    }
    if (perms[3] == 'p') {
        perm |= PERMS_PRIVATE;
    } else if (perms[3] == 's') {
        perm |= PERMS_SHARED;
    }
    return perm;
}

static procmaps_row_t *parse_procmaps_line(char *line)
{
    procmaps_row_t *procmaps_row = malloc(sizeof(*procmaps_row));

    if (procmaps_row == NULL)
        return NULL;
    procmaps_row->addr_begin = strtoull(strtok(line, "-"), NULL, 16);
    procmaps_row->addr_end = strtoull(strtok(NULL, " "), NULL, 16);
    procmaps_row->perms = make_perms(strtok(NULL, " "));
    procmaps_row->offset = strtoull(strtok(NULL, " "), NULL, 16);
    procmaps_row->dev.major = atoi(strtok(NULL, ":"));
    procmaps_row->dev.minor = atoi(strtok(NULL, " "));
    procmaps_row->inode = atoi(strtok(NULL, " "));
    procmaps_row->pathname = strdup(strtok(NULL, ""));
    return procmaps_row;
}

static hr_procmaps **make_procmaps_array(FILE *procmaps_file)
{
    size_t array_size = PROCMAPS_ARRAY_BASE_SIZE;
    hr_procmaps **procmaps_array = calloc(array_size, sizeof(*procmaps_array));
    size_t i = 0;
    size_t size = 0;
    char *line = NULL;

    while (getline(&line, &size, procmaps_file) != -1) {
        if (line != NULL)
            procmaps_array[i] = parse_procmaps_line(line);
        ++i;
        if (i == array_size) {
            procmaps_array = realloc(procmaps_array,
                (array_size + 16) * sizeof(*procmaps_array));
            memset(procmaps_array + array_size, 0,
                16 * sizeof(*procmaps_array));
            array_size += 16;
        }
        free(line);
        line = NULL;
    }
    return (free(line), procmaps_array);
}

hr_procmaps **contruct_procmaps(int pid)
{
    char path[100];
    FILE *procmaps_file = NULL;
    hr_procmaps **procmaps_array = NULL;

    if (pid <= 0) {
        sprintf(path, "/proc/self/maps");
    } else {
        sprintf(path, "/proc/%d/maps", pid);
    }
    procmaps_file = fopen(path, "r");
    if (procmaps_file == NULL) {
        perror("fopen");
        return NULL;
    }
    procmaps_array = make_procmaps_array(procmaps_file);
    fclose(procmaps_file);
    return procmaps_array;
}

void destroy_procmaps(hr_procmaps **procmaps)
{
    int i = 0;

    while (procmaps[i++] != NULL);
    i -= 2;
    while (i != -1) {
        free(procmaps[i]->pathname);
        free(procmaps[i]);
        --i;
    }
    free(procmaps);
}
