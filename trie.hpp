#include <unordered_map>
#include <memory>

class Node {

    public:
    /* attributes */
    bool flag;
    std::unordered_map<char, std::shared_ptr<Node>> children;

    /* methods */
    void setFlag(bool _flag) {
        flag = _flag;
    }

    bool &getFlag() {
        return flag;
    }


};

class NodeChar : public Node {

    std::unordered_map<char, std::shared_ptr<Node>> children;

    void setChildren(std::unordered_map<char, std::shared_ptr<Node>> _children) {
        children = _children;
    }

    std::unordered_map<char, std::shared_ptr<Node>> &getChildren() {
        return children;
    }
};

std::shared_ptr<Node> createNode(void) { 
    std::shared_ptr<Node> node(new Node); 
    node->flag = false; 
    return node; 
} 


void insert(std::shared_ptr<Node> root, std::string& word) { 

    if (root == nullptr) {
        root = createNode();
    }

    std::shared_ptr<Node> aux = root;

    for (char const &c: word) {
        if (aux->children.find(c) == aux->children.end()) {
            aux->children[c] = createNode(); 
        }
        aux = aux->children[c];
    } 
    aux->flag = true;
}


void insertRFC(std::shared_ptr<Node> root, std::string& word) { }


bool find(std::shared_ptr<Node> root, std::string word) { 

    if (root == nullptr) {
        return false;
    }

    std::shared_ptr<Node> aux = root;

    for (char const &c: word) {

        aux = aux->children[c];

        if (aux == nullptr) {
            return false;
        }

    } 
    return aux->flag;
}
