#include "ForwardList.h"

namespace Aleksei /* �� ������ ���� */ {

    /**
     * ����������� �� ���������
     */
    ForwardList::ForwardList() noexcept
        : head(nullptr),
        size(0),
        last_comparison_amount(0) {}


    /**
     * ����������
     * ��������������� ������� ���� ������, ������� � head
     */
    ForwardList::~ForwardList() noexcept {
        DeallocateList(head);
    }


    /**
     * ����������� �����������
     * ������������ ������, ��������������� ��������
     * ����� ���� �������� ������ another � ��� �� �������,
     * � ����� ��� ���� � ������ another.
     *
     * @param another - ������, �� �������� ���������� �������
     */
    ForwardList::ForwardList(const ForwardList& another) noexcept
        : head(nullptr),
        size(another.size),
        last_comparison_amount(0) {

        // ���� another - ������ ������, �� ���������� ������
        if (another.Empty())
            return;

        // �������� ������ ������� ������ another
        head = AllocateNode(std::move(another.head->data));
        Node* this_ptr = head;
        Node* another_ptr = another.head->next;

        // ��������������� �������� ��������� �������� another
        while (another_ptr != nullptr) {
            this_ptr->next = AllocateNode(std::move(another_ptr->data));
            this_ptr = this_ptr->next;
            another_ptr = another_ptr->next;
        }

        // ������ ����� ������ ������ ����� ������� another
        size = another.size;
    }


    /**
     * �������� ������������ ������������
     * �������� ��� ����������� ����������� � ��� ��������, ���
     * ��� ���� ��������� ������ ForwardList, � ������� ����
     * ���������� ����� ��������, ��� �� ������ ������ ������ another.
     *
     * @param another - ������, �� �������� ���������� �������
     */
    ForwardList& ForwardList::operator = (const ForwardList& another) noexcept {
        // ���� this � &another - ���������� ������, ��
        // � ��� ��� ����� � �� �����������.
        if (this == &another)
            return *this;

        if (another.Empty()) {                          // ���� another - ������ ������
            // ������� ��� �������� ������, ������� � head
            // � ������������� ������ ������ 0
            DeallocateList(head);
            size = 0;
        }
        else if (this->Empty()) {                     // ���� ������� ������ - ������
         // ��������� ����� ������ ������ ��� ������
         // ������������ �����������, ����� ����
         // ���������� �������� ������������� ������������
         // �� ������ �������.
         // ������������, ��� ������ �������� ��� std::move,
         // �� ��� ����������.
            *this = std::move(ForwardList(another));
        }
        else if (this->Size() < another.Size()) {      // ���� ������� ������ ������ another
         // ��������� ��� ��������� �� ���� ������ �������
            Node* this_ptr = head;
            Node* another_ptr = another.head;

            // �������� ��� ������� � ������� ������,
            // �� ������� ��������� ����� (�� �������� �����)
            while (this_ptr->next != nullptr) {
                this_ptr->data = another_ptr->data;
                this_ptr = this_ptr->next;
                another_ptr = another_ptr->next;
            }

            // �������� ��������� ������, ��� ��������
            // �������� ���� � ������� ������
            this_ptr->data = another_ptr->data;
            another_ptr = another_ptr->next;

            // ��������� ����� ���� ��� ��������, �������
            // �� ������� �����, � ��������� �� � ������
            while (another_ptr != nullptr) {
                this_ptr->next = AllocateNode(std::move(another_ptr->data));
                this_ptr = this_ptr->next;
                another_ptr = another_ptr->next;
            }

        }
        else {                                        // ���� ������� ������ ������/����� another
         // ��������� ��� ��������� �� ���� ������ �������
            Node* this_ptr = head;
            Node* another_ptr = another.head;

            // �������� ��� ������� � ������� ������,
            // �� ������� ��������� ����� (�� �������� �����)
            while (another_ptr->next != nullptr) {
                this_ptr->data = another_ptr->data;
                this_ptr = this_ptr->next;
                another_ptr = another_ptr->next;
            }

            // �������� ��������� ������� � ������� ������
            this_ptr->data = another_ptr->data;

            // ������� ����������/���������������� ���� ��
            // ������ � �������� �� ������� ���������� ���������
            // �����, ������� ����� ������ ������.
            size -= DeallocateList(this_ptr->next);
        }
        return *this;
    }


