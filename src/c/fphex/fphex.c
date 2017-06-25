#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for(size_t i = 0; i < strlen(argv[0]); i++)
        argv[0][i] = (char)tolower(argv[0][i]);

    char* end = NULL;

    // - Entry point for fptohex
    if((strcmp(argv[0], "./fptohex") == 0) && (argc == 2) &&
       (strlen(argv[1]) > 2)) {

        float f = strtof(argv[1], &end);
        if(f == HUGE_VAL || f == HUGE_VALF || f == HUGE_VALL || f == 0)
            printf("Invalid value '%s'", argv[1]);
        else {
            uint32_t r = *(uint32_t*)(&f);
            printf("0x%X <-> %s\n", r, argv[1]);
        }
    }

    // - Entry point for hextofp
    else if((strcmp(argv[0], "./hextofp") == 0) && (argc == 2) &&
            (strlen(argv[1]) == 10)) {

        unsigned long v = strtoul(argv[1], &end, 16);
        if(v == ULONG_MAX || v == ULLONG_MAX || v == 0)
            printf("Invalid value '%s'", argv[1]);
        else {
            float r = *(float*)(&v);
            printf("%s <-> %e\n", argv[1], r);
        }
    }

    else {
        printf("Usage:\tfptohex 5.65311e-4\n");
        printf("\thextofp 0xED1EB612\n");
    }

    return 0;
}
