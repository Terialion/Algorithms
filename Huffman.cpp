#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <bitset>


// 定义 Huffman 树节点
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// 比较器，用于优先队列
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// 递归生成 Huffman 编码
void generateCodes(HuffmanNode* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCode) {
    if (!root) {
        return;
    }
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// 释放 Huffman 树节点
void freeTree(HuffmanNode* root) {
    if (!root) { 
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

std::string intToBinaryString(int num, int length) {
    std::string binaryString;
    for (int i = length - 1; i >= 0; --i) {
        binaryString += ((num >> i) & 1) ? '1' : '0';
    }
    return binaryString;
}



int main() {
    system("chcp 65001");
    std::ifstream inputFile("");
    if (!inputFile) {
        std::cerr << "Open error" << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // 统计字符频率
    std::unordered_map<char, int> freq;
    for (char ch : text) {
        if (ch != ' ' && ch != '\n') {
            freq[ch]++;
        }
    }
    

    // 用优先队列构建 Huffman 树
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    for (int i = 1; i < freq.size(); i++) {
        HuffmanNode* z = new HuffmanNode('\0', 0);
        HuffmanNode* left = pq.top(); 
        pq.pop();
        HuffmanNode* right = pq.top(); 
        pq.pop();
        z->left = left;
        z->right = right;
        z->freq = z->left->freq + z->right->freq;
        pq.push(z);
    }
    HuffmanNode* root = pq.top();


    // 生成 Huffman 编码
    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // 编码输入字符串
    std::string encodedString;
    for (char ch : text) {
        if (ch != ' ' && ch != '\n') {
            encodedString += huffmanCode[ch];
        }
    }

    // 计算压缩率
    int num = freq.size();
    int index = 2;
    int length = 1;
    while (1) {
        if (num <= index) {
            break;
        }
        index *= 2;
        length++;
    }
    //算有几个字节
    std::unordered_map<char, std::string> fixedLengthCode;
    int code = 0;
    for (auto pair : freq) {
        fixedLengthCode[pair.first] = intToBinaryString(code, length);
        code++;
    }

    //未编码长度
    std::string fixedLengthString;
    for (char ch : text) {
        if (ch != ' ' && ch != '\n') {
            fixedLengthString += fixedLengthCode[ch];
        }
    }

    double compressionRate = (double)encodedString.length() / fixedLengthString.length() * 100;

    std::cout << "压缩率: " << compressionRate << "%" << std::endl;

    // 释放 Huffman 树节点
    freeTree(root);

    system("pause");
    return 0;
}