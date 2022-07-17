#include "TaskExecution.h"

namespace KHAS {
    std::pair<AVLTree*, AVLTree*> TaskExecution::create(int count_tree)
    {
                
        AVLTree* avl_tree{ new (std::nothrow) AVLTree(count_tree) };

        if (!avl_tree) return { nullptr, nullptr };

        AVLTree* isdp_tree{ new (std::nothrow) AVLTree(avl_tree) };

        if (!isdp_tree) {
            avl_tree->deleteTree();
            return { nullptr, nullptr };
        }

        return { avl_tree, isdp_tree };
    }

    bool TaskExecution::checkIsTree()
    {
        return (avlTree100_ != nullptr && avlTree200_ != nullptr
            && avlTree300_ != nullptr && avlTree400_ != nullptr
            && avlTree500_ != nullptr && isdpTree100_ != nullptr
            && isdpTree200_ != nullptr && isdpTree300_ != nullptr
            && isdpTree400_ != nullptr && isdpTree500_ != nullptr
            );
    }

    AVLTree* TaskExecution::selectTree(int index) const
    {
        AVLTree* bt{ nullptr };
        switch (index) {
        case 1:     bt = avlTree100_;  break;
        case 2:     bt = avlTree200_;  break;
        case 3:     bt = avlTree300_;  break;
        case 4:     bt = avlTree400_;  break;
        case 5:     bt = avlTree500_;  break;
        case 6:     bt = isdpTree100_;  break;
        case 7:     bt = isdpTree200_;  break;
        case 8:     bt = isdpTree300_;  break;
        case 9:     bt = isdpTree400_;  break;
        case 0:     bt = isdpTree500_;  break;
        default:    bt = nullptr;
        }
        return bt;
    }

    AVLTree* TaskExecution::selectTreeView()
    {
        using namespace std::literals;
        int index{};
        bool start{};
        bool isSelectBase{};
        AVLTree* bt{ nullptr };
        while (!isSelectBase || !start || std::cin.fail()) {
            std::cin.clear();
            if (start) {
                push(bufferItem("Ошибка ввода!"s));
                push(bufferItem("Повторите ввод!"s));
                std::cin.get();
            }
            push(delimiter('-'));
            push(bufferItem("Введите число от 0 до 9, в каком дереве хотим искать:"s));
            push(delimiter('-'));
            push(bufferItem("1 -"s, "АВЛ дерево размером в 100 элементов"s));
            push(bufferItem("2 -"s, "АВЛ дерево размером в 200 элементов"s));
            push(bufferItem("3 -"s, "АВЛ дерево размером в 300 элементов"s));
            push(bufferItem("4 -"s, "АВЛ дерево размером в 400 элементов"s));
            push(bufferItem("5 -"s, "АВЛ дерево размером в 500 элементов"s));
            push(delimiter('-'));
            push(bufferItem("6 -"s, "ИСДП дерево размером в 100 элементов"s));
            push(bufferItem("7 -"s, "ИСДП дерево размером в 200 элементов"s));
            push(bufferItem("8 -"s, "ИСДП дерево размером в 300 элементов"s));
            push(bufferItem("9 -"s, "ИСДП дерево размером в 400 элементов"s));
            push(bufferItem("0 -"s, "ИСДП дерево размером в 500 элементов"s));
            push(delimiter('-'));
            showStatusBar();
            std::cin >> index;
            start = true;
            if (bt = selectTree(index)) isSelectBase = true;
        }

        std::cin.get();
        return bt;
    }

    void TaskExecution::functionLaunch()
    {
        // проверяет созданные деревья на валидность
        if (!checkIsTree()) {
            system("cls");
            std::cout << "Внимание! не удалось выделить память из кучи под данные!";
            exit(1);
        }

        // выполняет определенную пользователем команду
        switch (getActiveCommand()) {
        case InputCommand::Print:       printView();    break;
        case InputCommand::Exit:        quit();         break;
        default: break;
        }

        // очистка команды
        clearActiveCommand();
    }

    TaskExecution
        ::TaskExecution()
    : Interface()
    , avlTree100_(nullptr), avlTree200_(nullptr)
    , avlTree300_(nullptr), avlTree400_(nullptr)
    , avlTree500_(nullptr), isdpTree100_(nullptr)
    , isdpTree200_(nullptr), isdpTree300_(nullptr)
    , isdpTree400_(nullptr), isdpTree500_(nullptr) {

        // создает необходимые деревья
        std::tie(avlTree100_, isdpTree100_) = create(100);
        std::tie(avlTree200_, isdpTree200_) = create(200);
        std::tie(avlTree300_, isdpTree300_) = create(300);
        std::tie(avlTree400_, isdpTree400_) = create(400);
        std::tie(avlTree500_, isdpTree500_) = create(500);

    }

    TaskExecution::~TaskExecution()
    {
        // очищает деревья и обнуляет указатели
        avlTree100_->deleteTree();
        avlTree200_->deleteTree();
        avlTree300_->deleteTree();
        avlTree400_->deleteTree();
        avlTree500_->deleteTree();
        isdpTree100_->deleteTree();
        isdpTree200_->deleteTree();
        isdpTree300_->deleteTree();
        isdpTree400_->deleteTree();
        isdpTree500_->deleteTree();

        delete avlTree100_;     delete isdpTree100_;
        delete avlTree200_;     delete isdpTree200_;
        delete avlTree300_;     delete isdpTree300_;        
        delete avlTree400_;     delete isdpTree400_;    
        delete avlTree500_;     delete isdpTree500_;

        avlTree100_ = nullptr;  isdpTree100_ = nullptr;
        avlTree200_ = nullptr;  isdpTree200_ = nullptr;
        avlTree300_ = nullptr;  isdpTree300_ = nullptr;
        avlTree400_ = nullptr;  isdpTree400_ = nullptr;
        avlTree500_ = nullptr;  isdpTree500_ = nullptr;
    }

    void TaskExecution::quit() const
    {
        system("cls");
        exit(0);
    }

    void TaskExecution::printView()
    {
        AVLTree* bt{ selectTreeView() };
        print(bt);
    }

    void TaskExecution::showMenu() const
    {
        using namespace std::literals;

        // добавляет отформатированные строки в буфер
        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Меню"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Клавиша"s, "Команда"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("1"s, "Распечать данные о дереве"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("9"s, "Закрыть приложение"s));
        pushToBuffer(delimiter('='));

        // сбрасывает на вывод в консоль
        show();
    }

}