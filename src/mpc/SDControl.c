#include "../system/global.h"
#include <string.h>

FATFS fso;
DIR dir;
FILINFO fileInfo;
FIL file;
UINT br, bw;

void sd_init() {
    FRESULT res;
    FILINFO fno;
    UARTprintf("Looking for SD\n", NULL);
    while (disk_initialize(0));
    f_mount(0, &fso);
    //f_chdir(PATH);
    //f_opendir(&dir, ".");
    sd_list(PATH);
    UARTprintf("SD card initialized\n", NULL);
}

void mpc_sample_open(mpc_sample *sample) {
    f_open(&sample->file, sample->fileName, FA_OPEN_EXISTING | FA_READ);
    f_read(&sample->file, &sample->header, sizeof sample->header, &sample->read_bytes);
}

void mpc_sample_reset(mpc_sample *sample) {
    f_lseek(&sample->file, sizeof sample->header);
    //DEBUG_PRINT("Reset: %s \n", sample->fileName);
}

float mpc_sample_load_next(mpc_sample *sample) {
    float val = 0;
    f_read(&sample->file, &val, sizeof(val), &sample->read_bytes);
    if(sizeof(val) != sample->read_bytes) {
        mpc_sample_reset(sample);
        trigger_sample_event(RESET, sample);
    }
    return val;
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
