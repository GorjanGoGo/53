#include <bits/stdc++.h>
using namespace std;

string decompress(const vector<uint32_t> &codes) {

    if(codes.empty())
        return "";

    unordered_map<uint32_t,string> dict;

    for(int i = 0; i < 256; i++)
        dict[i] = string(1, char(i));

    uint32_t code = 256;

    string prev = dict[codes[0]];
    string result = prev;

    for(size_t i = 1; i < codes.size(); i++) {

        string entry;

        if(dict.count(codes[i]))
            entry = dict[codes[i]];
        else
            entry = prev + prev[0];

        result += entry;

        dict[code++] = prev + entry[0];

        prev = entry;
    }

    return result;
}

int main() {

    ifstream in("book.bin", ios::binary);

    if(!in) {
        cout << "Error: Cannot open compressed file\n";
        return 1;
    }

    vector<uint32_t> codes;
    uint32_t x;

    while(in.read(reinterpret_cast<char*>(&x), sizeof(x)))
        codes.push_back(x);

    in.close();

    if(codes.empty()) {
        cout << "Compressed file empty\n";
        return 1;
    }

    string key = "secret";

    for(size_t i = 0; i < codes.size(); i++)
        codes[i] ^= key[i % key.size()];

    string text = decompress(codes);

    ofstream out("output.txt");

    if(!out) {
        cout << "Error: Cannot open output file\n";
        return 1;
    }

    out << text;
    out.close();

    cout << "Decompressed and decrypted\n";
}