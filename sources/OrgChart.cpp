#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "OrgChart.hpp"
#include <stdexcept>

using namespace std;


namespace ariel
{
    node::node(){
        this->parent = "";
        this->name = "";
        this->level =0;
    }
    /*OrgChart constructor*/
    OrgChart::OrgChart()
    {
        this->_node = nullptr;
        this->find_parent = false;
        this->num_of_nodes = 1;
        this->null_vector.push_back(nullptr);
    };
    
     OrgChart &OrgChart::add_root(const string&  name)
     {
         if (name.empty()){
             throw std::runtime_error("name empty");
         }
         if (this->_node != nullptr){
             this->_node->name = name;
             return *this;
         }
         node *new_node= new node();
         new_node->name = name;
         new_node->level = 0 ;
         this->_node = new_node;
         return *this;//return pointer to the head of tree
     }

     /*traversal over the tree if parent found so "find_parent" flag change to true */
    void OrgChart::parent_exist(node &head,const string&  parent,const string& child){
        if(head.name == parent)
        {
        node *new_node = new node();
        new_node->parent=parent;
        new_node->name=child;
        new_node->level = head.level+1;
        head.childs.push_back(new_node);
        this->add_node();
        this->find_parent = true;
        }
        else
        {
        for (auto& it : head.childs) {
            parent_exist((*it),parent,child);
        }
        }
    }
    /*this function add a new node to tree, if the parent's node doesn't exist so exception throws*/
    OrgChart &OrgChart::add_sub(const string & person1,const  string& person2)
    {
        this->root_exist();//throw exception if no root 
        this->empty_string(person1);
        this->parent_exist(*this->_node,person1,person2);
        if (!this->find_parent)
        {
            __throw_invalid_argument ("no parent");
        }
        this->find_parent = false;
        return *this;
    }
    //////////////////all-iterator////////////////////////
    /*0-level,1-reverse,2-pre order*/
    OrgChart::OrgIterator OrgChart::iterator_maker(int order_type){
        this->root_exist();
        this->order_vector.clear();
        if (order_type == 0)//if level order
        {
            //this->order_vector.push_back(this->_node);
            this->level_order_maker(*this->_node,this->order_vector);
        }
        else if (order_type == 1)//reverse order
        {
            this->reverse_order_maker();
        }
        else
        {
            this->pre_order_maker(*this->_node);
        }
        this->order_vector.push_back(nullptr);
        OrgIterator iterator(this->order_vector);
        return iterator;
    }
   ///////////////////////////////////////////////////////
   ///-----------------level-order---------------------///
   ///////////////////////////////////////////////////////
   /*traversal over the tree in level order*/
    void OrgChart::level_order_maker(node &head, std::vector<node*> &level)
    {      

        vector<node*> ve;
        ve.push_back(this->_node);
        size_t i = 0;
        while(i < ve.size())
        {
            node* temp = ve.at(i);
            vector<node*>::iterator it;
            for ( it = temp->childs.begin(); it != temp->childs.end(); ++it )//reverse iterator
            {
                ve.push_back((*it));
            }
            it++;
            i++;
        }
        for (int i = 0; i < ve.size(); i++)
        {
            node * n = ve[(size_t)i];
            order_vector.push_back(n);
        }
    }
    OrgChart::OrgIterator OrgChart::begin_level_order()
    {
        return iterator_maker(0);
    }
    OrgChart::OrgIterator OrgChart::end_level_order()
    {
        this->root_exist();
    OrgIterator iterator(null_vector);
    return iterator;
    }

