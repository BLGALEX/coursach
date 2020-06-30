#pragma once


#include "../helper/Vector.h"
#include "Company.h"


/**
 * ������� ������������� ������
 * �������� ������ - ������� ������ Company
 *
 * ����������
 * 1. ������������: �� ���������, �����������, �����������
 * 2. ����������
 * 3. ��������� ������������: ������������, ������������
 * 4. ������� ������� � ������ ������
 * 5. �������� ������� �� ����� (�������� ��������)
 * 6. �����������/������������� ����� ������� �� �����
 * 7. �������������� ������ � Vector<Company>
 * 8. ��������� ������� ������
 * 9. �������� �� �������
 * 10. ��������� ���������� ���������� ��������� ���
 *     ������/�������� �������.
 */


namespace Aleksei {

    class ForwardList {
    public:
        typedef Company value_t;
        typedef decltype(Company::name) key_t;

        ForwardList() noexcept;
        ~ForwardList() noexcept;
        ForwardList(const ForwardList& another) noexcept;
        ForwardList& operator=(const ForwardList& another) noexcept;
        ForwardList(ForwardList&& another) noexcept;
        ForwardList& operator=(ForwardList&& another) noexcept;

        void Push(value_t value) noexcept;
        bool Erase(const key_t& key) noexcept;
        const value_t* Find(const key_t& key) const noexcept;
        value_t* Find(const key_t& key) noexcept;
        Vector<value_t> ToVector() const noexcept;
        Vector<const value_t*> ToPointerVector() const noexcept;
        size_t Size() const noexcept;
        bool Empty() const noexcept;
        template <typename Predicate>
        Vector<const Company*> LookUp(Predicate pred) const noexcept;
        size_t LastComparisonAmount() const noexcept;
    private:
        // ���� ������
        struct Node {
            Company data;
            // ��������� �� ��������� ����
            Node* next;
        };

        // ��������� �� ������ ������
        Node* head;
        // ���������� ��������� � ������
        size_t size;
        // ���������� ��������� �������� Company
        // �� ��������� ����� Find/Erase
        mutable size_t last_comparison_amount;

        Node* AllocateNode(value_t data) const noexcept;
        void DeallocateNode(Node* node) const noexcept;
        size_t DeallocateList(Node* start) const noexcept;
        bool Equals(const key_t& lhs, const key_t& rhs) const noexcept;
    };


    template <typename Predicate>
    Vector<const Company*> ForwardList::LookUp(Predicate pred) const noexcept {
        Vector<const Company*> result;
        
        for (Node* it = head; it != nullptr; it = it->next)
            if (pred(it->data))
                result.PushBack(&it->data);
       
        return result;
    }
}