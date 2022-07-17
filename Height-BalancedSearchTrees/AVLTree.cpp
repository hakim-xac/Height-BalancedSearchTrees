#include "AVLTree.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>


namespace KHAS {

    void AVLTree::deleteTree(Node* root)
    {
        if (root) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }

    std::stringstream AVLTree::readTree(const Node* const root)
    {
        if (!root) return std::stringstream{};
        std::stringstream ss;
        ss << readTree(root->left).str();
        ss << root->data << " ";
        ss << readTree(root->right).str();
        return ss;
    }

    int AVLTree::sizeTree(const Node* const root)
    {
        // если Node == nullptr
        if (!root) return 0;
        // иначе 1 + размер(лева€ Node) + размер(права€ Node)
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int AVLTree::heightTree(const Node* const root)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // определ€ем высоту левого дерева
        int left_height{ heightTree(root->left) };
        // определ€ем высоту правого дерева
        int right_height{ heightTree(root->right) };

        // возвращаем большую высоту из левого и правого дерева и добавл€ем текущую, т.е. +1
        return (left_height > right_height ? left_height : right_height) + 1;		
    }

    int AVLTree::middleHeightTree(const Node* const root, int level)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // возвращаем среднюю высоту левого и правого дерева мен€ем уровень на +1
        return level 
            + middleHeightTree(root->left, level + 1)
            + middleHeightTree(root->right, level + 1);
    }

    long long AVLTree::hashTree(const Node* const root)
    {
        // если Node == nullptr  то возвращаем 0.
        if (!root) return 0;

        using out_type = long long;

        // возвращаем хеш-сумму левого + хеш-сумму правого дерева + данные
        return (
            static_cast<out_type>(root->data)
            + hashTree(root->left)
            + hashTree(root->right) );

    }

    bool AVLTree::isSearchTree(const Node* const root)
    {
        if(root && (
            (root->left && (root->data <= root->left->data || isSearchTree(root->left)))
            || (root->right && (root->data >= root->right->data || !isSearchTree(root->right)))
            )){
            return false;
        }
        return true;
    }

    bool AVLTree::toAVL()
    {
        if (vec_buffer_.size() == 0) return false;

        // добавл€ем поочередно все элементы массива в дерево 
        for (auto&& it: vec_buffer_) {
            insert(it, &root_);            
        }
        return true;
    }


    Node* AVLTree::toISDP(int left, int right)
    {
        // принимаем границы в массиве

        // если лева€ граница больше, то это не правильно, возвращаем nullptr
        if (left > right) return nullptr;

        int size{ static_cast<int>(vec_buffer_.size()) };

        if (size == 0) return nullptr;

        // если права€ граница больше размера массива, или меньше 0, то возврат nullptr
        if (right >= size || left < 0) return nullptr;

        int middle{ left + ((right - left) / 2) };

        // —оздаем Node с данными из €чейки массива со смещением "middle".
        Node* nd{ new (std::nothrow) Node(vec_buffer_[middle]) };

        // если Node не создалс€, то возврат nullptr
        if (!nd) return nullptr;

        // теперь создаем левую и правую Node
        nd->left = toISDP(left, middle - 1);
        nd->right = toISDP(middle + 1, right);

        // возвращаем указатель на созданную Node
        return nd;

    }

    bool AVLTree::fillVector(int size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-10000, 10000);
        


        for (int i{}, ie{ size }; i != ie; ++i) {

            auto tmp{ dist(gen) };
            while (std::find(vec_buffer_.begin(), vec_buffer_.end(), tmp) != vec_buffer_.end()) {
                tmp = dist(gen);
            }
            vec_buffer_.emplace_back(tmp);
        }     


        if (vec_buffer_.size() != size) {
            return false;
        }
        return true;
    }

    void AVLTree::insert(int key, Node** root)
    {
        // если *root не nulptr
        while (*root) {
            // если ключ меньше данных, то мен€ем указатель на левую ноду
            if (key < (*root)->data) root = &((*root)->left);
            // если ключ больше данных, то мен€ем указатель на правую ноду
            else if (key > (*root)->data) root = &(*root)->right;
            else return;
        }

        // если указатель пуст, то создаем ноду дл€ и присваиваем еЄ указателю
        if (*root == nullptr) *root = new (std::nothrow) Node(key);
    }

    AVLTree::AVLTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::AVL) {

        vec_buffer_.reserve(size);

        if (!fillVector(size)) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ Ѕј«”! " << std::endl;
            system("pause");
            exit(1);
        }

        if (!toAVL()) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ ƒ≈–≈¬ќ! " << std::endl;
            system("pause");
            exit(1);
        }

    }

    AVLTree::AVLTree(AVLTree* bt)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::ISDP) {

        if (bt == this) return;

        vec_buffer_ = bt->vec_buffer_;

        root_ = toISDP(0, static_cast<int>(vec_buffer_.size() - 1));
    }

    AVLTree::~AVLTree()
    {
        if(root_) deleteTree(root_);
    }

    size_t AVLTree::size() const
    {
        return sizeTree(root_);
    }

    std::stringstream AVLTree::print() const
    {        
        return readTree(root_);
    }

    int AVLTree::height() const
    {
        return heightTree(root_);
    }

    int AVLTree::middleHeight() const
    {
        return middleHeightTree(root_, 1) / sizeTree(root_);
    }

    long long AVLTree::hash() const
    {
        return hashTree(root_);
    }

    bool AVLTree::isSearch() const
    {
        return isSearchTree(root_);
    }
    void AVLTree::deleteTree()
    {
        deleteTree(root_);
    }
}