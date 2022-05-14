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
        if(this->root == nullptr)
        {
           
            this->root = new ONode{data};
        }
        this->root->data = data;
        return *this;
    }

    //add children
    OrgChart& OrgChart::add_sub(std::string father, std::string son)
    {
        ONode* pointer_father = this->find(father);
        if(pointer_father == nullptr)
        {
            throw std::invalid_argument("not find");
        }
        ONode* pointer_son = new ONode(son);
        pointer_son->father = pointer_father;
        if(pointer_father->child == nullptr)
        {
            pointer_father->child = pointer_son ;
        }
        else
        {
            pointer_father = pointer_father->child;
            while(pointer_father->brother != nullptr)
            {
                pointer_father = pointer_father->brother;
            }
            pointer_father->brother = pointer_son;
        }
        return *this;
    }

    OrgChart::ONode* OrgChart::find(std::string data)
    {
        for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
        {
            if(*it == data)
            {
                return it.get_ptr();
            }
        }
        return nullptr;
    }

    std::ostream& operator<<(std::ostream& My_output,const OrgChart& tree)
    {
        My_output<<"-----------------start----------"<<"\n";
        ulong colums =0;

        OrgChart::ONode* curr_node = tree.root;
        
        My_output<< curr_node->data;
        colums = curr_node->data.size();

        while(curr_node!= nullptr)
        {
            if(curr_node->child != nullptr)
            {
                curr_node= curr_node->child;
                My_output<< " -> " <<curr_node->data;
                colums = colums+curr_node->data.size() + 5 ;
            }
            else if(curr_node->brother != nullptr)
            {
                colums = colums -curr_node->data.size() - 5 ;
                curr_node = curr_node->brother;
                My_output<< "\n";
                for(int i= 0 ; i<colums ; i++)
                {
                   My_output<<" ";  
                }
                My_output<< " -> " <<curr_node->data;
            }
            else
            {
                curr_node = curr_node->father;
                colums = colums -curr_node->data.size() - 5 ;
            }
        }

        My_output<<"-----------------end----------"<<std::endl;
        return My_output;
    }
    
    OrgChart::Iterator OrgChart::begin_level_order()
    {
        
        return Iterator(this->root).full_tor();
    }

    OrgChart::Iterator OrgChart::end_level_order()
    {
        return nullptr;
    }
    
    OrgChart::Iterator OrgChart::begin_reverse_order()
    {
        return Iterator(this->root).full_stack();
    }

    OrgChart::Iterator OrgChart::reverse_order()
    {
        return nullptr;
    }

    OrgChart::Iterator OrgChart::begin_preorder()
    {
        return Iterator(this->root).full_vec();
    }

    OrgChart::Iterator OrgChart::end_preorder()
    {
        return nullptr;
    }
 
    OrgChart::Iterator OrgChart::begin()
    {
        return this->begin_preorder();
    }

    OrgChart::Iterator OrgChart::end()
    {
        return this->end_preorder();
    }
 
    std::string& OrgChart::Iterator::operator*()
    {
        return this->ptr->data;
    }

    std::string* OrgChart::Iterator::operator->()
    {
        return &(this->ptr->data);
    }
    
    OrgChart::Iterator& OrgChart::Iterator::operator++()
    {
        ++this->place;
        if(this->place == this->ptr_vec.size())
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->ptr_vec[this->place];
        }
        return *this;
    }
    
    OrgChart::Iterator OrgChart::Iterator::operator++(int)
    {
        Iterator temp = *this;
        ++this->place;
        if(this->place == this->ptr_vec.size())
        {
            this->ptr = nullptr;
        }
        else
        {
            this->ptr = this->ptr_vec[this->place];
        }
        return temp;
    }
    
    bool OrgChart::Iterator::operator!=(const Iterator &other) const
    {
        if(this->ptr!=other.ptr)
        {
            return true;
        }
        return false;
    }

    OrgChart::Iterator& OrgChart::Iterator::full_tor()
    {
        if(this->ptr == nullptr)
        {
            return *this;
        }

       this->ptr_vec.push_back(this->ptr);
       ONode* curr_node  = this->ptr;
       ulong tor_place = 0;

       while(tor_place < this->ptr_vec.size())
       {   
           curr_node = this->ptr_vec[tor_place];
           curr_node = curr_node->child;
           while(curr_node != nullptr)
           {
               this->ptr_vec.push_back(curr_node);
               curr_node = curr_node->brother;
           }
           ++tor_place;
       }
       return *this;
    }

    OrgChart::Iterator& OrgChart::Iterator::full_stack()
    {
        *this = this->full_tor();
        for(ulong index = 0 ; index< (this->ptr_vec.size()/2); index++)
        {
            ONode* tmp = this->ptr_vec[index];
            this->ptr_vec[index] = this->ptr_vec[ptr_vec.size()-1-index] ;
            this->ptr_vec[ptr_vec.size()-1-index] = tmp;
        }
        return *this;
    }

    OrgChart::Iterator& OrgChart::Iterator::full_vec()
    {
        ONode* curr_node = this->ptr;
        this->ptr_vec.push_back(curr_node);
        while(curr_node!= nullptr)
        {
            if(curr_node->child != nullptr)
            {
                curr_node= curr_node->child;
                this->ptr_vec.push_back(curr_node);
            }
            else if(curr_node->brother != nullptr)
            {
                curr_node= curr_node->brother;
                this->ptr_vec.push_back(curr_node);
            }
            else
            {
                this->ptr = this->ptr->father;
            }
        }
        return *this;
    }
    OrgChart::ONode* OrgChart::Iterator::get_ptr()
    {
        return this->ptr;
    }
}