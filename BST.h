#pragma once
#include <utility>
#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>

using Key = uint32_t;
using Value = double;
enum color
{
    BLACK = 0,
    RED = 1
};

class BinarySearchTree 
{
    //Node
    struct Node 
    {
    public:
        Node() = default;
        Node(Key key, Value value, 
             Node* parent = nullptr, Node* left = nullptr, 
             Node* right = nullptr);
        Node(const Node &other);

        bool operator==(const Node &other) const;

        size_t get_height(Node* node);
        void output_tree(Node* node);

        std::pair<Key, Value> keyValuePair; 
        bool color = RED;
        Node* parent = nullptr;
        Node* left = nullptr;   
        Node* right = nullptr;  
    };
    Node* overMax = new Node(0, 0, nullptr, _root, nullptr);
    Node* nill = new Node(0, 0, nullptr, nullptr, overMax);


    //Friend
    bool NodeExists(Node* node);
    size_t ChildCount(Node* node);
    Node* getChildOrMock(Node* node);
    Node* transplantNode(Node* ToNode, Node* FromNode);

    Node* Find(const Key& key);
    Node* findMin(Node* start);

    void NodeDelete(Node* node);
    Node* copyTree(Node* node);


    //Rebalancing
    void leftrotate(Node* node);
    void rightrotate(Node* node);
    void balanceTree(Node* node);
    void fixAfterErase(Node* node);

public:
    //Default constructor
    BinarySearchTree() = default;


    //Semantics copy
    explicit BinarySearchTree(const BinarySearchTree &other);
    BinarySearchTree &operator=(const BinarySearchTree &other);


    //Semantics move
    explicit BinarySearchTree(BinarySearchTree &&other) noexcept;
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;


    //Destructor
    ~BinarySearchTree();


    //Iterator and Const Iterator
    class Iterator 
    {
    public:
        explicit Iterator(Node *node);
        Node* getnode();

        std::pair<Key, Value> &operator*();
        const std::pair<Key, Value> &operator*() const;

        std::pair<Key, Value> *operator->();
        const std::pair<Key, Value> *operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        Node *_node;
    };
    class ConstIterator 
    {
    public:
        explicit ConstIterator(const Node *node);
        const Node* getnode();

        const std::pair<Key, Value> &operator*() const;
        const std::pair<Key, Value> *operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator &other) const;
        bool operator!=(const ConstIterator &other) const;

    private:
        const Node* _node;
    };


    //Find
    Iterator find(const Key& key) const;
    ConstIterator find(const Key& key);

    ConstIterator min() const;
    ConstIterator max() const;


    //Begin and End
    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    void insert(const Key& key, const Value& value);
    void erase(const Key& key);


    //Out
    size_t size() const;
    void output_tree();
	size_t max_height() const;

private:
    size_t _size = 0;
    Node *_root = nullptr;
};