    /**
     * ����������� �����������
     * ������������ ������ �� ����������� �����,
     * ����� ������ another ���������� ��� �������������
     *
     * @param another - ������, �� �������� ������������ �������
     */
    ForwardList::ForwardList(ForwardList&& another) noexcept
        : head(another.head),
        size(another.size),
        last_comparison_amount(another.last_comparison_amount) {

        // ������ ������ another ������ ����� nullptr, ������ ���
        // ����� ��� ����� �������� � ������� (�������� delete ������
        // �� ������ � ���� �� ����� � �����������)
        another.head = nullptr;
        size = 0;

    }


    /**
     * �������� ������������ ������������
     * �������� ��� ����������� ����������� � ��� ��������, ���
     * ��� ���� ��������� ������ ForwardList. ������ another
     * ����� ���������� ��� �������������.
     *
     * @param another - ������, �� �������� ���������� �������
     */
    ForwardList& ForwardList::operator = (ForwardList&& another) noexcept {
        // ��������� � ��������� ������������ ������������
        if (this == &another)
            return *this;

        // ������� ������� ������
        DeallocateList(head);

        // ���������� ���� ������ another � ������� ������.
        head = another.head;
        size = another.size;
        last_comparison_amount = another.last_comparison_amount;
        another.head = nullptr;
        size = 0;

        return *this;
    }


    /**
     * ������� �������
     * ������� ������������ � ������ ������. ������ ���������
     * ������� ������������� ��������
     *
     * @param value - ������ ��� �������
     */
    void ForwardList::Push(value_t value) noexcept {
        // ������� ����� ����
        Node* new_head = AllocateNode(std::move(value));
        // �������� ������ ������ ����� �����
        new_head->next = head;
        head = new_head;

        ++size;
    }


    /**
     * �������� �������
     * ������� ������ ��������� ������� � ������ (����� name)
     * key. ���� ������� � ����� ������ � ������ ���, �� ������
     * �� ����������.
     *
     * @param key ����, �� �������� ���� ������� ������
     * @return true, ���� ������ ��� ������, ����� - false
     */
    bool ForwardList::Erase(const key_t& key) noexcept {
        // �������� ����������, �������� ��������� ���-�� ���������
        last_comparison_amount = 0;

        if (Empty()) {                                          // ���� ������ - ������
            return false;
        }
        else if (Equals(head->data.GetName(), key)) {     // ���� ������ ������ ��������
                                                             // ������ � ������ key
         // �������� ����������, �������� ������ ������
            --size;
            // ������� ������ ���� ������
            Node* temp_ptr = head;
            head = head->next;
            DeallocateNode(temp_ptr);

            return true;

        }
        else {                                                // ���� ������ � ������
            Node* prev_ptr = head;
            Node* this_ptr = head->next;

            while (this_ptr != nullptr) {
                // ���� ������ � ����� ������ ������
                if (Equals(this_ptr->data.GetName(), key)) {
                    // �������� ����������, �������� ������ ������
                    --size;
                    // ������� ���� ���� ������
                    prev_ptr->next = this_ptr->next;
                    DeallocateNode(this_ptr);
                    return true;
                }
            }

        }

        return false;
    }


    /**
     * ����� ������� �� �����.
     * ���� ������ ��������� ������� � ������ key
     *
     * @param key ����, �� �������� ���� ����� ������
     * @return ����������� ��������� �� ������ ������� ������ � ������ ������, ���
     *         nullptr, ���� ������� � ������ ������
     */
    const ForwardList::value_t* ForwardList::Find(const key_t& key) const noexcept {
        // �������� ����������, �������� ��������� ���-�� ���������
        last_comparison_amount = 0;

        // ���� ������ - ������, �� ���������� nullptr
        if (Empty())
            return nullptr;

        // ������������� ������ ������� ������
        for (Node* it = head; it != nullptr; it = it->next) {
            // ���� ����� �������, ���������� ��������� �� ������ Company
            if (Equals(key, it->data.GetName()))
                return &it->data;
        }

        return nullptr;
    }


