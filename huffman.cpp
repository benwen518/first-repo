#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// 定义哈夫曼树节点结构体
struct HuffmanNode {
    char data; // 字符
    int freq; // 出现频率
    HuffmanNode* left; // 左子节点指针
    HuffmanNode* right; // 右子节点指针
    HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// 定义比较器类，用于优先队列的排序
class CompareNodes {
public:
    bool operator()(HuffmanNode* a, HuffmanNode* b) const {
        return a->freq > b->freq;
    }
};

// 生成哈夫曼树
HuffmanNode* buildHuffmanTree(string str) {
    unordered_map<char, int> freqMap;
    for (char c : str) {
        freqMap[c]++;
    }
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (auto p : freqMap) {
        pq.push(new HuffmanNode(p.first, p.second));
    }
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* parent = new HuffmanNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// 生成哈夫曼编码表
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& codes) {
    if (!root) {
        return;
    }
    if (root->data != '$') {
        codes[root->data] = code;
    }
    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

// 编码字符串
string encodeString(string str, unordered_map<char, string>& codes) {
    string encodedStr = "";
    for (char c : str) {
        encodedStr += codes[c];
    }
    return encodedStr;
}

// 解码字符串
string decodeString(string encodedStr, HuffmanNode* root) {
    string decodedStr = "";
    HuffmanNode* curr = root;
    for (char c : encodedStr) {
        if (c == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (!curr->left && !curr->right) {
            decodedStr += curr->data;
            curr = root;
        }
    }
    return decodedStr;
}

int main() {
    string str = "hello world";
    HuffmanNode* root = buildHuffmanTree(str);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);
    string encodedStr = encodeString(str, codes);
    string decodedStr = decodeString(encodedStr, root);
    cout << "原字符串：" << str << endl;
    cout << "编码后字符串：" << encodedStr << endl;
    cout << "解码后字符串：" << decodedStr << endl;
    return 0;
}