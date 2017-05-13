# Huffman Coding
Implementation of Huffman Coding for college project

## Installation

### 1) Get source code
    git clone https://github.com/matheuscarius/huffman-coding.git
    cd huffman-coding

### 2) Make project
    make

## Usage

### 1) Encoding

    bin/encode <input-file> <output-file>

### 2) Decoding

    bin/decode <input-file> <output-file>

### 3) Binary Encoding

    bin/text2bin <input-file> <output-file>

### Example

You have some sample files in `ex/` folder

    bin/encode ex/shakespeare.txt encoded
    bin/decode encoded decoded
    diff decoded ex/shakespeare.txt

`diff` should give an empty output, as expected.

To measure encoding efficiency you can do

    bin/text2bin ex/shakespeare.txt binary-encoded
    ls -sh

You can see that 'encoded' size is less than 'binary-encoded' size.

## Aditional information
This is not a efficient Huffmann Coding because it outputs characters '0' and '1', not bits '0' and '1'. To avoid working with bits and yet being able to measure its efficiency, I included encoding to binary characters to compare file sizes.
