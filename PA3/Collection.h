#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <iostream>
#include "Jeans.h"
#include "Stress_ball.h"

using namespace std;

/* Samyam Pandey - CSCE 221 */

enum class Sort_choice{bubble_sort, insertion_sort, selection_sort};

template <class Obj, class F1, class F2>
class Collection{
private:
    Obj *array;
    int size;
    int capacity;
    void resize();
public:
    Collection();
    Collection(int cap);
    Collection(const Collection& c);
    Collection& operator=(const Collection& c);
    ~Collection();
    Collection(Collection&& c);
    Collection& operator=(Collection&& c);
    void insert_item(const Obj& sb);
    bool contains(const Obj& sb) const;
    Obj remove_any_item();
    void remove_this_item(const Obj& sb);
    void make_empty();
    bool is_empty() const;
    int total_items() const;
    int total_items(F2 s) const;
    int total_items(F1 c) const;
    void print_items() const;
    Obj& operator[](int i);
    const Obj& operator[](int i) const;
};
template <class Obj, class F1, class F2>
Collection<Obj, F1, F2>::Collection() {
    array = nullptr;

    this->size = 0;

    this->capacity = 0;
}

template <class Obj, class F1, class F2>
Collection<Obj, F1, F2>::Collection(int sze) {

    array = new Obj[sze];

    this->size = 0;

    this->capacity = sze;
}
template <class Obj, class F1, class F2>
Collection<Obj, F1, F2>::Collection(const Collection& c) {

    size = c.size; // size

    capacity = c.capacity;


    array = new Obj[size];

    for (int i =0; i<size; ++i) {

        array[i] = c.array[i];
    }
}
template <class Obj, class F1, class F2>
Collection<Obj,F1,F2>& Collection<Obj,F1,F2>:: operator=(const Collection& c) {
    if (this != &c) {

        delete [] array;

        capacity = c.capacity;

        size = c.size;

        array = new Obj[capacity];

        for (int i =0; i< size; ++i) {

            array[i] = c.array[i];
        }
    }
    
    return *this;
}

template <class Obj, class F1, class F2>
Collection<Obj, F1, F2>::~Collection() { // destructor

    delete [] array;

    size = 0;

    capacity = 0; // size and capacity = 0
    // same as make empty
}

template <class Obj, class F1, class F2>
void Collection<Obj, F1,F2>::resize(){
    Obj* genericOb;
    if(capacity == 0){
        capacity =1;
    }
    genericOb = new Obj[capacity*2];
    for(int i = 0; i < size; i++){
        genericOb[i] = array[i];
    }
    delete array;
    array = genericOb;
    capacity*=2;
}

template <class Obj, class F1, class F2>
Collection<Obj, F1,F2>::Collection(Collection&& c) {
    size = c.size;

    capacity = c.capacity;

    array = c.array;

    c.array = nullptr; // nullptr so free the ptr

    c.size = 0;

    // c.capacity = 0;

}

template <class Obj, class F1, class F2>
Collection<Obj,F1,F2>& Collection<Obj, F1,F2>::operator=(Collection&& c) {
    
    if (this != &c) {

        size = c.size;
        capacity = c.capacity;

        array = c.array;


    
        c.array = nullptr;
        c.size = 0;
       
    }

    return *this;
}

template <class Obj, class F1, class F2>
void Collection<Obj, F1,F2>::insert_item(const Obj &sb) {
        if (size == capacity)
            this->resize();
        array[size] = sb;
        size++;
}

template <class Obj, class F1, class F2>
bool Collection <Obj, F1,F2>::contains (const Obj& sb) const {

    for (int i = 0; i < size; ++i) {

        if (array[i] == sb)
            return true;
    }
    return false;
}

template <class Obj, class F1, class F2>
Obj Collection<Obj, F1,F2>::remove_any_item(){
    Obj tempObject;
    if (size == 0)
    {
        throw "Collection empty";
    }
    int temp = rand() % size;

    Obj *n_arr = new Obj[capacity];

    int ct = 0;

    for (int i = 0; i < size; i++)
    {
        if (i != temp)
        {
            n_arr[ct] = array[i];
            ct++;
        }
        else
        {
            tempObject = Obj(array[i].get_color(), array[i].get_size());
        }
    }
    delete[] array;
    array = n_arr;
    size--;
    return tempObject;
}


