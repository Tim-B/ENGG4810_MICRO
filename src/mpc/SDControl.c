#include "global.h"
#include <string.h>

FATFS fso;
DIR dir;
FILINFO fileInfo;
FIL file;

void sd_init() {
    FRESULT res;
    FILINFO fno;
    IntMasterDisable();
    UARTprintf("Init SD\n");
    while (disk_initialize(0));
    UARTprintf("Mounting FS\n");
    f_mount(0, &fso);
    UARTprintf("\n");
    //f_chdir(PATH);
    UARTprintf("Opening %s\n", PATH);
    //f_opendir(&dir, ".");
    sd_list(PATH);
    UARTprintf("shitcunt %s\n", PATH);
}

void sd_read() {
    
}

FRESULT sd_list(char* path) {
    FRESULT res;
    FILINFO fno;
    int i;
    char *fn; /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof lfn;
#endif


    res = f_opendir(&dir, path); /* Open the directory */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno); /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break; /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue; /* Ignore dot entry */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) { /* It is a directory */
                UARTprintf(&path[i], "/%s", fn);
                res = sd_list(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else { /* It is a file. */
                UARTprintf("%s/%s\n", path, fn);
            }
        }
    }

    return res;
}
