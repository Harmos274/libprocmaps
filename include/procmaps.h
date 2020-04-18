/**
 * @file procmaps.h
 * @brief Header file for lib procmaps
 * @author Lilian VERLHAC
 * @version 1.0
 * @date 2020-04-18
 */

#ifndef PROCMAPS_H_
#define PROCMAPS_H_

typedef struct dev_major_minor_s dev_major_minor_t;

/**
 * @brief Hold the major minor id for the map's device
 */
struct dev_major_minor_s {
    int major;
    int minor;
};

typedef struct procmaps_row_s procmaps_row_t;

/**
 * @brief Hold all the information of a map
 */
struct procmaps_row_s {
    unsigned long long addr_begin;
    unsigned long long addr_end;
    unsigned char perms;
    unsigned long long offset;
    dev_major_minor_t dev;
    int inode;
    char *pathname;
};

/**
 * @brief Permissions associated to a map
 */
enum MAPS_PERMS {
    PERMS_READ = 1 << 0,
    PERMS_WRITE = 1 << 1,
    PERMS_EXECUTE = 1 << 2,
    PERMS_PRIVATE = 1 << 3,
    PERMS_SHARED = 1 << 4
};

typedef procmaps_row_t hr_procmaps;

#define MAX_PROCPATH_LEN 100
#define PROCMAPS_ARRAY_BASE_SIZE 32

/**
 * @brief Parse /proc/pid/maps to create an array of struct ptr which
 *        hold of the information
 *
 * @param pid Process pid, if pid <= 0 use self process
 *
 * @return Array of filled procmaps_row_t *
 */
hr_procmaps **contruct_procmaps(int pid);

/**
 * @brief Destroy hr_procmaps object, free all the allocated memory
 *
 * @param procmaps Array of procmaps_row_t *
 */
void destroy_procmaps(hr_procmaps **procmaps);

#endif // PROCMAPS_H_
