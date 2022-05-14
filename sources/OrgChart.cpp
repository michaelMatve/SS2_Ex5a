#include "OrgChart.hpp"

namespace ariel{

//////////////////////////////////////////////////////////////////
///////////////OrgChart class ////////////////////////////////////
//////////////////////////////////////////////////////////////////

    OrgChart::OrgChart()
    {
        this->root = nullptr;
    }

    //change root
    OrgChart& OrgChart::add_root(std::string data)
    {
        if(this->root = nullptr)
        {
           
            this->root = new ONode{data};
        }
        this->root->data = data;
        return *this;
    }

    //add children
    OrgChart& OrgChart::add_sub(std::string son, std::string father)
    {
        ONode* pointer_father = this->find(father);
        ONode* pointer_son = new ONode(son);
        pointer_son->father = pointer_father;
        pointer_son -> brother = pointer_father->child;
        pointer_father->child = pointer_son ;
    }

    OrgChart::level_order_Iterator OrgChart::begin_level_order()
    {
        
        return level_order_Iterator(this->root).full_tor();
    }

    OrgChart::level_order_Iterator OrgChart::end_level_order()
    {
        return nullptr;
    }
    
    OrgChart::reverse_order_Iterator OrgChart::begin_reverse_order()
    {
        return reverse_order_Iterator(this->root);
    }

    OrgChart::reverse_order_Iterator OrgChart::end_reverse_order()
    {
        return nullptr;
    }

    OrgChart::preorder_Iterator OrgChart::begin_preorder()
    {
        return preorder_Iterator(this->root);
    }

    OrgChart::preorder_Iterator OrgChart::end_preorder()
    {
        return nullptr;
    }
    /////////////////////////////////////////////////
            //level_order_Iterator
    ////////////////////////////////////////////////

    std::string& OrgChart::level_order_Iterator::operator*(){
        return ptr->data;
    }
    
    OrgChart::level_order_Iterator& OrgChart::level_order_Iterator::operator++()
    {
        ++this->place;
        if(this->place == this->tor.size())
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->tor[this->place];
        }
        return *this;
    }
    
    OrgChart::level_order_Iterator OrgChart::level_order_Iterator::operator++(int)
    {
        level_order_Iterator temp = *this;
        ++this->place;
        if(this->place == this->tor.size())
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->tor[this->place];
        }
        return temp;
    }
    
    bool OrgChart::level_order_Iterator::operator!=(level_order_Iterator &other)
    {
        if(this->ptr!=other.ptr)
        {
            return true;
        }
        return false;
    }

    OrgChart::level_order_Iterator& OrgChart::level_order_Iterator::full_tor()
    {
        if(this->ptr == nullptr)
        {
            return *this;
        }

       this->tor.push_back(this->ptr);
       ONode* curr_node  = this->ptr;
       int tor_place = 0;

       while(tor_place < this->tor.size())
       {   
           curr_node = this->tor[tor_place];
           while(curr_node != nullptr)
           {
               this->tor.push_back(curr_node);
               curr_node = curr_node->brother;
           }
           ++tor_place;
       }
       return *this;
    }

        /////////////////////////////////////////////////
            //////reverse_order//////
        /////////////////////////////////////////////////
    std::string& OrgChart::reverse_order_Iterator::operator*()
    {
        return ptr->data;
    }
    
    OrgChart::reverse_order_Iterator& OrgChart::reverse_order_Iterator::operator++()
    {
        --this->place;
        if(this->place < 0)
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->stack[this->place];
        }
        return *this;
    }
    
    OrgChart::reverse_order_Iterator OrgChart::reverse_order_Iterator::operator++(int)
    {
        reverse_order_Iterator temp = *this;

       --this->place;
        if(this->place < 0)
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->stack[this->place];
        }
        return *this;

        return temp;
    }
    
    bool OrgChart::reverse_order_Iterator::operator!=(reverse_order_Iterator &other)
    {
        if(this->ptr!=other.ptr)
        {
            return true;
        }
        return false;
    }

    OrgChart::reverse_order_Iterator& OrgChart::reverse_order_Iterator::full_Stuck()
    {
        if(this->ptr == nullptr)
        {
            return *this;
        }

       this->stack.push_back(this->ptr);
       ONode* curr_node  = this->ptr;
       int stack_place = 0;

       while(stack_place < this->stack.size())
       {   
           curr_node = this->stack[stack_place];
           while(curr_node != nullptr)
           {
               this->stack.push_back(curr_node);
               curr_node = curr_node->brother;
           }
           ++stack_place;
       }

       this->place = stack_place-1;
       this->ptr =this->stack[this->place];
       return *this;
    }


        /////////////////////////////////////////////////
                //////preorder/////
        /////////////////////////////////////////////////


    std::string& OrgChart::preorder_Iterator::operator*()
    {
        return ptr->data;
    }
    
    OrgChart::preorder_Iterator& OrgChart::preorder_Iterator::operator++()
    {
        while(this->ptr != nullptr)
        {
            if(this->ptr->child != nullptr)
            {
                this->ptr = this->ptr->child;
                return *this;
            }
            if(this->ptr->brother != nullptr)
            {
                this->ptr = this->ptr->brother;
                return *this;
            }
            this->ptr = this->ptr->father;
        }
        return *this;
    }
    
    OrgChart::preorder_Iterator OrgChart::preorder_Iterator::operator++(int)
    {
        preorder_Iterator temp = *this;

        while(this->ptr != nullptr)
        {
            if(this->ptr->child != nullptr)
            {
                this->ptr = this->ptr->child;
                return temp;
            }
            if(this->ptr->brother != nullptr)
            {
                this->ptr = this->ptr->brother;
                return temp;
            }
            this->ptr = this->ptr->father;
        }
        return temp;
    }
    
    bool OrgChart::preorder_Iterator::operator!=(preorder_Iterator &other)
    {
        if(this->ptr!=other.ptr)
        {
            return true;
        }
        return false;
    }


}