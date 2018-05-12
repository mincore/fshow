/* ===================================================
 * Copyright (C) 2018 speed-clouds All Right Reserved.
 *      Author: chenshuangping@speed-clouds.com
 *    Filename: 1.c
 *     Created: 2018-01-08 01:50
 * Description:
 * ===================================================
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#define W 20

template<typename T>
void show(int argc, char **argv) {
    int fds[argc];
    int work = 0;

    for (int i=0; i<argc; i++) {
        fds[i] = open(argv[i], O_RDONLY);
        if (fds[i] != -1)
            work++;
    }

    while (work) {
        for (int i=0; i<argc; i++) {
            if (fds[i] == -1) {
                std::cout << std::left << std::setw(W) << ".";
                continue;
            }

            T v;
            if (read(fds[i], &v, sizeof(T)) > 0) {
                std::cout << std::left << std::setw(W) << v;
            } else {
                close(fds[i]);
                fds[i] = -1;
                std::cout << std::left << std::setw(W) << ".";
                work--;
            }
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[])
{
    int opt = getopt(argc, argv, "i:f:d:l:");
    switch (opt) {
    case 'i': show<int>(argc-optind+1, &argv[optind-1]); break;
    case 'l': show<long long>(argc-optind+1, &argv[optind-1]); break;
    case 'd': show<double>(argc-optind+1, &argv[optind-1]); break;
    case 'f': show<float>(argc-optind+1, &argv[optind-1]); break;
    default:
        printf("usage: %s OPTIONS FILES\n"
               "OPTIONS\n"
               "\t-i: show as int\n"
               "\t-f: show as float\n"
               "\t-d: show as double\n"
               "\t-l: show as long long\n"
               , argv[0]);
        return -1;
    }

    return 0;
}

