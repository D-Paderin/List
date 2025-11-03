#include <stdexcept>

#include "list.h"

List::Node::Node(double value_, Node *prev_, Node *next_) noexcept : value(value_), prev(prev_), next(next_) {};

void List::CreateFirstNode(double value)
{
    Node* new_n = new Node (value, nullptr, nullptr);
    this->last = new_n;
    this->first = new_n;

    this->cached_size = 1;

}

void List::CheckIter(const Iterator it)
{
    if (it.l == nullptr)
    {
        throw std::runtime_error("Итератор указывает в несуществующий список");
    }
    if (it.n == nullptr)
    {
        throw std::runtime_error("Итератор указывает в несуществующий узел");
    }
    if (it.l != this)
    {
        throw std::runtime_error("Итератор указывает в другой список");
    }
}

List::List(const List &other)
{
    Node *current = other.first;
    while (current) 
    {
        this->push_back(current->value);
        current = current->next;
    }
}

List::List(List &&other)
{
    this->first = other.first;
    this->last = other.last;
    this->cached_size = other.size();
    other.first = nullptr;
    other.last = nullptr;
    other.cached_size = 0;
}

void List::push_before(Iterator it, double value) 
{
    this->CheckIter(it);

    if (it.n == this->first) 
    {
        Node* new_n = new Node(value, nullptr , it.n);
        this->first->prev = new_n;
        this->first = new_n;
    }
    else
    {
        Node* new_n = new Node (value, it.n->prev, it.n);
        it.n->prev->next = new_n;
        it.n->prev = new_n;
    }
    this->cached_size += 1;
}

void List::push_after(Iterator it, double value)
{
    this->CheckIter(it);

    if (it.n == this->last) 
    {
        Node* new_n = new Node (value, it.n, nullptr);
        this->last->next = new_n;
        this->last = new_n;
    }
    else
    {
        Node* new_n = new Node (value, it.n, it.n->next);
        it.n->next->prev = new_n;
        it.n->next = new_n;
    }
    this->cached_size += 1;
}

void List::pop(Iterator it)
{
    this->CheckIter(it);
    if (it.n == this->first) 
    {
        this->first = this->first->next;
        if (this->first)
        {
            this->first->prev = nullptr;
        }
        else 
        {
            this->first = nullptr;
        }
    }
    else if (it.n == this->last) 
    {
        this->last = this->last->prev;
        if (this->last)
        {
            this->last->next = nullptr;
        } 
        else
        {
            this->first = nullptr;
        }
    }
    else 
    {
        it.n->prev->next = it.n->next;
        it.n->next->prev = it.n->prev;
    }
    this->cached_size -= 1;
    delete it.n;
}

void List::push_back(double value)
{
    if (this->last == nullptr)
    {
        this->CreateFirstNode(value);
    }
    else
    {
        Iterator it(this, this->last);
        this->push_after(it, value);
    }
}

void List::push_front(double value)
{
    if (this->first == nullptr)
    {
        this->CreateFirstNode(value);
    }
    else
    {
        Iterator it(this, this->first);
        this->push_before(it, value);
    }
}

void List::pop_back()
{
    if (this->size() == 0)
    {
        throw std::runtime_error("Попытка удаления элемента из пустого списка!");
    }
    if (this->last) {
        Iterator it(this, this->last);
        this->pop(it);
    }
    else 
    {
        throw std::runtime_error("Последний элемент списка пустой!");
    }
}

void List::pop_front()
{
    if (this->size() == 0)
    {
        throw std::runtime_error("Попытка удаления элемента из пустого списка!");
    }
    if (this->first) {
        Iterator it(this, this->first);
        this->pop(it);
    }
    else 
    {
        throw std::runtime_error("Первый элемент списка пустой!");
    }
}

void List::clear()
{
    while (this->first)
    {
        Node *temp = this->first;
        this->first = this->first->next;
        delete temp;
    }
    this->last = nullptr;
    this->cached_size = 0;
}