//#pragma once

#include <iostream>
#include <vector>
#include "node.hpp"
#include <stdexcept>

namespace ariel
{
    class OrgChart
    {
        public:
        /******************class Iterator - inner class*********************/
        /**
         * @brief this class represents iterator  
         * level order,reverse order and preorder
        * @param it_vector:vector for iterate over the structure
        * @param ptr: pointer to the current place the iterator point now
         */
        class OrgIterator : public std::iterator<std::forward_iterator_tag, node*> 
        {
        private:
        std::vector<node*> *it_vector;
        size_t ptr;

        public:
        /*constructor*/
        OrgIterator(std::vector<node*>&);

        /*operators of iterator*/
        friend bool operator == (OrgIterator const &first_iter, OrgIterator const &second_iter);
        bool operator != (OrgIterator const &other)const;
        std::string operator*() const;
        OrgIterator & operator ++ ();
        std::string const * operator->() const;
        };
        /*end of iterator class*/
        /**
         * @brief this class represents orgchart that include some types of iterators 
         * level order,reverse order and preorder
         * @param _node: save all the details about the organization
         * @param find_parents: flag to know if son find is father in add_sub func
         */
        private:
        node *_node;
        bool find_parent;
        int num_of_nodes;
        /*vectors that save the order of each iterator*/
        std::vector<node*> order_vector;
        std::vector<node*> null_vector;
        public:
        /*constructor*/
        OrgChart();
        OrgChart(OrgChart &o)
        {
        this->_node = o._node;    
        this->find_parent = o.find_parent;
        this->num_of_nodes = o.num_of_nodes;
        }
            //copy
        OrgChart(OrgChart &&) noexcept; // move constructor


        /**
         * @brief add_ root func get a name and put this name in the head/root of the tree
         * @return OrgChart& 
         */
        OrgChart &add_root(const std::string& name);
        /**
         * @brief add_sub func get two string and add son to father if he exist
         * @return OrgChart& 
         */
        OrgChart &add_sub(const std::string&  person1,const std::string& person2);
        /**
         * @brief get the head of the tree and insert the elements in level order to order vector
         */
        void level_order_maker(node &head,  std::vector<node*> &level);
        /**
         * @brief insert the elements in reverse order to order vector
         */
        void reverse_order_maker();
        /**
         * @brief insert the elements in pre order to order vector
         */
        void pre_order_maker(node &head);
        /**
         * @brief 
         * 
         * @param order_type 
         * @return OrgIterator 
         */
        OrgIterator iterator_maker(int order_type);

        OrgIterator begin_level_order();
        OrgIterator end_level_order();
        OrgIterator begin_reverse_order();
        OrgIterator reverse_order();
        OrgIterator begin_preorder();
        OrgIterator end_preorder();

        std::string &_output(node &head);
        friend std::ostream &operator<<(std::ostream &output,  OrgChart &head);
        
        OrgChart& operator=(OrgChart const&);
        OrgChart& operator=(OrgChart&&) noexcept;// move assigemnt operator
        
        /*inline implements of begin and end iterator's methods*/
        OrgIterator begin() {return begin_level_order();}
        OrgIterator end(){return end_level_order();}
        
        /*recursive traversals for add_sub,level order,reverse order and pre order functions*/
        void parent_exist(node &head,const std::string& parent,const std::string& child);
                /*getters*/
        std::string &get_name(){return this->_node->name;}
        ////////////////////////////
        //bool OrgChart::OrgIterator::operator != (OrgChart::OrgIterator const &other)
        void add_node()
        {
            this->num_of_nodes++;
        }
        int  get_nodes_len() const
        {
            return this->num_of_nodes;
        }
        /*******Exceptions**********/
        void root_exist()
        {
        if (this->_node == nullptr)
            {
                 throw std::runtime_error("no root and chart is empty");
            }  
        }
        //void empty_string(const std::string & s);

    ~OrgChart();
    };
}
