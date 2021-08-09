//
// Created by Macross on 4/10/2021.
//

#include "include/barnes-hut/quadtree.h"

namespace space {
    quadtree::quadtree() {
        this->current = this->root;
    }

    quadtree::quadtree(space::list<space::object> &universe) : quadtree() {
        this->objects = &universe;
        int size = this->objects->size();

        if (size == 0) {
            return;
        }

        // create a COM-object fom the first object of the universe list, this will be the quadtree root
        object root_com;
        root_com.COM((*this->objects)[0]);

        // create a COM-node from the root COM-object and set it at the quadtree root
        this->root = new node(root_com);

        // insert the first object of the universe container as quadtree root's leaf
        this->root->top_left = new node((*this->objects)[0]);

        this->ResetCurrent();
        this->tree_size += 2;
        this->tree_height += 2;

        // insert the rest of the universe list starting at index 1, index 0 was already inserted as the root
        for (int i = 1; i < this->objects->size(); i++) {
            this->insert((*this->objects)[i]);
        }

        std::cout << "\nEnd Of Insert------------------------------------------------------------\n";

        this->PrintChildren(this->root);
        this->PrintChildren(this->root->top_left);
        this->PrintChildren(this->root->top_left->top_right);
        this->PrintChildren(this->root->top_right);
    }


    quadtree::~quadtree() = default;

    // Check if tree is empty or not
    // TODO: rewrite with more robust checks
    bool quadtree::IsEmpty() const {
        return this->root == nullptr && this->size() == 0;
    }


    // Return the tree's height
    int quadtree::height() const {
        return this->tree_height;// + 1;
    }


    // return the number of non-null nodes in the tree
    int quadtree::size() const {
        return this->tree_size;
    }


    /**
     * Recursively determines the correct quadrant/subtree and performs one insertion
     *
     * @param new_object, reference to stellar object being inserted
     * @return boolean,   returns TRUE is insert successful, else FALSE
     */
    bool quadtree::insert(object &new_object) {
        std::cout << "\nroot is : " << this->root->object->mass << ", calling insert on " << new_object.mass << "\n";


        if (this->current == nullptr) {
            std::cout << "current is empty, creating and inserting a node here\n";
            std::cout << "but previous is: " << this->previous->object->name << "\n";
            this->current = new node(new_object);
            node *previous_quadrant = this->route(new_object, this->previous);
            previous_quadrant = this->current;
            this->ResetCurrent();
        } else if (this->current->object->is_com) {
            std::cout << "current is at a COM-node\n";
            this->current->object->UpdateCOM(new_object);
            std::cout << "Update COM complete, new mass is: " << this->current->object->mass << "\n";
            this->previous = this->current;
            std::cout << "we have set previous: " << this->previous->object->mass << "\n";
            this->current = this->route(new_object, this->current);
            this->insert(new_object);
        } else if (!this->current->object->is_com) {
            std::cout << "current is a leaf: " << this->current->object->name << ", it will be converted into COM\n";
            // current is non-com node, change it to a com-node and reinsert the new and existing objects
            this->InsertCOM(new_object);
        } else {
            std::cout << "\nObject insertion failure for name: " << new_object.name
                      << ", mass: " << new_object.mass << "\n";
        }

        //this->ResetCurrent();
        return false;
    }


    inline void quadtree::ResetCurrent() {
        this->current = this->root;
        this->previous = nullptr;
    }


    /**
     * Set the current pointer to the correct sub-quadrant of a node in which the
     * object should be inserted into. Compares coordinates between existing node's
     * object and the inserting object
     *
     * @param object,   object to be inserted for coordinate checking
     * @param router,   pointer whose quadrant we want to determine suitable for the object
     */
    node *quadtree::route(object &object, node *router) {
        // upper quadrant
        if (object.y > this->current->object->y) {
            if (object.x < this->current->object->x) {
                std::cout << "routing to top_left\n";
                return router->top_left;
                //return this->current->top_left;
            } else if (object.x > this->current->object->x) {
                std::cout << "routing to top_right\n";
                return router->top_right;
                //return this->current->top_right;
            }
        }
            // bottom quadrant
        else if (object.y < this->current->object->y) {
            if (object.x < this->current->object->x) {
                std::cout << "routing to bottom_left\n";
                return router->bottom_left;
                //return this->current->bottom_left;
            }
                // bottom right
            else if (object.x > this->current->object->x) {
                std::cout << "routing to bottom_right\n";
                return router->bottom_right;
                //return this->current->bottom_right;
            }
        }

        return nullptr;
    }


