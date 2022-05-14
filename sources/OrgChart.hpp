#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel{
    class OrgChart
    {
        private:
            struct ONode
            {
                std::string data;
                ONode* father;
                ONode* child;
                ONode* brother;
                ONode(std::string& data)
                {
                    this->data = data;
                    this->father = nullptr;
                    this->child = nullptr;
                    this->brother = nullptr;
                };
            };
            
        ONode* root;

        public:

        OrgChart();

        //change root
        OrgChart& add_root(std::string data);

        //add children
        OrgChart& add_sub(std::string father, std::string son);

        //find
        ONode* find(std::string data);

        friend std::ostream& operator<<(std::ostream& My_output,const OrgChart& tree);

        class Iterator
        {
            ONode * ptr;
            std::vector<ONode*> ptr_vec;
            ulong place;
        
            public:
                Iterator(ONode* new_ptr)
                {
                    this->ptr = new_ptr;
                    this->place = 0;
                }
                std::string& operator*();

                Iterator& operator++();
                
                Iterator operator++(int);
                
                bool operator!=(const Iterator &other) const ;

                Iterator& full_tor();
                
                Iterator& full_stack();

                Iterator& full_vec();

                std::string* operator->();

                ONode* get_ptr();

    };

    Iterator begin();

    Iterator end();

    Iterator begin_level_order();

    Iterator end_level_order();

    Iterator begin_reverse_order();

    Iterator reverse_order();

    Iterator begin_preorder();

    Iterator end_preorder();
    };
}