   ///////////////////////////////////////////////////////
   ///-----------------reverse-order---------------------///
   ///////////////////////////////////////////////////////
   /*traversal over the tree in reverse order*/
   void OrgChart::reverse_order_maker(){
vector<node*> ve;
        ve.push_back(this->_node);
        size_t i = 0;
        while(i < ve.size())
        {
            node* temp = ve.at(i);
            vector<node*>::reverse_iterator it;
            for ( it = temp->childs.rbegin(); it != temp->childs.rend(); ++it )//reverse iterator
            {
                ve.push_back((*it));
            }
            it++;
            i++;
        }
        reverse(ve.begin(),ve.end());
        for (int i = 0; i < ve.size(); i++)
        {
            node * n = ve[(size_t)i];
            order_vector.push_back(n);
        }
   }
    OrgChart::OrgIterator OrgChart::begin_reverse_order()
    {
    return iterator_maker(1);
    }
    OrgChart::OrgIterator OrgChart::reverse_order()
    {
        this->root_exist();
    OrgIterator iterator(null_vector);
    return iterator;
    }

   ///////////////////////////////////////////////////////
   ///-----------------pre-order---------------------///
   ///////////////////////////////////////////////////////
       void OrgChart::pre_order_maker(node &head)
    {      
        this->order_vector.push_back(&head);
        for (size_t i = 0; i < head.childs.size(); i++)
        {
            pre_order_maker(*head.childs.at(i));
        }
    }
   /*traversal over the tree in pre order*/
    OrgChart::OrgIterator OrgChart::begin_preorder()
    {
        return iterator_maker(2);
    }

    OrgChart::OrgIterator OrgChart::end_preorder()
    {
        this->root_exist();
    OrgIterator iterator(null_vector);
    return iterator;
    }

    ostream &operator<<(ostream &output,  OrgChart &head)
    {
        int last_level=0;
        vector<node*> ve;
        ve.push_back(head._node);
        size_t i = 0;
        if (head._node->childs.size() > 1)
        {
            output << "            " << head._node->name ; 
        }
        while(i < ve.size())
        {   
            node* temp = ve.at(i);
            vector<node*>::iterator it;
            int j=0;
            for ( it = temp->childs.begin(); it != temp->childs.end(); ++it )//reverse iterator
            {
            if ((*it)->level > last_level )
            {
                output << endl;
                last_level = (*it)->level;
            }
                ve.push_back((*it));
                output << (*it)->name ;
                if (temp->childs.size()-1  != j )
                {
                    output <<" ------";
                }
                else
                {
                    output << "|";
                }
                
                j++;
                
            }
            it++;
            i++;
            
        }
         return output;
    }


    
    OrgChart::~OrgChart(){}
    
    /*OrgIterator constructor*/
    OrgChart::OrgIterator::OrgIterator(std::vector<node*> & it_vector)
    {
        this->it_vector =  &it_vector;
        this->ptr = 0;
    }

bool operator == (OrgChart::OrgIterator const &first_iter, OrgChart::OrgIterator const &second_iter) {
   // return first_iter.it_vector->at(first_iter.ptr)
        return (first_iter.it_vector->at(first_iter.ptr) == second_iter.it_vector->at(second_iter.ptr));
    }
    bool OrgChart::OrgIterator::operator != (OrgChart::OrgIterator const &other)const {
     return !(*this == other);
    }
    string OrgChart::OrgIterator::operator*()const{
        return it_vector->at(this->ptr)->name;
    }
    OrgChart::OrgIterator& OrgChart::OrgIterator::operator ++ (){
        this->ptr++;
        return *this;
    }
    string const * OrgChart::OrgIterator::operator->() const{
        return &it_vector->at(ptr)->name;
    }

};



// using namespace ariel;
// int main(){
//     OrgChart organization;
//     organization.add_root("manager");
//     //cout << organization.get_name() << endl;
//     organization.add_sub("manager","Assistant1");
//    //cout << organization.get_list().at(0).role << endl;
//    organization.add_root("manager");
//     organization.add_sub("manager","Assistant2");
//     // //cout << organization.get_list().at(1).role << endl;
//     organization.add_sub("Assistant1","player1");
//     // //cout << organization.get_list().at(2).role << endl;
//     organization.add_sub("Assistant2","player2");
//     organization.add_sub("Assistant2","player3");
//     cout << organization << endl;
    //organization.add_root("haim");
