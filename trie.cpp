#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <unordered_map>

namespace py = pybind11;

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

PYBIND11_MODULE(trie, m) {
    m.doc() = "Trie Tree";
    m.def("insert", &insert, "A function to insert new word");
    m.def("create_node", &createNode, "A function to create a new node");
    m.def("find", &find, "A function to check if some word is stored in the trie");

    py::class_<Node, std::shared_ptr<Node>>(m, "node")
        .def(py::init<>())
        .def_readwrite("flag", &Node::flag)
        .def_readwrite("children", &Node::children)
        .def(py::pickle(
            // __getstate__
            [](const Node &p) {
                return py::make_tuple(p.flag, p.children);
            },
            // __setstate__, rebuild the tree
            [](py::tuple t) {
                std::shared_ptr<Node> root(new Node);
                root->setFlag(t[0].cast<bool>());
                root->children = t[1].cast<std::unordered_map<char, std::shared_ptr<Node>>>();
                return root;
            }
        ));
}
