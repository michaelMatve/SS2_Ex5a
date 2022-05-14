#include <string>
#include <vector>

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
        OrgChart& add_sub(std::string son, std::string father);

        //find
        ONode* find(std::string data);
        //////level_order//////
        class level_order_Iterator
        {
            ONode * ptr;
            std::vector<ONode*> tor;
            int place;
        
            public:
                level_order_Iterator(ONode* new_ptr)
                {
                    this->ptr = new_ptr;
                    this->place = 0;
                }
    
                std::string& operator*();
    
                level_order_Iterator& operator++();

                level_order_Iterator operator++(int);
    
                bool operator!=(level_order_Iterator &other);

                level_order_Iterator& full_tor();
    
        };

    level_order_Iterator begin_level_order();

    level_order_Iterator end_level_order();

    //////reverse_order//////
    
        class reverse_order_Iterator
        {
            ONode * ptr;
            std::vector<ONode*> stack;
            int place;
        
            public:
                reverse_order_Iterator(ONode* new_ptr)
                {
                    this->ptr = new_ptr;
                    this->place = 0;
                }
    
                std::string& operator*();
    
                reverse_order_Iterator& operator++();

                reverse_order_Iterator operator++(int);

                bool operator!=(reverse_order_Iterator &other);
                
                reverse_order_Iterator& full_Stuck();
    
        };

    reverse_order_Iterator begin_reverse_order();

    reverse_order_Iterator end_reverse_order();

        //////preorder/////

        class preorder_Iterator
        {
            ONode * ptr;
        
            public:
                preorder_Iterator(ONode* new_ptr)
                {
                    this->ptr = new_ptr;
                }
    
                std::string& operator*();
    
                preorder_Iterator& operator++();

                preorder_Iterator operator++(int);
    
                bool operator!=(preorder_Iterator &other);
    
        };

    preorder_Iterator begin_preorder();

    preorder_Iterator end_preorder();


    };
}

