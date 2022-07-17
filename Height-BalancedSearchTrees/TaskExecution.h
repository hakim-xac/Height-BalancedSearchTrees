#pragma once
#include "Interface.h"
#include "AVLTree.h"
#include "Enums.h"

namespace KHAS {

    class TaskExecution : public Interface {

        template <typename BTree>
        using isBinaryTree_t = std::enable_if_t<std::is_same_v<BTree, AVLTree>>;

        AVLTree* avlTree100_;
        AVLTree* avlTree200_;
        AVLTree* avlTree300_;
        AVLTree* avlTree400_;
        AVLTree* avlTree500_;

        AVLTree* isdpTree100_;
        AVLTree* isdpTree200_;
        AVLTree* isdpTree300_;
        AVLTree* isdpTree400_;
        AVLTree* isdpTree500_;


    private:

        /// <summary>
        /// создает дерево с количеством элементов count_tree
        /// </summary>
        static std::pair<AVLTree*, AVLTree*> create(int count_tree);

        /// <summary>
        /// проверяет на валидность созданные деревья
        /// </summary>
        bool checkIsTree();

        /// <summary>
        /// выводит, необходимый по условию задачи, результат в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void print(const BTree* const tree);

        /// <summary>
        /// считывает дерево и добовляет данные в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void readTree(const BTree* const tree);

        /// <summary>
        /// считает хеш-сумму и выводит в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void hashTree(const BTree* const tree);

        /// <summary>
        /// считает высоту дерева и выводит в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void heightTree(const BTree* const tree);

        /// <summary>
        /// считает размер дерева
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void sizeTree(const BTree* const tree);

        /// <summary>
        /// считает среднюю высоту дерева
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void middleHeightTree(const BTree* const tree);

        /// <summary>
        /// определяет, является двоичное дерево, деревом поиска
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void searchTree(const BTree* const tree);

        /// <summary>
        /// выбирает дерево по индексу
        /// </summary>
        AVLTree* selectTree(int index) const;

        /// <summary>
        /// меню выбора дерева
        /// </summary>
        AVLTree* selectTreeView();

        /// <summary>
        /// выполняет функцию, в зависимости от команды
        /// </summary>
        void functionLaunch() override;

        /// <summary>
        /// выходит из программы
        /// </summary>
        void quit()         const;

        /// <summary>
        /// добавляет данные о дереве в буфер
        /// </summary>
        void printView();



    public:
        TaskExecution()          ;
        ~TaskExecution()         ;
        void showMenu() const override;
        
    };



    template<typename BTree, typename T2>
    inline void TaskExecution::print(const BTree* const tree)
    {
        using namespace std::literals;

        push(delimiter('-'));
        push(bufferItem("Данные о дереве"s));
        push(delimiter('-'));

        readTree(tree);
        sizeTree(tree);
        hashTree(tree);
        heightTree(tree);
        middleHeightTree(tree);
        searchTree(tree);
        showStatusBar();
        
    }

    template<typename BTree, typename T2>
    inline void TaskExecution::readTree(const BTree* const tree)
    {
        using namespace std::literals;

        std::stringstream ss{ tree->print() };

        push(delimiter('='));
        push(bufferItem("Вывод дерева"s));
        push(delimiter('='));

        std::string first{}, second{}, third{}, fourth{}, fiveth{};
        do {

            ss >> first >> second >> third >> fourth >> fiveth;
            if (ss.good()) {
                push(bufferItem(
                    first
                    , second
                    , third
                    , fourth
                    , fiveth));
            }
        } while (ss.good());
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::hashTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Хеш сумма дерева:"s
            , std::to_string(tree->hash())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::heightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Высота дерева:"s
            , std::to_string(tree->height())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::sizeTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Размер дерева:"s
            , std::to_string(tree->size())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::middleHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Средняя высота дерева:"s
            , std::to_string(tree->middleHeight())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::searchTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Является двоичное дерево, деревом поиска :"s
            , tree->isSearch() ? "ДА"s : "НЕТ"s ));
        push(delimiter('='));
    }





}