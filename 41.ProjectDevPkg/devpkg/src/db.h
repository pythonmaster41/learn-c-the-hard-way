#ifndef _DEVPKG_DB_H
#define _DEVPKG_DB_H

#include <stdbool.h>

#define DB_FILE "/usr/local/.devpkg/db"
#define DB_DIR "/usr/local/.devpkg"

int DB_init();
int DB_list();
int DB_update(const char *url);
bool DB_find(const char *url);

#endif // _DEVPKG_DB_H