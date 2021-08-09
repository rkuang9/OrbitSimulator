//
// Created by Macross on 4/10/2021.
//

#ifndef SIMULATOR_QUADTREE_H
#define SIMULATOR_QUADTREE_H

#include "include/barnes-hut/object.h"
#include "include/list.h"

namespace space {
    struct node {
        object *object;
        node *top_right = nullptr;
        node *top_left = nullptr;
        node *bottom_left = nullptr;
        node *bottom_right = nullptr;

        explicit node(space::object &_object) {
            this->object = &_object;
        }
    };

    /**
     * http://arborjs.org/docs/barnes-hut
     */
    class quadtree {
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

        node *root = nullptr;
        node *current = nullptr;
        node *previous = nullptr;

        node *search_decision(node **node_pointer, object &target_object);

        void destroy_recursion(node *node_pointer);

        void InsertCOM(object &object);

        void SwapNodes(node **first, node **second);

        inline void ResetCurrent();


        //public:
        quadtree();

        explicit quadtree(space::list<space::object> &universe);


        ~quadtree();

        bool IsEmpty() const;

        int height() const;

        int size() const;

        bool insert(object &new_object);

        node *route(object &object, node *router);

        node *search(object &target_object);

        bool remove();

        bool equals(object &left, object &right);

        bool destroy();

        double NetForce();

        void PrintChildren(node *node);
    };
}


#endif //SIMULATOR_QUADTREE_H