template <class Obj, class F1, class F2>
void Collection<Obj, F1,F2>::remove_this_item(const Obj& sb){
    if (size == 0 || !contains(sb))
    {
        cerr << "Collection is empty";
        return;
    }
    Obj *new_array = new Obj[capacity];
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (!(array[i] == sb))
        {
            new_array[count] = array[i];
            count++;
        }
    }
    delete[] array;
    array = new_array;
    size--;
}

template <class Obj, class F1, class F2>
void Collection<Obj, F1,F2>::make_empty() {
    delete[] array;

    array = nullptr;



    size = 0;
    capacity = 0;
}

template <class Obj, class F1, class F2>
bool Collection<Obj, F1,F2>::is_empty() const {
    if (size==0) 
        return true;
    return false;

}

template <class Obj, class F1, class F2>
void Collection<Obj, F1,F2>::print_items() const {
    for (int i = 0; i < size; ++i) {
        
        cout << array[i] << endl; // printing items
    }
}

template <class Obj, class F1, class F2>
int Collection<Obj, F1,F2>::total_items () const {return size;}

template <class Obj, class F1, class F2>
int Collection<Obj, F1,F2>::total_items (F2 s) const {
    int num = 0;

    for (int i = 0; i < size; ++i) {

        if (array[i].get_size()==s)
            num++;
    }
    return num;
}

template <class Obj, class F1, class F2>
int Collection<Obj, F1,F2>::total_items (F1 c) const {
    int num = 0;

    for (int i = 0; i < size; ++i) {
        if (array[i].get_color()==c) 
            num++; 
    }
    return num;
}

template <class Obj, class F1, class F2>
Obj& Collection<Obj, F1,F2>::operator[](int i) {
    return array[i];
}

template <class Obj, class F1, class F2>
const Obj& Collection <Obj, F1,F2>::operator[](int i) const{
    return array[i];
}


template<class Obj, class F1, class F2>
ostream& operator<<(ostream& os, const Collection<Obj, F1, F2> &c) {

    for (int i = 0; i < c.total_items(); i++)
    {
        os << c[i] << endl;
    }
    return os;
}




template <class Obj, class F1, class F2>
Collection<Obj, F1, F2> make_union (const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2) {
    Collection<Obj, F1, F2> * c3 = new Collection<Obj, F1, F2>(); // make union with c1 and c2 = adding sizes
    
    for (int i = 0; i<c1.total_items(); ++i) {
        c3->insert_item(c1[i]);
    }
    for (int i = 0; i<c2.total_items(); ++i) {
        c3->insert_item(c2[i]);
    }

    return *c3;
}

template <class Obj, class F1, class F2>
void swap (Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2) {
    Collection<Obj, F1, F2> tmpBall;
    tmpBall = c1;
    c1 = Collection<Obj, F1, F2>(c2); // move const
    c2 = Collection<Obj, F1, F2>(tmpBall);
}

template <class Obj, class F1, class F2>
void sort_by_size(Collection<Obj, F1, F2>& c, Sort_choice sort) {
    switch(sort) {

        case Sort_choice::bubble_sort: 
            for (int i = 1 ; i < c.total_items(); ++i) {

                bool numb = false;

                for (int j = 0; j < c.total_items()-i; j++) {
                    /*
                    for (int j = 0; j < c.total_items()-i; j++) {
                        go through items
                        */

                    if (c[j].get_size() > c[j+1].get_size()) {
                        
                        Obj tmpBall = c[j];
                        c[j] = c[j+1];
                        c[j+1] = tmpBall;
                        numb = true;
                    }
                }
                if (numb==false) break; // break when is false
            }
            break;

        case Sort_choice::insertion_sort: 
            for (int i = 0; i<c.total_items(); ++i) {

                Obj tmpBall = c[i];
                int j = i;
                for ( ; (j>0) && (tmpBall.get_size() < c[j-1].get_size()); j--) {
                    c[j] = c[j-1];
                }
                c[j] = tmpBall;
            }
            break;
        case Sort_choice::selection_sort: 
            for (int i =0; i< c.total_items()-1; ++i) 
            {
                int indx = i;
                for (int j = i+1; j < c.total_items(); j++) 
                {
                    if (c[j].get_size() < c[indx].get_size()) {
                        indx = j;
                    }
                }
                Obj tmpBall = c[i];

                c[i] = c[indx];


                c[indx] = tmpBall;
            }
            break;
    }
}




#endif
