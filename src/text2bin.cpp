#include<bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
    int freq[256] = {};

    //Explain usage
    if(argc < 3) {
        fprintf(stderr, "Missing argument\n");
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        return 0;
    }
    else if(argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        return 0;
    }

    //Open input file
    FILE *in = fopen(argv[1], "r");
    if(in == NULL) {
        fprintf(stderr, "Could not open '%s'\n", argv[1]);
        return 0;
    }

    //Open output file
    FILE *out = fopen(argv[2], "w");
    if(in == NULL) {
        fprintf(stderr, "Could not open '%s'\n", argv[2]);
        return 0;
    }

    //Convert char to binary
    while(1) {
        unsigned char c = fgetc(in);
        if(feof(in)) break;
        bitset<8> b(c);
        fprintf(out, "%s", b.to_string().c_str());
    }

    fclose(in);
    fclose(out);

    return 0;
}
