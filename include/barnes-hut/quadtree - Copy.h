//
// Created by Macross on 4/10/2021.
//

#ifndef SIMULATOR_QUADTREE_H
#define SIMULATOR_QUADTREE_H

#include "include/barnes-hut/object.hpp"
#include "include/list.hpp"

namespace space {
    struct Node {
        object *object;
        Node *top_right = nullptr;
        Node *top_left = nullptr;
        Node *bottom_left = nullptr;
        Node *bottom_right = nullptr;

        explicit Node(space::object &_object) {
            this->object = &_object;
        }
    };

    /**
     * http://arborjs.org/docs/barnes-hut
     */
    class Quadtree {
        //private:
    public:
        bool enable_logging = false;

        space::list<object> *objects;
        int tree_size = 0;       // number of nodes including com-nodes
        int tree_height = 0;     // height of a tree
        int recursion_level = 1; // how deep insert recursion goes, for setting height
        int deleted = 0;         // number of nodes deleted
        double sd_ratio;

        // simulator coordinate bounds
        const double AU = 1.496e11;
        double x_max;
        double x_min;
        double y_max;
        double y_min;

        Node *root = nullptr;
        Node *current = nullptr;
        Node *previous = nullptr;

        Node *search_decision(Node **node_pointer, object &target_object);

        void destroy_recursion(Node *node_pointer);

        void InsertCOM(object &object);

        void SwapNodes(Node **first, Node **second);

        inline void ResetCurrent();


        //public:
        Quadtree();

        explicit Quadtree(space::list<space::object> &universe);


        ~Quadtree();

        bool IsEmpty() const;

        int height() const;

        int size() const;

        bool insert(object &new_object);

        Node *route(object &object, Node *router);

        Node *search(object &target_object);

        bool remove();

        bool equals(object &left, object &right);

        bool destroy();

        double NetForce();

        void PrintChildren(Node *node);
    };
}


#endif //SIMULATOR_QUADTREE_H
