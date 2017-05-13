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
void print_tree(Node *root, string& s) {
    if(root == NULL) return;
    else if(root->left == NULL and root->right == NULL)
        cout << root->c << " : " << root->f << " : " << s << endl;
    s.push_back('0');
    print_tree(root->left, s);
    s.pop_back();
    s.push_back('1');
    print_tree(root->right, s);
    s.pop_back();
}

//Build code table
void build_code_map(Node *root, string &s, map<unsigned char, string> &code) {
    if(root == NULL) return;
    else if(root->left == NULL and root->right == NULL)
        code[root->c] = s;
    s.push_back('0');
    print_tree(root->left, s);
    s.pop_back();
    s.push_back('1');
    print_tree(root->right, s);
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

    //Set FILE pointer to begin
    rewind(in);

}
