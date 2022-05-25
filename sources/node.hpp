#pragma once

#include <iostream>
#include <vector>


namespace ariel{
        /**
     * @brief struct to hold details about the node
     * @param parent:save the father node
     * @param role: save the name/role of the employee
     * @param childs: vector that save the children of curr node
     * @param num_of_children: save the number of node's childs
     */
    class node
    {
        public:
        node();
        node(const std::string& name,int level):name(name),level(level){}
        node(const node& other)
        {
            this->childs = other.childs;
            this->level = other.level;
            this->name = other.name;
            this->parent = other.parent;
        }
        node(node &&) noexcept;
        ~node(){
                for (node* c : this->childs) {
                    delete c;
                }
        }
        node& operator=(node const&);
        node& operator=(node&&) noexcept;// move assigemnt operator
        std::string parent;
        std::string name;
        std::vector<node*> childs;
        int level;
    };
}