// //     //cout << organization.get_list().at(3).role << endl;
// //     //cout << organization.get_list().at(4).role << endl;
// // //     // for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
// // //     // {
// // //     // cout << organization << endl ;
// // //     // //} // prints: CEO CTO CFO COO VP_SW VP_BI
// // //     // //return 1;
// // //     cout << "level order:" << endl;
// // // for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
// // //   {
// // //     cout << (*it) << endl ;
// // //   }
// // //   cout <<  endl ;
// // //   cout << "reverse order:" << endl;
// // //     for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
// // //   {
// // //     cout << (*it) << " " ;
// // //   } // prints: VP_SW VP_BI CTO CFO COO CEO
// //     cout <<  endl ;
// //     OrgChart org;
// //     org.add_root("shir");
// //     org.add_sub("shir", "tal");
// //     org.add_sub("shir", "sapir");
// //     org.add_sub("sapir", "dan");
// //     org.add_sub("dan", "ziv");
// //     org.add_sub("tal", "avi");
// //     org.add_sub("tal", "yossi");
// //     org.add_sub("shir", "ido");
// //     org.add_sub("ziv", "shaked");
// //     org.add_sub("ziv", "ofer");
// //         std::vector<std::string> v = {"shaked", "ofer", "ziv", "avi", "yossi", "dan", "tal", "sapir", "ido", "shir"};
// //         size_t i = 0;
// //         for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
// //             cout << "iterator" <<*it << "vector" << v.at(i++) << endl;
// //         }
//     OrgChart chart2;
//             chart2.add_root("Owner");
//             chart2.add_root("New_Owner");
//             chart2.add_sub("New_Owner" , "General_Manager");
//             chart2.add_sub("New_Owner" , "Share_Holders");
//             chart2.add_sub("New_Owner" , "Head_of_operations");
//             chart2.add_sub("General_Manager" , "Head_Coach");
//             chart2.add_sub("General_Manager" , "Assistant_Coach");
//             chart2.add_sub("Head_of_operations" , "Team_Doctor");
//             chart2.add_sub("Head_of_operations" , "Head_Scout");
//             chart2.add_sub("Share_Holders" , "Sub_Share_Holder1");
//             chart2.add_sub("Share_Holders" , "Sub_Share_Holder2");
//             chart2.add_sub("Head_Coach" , "Captain");
//             chart2.add_sub("Team_Doctor" , "Team_Physiotherapist");
//             // test level order
//             vector<string> lvl_order;
//             for (auto it = chart2.begin_level_order(); it != chart2.end_level_order(); ++it)
//             {
//                lvl_order.push_back(*it);
//             }
//             cout << lvl_order.at(0)<<"-------"<< "New_Owner" << endl;
//             cout << lvl_order.at(1)<<"-------" << "General_Manager"<< endl;
//             cout << lvl_order.at(2) <<"-------"<< "Share_Holders"<< endl;
//            cout << lvl_order.at(3) <<"-------"<< "Head_of_operations"<< endl;
//             cout << lvl_order.at(4)<<"-------" << "Head_Coach"<< endl;
//             cout << lvl_order.at(5) <<"-------"<< "Assistant_Coach"<< endl;
//             cout << lvl_order.at(6) <<"-------"<< "Sub_Share_Holder1"<< endl;
//             cout << lvl_order.at(7)<<"-------" << "Sub_Share_Holder2"<< endl;
//             cout << lvl_order.at(8) <<"-------"<< "Team_Doctor"<< endl;
//             cout << lvl_order.at(9) <<"-------"<< "Head_Scout"<< endl;
//             cout << lvl_order.at(10) <<"-------"<< "Captain"<< endl;
//             cout <<  lvl_order.at(11) <<"-------"<< "Team_Physiotherapist"<< endl;
 // }