    /**
     * ����� ������� �� �����.
     * ���� ������ ��������� ������� � ������ key
     *
     * @param key ����, �� �������� ���� ����� ������
     * @return ��������� �� ������ ������� ������ � ������ ������, ���
     *         nullptr, ���� ������� � ������ ������
     */
    ForwardList::value_t* ForwardList::Find(const key_t& key) noexcept {
        // �������� ����������� ����� Find
        return const_cast<value_t*>(
            static_cast<const ForwardList*>(this)->Find(key)
            );
    }


    /**
     * �������������� � Vector<value_t>
     * �������� �������, ���������� � ������ � Vector � ���������� ���
     *
     * @return Vector<value_t>, ��������� �� ��������, ���������� � ������
     */
    Vector<ForwardList::value_t> ForwardList::ToVector() const noexcept {
        // ������� Vector � ����������������� ������� ��� size ���������
        Vector<value_t> result;
        result.Reserve(size);

        // ��������������� �������� ������� ������ � Vector
        for (Node* it = head; it != nullptr; it = it->next)
            result.PushBack(it->data);

        return result;
    }

    /**
     * �������������� � Vector<const value_t*>
     * �������� ��������� �� �������, ���������� � ������ � Vector � ���������� ���
     *
     * @return Vector<const value_t*>, ��������� �� ���������� �� �������, ���������� � ������
     */
    Vector<const ForwardList::value_t*> ForwardList::ToPointerVector() const noexcept {
        // ������� Vector � ����������������� ������� ��� size ���������
        Vector<const value_t*> result;
        result.Reserve(size);

        // ��������������� �������� ��������� �� ������� ������ � Vector
        for (Node* it = head; it != nullptr; it = it->next)
            result.PushBack(&it->data);

        return result;
    }
    /**
     * ������ ������
     *
     * @return ���������� ��������� � ������
     */
    size_t ForwardList::Size() const noexcept {
        return size;
    }


    /**
     * �������� �� �������
     *
     * @return true, ���� ������ - ������, ����� - false
     */
    bool ForwardList::Empty() const noexcept {
        return head == nullptr;
    }


    /**
     * ���������� ���������
     *
     * @return ���������� ��������� �������� Company �� ���������
     *         ����� ������ Find/Remove
     */
    size_t ForwardList::LastComparisonAmount() const noexcept {
        return last_comparison_amount;
    }


    /**
     * ��������� ������ ����
     *
     * @param data - ������ ������ Company
     * @return ��������� �� ����� ���� � �������� Company
     */
    ForwardList::Node* ForwardList::AllocateNode(value_t data) const noexcept {
        return new Node{ std::move(data), nullptr };
    }


    /**
     * ����������� ����
     *
     * @param node ����, ������� ���� ��������������
     */
    void ForwardList::DeallocateNode(Node* node) const noexcept {
        delete node;
    }


    /**
     * ����������� ������, ������� � ���� start
     *
     * @param start ����, � �������� ���� ������ ����������������
     *        �����������
     * @return ���������� ��������� �����
     */
    size_t ForwardList::DeallocateList(Node* start) const noexcept {
        size_t counter = 0;

        while (start != nullptr) {
            // ������� ���� start
            Node* temp = start->next;
            DeallocateNode(start);
            start = temp;
            ++counter;
        }

        return counter;
    }


    /**
     * �������� ������ �� ���������
     *
     * @param lhs ���� ������� �������
     * @param rhs ���� ������� �������
     * @return true, ���� ����� �����, ����� - false
     */
    bool ForwardList::Equals(const key_t& lhs, const key_t& rhs) const noexcept {
        ++last_comparison_amount;
        return lhs == rhs;
    }
}