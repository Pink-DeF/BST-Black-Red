#include "BST.h"

//Node
BinarySearchTree::Node::Node(Key key, Value value,
    Node* parent, Node* left, Node* right)
    : parent(parent), left(left), right(right)
{
    if (!parent) { color = BLACK; }
    keyValuePair = std::make_pair (key, value);
}
BinarySearchTree::Node::Node(const Node& other)
{
    if (*this == other) { return; }
    parent = other.parent;
    left = other.left;
    right = other.right;

    keyValuePair = other.keyValuePair;
}

bool BinarySearchTree::Node::operator==(const Node& other) const
{
    return keyValuePair.first == other.keyValuePair.first ? 1 : 0;
}

void BinarySearchTree::Node::output_node_tree() const
{
    if (this == nullptr)
    {
        std::cout << this;
        return;
    }
    std::cout << "      " << keyValuePair.first << "        " << std::endl;
    if (left)
    {
        std::cout << left->keyValuePair.first << "                ";
    }
    else
    {
        std::cout << "null" << "                ";
    }
    if (right)
    {
        std::cout << right->keyValuePair.first << "                " << std::endl;
    }
    else
    {
        std::cout << "null" << "                ";
    }
    std::cout << std::endl;
}


//Rebalancing
void BinarySearchTree::leftrotate(Node* node)
{
    node->right->parent = node->parent;
    node->parent = node->right;
    node->right = node->right->left;
    node->parent->left = nill;
}
void BinarySearchTree::rightrotate(Node* node)
{
    node->left->parent = node->parent;
    node->parent = node->left;
    node->left =  node->left->right;
    node->parent->right = nill;
}
void BinarySearchTree::balanceTree(Node* node)
{
    Node* uncle;
    while (node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;
            if (uncle)
            {
                if (uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    leftrotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightrotate(node);
            }
        }
        else
        {
            uncle = node->parent->parent->left;
            if (uncle)
            {
                if (uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rightrotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftrotate(node);
            }
        }
    }
    _root->color = BLACK;
}
void BinarySearchTree::fixAfterErase(BinarySearchTree::Node* node)
{
    while (node != _root && node->color == BLACK)
    {
        BinarySearchTree::Node* brother;
        if (node == node->parent->left)
        {
            brother = node->parent->right;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                leftrotate(node->parent);
                brother = node->parent->right;
            }

            if (brother->left->color == BLACK && brother->right->color ==BLACK)
            {
                brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother->right->color == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rightrotate(brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                leftrotate(node->parent);
                node = _root;
            }
        }
        else
        {
            brother = node->parent->left;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                rightrotate(node->parent);
                brother = node->parent->left;
            }

            if (brother->left->color == BLACK && brother->right->color == BLACK)
            {
                rightrotate(node->parent);
                brother = node->parent->left;
            }
            else
            {
                if (brother->right->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    leftrotate(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                rightrotate(node->parent);
                node = _root;
            }
        }
    }
    node->color = BLACK;
}


//Friend
bool BinarySearchTree::NodeExists(Node* node)
{
    return node != nill;
}
size_t BinarySearchTree::ChildCount(BinarySearchTree::Node* node)
{
    size_t count = 0;
    if (NodeExists(node->left)) { count++; }
    if (NodeExists(node->right)) { count++; }
    return count;
}
BinarySearchTree::Node* BinarySearchTree::getChildOrMock(BinarySearchTree::Node* node)
{
    return NodeExists(node->left) ? node->left : node->right;
}
BinarySearchTree::Node* BinarySearchTree::transplantNode(BinarySearchTree::Node* ToNode, BinarySearchTree::Node* FromNode)
{
    if (ToNode == _root) { _root = FromNode; }
    else if (ToNode == ToNode->parent->left) { ToNode->parent->left = FromNode; }
    else ToNode->parent->right = FromNode;
    FromNode->parent = ToNode->parent;
}


//Iterator
BinarySearchTree::Iterator::Iterator(Node* node): _node(node){}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*()
{
    return _node->keyValuePair;
}
const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const
{
    return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->()
{
    return &_node->keyValuePair;
}
const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const
{
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++()
{
    if (_node->parent == nullptr) { return *this; }

    // 1. Если у текущего узла есть правое поддерево
    if (_node->right->parent != nullptr)
    {
        _node = _node->right;
        while (_node->left->parent != nullptr){ _node = _node->left; }
    }
    else
    {
        // 2. Если правого поддерева нет, поднимаемся к родителю
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->right)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return *this;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int)
{
    if (_node->parent == nullptr) { return *this; }

    // 1. Если у текущего узла есть правое поддерево
    if (_node->right->parent != nullptr)
    {
        _node = _node->right;
        while (_node->left->parent != nullptr) { _node = _node->left; }
    }
    else
    {
        // 2. Если правого поддерева нет, поднимаемся к родителю
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->right)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return Iterator(temp);
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--()
{
    if (_node->parent == nullptr) { return *this; }

    // 1. Если у узла есть левое поддерево
    if (_node->left->parent != nullptr)
    {
        _node = _node->left;
        while (_node->right->parent != nullptr) { _node = _node->right; }
    }
    else
    {
        // 2. Если левого поддерева нет
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->left)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return *this;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int)
{
    if (_node->parent == nullptr) { return *this; }
    Node* temp = _node;

    // 1. Если у узла есть левое поддерево
    if (_node->left->parent != nullptr)
    {
        _node = _node->left;
        while (_node->right->parent != nullptr) { _node = _node->right; }
    }
    else
    {
        // 2. Если левого поддерева нет
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->left)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return Iterator(temp);
}

bool BinarySearchTree::Iterator::operator==(const Iterator& other) const
{
    return _node == other._node;
}
bool BinarySearchTree::Iterator::operator!=(const Iterator& other) const
{
    return _node != other._node;
}


//Const Iterator
explicit BinarySearchTree::ConstIterator::ConstIterator(const Node* node): _node(node){}

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const
{
    return _node->keyValuePair;
}
const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const
{
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
    if (_node->parent == nullptr) { return *this; }

    // 1. Если у текущего узла есть правое поддерево
    if (_node->right->parent != nullptr)
    {
        _node = _node->right;
        while (_node->left->parent != nullptr) { _node = _node->left; }
    }
    else
    {
        // 2. Если правого поддерева нет, поднимаемся к родителю
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->right)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return *this;
}
BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int)
{
    if (_node->parent == nullptr) { return *this; }
    const Node* temp = _node;

    // 1. Если у текущего узла есть правое поддерево
    if (_node->right->parent != nullptr)
    {
        _node = _node->right;
        while (_node->left->parent != nullptr) { _node = _node->left; }
    }
    else
    {
        // 2. Если правого поддерева нет, поднимаемся к родителю
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->right)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return ConstIterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--()
{
    if (_node->parent == nullptr) { return *this; }

    // 1. Если у узла есть левое поддерево
    if (_node->left->parent != nullptr)
    {
        _node = _node->left;
        while (_node->right->parent != nullptr) { _node = _node->right; }
    }
    else
    {
        // 2. Если левого поддерева нет
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->left)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return *this;
}
BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
    if (_node->parent == nullptr) { return *this; }
    const Node* temp = _node;

    // 1. Если у узла есть левое поддерево
    if (_node->left->parent != nullptr)
    {
        _node = _node->left;
        while (_node->right->parent != nullptr) { _node = _node->right; }
    }
    else
    {
        // 2. Если левого поддерева нет
        Node* parent = _node->parent;
        while (parent->parent != nullptr && _node == parent->left)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }

    return ConstIterator(temp);
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator& other) const
{
    return _node == other._node;
}
bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator& other) const
{
    return _node != other._node;
}

//Find
BinarySearchTree::ConstIterator BinarySearchTree::min() const
{

}
BinarySearchTree::ConstIterator BinarySearchTree::max() const
{

}

BinarySearchTree::Iterator BinarySearchTree::find(const Key& key) const
{
    Iterator node(_root);

    while ((*node).first != key)
    {
        if ((*node).first > key)
        {
            node--;
        }
        else
        {
            node++;
        }
    }

    return node;
}
BinarySearchTree::ConstIterator BinarySearchTree::find(const Key& key)
{
    ConstIterator node(_root);

    while ((*node).first != key)
    {
        if ((*node).first > key)
        {
            node--;
        }
        else
        {
            node++;
        }
    }

    return node;
}

//Tree main
void BinarySearchTree::insert(const Key& key, const Value& value)
{
    Node location = *_root;
    std::pair<Node*, bool> direction;

    if (key < location.keyValuePair.first) { direction = std::make_pair(location.left, 1); }
    else { direction = std::make_pair(location.right, 0); }

    while (direction.first != nill)
    {
        location = *direction.first;

        if (key < location.keyValuePair.first) { direction = { location.left, 1 }; }
        else { direction = { location.right, 0 }; }
    }

    Node* nNode = new Node(key, value, &location, nill, nill);
    if (direction.second)
    {
        location.left = nNode;
    }
    else
    {
        location.right = nNode;
    }

    balanceTree(nNode);
    _size++;
}
void BinarySearchTree::erase(const Key& key)
{
    Node* DeleteNode = find(key);
    bool DeleteColor = DeleteNode->color;
    Node* child;

    if (ChildCount(DeleteNode) < 2)
    {
        child = getChildOrMock(DeleteNode);
        transplantNode(DeleteNode, child);
    }
    else
    {
        Node* minNode = findMin(DeleteNode->right);
        DeleteNode->keyValuePair = minNode->keyValuePair;
        DeleteNode->color = minNode->color;
        child = getChildOrMock(minNode);
        transplantNode(minNode, child);
    }
    if (DeleteColor == BLACK) { fixAfterErase(child); }
}