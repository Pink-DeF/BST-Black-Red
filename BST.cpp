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
    if (keyValuePair.first == other.keyValuePair.first) { return 1; }
    return 0;
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

BinarySearchTree::Node* BinarySearchTree::Node::find(Key key)
{
    Node* temp = this;
    while (temp->keyValuePair.first != key)
    {
        if (key > temp->keyValuePair.first)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    return temp;
}
BinarySearchTree::Node* BinarySearchTree::Node::find_min()
{
    Node* temp = this;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp;
}
BinarySearchTree::Node* BinarySearchTree::Node::find_max()
{
    Node* temp = this;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }
    return temp;
}

void BinarySearchTree::Node::insert(const Key& key, const Value& value)
{
    Node location = *this;
    std::pair<Node*, bool> direction;

    if (key < location.keyValuePair.first) { direction = std::make_pair(location.left, 1); }
    else { direction = std::make_pair(location.right, 0); }

    while (direction.first != nullptr)
    {
        location = *direction.first;

        if (key < location.keyValuePair.first) { direction = { location.left, 1 }; }
        else { direction = { location.right, 0 }; }
    }

    if (direction.second)
    {
        location.left = new Node(key, value, &location, nullptr, nullptr);
    }
    else
    {
        location.right = new Node(key, value, &location, nullptr, nullptr);
    }

    return;
}
void BinarySearchTree::Node::erase(const Key& key)
{
    Node* find_node = this->find(key);
    Node* parent_find_node = find_node->parent;
    Node* temp;
    Node* temp2;
    if (find_node == nullptr)
    {
        return;
    }
    //удаление узла, у которого вообще нет наследников
    if ((find_node->left == nullptr) && (find_node->right == nullptr))
    {
        if (key >= parent_find_node->keyValuePair.first)
        {
            parent_find_node->right = nullptr;
        }
        else
        {
            parent_find_node->left = nullptr;
        }
    }
    //удаление узла, у которого есть 1 наследник
    else if ((find_node->left == nullptr) + (find_node->right == nullptr) == 1)
    {
        if (find_node->right != nullptr)
        {
            temp = find_node->right;
        }
        else
        {
            temp = find_node->left;
        }
        if (key >= parent_find_node->keyValuePair.first)
        {
            parent_find_node->right = temp;
        }
        else
        {
            parent_find_node->left = temp;
        }
    }
    //удаление узла, у которого 2 наследника
    else
    {
        temp = find_node->right; //правая часть удаляемого узла
        temp2 = find_node->left; //левая часть удаляемого узла
        Node* temp_min = temp->find_min();
        temp_min->left = temp2;
        if (key >= parent_find_node->keyValuePair.first)
        {
            parent_find_node->right = temp;
        }
        else
        {
            parent_find_node->left = temp;
        }
    }
    delete find_node;
}

//Rebalancing
void BinarySearchTree::leftrotate(Node* node)
{

}
void BinarySearchTree::rightrotate(Node* node)
{

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

}
BinarySearchTree::Node* BinarySearchTree::transplantNode(BinarySearchTree::Node* ToNode, BinarySearchTree::Node* FromNode)
{

}

//Tree main
void BinarySearchTree::insert(const Key& key, const Value& value)
{
    if (!_root) { _root = new Node(key, value, nullptr, nill, nill); return; }

    Node location = *_root;
    std::pair<Node*, bool> direction;

    if (key < location.keyValuePair.first) { direction = std::make_pair(location.left, 1); }
    else { direction = std::make_pair(location.right, 0); }

    while (direction.first != nullptr)
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

    }
    else
    {
        Node* minNode = find_min(DeleteNode->right);
        DeleteNode->keyValuePair = minNode->keyValuePair;
        DeleteNode->color = minNode->color;
        child = getChildOrMock(minNode);
        transplantNode(minNode, child);
    }
    if(DeleteColor == BLACK){}
}
