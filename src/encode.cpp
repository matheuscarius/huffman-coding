#include<bits/stdc++.h>

using namespace std;

//Node struct
struct Node {
    unsigned char c;
    int f;
    Node *left, *right;
    Node() : c(0), f(0), left(NULL), right(NULL) {}
    Node(unsigned char c, int f): c(c), f(f), left(NULL), right(NULL) {}
    Node(Node* a, Node* b): c(0), f(a->f+b->f), left(a), right(b) {}
};

//Compare function for minheap
struct nodeptrcomp {
    bool operator() (const Node* lhs, const Node* rhs) const {
        return lhs->f > rhs->f;
    }
};

//Print Huffman Tree
void print_tree(Node *root, FILE *out) {
    if(root == NULL) return;
    else if(root->left == NULL and root->right == NULL)
        //'.' indicates a leaf-node, followed by char of leaf
        fputc('.', out), fputc(root->c, out);

    //'0' indicates go to left
    fputc('0', out);
    //go to left child
    print_tree(root->left, out);
    //'*' indicates go up
    fputc('*', out);

    //'1' indicates go to right
    fputc('1', out);
    //go to right child
    print_tree(root->right, out);
    //'*' indicates go up
    fputc('*', out);
}

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

    //Count frequencies
    while(1) {
        unsigned char c = fgetc(in);
        if(feof(in)) break;
        freq[c]++;
    }

    //Create minheap
    priority_queue<Node*, vector<Node*>, nodeptrcomp> pq;

    //Build nodes
    for(int i = 0; i < 256; i++)
        if(freq[i])
            pq.push(new Node(i, freq[i]));
    //Join nodes
    while(pq.size()>1) {
        Node *a = pq.top(); pq.pop();
        Node *b = pq.top(); pq.pop();
        pq.push(new Node(b, a));
    }
    //Extract Huffman Tree
    Node *root = pq.top(); pq.pop();

    //Build code table
    map<unsigned char, string> code;
    string s;
    build_code_map(root, s, code);

#if 0
    for(auto x : code) {
        printf("%c : %s\n", x.first, x.second.c_str());
    }
#endif

    //Write Huffman Tree
    print_tree(root, out);
    //Indicates end of tree
    fputc('*', out);

    //Set FILE pointer to begin
    rewind(in);

    //Encode and write to output
    while(1) {
        unsigned char c = fgetc(in);
        if(feof(in)) break;
        fprintf(out, "%s", code[c].c_str());
    }

    fclose(in);
    fclose(out);

    return 0;
}
