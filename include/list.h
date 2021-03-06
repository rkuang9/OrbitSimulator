#ifndef ORBITSIMULATOR_LIST_H
#define ORBITSIMULATOR_LIST_H


/**
 * A singly-linked list version of STL's list class
 */
namespace space
{
    // a node in the linked list container
    template<typename T>
    struct listnode
    {
        T object;
        listnode *next = nullptr;

        explicit listnode<T>(T &_object);

        explicit listnode<T>(T *_object);
    };


    template<typename T>
    listnode<T>::listnode(T &_object)
    {
        this->object = _object;
    }


    template<typename T>
    listnode<T>::listnode(T *_object)
    {
        this->object = *_object;
    }


    template<class T>
    class list
    {
    private:
        int current_index = 0;
        listnode<T> *search_ptr = nullptr;
        listnode<T> *tail = nullptr;
        listnode<T> *head = nullptr;
        listnode<T> *current = nullptr;

        int container_size = 0;

    public:
        list<T>();

        ~list<T>();

        T &operator[](int i);

        void add(T obj);

        void add(T *obj);

        void insert(T &obj);

        void traverse(int index);

        void remove(T &obj);

        void remove(int i);

        void pop_front();

        void pop_back();

        int size();

        // multithread this
        listnode<T> *search(T &obj);
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
            throw std::out_of_range("[] overload index out of bounds");
        }
        // target value is past the current pointer, it means
        // we can traverse to it from the current position
        if (i - this->current_index > 0) {
            this->traverse(i - this->current_index);
        }
            // otherwise we start traversing from the root
        else {
            this->current = this->head;
            this->traverse(i);
        }

        this->current_index = i;
        return this->current->object;
    }


    template<class T>
    void list<T>::add(T obj)
    {
        if (this->head == nullptr) {
            this->head = new listnode<T>(obj);
            this->tail = this->head;
            this->current = this->head;
        }
        else {
            this->tail->next = new listnode<T>(obj);
            this->tail = this->tail->next;
        }

        this->container_size++;
    }


    template<class T>
    void list<T>::add(T *obj)
    {
        if (this->head == nullptr) {
            this->head = new listnode<T>(obj);
            this->tail = this->head;
            this->current = this->head;
        }
        else {
            this->tail = this->tail->next;
            this->tail = new listnode<T>(obj);
        }

        this->container_size++;
    }


    /**
     * Add an object that's already created
     * @param obj
     */
    template<class T>
    void list<T>::insert(T &obj)
    {
        this->add(&obj);
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
     * @param obj
     */
    template<class T>
    void list<T>::remove(T &obj)
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
        std::cout << "is it still here? " << is_it_still_there->object.name << std::endl;
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
    listnode<T> *list<T>::search(T &obj)
    {
        return this->current;
    }


    template<class T>
    int list<T>::size()
    {
        return this->container_size;
    }
}


#endif //ORBITSIMULATOR_LIST_H
