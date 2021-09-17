#ifndef ORBITSIMULATOR_LIST_HPP
#define ORBITSIMULATOR_LIST_HPP

#include <iostream>

/**
 * A singly-linked list version of std::list
 * with array-like access
 */
namespace space
{
    // a node in the linked list container
    template<typename T>
    struct listnode
    {
        T value;
        listnode *next = nullptr;

        explicit listnode<T>(T &_value);

        explicit listnode<T>(T *_value);
    };


    template<typename T>
    listnode<T>::listnode(T &_value)
    {
        this->value = _value;
    }


    template<typename T>
    listnode<T>::listnode(T *_value)
    {
        this->value = *_value;
    }


    template<class T>
    class list
    {
    public:
        int current_index = 0;
        listnode<T> *search_ptr = nullptr;
        listnode<T> *tail = nullptr;
        listnode<T> *head = nullptr;
        listnode<T> *current = nullptr;

        int container_size = 0;
        void traverse(int index);

    public:
        list<T>();

        ~list<T>();

        T &operator[](int i);

        void add(T value);

        void add(T *value);

        void insert(T &value);



        void remove(T &value);

        void remove(int i);

        void pop_front();

        void pop_back();

        int size() const;

        // multithread this
        listnode<T> *search(T &value);
    };
}


/**
 * universe Container Implementation file
 */
namespace space
{
    template<class T>
    list<T>::list()
    {
        this->container_size = 0;
        this->current = this->head;
    }


    template<class T>
    list<T>::~list() = default;


    // overload [] for array-like access
    template<class T>
    T &list<T>::operator[](int i)
    {
        if (i > this->container_size - 1) {
            throw std::out_of_range("[] index out of bounds");
        }
        // if index value is past the current pointer, it means
        // we can traverse to it from the current position
        if (i > this->current_index) {
            this->traverse(i - this->current_index);
        }
            // otherwise we start traversing from the root
        else {
            this->current = this->head;
            this->traverse(i);
        }

        this->current_index = i;
        return this->current->value;
    }


    template<class T>
    void list<T>::add(T value)
    {
        if (this->head == nullptr) {
            this->head = new listnode<T>(value);
            this->tail = this->head;
            this->current = this->head;
        }
        else {
            this->tail->next = new listnode<T>(value);
            this->tail = this->tail->next;
        }

        this->container_size++;
    }


    template<class T>
    void list<T>::add(T *value)
    {
        if (this->head == nullptr) {
            this->head = new listnode<T>(value);
            this->tail = this->head;
            this->current = this->head;
        }
        else {
            this->tail = this->tail->next;
            this->tail = new listnode<T>(value);
        }

        this->container_size++;
    }


    /**
     * Add an object that's already created
     * @param value
     */
    template<class T>
    void list<T>::insert(T &value)
    {
        this->add(&value);
    }


    template<class T>
    void list<T>::traverse(int index)
    {
        if (index >= this->container_size) {
            throw std::out_of_range("universe::traverse index out of bounds");
        }

        int i = 0;

        while (i < index) {
            this->current = this->current->next;
            i++;
        }
    }


    /**
     * Search for the object and remove it
     * @param value
     */
    template<class T>
    void list<T>::remove(T &value)
    {

    }


    /**
     * Remove node at index
     * Time complexity O(n)
     * @param {integer} index   index of element to remove
     */
    template<class T>
    void list<T>::remove(int index)
    {
        if (index > this->container_size - 1 || index < 0) {
            throw std::out_of_range("universe::remove() index out of bounds");
        }

        this->traverse(index - 1);
        listnode<T> *to_delete = this->current->next;
        listnode<T> *is_it_still_there = this->current->next;
        this->current->next = this->current->next->next;

        //delete to_delete;
        std::cout << "is it still here? " << is_it_still_there->value.name << std::endl;
    }


    /**
     * Removes the first element from the linked list
     * Time complexity O(1)
     */
    template<class T>
    void list<T>::pop_front()
    {
        if (this->container_size == 0) {
            return;
        }

        listnode<T> *head_temp = this->head;
        this->head = this->head->next;
        delete head_temp;
        this->container_size--;
    }


    /**
     * Removes last element from the singly linked list
     * Time complexity O(n), must traverse from start to end to delete last element
     */
    template<class T>
    void list<T>::pop_back()
    {
        if (this->container_size == 0) {
            return;
        }

        listnode<T> *tail_temp = this->tail;
        this->traverse(this->container_size - 1);
        this->tail = this->current;
        delete tail_temp;
        this->container_size--;
    }


    template<class T>
    listnode<T> *list<T>::search(T &value)
    {
        return this->current;
    }


    template<class T>
    int list<T>::size() const
    {
        return this->container_size;
    }
}


#endif //ORBITSIMULATOR_LIST_HPP
