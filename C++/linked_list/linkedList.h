#ifndef _LIST_H
#define _LIST_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <stdlib.h>

namespace llist{

    enum class ListStatus
    {
        SUCCESS,
        TRUE,
        FALSE,

        LIST_EMPTY,
        LIST_DATA_NOT_FOUND
    };

    class list_data_not_found: public std::runtime_error
    {
        public:
            list_data_not_found(const char* msg):std::runtime_error(msg)
            {

            }
    };

    class list_empty: public std::runtime_error
    {
        public:
            list_empty(const char* msg):std::runtime_error(msg)
            {

            }
    };

    template <typename T> // Make it varadic template based on T type constuction
    class node 
    {
            template <typename V>
            friend class list;

            template<typename V>
            friend class _List_iterator;
            
            template<typename V>
            friend class _List_const_iterator;              
        private:
            T mData;
            node* pNext;
            node* pPrev;
            template<typename... Args>
        
            node(Args&&... args)
                : mData(std::forward<Args>(args)...),
                pNext(nullptr),
                pPrev(nullptr)
    {}
    };

    template<typename T>
    class _List_iterator 
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = T*;
            using reference         = T&;
            
            node<T>* pNode;

            _List_iterator():pNode(nullptr){}
            explicit _List_iterator(node<T>* _x): pNode(_x){}
            T& operator*() const
            {
                return pNode->mData;
            }

            T* operator->() const
            {
                return std::addressof(*this);
            }

            _List_iterator<T>& operator++()
            {
                pNode = pNode->pNext;
                return *this;
            }

            _List_iterator<T> operator++(int)
            {
                _List_iterator _tmp = *this;
                pNode = pNode->pNext;
                return _tmp;
            }

            _List_iterator<T>& operator--()
            {
                pNode = pNode->pPrev;
                return *this;
            }

            _List_iterator<T> operator--(int)
            {
                _List_iterator _tmp = *this;
                pNode = pNode->pPrev;
                return _tmp;
            }

            bool operator==(const _List_iterator<T>& _x) const
            {
                return (pNode == _x.pNode);
            }  

            bool operator!=(const _List_iterator<T>& _x) const
            {
                return (pNode != _x.pNode);
            }          
    };

