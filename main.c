#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* transfer function */
int transfer(int c) {
    static int mode = 0;

    /* check end of file*/
    if (c == EOF) { return 0; }

    switch (mode) {
    case 0: /* normal mord */
        /* enter string mode */
        if (c == '\"') {
            mode = 1;
            return 2;
        }

        /* end of field */
        if (c == ',') { c = '\0'; }

        /* end of record */
        else if (c == '\n') { c = '\f'; }

        /* default: */
        break;
    case 1: /* string mode */
        /* enter check string end mode */
        if (c == '\"') {
            mode = 2;
            return 3;
        }

        /* default: */
        break;
    case 2: /* check string end mode */
        /* escaped double quotation */
        if (c == '\"') { mode = 1; }

        /* end of string mode */
        else if (c == ',') {
            c    = '\0';
            mode = 0;
        }

        /* error */
        else { exit(3); }

        /* default: */
        break;
    }

    /* print value */
    fprintf(stdout, "%c", c);
    return 1;
}

int main() {
    int        i;
    int        c;
    char       val[4]  = {};
    const char cval[4] = "\xEF\xBB\xBF";

    /* BOM detecting */
    for (i = 0; i < 3; ++i) {
        c = getchar();
        if (c == EOF) exit(1);
        val[i] = (char)c;
    }
    if (strcmp(val, cval) != 0) {
        /* roll back if not BOM */
        for (i = 0; i < 3; ++i) {
            if (!transfer(val[i])) { exit(0); }
        }
    }

    /* main loop */
    while (transfer(getchar()))
        ;
    return 0;
}