    /**
     * When this function is called, two nodes are involved
     * 1st node: the object being inserted into a non-COM node
     * 2nd node: the existing object residing in node the inserting as arrived at
     *
     * A COM-node will be created out of these two nodes and swapped with the 2nd node
     *
     * The 1st node and the 2nd node (whose pointer is actually the com_node in this function
     * scope will be reinserted starting at the newly created and placed COM-node
     *
     * @param new_object
     */
    void quadtree::InsertCOM(object &new_object) {
        std::cout << "before starting anything, heres the current setup:\n";
        std::cout << "inserting: " << new_object.mass << "\n";
        std::cout << "existing: " << this->current->object->mass << "\n\n";

        node *existing_node = this->current;

        // create a COM node from the inserting object and the current object
        object com;
        com.COM(new_object);

        // add the COM node to the quadtree
        node *previous_quadrant = this->route(com, this->previous);
        previous_quadrant = new node(com);

        /*std::cout << "pre-swap: current is " << this->current->object->mass << " and com_node: "
                  << com_node->object->mass << "\n";
        this->SwapNodes(&this->current, &com_node);
        std::cout << "post-swap: current is " << this->current->object->mass << " and com_node: "
                  << com_node->object->mass << "\n";*/

        // TODO: reinsert new_object and existing (this->current->object)
        // route current to the correct quadrant of the new COM node
        this->current = previous_quadrant;

        // remember current position because we need to insert new_object and re-insert existing object from here
        node *current_holder = this->current;
        this->insert(new_object);
        this->current = current_holder;
        this->insert(*existing_node->object);

        // since the existing node was created on heap, free that memory to avoid memory leaking
        //delete existing_node; // TODO: exist code not successful
    }


    // swap current leaf with a center of mass node
    void quadtree::SwapNodes(node **first, node **second) {
        node *temp = *first;
        *first = *second;
        *second = temp;
    }


    /**
     *
     * @return
     */
    bool quadtree::remove() {
        // use the same recursion from insert and pull the node from the same quadrant of it's leaf
        // if no leaves, remove the entire node itself
        this->tree_size--;
        return false;
    }


    /**
     * Recursively search for and returns a pointer to the searched object within the tree
     *
     * @param target_object,    object which to search for
     * @return Node pointer,    returns pointer to object within tree, else nullptr is not found
     */
    node *quadtree::search(object &target_object) {
        if (this->root->object == &target_object) {
            return this->current;
        }

        //return this->search_decision(this->RouteNode(target_object), target_object);


        return nullptr;
    }


    node *quadtree::search_decision(node **node_pointer, object &target_object) {
        if (*node_pointer == nullptr) {
            this->current = this->root;
            return nullptr;
        } else if (this->equals(*(*node_pointer)->object, target_object)) {
            this->current = this->root;
            return *node_pointer;
        } else {
            this->current = *node_pointer;
            return this->search(target_object);
        }
    }


    /**
     * Compares two objects' name, mass
     *
     * @param left,right,   the objects for comparison
     * @return booleam,     returns TRUE if their name, mass  and equivalent, else FALSE
     */
    bool quadtree::equals(object &left, object &right) {
        return (left.name == right.name &&
                left.mass == right.mass);
    }


    bool quadtree::destroy() {
        destroy_recursion(this->root);
        return this->IsEmpty();
    }


    void quadtree::destroy_recursion(node *node_pointer) {
        if (node_pointer != nullptr) {
            destroy_recursion(node_pointer->top_left);
            destroy_recursion(node_pointer->top_right);
            destroy_recursion(node_pointer->bottom_left);
            destroy_recursion(node_pointer->bottom_right);
            this->deleted++;
            delete node_pointer;
            node_pointer = nullptr;
        }
    }


    // calculate the sd_ratio to determine if subtree is sufficiently far enough to
    // treat as a single object
    // TODO: implement function
    double quadtree::NetForce() {
        return 0.00;
    }


