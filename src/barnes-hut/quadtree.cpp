//
// Created by Macross on 4/10/2021.
//

#include "include/barnes-hut/quadtree.hpp"


namespace space
{
    sQuadtree::sQuadtree()
    {
        // create root quadrant
        this->root = new sQuadrant(sPoint(0, 0), 100, nullptr);
        //this->root = new sQuadrant(sPoint(0, 0), 1921.56 * constants::AU, nullptr);

        // create initial COM object
        sObject *root_com = new sObject(sPoint(0, 0), 0, 0, "Root COM");
        root_com->SetIsCOM(true);

        this->root->SetObject(*root_com);
        //this->root->NewSubQuadrant(NORTH_WEST);
        this->current = this->root;
    }


    sQuadtree::sQuadtree(space::list<sObject *> &universe) : sQuadtree()
    {
        for (int i = 0; i < universe.size(); i++) {
            this->Insert(universe[i]);
        }
    }


    void sQuadtree::PointCurrentTo(sQuadrant *point_to)
    {
        this->current = point_to;
    }


    sQuadrant *sQuadtree::GetRoot()
    {
        return this->root;
    }

    sQuadrant *sQuadtree::GetCurrent()
    {
        return this->current;
    }


    void sQuadtree::Insert(sObject *new_object)
    {
        if (this->current->IsEmpty()) {
            this->current->SetObject(*new_object);
            this->PointCurrentTo(this->root);
        }
        else if (this->current->IsInternal()) {
            // move into subquadrant if exists, creates one if not
            // calls insert again
            this->InsertInternal(new_object,
                                 this->current->GetPoint().Compare(new_object->GetPoint()));
            return;
        }
        else if (this->current->IsExternal()) {
            // leaf node with COM object, happens when an external
            // quadrant's object is swapped for a COM object
            if (this->current->GetObject()->IsCOM()) {
                this->InsertInternal(new_object,
                                     this->current->GetPoint().Compare(new_object->GetPoint()));
            }
                // leaf node with non-COM object
            else {
                this->InsertExternal(new_object,
                                     this->current->GetPoint().Compare(new_object->GetPoint()));
            }
        }
        else {
            std::cout << "REACHED ELSE-BLOCK, ERROR HAS OCCURED ON " << new_object->GetName() << "\n";
        }
    }


    /**
     * Inserting in an internal quadrant, update its COM then
     * redirect into the proper subquadrant
     */
    void sQuadtree::InsertInternal(sObject *new_object, int quadrant)
    {
        this->current->GetObject()->UpdateCOM(*new_object);

        if (!this->current->GetQuadrant(quadrant)) {
            this->current = this->current->NewSubQuadrant(quadrant);
        }
        else {
            this->current = this->current->GetQuadrant(quadrant);
        }

        this->Insert(new_object); // should run the initial if-block of this function
    }


    /**
     * Inserting in an external quadrant, detach the existing object and
     * plop in a COM object, then insert the detached and new object
     */
    void sQuadtree::InsertExternal(sObject *new_object, int correct_quad)
    {
        // current quadrant's object is normal object, convert it to COM
        sObject *detached = this->current->GetObject();

        sObject *com = new sObject(sPoint(0, 0), 0, 0, "Root COM");
        com->SetIsCOM(true);

        this->current->SetObject(*com);

        // after setting the COM object, this quadrant will serve as a
        // launch point to insert the new and detached objects
        sQuadrant *pointer_to_com = this->current;

        this->Insert(detached);

        this->PointCurrentTo(pointer_to_com);
        this->Insert(new_object);
    }
}

