#include <stdexcept>
#include <memory>

#include "list.h"

void List::CreateFirstNode(double value)
{
    Node* new_n = new Node {value, nullptr, nullptr};
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
        Node* new_n = new Node{value, nullptr , it.n};
        this->first->prev = new_n;
        this->first = new_n;
    }
    else
    {
        Node* new_n = new Node {value, it.n->prev, it.n};
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
        Node* new_n = new Node {value, it.n, nullptr};
        this->last->next = new_n;
        this->last = new_n;
    }
    else
    {
        Node* new_n = new Node {value, it.n, it.n->next};
        it.n->next->prev = new_n;
        it.n->next = new_n;
    }
    this->cached_size += 1;
}

void List::pop(Iterator it)

{
    this->CheckIter(it);  
    
    if (it.n != this->first) it.n->prev->next = it.n->next; //Итератор указывает не на первую ноду списка
    else this->first = it.n->next;                          //Итератор указывает на первую ноду списка
    if (it.n != this->last) it.n->next->prev = it.n->prev;  //Итератор указывает не на поcледнюю ноду списка
    else this->last = it.n->prev;                           //Итератор указывает на поcледнюю ноду списка

    this->cached_size--;
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
        this->push_after(Iterator(this, this->last), value);
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
        this->push_before(Iterator(this, this->first), value);
    }
}

void List::pop_back()
{
    this->pop(Iterator(this, this->last));
}

void List::pop_front()
{
        this->pop(Iterator(this, this->first));
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