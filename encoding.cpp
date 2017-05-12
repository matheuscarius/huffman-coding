#include<bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
    int freq[256] = {};

    //Explain usage
    if(argc == 1) {
        fprintf(stderr, "Missing argument\n");
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 0;
    }
    else if(argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 0;
    }

    //Open file
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        fprintf(stderr, "Could not open '%s'\n", argv[1]);
        return 0;
    }

    //Count frequencies
    while(1) {
        unsigned char c = fgetc(f);
        if(feof(f)) break;
        freq[c]++;
    }

}
