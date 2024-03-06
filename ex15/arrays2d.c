#include <stdio.h>
int main(void){
     //! showMemory(cursors=[a, arrays[0], b, arrays[1], c, arrays[2]], start=65520)
    short a[3] = {234,655, 843};
    short b[2] = {12, 62};
    short c[4] = {3456, 3467, 23, 276};
    short * arrays[3] = {a, b, c};
    * arrays[0] = 5;
    * (arrays[0] + 1) = 6;
    * (arrays[0] + 2) = 7;
    * arrays[1] = 3;
    * (arrays[1] + 1) = 4;
    return 0;
}

// main()
// short a[3] = {5, 6, 7}
// short b[2] = {3, 4}
// short c[4] = {3456, 3467, 23, 276}
// short *arrays[3] = {0xfffa, 0xfff6, 0xffee}