/* ===================================================
 * Copyright (C) 2018 speed-clouds All Right Reserved.
 *      Author: chenshuangping@speed-clouds.com
 *    Filename: gen.cpp
 *     Created: 2018-01-31 14:03
 * Description:
 * ===================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdarg.h>
#include <time.h>

static int write_file(void *data, int size, const char *fmt, ...)
{
    char file[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(file, sizeof(file), fmt, ap);
    va_end(ap);

    FILE *fp = fopen(file, "w");
    if (!fp) {
        printf("open %s failed\n", file);
        return -1;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        return -1;

    int size = atoi(argv[1]);
    std::vector<int> data;

    srand(time(NULL));

    for (int i=0; i<size/4; i++)
        data.push_back(rand());

    if (size%4)
        data.push_back(0);

    write_file(&data[0], size, argv[2]);

    return 0;
}

