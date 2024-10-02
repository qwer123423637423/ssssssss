#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TrieNode {
    char c;
    bool isWord;
    vector<TrieNode*> children;

    TrieNode(char c) : c(c), isWord(false) {}
};

class Trie {
public:
    Trie() : root(new TrieNode('\0')) {}

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            bool found = false;
            for (TrieNode* child : current->children) {
                if (child->c == c) {
                    current = child;
                    found = true;
                    break;
                }
            }
            if (!found) {
                current->children.push_back(new TrieNode(c));
                current = current->children.back();
            }
        }
        current->isWord = true;
    }

    vector<string> suggestCompletions(const string& prefix) {
        vector<string> completions;
        TrieNode* current = root;
        for (char c : prefix) {
            bool found = false;
            for (TrieNode* child : current->children) {
                if (child->c == c) {
                    current = child;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return completions;
            }
        }
        collectCompletions(current, prefix, completions);
        return completions;
    }

private:
    TrieNode* root;

    void collectCompletions(TrieNode* node, const string& prefix, vector<string>& completions) {
        if (node->isWord) {
            completions.push_back(prefix);
        }
        for (TrieNode* child : node->children) {
            collectCompletions(child, prefix + child->c, completions);
        }
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");
    trie.insert("appetite");
    trie.insert("application");

    string input;
    while (true) {
        cout << "Введите слово: ";
        cin >> input;
        vector<string> completions = trie.suggestCompletions(input);
        for (const string& completion : completions) {
            cout << completion << " ";
        }
        cout << endl;
    }

    return 0;
}