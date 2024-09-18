class Trie {

    struct TrieNode {
        struct TrieNode *child[26];
        bool isEnd;
        TrieNode() {
            isEnd = false;
            for (int i = 0; i < 26; i++)
                child[i] = NULL;
        }
    };

    TrieNode *head;

public:
    Trie() {
        head = new TrieNode();
    }

    void insert(string word) {
        TrieNode *curr = head;
        for (char &c : word) {
            if (curr->child[c - 'a'] == NULL)
                curr->child[c - 'a'] = new TrieNode();
            curr = curr->child[c - 'a'];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        TrieNode *curr = head;
        for (char &c : word) {
            if (curr->child[c - 'a'] == NULL)
                return false;
            curr = curr->child[c - 'a'];
        }
        return curr->isEnd;
    }
};