#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

// ��������� ��� ������������� ���� � ������ ��������
struct HuffmanNode {
    char data; // ������
    int frequency; // �������
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

// ������� ��� ��������� ����� ������������ ������� �� ������ �������
struct Compare {
    bool operator() (HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// ������� ��� ���������� ������ �������� � �������� ��������� ����
HuffmanNode* buildHuffmanTree(map<char, int> frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto entry : frequencies) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

// ������� ��� ���������� ����� �������� � ���������� �� � map
void generateHuffmanCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    setlocale(LC_ALL,"rus");
    map<char, int> frequencies;
    string inputString = "Hello, World!";
    cout << inputString << endl;
    // ���������� ������ �������� �� ������� ������
    for (char c : inputString) {
        frequencies[c]++;
    }

    // ���������� ������ ��������
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // ��������� ����� �������� ��� ��������
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // ����� �������� � �� ����� ��������
    cout << "������\t�������\t��� ��������" << endl;
    for (auto entry : huffmanCodes) {
        cout << entry.first << "\t" << frequencies[entry.first] << "\t" << entry.second << endl;
    }

    return 0;
}