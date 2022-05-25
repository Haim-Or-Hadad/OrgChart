// #include <iostream>
// #include <vector>
// #include <bits/stdc++.h>
// #include "OrgChart.hpp"

// using namespace std;


// namespace ariel
// {

//     /*OrgIterator constructor*/
//     OrgChart::OrgIterator::OrgIterator(std::vector<node*> & it_vector)
//     {
//         this->it_vector =  it_vector;
//         this->ptr = 0;
//     }

// bool operator == (OrgChart::OrgIterator const &first_iter, OrgChart::OrgIterator const &second_iter) {
//         return first_iter.it_vector.at(first_iter.ptr) == second_iter.it_vector.at(second_iter.ptr);
//     }
//     bool OrgChart::OrgIterator::operator != (OrgChart::OrgIterator const &other) {
//      return !(*this == other);
//     }
//     string OrgChart::OrgIterator::operator*()const{
//         return this->it_vector.at(this->ptr)->name;
//     }
//     OrgChart::OrgIterator& OrgChart::OrgIterator::operator ++ (){
//         this->ptr++;
//         return *this;
//     }
//     string const * OrgChart::OrgIterator::operator->() const{
//         return &this->it_vector.at(ptr)->name;
//     }
// };