template<typename T>
    class _List_const_iterator 
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = T*;
            using reference         = T&;

            node<T>* pNode;

            _List_const_iterator():pNode(nullptr){}
            explicit _List_const_iterator(node<T>* _x): pNode(_x){}
            _List_const_iterator(const _List_const_iterator& _x):pNode(_x.pNode){}

            T& operator*() const
            {
                return pNode->mData;
            }

            T* operator->() const
            {
                return std::addressof(*this);
            }

            _List_const_iterator<T>& operator++()
            {
                pNode = pNode->pNext;
                return *this;
            }

            _List_const_iterator<T> operator++(int)
            {
                _List_const_iterator _tmp = *this;
                pNode = pNode->pNext;
                return _tmp;
            }

            _List_const_iterator<T>& operator--()
            {
                pNode = pNode->pPrev;
                return *this;
            }

            _List_const_iterator<T> operator--(int)
            {
                _List_const_iterator _tmp = *this;
                pNode = pNode->pPrev;
                return _tmp;
            }

            bool operator==(const _List_const_iterator<T>& _x) const
            {
                return (pNode == _x.pNode);
            }  

            bool operator!=(const _List_const_iterator<T>& _x) const
            {
                return (pNode != _x.pNode);
            }          
    };

    template <typename val>
    inline bool operator==(_List_iterator<val>& _x, _List_const_iterator<val>& _y)
    {
        return _x.pNode == _y.pNode;
    }

    template <typename val>
    inline bool operator!=(_List_iterator<val>& _x, _List_const_iterator<val>& _y)
    {
        return _x.pNode != _y.pNode;
    }    

    template <typename T>
    class list
    {
        private:
            node<T>* pHeadNode;
            std::size_t nrNodes;
        
        public:
            using iterator = _List_iterator<T>;
            using const_iterator = _List_const_iterator<T>;
            using reverse_iterator = std::reverse_iterator<_List_iterator<T>>;
            using reverse_const_iterator = std::reverse_iterator<_List_const_iterator<T>>;
            using difference_type = std::ptrdiff_t;

        protected:
            template<typename... Args>
            node<T>* getNode(Args... args)
            {
                return new node<T>(std::forward<Args>(args)...);
            }

            void putNode(node<T>* _p)
            {
                if(_p != nullptr)
                    delete _p;
            }

            node<T>* createNode(T _val)
            {
                // get node and allocate using allocatot -  handle exception
            }

            static void generic_insert(node<T>* _beg, node<T>* _mid, node<T>* _end)
            {
                _mid->pNext = _end;
                _mid->pPrev = _beg;
                _beg->pNext = _mid;
                _end->pPrev = _mid;
            }
            
            template<typename... _Args>
            void generic_insert(iterator _p, _Args&&... _args)
            {
               // Implementing later
            }


            static void generic_delete(node<T>* _delete_node)
            {
                _delete_node -> pPrev -> pNext = _delete_node -> pNext;
                _delete_node -> pNext -> pPrev = _delete_node -> pPrev;
                delete _delete_node;                
            }
            
            void fillInitialize(size_t _n, T _val)
            {
                while(_n--)
                {   
                    push_back(_val);
                }              
            }

            template <typename inputIterator>
            void fillInitialize(inputIterator _first, inputIterator _last)
            {
                for(;_first != _last; ++_first)
                {
                    push_back(*_first);
                }   
            }
            
            /**
             * @brief Search a given eleemnt in the list
             * @param Eleemnt to be searched in list
             * @return Return nodes address with read-write access 
             */
            node<T>* search_node(T searchData)
            {
                iterator iter = search_node(searchData);
                
                return iter.pNode;
            }            

        public:
            // Constructors
            // @brief Default constructor creates head node with -1 value
            list():pHeadNode(std::move(getNode(T{}))), nrNodes(0)
            {
                pHeadNode->pNext = pHeadNode;
                pHeadNode->pPrev = pHeadNode;
            }

            /**
             * @brief Copy constructor, creates new list as copy of l
             * @param l other list to be copied             
             */
            list(const list<T>& _l) : list()
            {
                fillInitialize(_l.cbegin(), _l.cend());
            }

            /**
             * @brief Move constructor, creates new list out of content of @l
             * @param l other list to be moved               
             */
            list(list<T>&& _l):list()
            {
                this->swap(_l);
            } 

            /**
             * @brief Creates a %list with copies of an default value
             * @param n The number of elements to initially create
             * Constructor fills the list with _n copies with default value
             */
            list(size_t _n):list()
            {
                fillInitialize(_n, T{});
            }

            /**
             * @brief Creates a %list with copies of an exempler elements
             * @param n The number of elements to initially create
             * @param value An element to copy
             * Constructor fills the list with _n copies with _value
             */
            list(size_t _n, const T& _value):list()
            {
                fillInitialize(_n, _value);
            }

            /**
             * @brief Create list initialized with initializer_list
             * @param l initializer list
             */            
            list(std::initializer_list<T> _l):list()
            {
                fillInitialize(_l.begin(), _l.end());
            }

            /**
             * @brief Create list initialized with 2 iterators
             * @param first input iterator starting position
             * @param last input iterator end position
             */                
            template <typename inputIterator>
            list(inputIterator _first, inputIterator _last):list()
            {
                fillInitialize(_first, _last);
            }

            //Destructor
            ~list()
            {
                if(!pHeadNode)
                    return;
                clear();
                delete pHeadNode;
                pHeadNode = nullptr;
            }

            // Assignment operations
            /**
             * @brief Assigns all elements of @l to exisitn list - Assignment operator
             * @param l other list to be assigned
             */            
            list<T>& operator=(const list<T>& _l)
            {
                this->swap(_l);
                return *this;
            } 

            /**
             * @brief Moves all elements of @l to exisitn list - Move assignment operator
             * @param l other list to be moved
             */            
            list<T>& operator=(list<T>&& _l)
            {
                this->swap(_l);
                return *this;
            }

            /**
             * @brief Assigns all elements of the initializer list to existing list
             * @param l initializer list
             */            
            list<T>& operator=(std::initializer_list<T> _l)
            {
                this->assign(_l.begin(), _l.end());
                return *this;
            }
            
            /**
             * @brief Assigns n copies of elements of @value to exisitn list
             * @param n number of copies
             * @param value element value
             */             
            void assign(size_t _n, T _value)
            {
                size_t _count = 0;
                iterator _it = begin();
 
                for(; _it != end() && _count < _n; ++_count, ++_it)
                {
                    *_it = _value;
                }

                if(_count == _n)
                {
                    erase(_it, end());
                }
                else
                {
                    for(;_count < _n; ++_count)
                        emplace_back(_value);
                }
            }

            /**
             * @brief Assigns elements of range [beg,end)
             * @param beg starting position
             * @param end end position
             */
            template <typename inputIterator>             
            void assign(inputIterator _first, inputIterator _last)
            {
                size_t _count;
                iterator _it = begin();

                for(; _it != end() && _first != _last; ++_it, ++_first)
                {
                    *_it = *_first;
                }

                if(_first == _last)
                {
                    erase(_it, end());
                }
                else
                {
                    for(;_first != _last; ++_first)
                        emplace_back(*_first);
                }                
            }

            /**
             * @brief Assigns elements of initializerlist
             * @param l Initializer list
             */             
            void assign(std::initializer_list<T> _l)
            {
                assign(_l.begin(), _l.end());
            }
            
            /**
             * @brief Swap the data of list with @l list
             * @param l other list to be assigned
             */               
            void swap(list<T>& _l) throw()
            {
                std::swap(pHeadNode, _l.pHeadNode);
                std::swap(nrNodes, _l.nrNodes);
            }
            
            /**
             * @brief Swap the data of list with @l list
             * @param l other list to be assigned
             */               
            void static swap(list<T>& _l1, list<T>& _l2)
            {
                std::swap(_l1.pHeadNode, _l2.pHeadNode);
                std::swap(_l1.nrNodes, _l2.nrNodes);
            }
            // Nonmodifying operations
            /**
             * @brief Returns whether list is empty  equivalent to size()==0 but faster
             */
            bool empty()const
            {
                return (pHeadNode->pNext == pHeadNode && pHeadNode->pPrev == pHeadNode);
            }

            /**
             * @brief Returns the current number of elements
             */
            difference_type size()const
            {
                return std::distance(cbegin(), cend());
            }

            /**
             * @brief Returns max number of possible elements
             */
            size_t max_size()const
            {
                return nrNodes;
            }
            
            /**
             * @brief Returns whether list is equal to @l (calls == for all elements)
             * @param l amother list to be compared
             */
            bool operator==(const list<T>& _l)const
            {
                if (nrNodes != _l.nrNodes)
                        return false;

                    auto it1 = cbegin();
                    auto it2 = _l.cbegin();

                    for (; it1 != cend(); ++it1, ++it2)
                    {
                        if (!(*it1 == *it2))
                            return false;
                    }

                    return true;
            }

            /**
             * @brief Returns whether list is not equal to @l (calls != for all elements)
             * @param l amother list to be compared
             */
            bool operator!=(const list<T>& _l)const
            {
                return !(*this==_l);
            }            

            /**
             * @brief Returns whether list is less than @l
             * @param l amother list to be compared
             */
            bool operator<(const list<T>& _l)const
            {
                auto it1 = cbegin();
                auto it2 = _l.cbegin();

                while (it1 != cend() && it2 != _l.cend())
                {
                    if (*it1 < *it2)
                        continue;

                    if (*it2 < *it1)
                        return false;

                    ++it1;
                    ++it2;
                }
                if(it1 == cend() && it2 != _l.cend())
                    return true;
                else if(it1 != cend() && it2 == _l.cend())
                    return false;
                else
                    return false;
            } 

            /**
             * @brief Returns whether list is greather than @l
             * @param l amother list to be compared
             */
            bool operator>(const list<T>& _l)const
            {
                return (_l < *this);
            }             

            /**
             * @brief Returns whether list is less than or equal to @l
             * @param l amother list to be compared
             */
            bool operator<=(const list<T>& _l)const
            {
                return !(*this > _l);
            } 

            /**
             * @brief Returns whether list is less than or equal to @l
             * @param l amother list to be compared
             */
            bool operator>=(list<T>& _l)const
            {
                return !(*this < _l);
            }

             /**
             * @brief Returns read/write reference to the first element (no check whether exists or not)
             */            
            T& front()
            {
                return *begin();
            }

             /**
             * @brief Returns read only reference to the first element (no check whether exists or not)
             */            
            const T& front() const
            {
                return *begin();
            }

             /**
             * @brief Returns read/write reference to the last element (no check whether exists or not)
             */              
            T& back()
            {
                iterator _tmp = end();
                return *--_tmp;
            }

             /**
             * @brief Returns read-only reference to the last element (no check whether exists or not)
             */              
            const T& back() const
            {
                iterator _tmp = end();
                return *--_tmp;
            }            

            // Insert and remove opearations
             /**
             * @brief Append a copy element at end of the list
             * @param x An element to copy
             */
            void push_back(const T& _x)
            {
                this->insert(end(), _x);
            }

            /**
             * @brief Removes the last element
             */ 
            void pop_back()
            {
                erase(iterator(pHeadNode->pPrev));
            }
             /**
             * @brief Insert a copy element at beginning of the list
             * @param x An element to copy
             */            
            void push_front(const T& _x)
            {
                this->insert(begin(), _x);
            }

            /**
             * @brief Removes the first element
             */             
            void pop_front()
            {
                erase(begin());
            }              
            // Insert operations
            /**
             * @brief Insets a copy of all elements of range[first, last) before iterator postion
             * @param position Iterator position
             * @param first First position in range
             * @param last Last position in range
             * @return Returns position of first new element
             */
            template <typename inputIterator>
            void insert(iterator _position, inputIterator _first, inputIterator _last)
            {
                list<T> _tmp(_first, _last);
                splice(_position, _tmp);
            }

            /**
             * @brief Insets a ccontent of initializer list before iterator postion
             * @param position Iterator position
             * @param l Initializer list of value type
             */            
            void insert(iterator _position, std::initializer_list<T> _l)
            {
                this->insert(_position, _l.begin(), _l.end());
            }
            
            /**
             * @brief Insets given value in list before specified iterator
             * @param position Iterator position
             * @param x Data to be inserted
             * @return Returns position of inserted element
             */
            iterator insert(iterator _position, const T& _x)
            {
                //node<T>* newNode = getNode(std::move(_x));
                return emplace(_position, std::move(_x));
            }

             /**
             * @brief Inserts a number of copies of given data into the list before specified iterator
             * @param n  Number of elements to be inserted
             * @param x Data to be inserted
             * @return Returns position of inserted element
             */           
            void insert(iterator _position, size_t _n, const T& _x)
            {
                list<T> _tmp(_n, _x);
                splice(_position, _tmp);
            }
            
            // Emplace operations
            /**
             * @brief Insert a copy of an element initialized with args before iterator position and 
             *          returns the position of new element
             * @param p Iterator position before data to be inerted
             * @param _args Varadic elements inputs
             * @return Returns iterator postion of new element 
             */
            template <typename... Args>
            iterator emplace(iterator _p, Args&&... args)
            {
                node<T>* pNode = _p.pNode;
                if(pNode == nullptr)
                    throw std::runtime_error("Invalid Iterator");

                node<T>* newNode = getNode(std::forward<Args>(args)...);

                generic_insert(pNode->pPrev, newNode, pNode);

                ++nrNodes;

                return iterator(newNode);
            }

            /**
             * @brief Appends a copy elements in Args at the end of the list
             * @param _args Varadic elements inputs
             */
            template <typename... Args>
            void emplace_back(Args&&... args)
            {
                emplace(end(), std::forward<Args>(args)...);
            }            

            /**
             * @brief Inserts a copy elements in Args at the beginning of the list
             * @param _args Varadic elements inputs
             */
            template <typename... Args>
            void emplace_front(Args&&... args)
            {
                emplace(begin(), std::forward<Args>(args)...);
            }

            // Erase operations
            /**
             * @brief Removes element at iterator position and returns iterator position of next element
             * @param p Iterator position before data to be inerted
             * @return Returns iterator postion of next element 
             */            
            iterator erase(iterator _p)
            {
                node<T>* _tmp = _p.pNode;
                ++_p;
                generic_delete(_tmp);
                --nrNodes;
                return _p;
            }
            
            /**
             * @brief Removes elements in the range of [beg and end) and returns iterator position of next element
             * @param beg Starting iterator position 
             * @param end End iterator position 
             * @return Returns iterator postion of next element 
             */            
            iterator erase(iterator _first, iterator _last)
            {
                while(_first != _last)
                    _first = erase(_first);
                return _last;
            }

            /**
            *  @brief Resizes the %list to the specified number of elements.
            *  @param new_size Number of elements the %list should contain.
            * */
            void resize(size_t _new_size)
            {
                resize(_new_size, T{});
            }

            /**
            *  @brief Resizes the %list to the specified number of elements.
            *  @param new_size Number of elements the %list should contain.
            *  @param _value Grows new elements with default value          
            * */
            void resize(size_t _new_size, const T& _value)
            {
                size_t _size = this->size();
                size_t _j = 0;
                if(_size < _new_size)
                {
                    for(size_t _i = _size; _i < _new_size; ++_i)
                        emplace_back(_value);
                }
                else
                {
                    iterator it = begin();
                    for(size_t _i = 0; _i < _new_size; ++_i)
                        ++it;
                    erase(it, end());
                }
            }   

            // Remove operations
            /**
             * @brief Removes all elements with value specifies in the list
             * @param value Elements Value to deleted
             */            
            void remove(T _value)
            {
                for(auto it = begin(); it != end();)
                {
                    if(*it == _value)
                        it = erase(it);
                    else
                        ++it;
                }
            }  
            
            /**
             * @brief Removes all elements which op(elem) yeilds true
             * @param value Elements Value to deleted
             */
            template<typename _Predicate>            
            void remove_if(_Predicate op)
            {
                for(auto it = begin(); it != end();)
                {
                    if(op(*it))
                        it = erase(it);
                    else
                        ++it;
                }
            }
            
            /**
             * @brief Removes all elements, container is empty
             */
            void clear()
            {
                if(!pHeadNode)
                    return;
                node<T>* current = pHeadNode->pNext;

                while (current != pHeadNode)
                {
                    node<T>* next = current->pNext;
                    delete current;
                    current = next;
                    --nrNodes;
                }
                pHeadNode->pNext = pHeadNode;
                pHeadNode->pPrev = pHeadNode;
            }

            // Special modifying operations
            /**
             * @brief Removes duplicates of consecutive elements with same values
             */
            void unique()
            {
                if(size() < 2)
                    return;
                for(iterator _it = begin(); _it != end();)
                {
                    iterator _j = _it;
                    ++_j;
                    if(_j != end() && *_it == *_j)
                        erase(_j);
                    else
                        _it = _j;
                }
            }

            /**
             * @brief Removes duplicates of consecutive elements with same values but the first one, for which op() yeilds true
             */
            template<typename _Predicate>                
            void unique(_Predicate op)
            {
                if(size() < 2)
                    return;
                for(iterator _it = begin(); _it != end();)
                {
                    iterator _j = _it;
                    ++_j;
                    if(_j != end() && op(*_it, *_j))
                        erase(_j);
                    else
                        _it = _j;
                }                
            }

            /**
             * @brief Moves all elements of other list to %list in front of iterator position
             * @param p Position before elements are moved
             * @param l Another list
             */            
            void splice(iterator _p, list<T>& _l)
            {
                if(_l.empty() || this == &_l)
                    return;
                
                node<T>* _pos = _p.pNode;
                node<T>* _posPrev = _pos->pPrev;

                node<T>* _lFirst = _l.pHeadNode->pNext;
                node<T>* _lLast = _l.pHeadNode->pPrev;

                _pos -> pPrev = _lLast;
                _lLast -> pNext = _pos;
                _lFirst->pPrev = _posPrev;
                _posPrev->pNext = _lFirst;

                nrNodes += _l.nrNodes;
                
                _l.pHeadNode->pNext = _l.pHeadNode;
                _l.pHeadNode->pPrev = _l.pHeadNode;

                _l.nrNodes = 0;
            }

            /**
             * @brief Moves elements at iterator position of other list to %list in front of iterator position
             * @param p Position before elements are moved
             * @param l Another list
             * @param pl2  Postion of another list element to be moved in existing list
             */            
            void splice(iterator _p, list<T>& _l, iterator _pl)
            {
                if(_l.empty() || this == &_l)
                    return;
                
                node<T>* _pos = _p.pNode;
                node<T>* _posPrev = _pos->pPrev;
                
                node<T>* _lNodeToMove = _pl.pNode;

                generic_insert(_posPrev, _lNodeToMove, _pos);
                ++nrNodes;

                generic_delete(_lNodeToMove);
                --_l.nrNodes;
            }

            /**
             * @brief Moves elementss at iterator position range [l2.beg, l2end) other list to %list in front of iterator position
             * @param p Position before elements are moved
             * @param l Another list
             * @param pl2beg  Starting Postion of another list
             * @param pl2end  End Postion of another list
             */            
            void splice(iterator _p, list<T>& _l, iterator _plbeg, iterator _plend)
            {
                if(_l.empty() || this == &_l)
                    return;
                
                node<T>* _pos = _p.pNode;
                node<T>* _posPrev = _pos->pPrev;

                node<T>* _lFirst = _plbeg.pNode;
                node<T>* _lLast = _plend.pNode;

                _pos -> pPrev = _lLast;
                _lLast -> pNext = _pos;
                _lFirst->pPrev = _posPrev;
                _posPrev->pNext = _lFirst;

                nrNodes += std::distance(_lFirst, _lLast);
                
                _l.erase(_plbeg, _plend);              
            }
            
            /**
             * @brief Sorts all elements in the list with operator <
             */
            void sort()
            {
                
            }

            /**
             * @brief Sorts all elements in the list with operator op()
             */
            template<typename _Predicate>             
            void sort(_Predicate op)
            {

            }
            
            /**
             * @brief Assuming all elements of both list are sorted, moves all elements of another list 
             *          and such that all elements are still sorted
             * @param l Another list to be merged
             */
            void merge(list<T>& _l)
            {
                iterator _iter1 = begin();
                iterator _iter2 = _l.begin();
                T _data;
                while(true)
                {
                   if(_iter1 == end())
                   {
                        insert(end(), _iter2, _l.end());
                        break;
                   }
                   if(_iter2 == _l.end())
                   {
                        break;
                   }
                   if(*_iter1 >= * _iter2)
                   {
                        emplace(_iter1, *_iter2);
                        ++_iter2;
                   }
                   else
                   {
                        ++_iter1;
                   }                  
                }
            }

            /**
             * @brief Assuming all elements of both list are sorted with criteria op(), moves all elements of another list 
             *          and such that all elements are sorted with op()
             * @param l Another list to be merged
             */
            template<typename _Predicate> 
            void merge(list<T> _l, _Predicate op)
            {

            }

            /**
             * @brief Reverse the order of all elements 
             */            
            void reverse()
            {
                if(!(pHeadNode->pNext == pHeadNode || pHeadNode->pNext->pNext == pHeadNode))
                {
                    node<T>* original_first = pHeadNode->pNext;
                    node<T>* run_next = nullptr;

                    for(node<T>* run = original_first->pNext; run != pHeadNode; run = run_next)
                    {   
                       run_next = run->pNext;

                       run -> pNext = pHeadNode -> pNext;
                       run -> pPrev = pHeadNode;
                       pHeadNode -> pNext = run;
                       pHeadNode -> pNext -> pPrev = run;
                    }
                    original_first -> pNext = pHeadNode;
                    pHeadNode -> pPrev = original_first;
                }
            }

            /**
             * @brief Search a given eleemnt in the list
             * @param Eleemnt to be searched in list
             * @return Return nodes address with read-write access 
             */
            iterator search(T searchData)
            {
                iterator iter;
                for(iter = begin(); iter != end(); ++iter)
                {
                    if(*iter == searchData)
                        return iter;
                }
                return iterator();
            }

            /**
             * @brief Search a given eleemnt in the list
             * @param Predicate Condition for searching element, 
             * @return Return nodes address with read-write access for first element  with specified condition
             */
            template<typename _predicate>
            iterator search(_predicate op)
            {
                iterator iter;
                for(iter = begin(); iter != end(); ++iter)
                {
                    if(op(*iter))
                        return iter;
                }
                return iterator();
            }           
            /**
             * @brief shows lists on console
             */
            void display(const std::string msg = {})
            {
                std::cout << msg << "\t\t";

                std::cout << "[START] <-> "; 
                for(auto it = begin(); it != end(); ++it)
                {
                    std::cout << "[" << *it << "] <-> "; 
                }
                std::cout << "[END]" << std::endl; 
            }

            // Iterator operations
            /**
             * @brief Returns read/write iterator that points to first element in the list
             */
            iterator begin()
            {
                return iterator(this->pHeadNode->pNext);
            }

            /**
             * @brief Returns read only iterator that points to first element in the list
             */
            const_iterator cbegin() const 
            {
                return const_iterator(this->pHeadNode->pNext);
            }
            
            /**
             * @brief Returns read/write iterator that points to one past the last element in the list
             */
            iterator end()
            {
                return iterator(this->pHeadNode);
            }

            /**
             * @brief Returns read only iterator that points to first element in the list
             */
            const_iterator cend() const 
            {
                return const_iterator(this->pHeadNode);
            }
            
            /**
             * @brief Returns read/write iterator that points to last element in the list
             */
            iterator rbegin()
            {
                return reverse_iterator(end());
            }

            /**
             * @brief Returns read only iterator that points to first element in the list
             */
            const_iterator crbegin() const
            {
                return const_reverse_iterator(end());
            }
            
            /**
             * @brief Returns read/write iterator that points to one past the last element in the list
             */
            iterator rend()
            {
                return reverse_iterator(begin());
            }

            /**
             * @brief Returns read only iterator that points to first element in the list
             */
            const_iterator crend() const
            {
                return const_reverse_iterator(begin());
            }            
    };
}//namespace linkedList

#endif //_LIST_H

