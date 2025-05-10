#pragma once
#include <utility>
#include <cstdint>
#include <string>
#include <iostream>

using Key = uint32_t;
using Value = double;
enum color
{
    BLACK = 0,
    RED = 1
};

class BinarySearchTree 
{

    struct Node 
    {
    public:
        Node() = default;
        Node(Key key, Value value, 
             Node* parent = nullptr, Node* left = nullptr, 
             Node* right = nullptr);
        Node(const Node &other);
        bool operator==(const Node &other) const;

        void output_node_tree() const;

        void insert(const Key &key, const Value &value);
        void erase(const Key &key);

        std::pair<Key, Value> keyValuePair; 
        bool color = RED;
        Node* parent = nullptr;
        Node* left = nullptr;   
        Node* right = nullptr;  
    };
    Node* nill = new Node();

    //Rebalancing
    void leftrotate(Node* node);
    void rightrotate(Node* node);
    void balanceTree(Node* node);

    //Friend
    bool NodeExists(Node* node);
    size_t ChildCount(Node* node);
    Node* getChildOrMock(Node* node);
    Node* transplantNode(Node* ToNode, Node* FromNode);
    void fixAfterErase(Node* node);
public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;
    //! Конструктор копирования
    explicit BinarySearchTree(const BinarySearchTree &other);
    //! Оператор присваивания копированием
    BinarySearchTree &operator=(const BinarySearchTree &other);
    //! Конструктор перемещения
    explicit BinarySearchTree(BinarySearchTree &&other) noexcept;
    //! Оператор присваивания перемещением
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
    //! Деструктор
    ~BinarySearchTree();

    //! \brief Итератор бинарного дерева поиска
    //! \note Обходит дерево последовательно от узла с меньшим ключом к узлу с большим 
    class Iterator 
    {
    public:
        explicit Iterator(Node *node);

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

        const std::pair<Key, Value> &operator*() const;
        const std::pair<Key, Value> *operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator &other) const;
        bool operator!=(const ConstIterator &other) const;

    private:
        const Node *_node;
    };

    void insert(const Key &key, const Value &value);
    void erase(const Key &key);

    ConstIterator find(const Key& key) const;
    Iterator find(const Key& key);

    /*!***********************************************************
    Найти все элементы, у которых ключ равен key:
      - первый итератор пары - первый элемент в дереве, равный key
      - второй итератор пары - первый элемент в дереве больший, чем key
     
    [pair.first, pair.second) - полуинтервал, содержащий все 
    элементы с ключем key
    **************************************************************/
    std::pair<Iterator, Iterator> equalRange(const Key &key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key &key) const;
    
    //! Получить итератор на элемент с наименьшим ключем в дереве
    ConstIterator min() const;
    //! Получить итератор на элемент с наибольшим ключем в дереве
    ConstIterator max() const;
    //! Получить итератор на элемент с ключем key с наименьшим значением 
    ConstIterator min(const Key &key) const;
    //! Получить итератор на элемент с ключем key с наибольшим значением
    ConstIterator max(const Key &key) const;

    //! Получить итератор на первый элемент дерева (элемент с наименьшим key)
    Iterator begin();
    //! Получить итератор на элемент, следующий за последним элементом дерева
    //! \note Т.е. tree.end()-- == tree.max()
    Iterator end();

    //! Получить константный итератор на начало
    ConstIterator cbegin() const;
    //! Получить константный итератор на конец
    ConstIterator cend() const;

    //! Получить размер дерева
    size_t size() const;
    //! Вывести дерево в консоль
    void output_tree();
	//! Получить максимальную высоту в дереве
	size_t max_height() const;

private:
    size_t _size = 0;
    Node *_root = nullptr;
};
