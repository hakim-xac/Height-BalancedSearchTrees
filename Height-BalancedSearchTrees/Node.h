#pragma once

namespace KHAS {

    class Node {

    public:

        // ��������� �� ����� ������
        Node* left{ nullptr };

        // ��������� �� ������ ������
        Node* right{ nullptr };

        // ������
        int data{};


        Node(int value, int level = 0)
            : left(nullptr)
            , right(nullptr)
            , data(value) {}

        Node() = delete;
    };

}