/**
 * @file BST.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 2.0
 * @brief Templated BST Binary Search Tree with full set of operations (insert, search, traversal, copy).
 * minimal and completed BST template class
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <stdexcept>

 /**
 * @struct Node
 * @brief Node structure for BST
 *
 * This structure represents each node in a templated binary search tree.
 * It stores the data and pointers to the left and right child.
 *
 * @tparam T Data type stored in each node. Must support comparison operators.
 */
template <typename T>
struct Node {
    T data;     ///< Value stored in this node
    Node* left; ///< Pointer to left child
    Node* right;///< Pointer to right child
};

/**
* @class BST
* @brief Templated Binary Search Tree (BST) implementation.
*
* Provides methods for insertion, searching, copying, and
* three types of traversal using function pointers.
*
* The tree stores values of type T which must implement comparison operators.
* All resources are properly managed for deep copy and destruction.
*
* @author Svetlana Alkhasova
* @version 2.0
* @date 18/07/25
*
* @tparam T Data type stored in BST nodes (must support comparison)
*/
template <typename T>
class BST {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty BST.
     */
    BST();

    /**
     * @brief Destructor
     *
     * Frees all nodes and memory used by BST.
     */
    ~BST();

    /**
     * @brief Copy constructor for deep copy.
     * @param other Another BST of the same type
     *
     * Creates a new BST as a deep copy of another tree.
     */
    BST(const BST<T>& other);

    /**
     * @brief Assignment operator (deep copy/cleanup)
     * @param otherTree BST to assign from.
     * @return Reference to this BST after assignment.
     */
    BST<T>& operator=(const BST<T>& otherTree);

    /**
     * @brief Insert value into BST.
     *
     * Adds a new value to the tree. If the value already exists, it is not inserted again.
     *
     * @param value Value to be inserted.
     */
    void insert(const T& value);

    /**
     * @brief Search for a value in the BST.
     *
     * @param value Value to search for.
     * @return True if found, false otherwise.
     */
    bool search(const T& value) const;

    /**
     * @brief In-order traversal (left, root, right).
     *
     * Calls the given function pointer for each node in sorted order.
     *
     * @param process Function pointer to process each node's data.
     */
    void InOrder(void (*process)(const T&)) const;

    /**
     * @brief Pre-order traversal (root, left, right).
     *
     * Calls the given function pointer for each node in pre-order.
     *
     * @param process Function pointer to process each node's data.
     */
    void PreOrder(void (*process)(const T&)) const;

    /**
     * @brief Post-order traversal (left, right, root).
     *
     * Calls the given function pointer for each node in post-order.
     *
     * @param process Function pointer to process each node's data.
     */
    void PostOrder(void (*process)(const T&)) const;

private:
    Node<T>* root; ///< Root pointer

    /**
     * @brief Helper to deep copy a subtree.
     *
     * @param node Subtree to copy.
     * @return Pointer to new subtree.
     */
    Node<T>* copy(Node<T>* node);

    /**
     * @brief Helper for recursive destruction.
     * @param node Subtree to destroy.
     */
    void destroy(Node<T>* node);

    /**
     * @brief Helper for recursive node insertion.
     * @param node Subtree to insert into.
     * @param value Value to insert.
     * @return Updated subtree pointer.
     */
    Node<T>* insert(Node<T>* node, const T& value);

    /**
     * @brief Helper for recursive search in subtree.
     * @param node Subtree to search.
     * @param value Value to search for.
     * @return True if value is found, else false.
     */
    bool search(Node<T>* node, const T& value) const;

    /**
     * @brief Helper for in-order traversal in subtree.
     * @param node Subtree to process.
     * @param process Function pointer for processing node data.
     */
    void InOrder(Node<T>* node, void (*process)(const T&)) const;

    /**
     * @brief Helper for pre-order traversal in subtree.
     * @param node Subtree to process.
     * @param process Function pointer for processing node data.
     */
    void PreOrder(Node<T>* node, void (*process)(const T&)) const;

    /**
     * @brief Helper for post-order traversal in subtree.
     * @param node Subtree to process.
     * @param process Function pointer for processing node data.
     */
    void PostOrder(Node<T>* node, void (*process)(const T&)) const;
};

// IMPLEMENTATION

template <typename T>
BST<T>::BST() : root(NULL) {}

template <typename T>
BST<T>::~BST() {
    destroy(root);
    root = NULL;
}

template <typename T>
BST<T>::BST(const BST<T>& other) {
    root = copy(other.root);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& otherTree) {
    if (this != &otherTree) {
        destroy(root);
        root = copy(otherTree.root);
    }
    return *this;
}

template <typename T>
Node<T>* BST<T>::copy(Node<T>* node) {
    if (!node) return NULL;
    Node<T>* newNode = new Node<T>;
    newNode->data = node->data;
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
}

template <typename T>
void BST<T>::insert(const T& value) {
    root = insert(root, value);
}

template <typename T>
Node<T>* BST<T>::insert(Node<T>* node, const T& value) {
    if (!node) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    return node;
}

template <typename T>
bool BST<T>::search(const T& value) const {
    return search(root, value);
}

template <typename T>
bool BST<T>::search(Node<T>* node, const T& value) const {
    if (!node) return false;
    if (node->data == value) return true;
    if (value < node->data)
        return search(node->left, value);
    return search(node->right, value);
}

template <typename T>
void BST<T>::InOrder(void (*process)(const T&)) const {
    InOrder(root, process);
}

template <typename T>
void BST<T>::InOrder(Node<T>* node, void (*process)(const T&)) const {
    if (!node) return;
    InOrder(node->left, process);
    process(node->data);
    InOrder(node->right, process);
}

template <typename T>
void BST<T>::PreOrder(void (*process)(const T&)) const {
    PreOrder(root, process);
}

template <typename T>
void BST<T>::PreOrder(Node<T>* node, void (*process)(const T&)) const {
    if (!node) return;
    process(node->data);
    PreOrder(node->left, process);
    PreOrder(node->right, process);
}

template <typename T>
void BST<T>::PostOrder(void (*process)(const T&)) const {
    PostOrder(root, process);
}

template <typename T>
void BST<T>::PostOrder(Node<T>* node, void (*process)(const T&)) const {
    if (!node) return;
    PostOrder(node->left, process);
    PostOrder(node->right, process);
    process(node->data);
}

template <typename T>
void BST<T>::destroy(Node<T>* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = NULL;
}

#endif // BST_H
