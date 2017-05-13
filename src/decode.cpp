#include<bits/stdc++.h>

using namespace std;

//Node struct
struct Node {
    unsigned char c;
    Node *left, *right, *up;
    Node() : c(0), left(NULL), right(NULL), up(NULL) {}
    Node(Node *up) : c(0), left(NULL), right(NULL), up(up) {}
    Node* go_left() {
        if(left == NULL)
            left = new Node(this);
        return left;
    }
    Node* go_right() {
        if(right == NULL)
            right = new Node(this);
        return right;
    }
    Node* go_up(){
        return up;
    }
};

//Build code table
void build_code_map(Node *root, string &s, map<unsigned char, string> &code) {
    if(root == NULL) return;
    else if(root->left == NULL and root->right == NULL)
        code[root->c] = s;
    s.push_back('0');
    build_code_map(root->left, s, code);
    s.pop_back();
    s.push_back('1');
    build_code_map(root->right, s, code);
    s.pop_back();
}

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

    //Build Huffman Tree
    Node *root = new Node;
    Node *aux = root;
    while(aux != NULL) {
        unsigned char c = fgetc(in);
        //Left child
        if(c == '0')
            aux = aux->go_left();
        //Right child
        else if(c == '1')
            aux = aux->go_right();
        //Go up
        else if(c == '*')
            aux = aux->go_up();
        //Leaf node
        else if(c == '.') {
            c = fgetc(in);
            aux->c = c;
        }
    }

#if 0
    string s;
    map<unsigned char, string> code;
    build_code_map(root, s, code);
    for(auto x : code) {
        printf("%c : %s\n", x.first, x.second.c_str());
    }
#endif

    //Decode input
    aux = root;
    while(1) {
        unsigned char c = fgetc(in);
        if(feof(in)) break;
        //Leaf node
        if(c == '0')
            aux = aux->left;
        else if(c == '1')
            aux = aux->right;
        if(aux->left == NULL and aux->right == NULL)
            fputc(aux->c, out), aux=root;
    }

    fclose(in);
    fclose(out);

    return 0;
}
