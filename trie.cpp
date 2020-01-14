#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "trie.hpp"

namespace py = pybind11;

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