    void quadtree::PrintChildren(node *node) {
        if (node == nullptr) {
            std::cout << "\nNode is null\n";
            return;
        }

        std::cout << "\n";
        if (node->object->is_com) {
            std::cout << "COM Node" << " - mass: " << node->object->mass << " - ("
                      << node->object->x << ", " << node->object->y << ")" << " - has leaves:\n";
        } else {
            std::cout << "Node - name: " << node->object->name << " - mass: " << node->object->mass << " - ("
                      << node->object->x << ", " << node->object->y << ")" << " - has leaves:\n";
        }

        if (node->top_left != nullptr) {
            std::cout << "top-left name: " << node->top_left->object->name << " - mass: "
                      << node->top_left->object->mass << " - (" << node->object->x << ", "
                      << node->object->y << ")" << "\n";
        }

        if (node->top_right != nullptr) {
            std::cout << "top_right name: " << node->top_right->object->name << " - mass: "
                      << node->top_right->object->mass << " - (" << node->object->x << ", "
                      << node->object->y << ")" << "\n";
        }

        if (node->bottom_left != nullptr) {
            std::cout << "bottom_left name: " << node->bottom_left->object->name << " - mass: "
                      << node->bottom_left->object->mass << " - (" << node->object->x << ", "
                      << node->object->y << ")" << "\n";
        }

        if (node->bottom_right != nullptr) {
            std::cout << "bottom_right name: " << node->bottom_right->object->name << " - mass: "
                      << node->bottom_right->object->mass << " - (" << node->object->x << ", "
                      << node->object->y << ")" << "\n";
        }
    }

}




/*
		// upper quadrant
		if (target_object.y > this->current->object->y) {
			// top left
			if (target_object.x < this->current->object->x) {
				return search_decision(&this->current->top_left, target_object);
			}
				// top right
			else if (target_object.x > this->current->object->x) {
				return search_decision(&this->current->top_right, target_object);
			}
		}
			// lower quadrant
		else if (target_object.y < this->current->object->y) {
			// lower left
			if (target_object.x < this->current->object->x) {
				return search_decision(&this->current->bottom_left, target_object);
			}
				// lower right
			else if (target_object.x > this->current->object->x) {
				return search_decision(&this->current->bottom_right, target_object);
			}
		}
 */



/**
 * Recursively search for an empty node in the correct quadrant and set it with the
 * current stellar object
 *
 * Restriction: no two nodes may share the same x or y coordinate otherwise it may not match the quadrant's ifs
 *
 * @param new_object, reference to stellar object being inserted
 * @return boolean,   returns TRUE is insert successful,
 *                    shouldn't return false unless I find a case in which it shouldn't be inserted
 *//*
 bool QuadTree::insert(Object &new_object)
 {
	 // first node of tree
	 if (this->IsEmpty()) {
		 this->root = new Node(new_object);;
		 this->ResetCurrent();
		 this->tree_size++;
		 return true;
	 }

	 // upper quadrant
	 if (new_object.y > this->current->object->y) {
		 // top left
		 if (new_object.x < this->current->object->x) {
			 return insert_decision(&this->current->top_left, new_object);
		 }
		 // top right
		 else if (new_object.x > this->current->object->x) {
			 return insert_decision(&this->current->top_right, new_object);
		 }
	 }
	 // lower quadrant
	 else if (new_object.y < this->current->object->y) {
		 // lower left
		 if (new_object.x < this->current->object->x) {
			 return insert_decision(&this->current->bottom_left, new_object);
		 }
		 // lower right
		 else if (new_object.x > this->current->object->x) {
			 return insert_decision(&this->current->bottom_right, new_object);
		 }
	 }

	 return false;
 }*/

/*
// handles setting node or going down into the leaves
// avoids having 4 blocks of this same code in insert()
bool QuadTree::insert_decision(Node **node_pointer, Object &object)
{
    // leaf is empty, add the node to it
    if (*node_pointer == nullptr) {
        *node_pointer = new Node(object);
        this->ResetCurrent();
        this->tree_size++;

        if (this->recursion_level > this->tree_height) {
            this->tree_height = this->recursion_level;
        }

        this->recursion_level = 1;
        return true;
    }
    // leaf is occupied, go down one level
    else {
        this->current = *node_pointer;
        this->recursion_level++;
        return this->insert(object);
    }
}*/