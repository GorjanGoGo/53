#include <bits/stdc++.h>
using namespace std;

vector<uint32_t> compress(const string &s) {

    unordered_map<string,uint32_t> dict;

    for(int i = 0; i < 256; i++)
        dict[string(1, char(i))] = i;

    string p = "";
    uint32_t code = 256;

    vector<uint32_t> out;

    for(char c : s) {

        string pc = p + c;

        if(dict.count(pc))
            p = pc;
        else {
            out.push_back(dict[p]);
            dict[pc] = code++;
            p = string(1, c);
        }
    }

    if(!p.empty())
        out.push_back(dict[p]);

    return out;
}

int main() {

    ifstream in("Ana Karenina.txt", ios::binary);

    if(!in) {
        cout << "Error: Cannot open input file\n";
        return 1;
    }

    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    if(text.empty()) {
        cout << "Input file empty\n";
        return 1;
    }

    vector<uint32_t> codes = compress(text);

    string key = "secret";

    ofstream out("book.bin", ios::binary);

    if(!out) {
        cout << "Error: Cannot open output file\n";
        return 1;
    }

    for(size_t i = 0; i < codes.size(); i++) {

        uint32_t x = codes[i];

        x ^= key[i % key.size()];

        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    out.close();

    cout << "Compressed and encrypted\n";
}