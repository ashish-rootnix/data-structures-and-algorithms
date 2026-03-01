#include <iostream>
#include "linkedList.h"

using namespace llist;
int main()
{
    std::cout << "---Testing all construcors---" << std::endl;
    list<int> l1;
    std::cout << "Is list empty = " << std::boolalpha << (l1.empty()) << std::endl;
    l1.display("list()");
    
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    std::cout << "Size of list<> = " << l1.size() << std::endl;
    l1.display("list()");
    
    list<int>  l2(l1);
    l2.display("list(const list<>&)");

    list<int>  l3 (std::move(l2));
    l3.display("list(const list<>&&)"); 

    list<float> l4(3);
    l4.display("list(size_t)"); 

    list<float> l5(5, 3.14);
    l5.display("list(size_t, T&)");
    
    list<std::string> l6{"Hello", "World", "Enjoy!!!"};
    l6.display("list(std::initializer_list<T>)");    

    list<std::string> l_iter(l6.begin(), l6.end());
    l_iter.display("list(inputIterator, inputIterator)");    
    std::cout << std::endl;

    std::cout << "---Testing all assignments operators---" << std::endl;
    list<int> l7 = l1;
    l7.display("list<T>& operator=(const list<T>&)");

    list<std::string> l8 = std::move(l6);
    l8.display("list<T>& operator=(list<T>&&)");    

    list<float> l9 = {3.14, 6.28, 9.42};
    l9.display("list<T>& operator=(std::initializer_list<T>)");

    std::cout << std::endl;

    std::cout << "---Testing all assign function calls---" << std::endl;    
    l7.assign((size_t)10, 5);
    l7.display("list<T>::assign(size_T, T&)");

    l7.assign((size_t)5, 10);
    l7.display("list<T>::assign(size_T, T&)");
    
    l7.assign({10, 20, 30, 40});
    l7.display("list<T>::assign(std::initializer_list<T>)");

    l7.assign({100, 200, 300, 400, 500, 600, 700});
    l7.display("list<T>::assign(std::initializer_list<T>)");    

    l7.assign(l3.begin(), l3.end());
    l7.display("list<T>::assign(inputIterator, inputIterator))");  
    
    l4.assign(l5.begin(), l5.end());
    l4.display("list<T>::assign(inputIterator, inputIterator))");
    
    std::cout << std::endl;

    std::cout << "---Testing all swap operators---" << std::endl;
    l7.assign((size_t)5, 10);
    l7.swap(l3);
    l3.display("list<T>::swap(list<>&)");
    l7.display("list<T>::swap(list<>&)");
    l7.swap(l3);
    l3.display("list<T>::swap(list<>&)");
    l7.display("list<T>::swap(list<>&)");
    

    llist::list<int>::swap(l3, l7);
    l3.display("static llist::list<int>::swap(list<T>&, list<T>&)");
    l7.display("static llist::list<int>::swap(list<T>&, list<T>&)");    

    llist::list<int>::swap(l3, l7);
    l3.display("static llist::list<int>::swap(list<T>&, list<T>&)");
    l7.display("static llist::list<int>::swap(list<T>&, list<T>&)");
 
    std::cout << std::endl;

    std::cout << "---Testing all comparision operators---" << std::endl;    
    list<int> l10 = {1, 2, 3, 4, 5};
    list<int> l11 = {1, 2, 3, 4, 5};
    l10.display("L1");
    l11.display("L2");    
    std::cout << "L1 == L2 : "<<std::boolalpha << (l10 == l11) << std::endl;
    std::cout << "L1 <= L2 : "<<std::boolalpha << (l10 <= l11) << std::endl;    

    l11.pop_back(); l11.push_back(10);
    l10.display("L1");
    l11.display("L2");    
    std::cout << "L1 == L2 : "<<std::boolalpha << (l10 == l11) << std::endl;    
    std::cout << "L1 <= L2 : "<<std::boolalpha << (l10 <= l11) << std::endl;

    l11.pop_back();
    l10.display("L1");
    l11.display("L2");    
    std::cout << "L1 == L2 : "<<std::boolalpha << (l10 == l11) << std::endl;
    std::cout << "L1 != L2 : "<<std::boolalpha << (l10 != l11) << std::endl;        
    std::cout << "L1 < L2 : "<<std::boolalpha << (l10 < l11) << std::endl; 
    std::cout << "L1 <= L2 : "<<std::boolalpha << (l10 <= l11) << std::endl;
    std::cout << "L1 > L2 : "<<std::boolalpha << (l10 > l11) << std::endl;    
    std::cout << "L1 >= L2 : "<<std::boolalpha << (l10 >= l11) << std::endl; 


    l11.display("L1"); 
    std::cout << "L.front() : " << l11.front() << std::endl;
    std::cout << "L.back() : " << l11.back() << std::endl;
    int& front = l11.front();
    int& back = l11.back();    
    front = front + 100;
    back = back + 100;
    l11.display("L1 modified with front() back() returned reference"); 

    l11.push_back(1000);
    l11.display("L1 after push_back");

    l11.push_front(2000);
    l11.display("L1 after push_front");

    l11.pop_back();
    l11.display("L1 after pop_back");

    l11.pop_front();
    l11.display("L1 after pop_front");    

    std::cout << std::endl;
    std::cout << "---Testing all splice operators---" << std::endl;    
    l10.display("L1");
    l11.display("L2");      
    l11.splice(l11.begin(), l10);
    l10.display("L1 after L2.splice(begin(), L1)");
    l11.display("L2 after L2.splice(begin(), L1)");

    l10.splice(l10.begin(), l11);
    l10.display("L1 after L1.splice(begin(), L2)");
    l11.display("L2 after L1.splice(begin(), L2)");
  
    std::cout << std::endl;
    std::cout << "---Testing all insert operators---" << std::endl;       
    l11.insert(l11.begin(), l10.begin(), l10.end());
    l11.display("L2 after insert(L2.begin(), L1.begin(), L1.end())");
    
    l10.insert(l10.end(), {501, 502, 503, 504, 505});
    l10.display("L1 after insert(L2.end(), Initializer_list<T>}");

    l10.insert(l10.begin(), 555);
    l10.display("L1 after insert(L2.begin(), const &T}");
    
    l10.insert(l10.begin(), (size_t)3, 777);
    l10.display("L1 after insert(L2.begin(), size_t, const &T}");
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "---Testing all emplace operators---" << std::endl;
    list<int> l_12{101, 102, 103, 104, 105};
    l_12.display("L1");    
    l_12.emplace(l_12.begin(), 1000);
    l_12.display("L1.emplace(1000)");
    l_12.emplace_back(500);
    l_12.display("L1.emplace_back()");
    l_12.emplace_front(500);
    l_12.display("L1.emplace_front()");          

    std::cout << std::endl;
    std::cout << "---Testing all erase operators---" << std::endl;

    list<int> l12{101, 102, 103, 104, 105};
    l12.display("L1");
    l12.erase(l12.begin());
    l12.display("L1 erase(begin())");

    l12.erase(l12.begin(), l12.end());
    l12.display("L1 erase(begin(), end())");

    std::cout << std::endl;
    std::cout << "---Testing resize operators---" << std::endl;
    l12.resize(10);
    l12.display("L1 resize(10)");

    l12.resize(12, 10);
    l12.display("L1 resize(5, 10)");    

    std::cout << std::endl;
    std::cout << "---Testing remove operators---" << std::endl;
    l12.remove(std::move(0));
    l12.display("L1 remove(10)");
    
    l12.insert(l12.begin(), {1, 2, 3, 4, 5});
    l12.display("L1 insert({1, 2, 3, 4, 5})");
    l12.remove_if([](int x){return x == 10;});
    l12.display("L1 remove([](int x){return x == 10;})");

    std::cout << std::endl;
    std::cout << "---Testing clear operators---" << std::endl;
    l12.clear();
    l12.display();

    std::cout << std::endl;
    std::cout << "---Testing unique operators---" << std::endl;
    list<int> l13 {1, 1, 2, 3, 3, 5 ,3, 2, 1};
    l13.display("L1");
    l13.unique();
    l13.display("L1 unique()");
    l13.unique([](int x, int y){return x > y;});
    l13.display("L1 unique([](int x, int y){return x > y;})"); 
    
    std::cout << std::endl;
    std::cout << "---Testing search operators---" << std::endl;
    std::cout << "search(2) " << std::boolalpha << ((l13.search(2)).pNode != nullptr) << std::endl;

    std::cout << "---Testing reverse operators---" << std::endl;
    list<std::string> l14 = {"Hello", "World", "Circular", "list", "reversed"};
    l14.display("L1");
    l14.reverse();
    l14.display("L1 reversed : ");

   std::cout << "---Testing merge operators---" << std::endl;
   list<int> l15 = {1, 2, 5, 7, 9, 11, 13, 15};
   list<int> l16 = {3, 4, 6, 8, 10, 12, 14, 16, 17};
   l15.display("L1");
   l16.display("L2");
   l15.merge(l16);
   l15.display("L1 merged : ");
 
   list<int> l17 = {1, 2, 5, 7, 9, 11, 13, 15};
   list<int> l18 = {3, 4, 6, 8};
   l17.display("L1");
   std::cout << "L1 : "<<l17.size() << std::endl; 
   l18.display("L2");
   std::cout << "L2 : "<<l18.size() << std::endl;    
   l17.merge(l18);
   l17.display("L1 merged : ");
   std::cout << "Merged list size : "<<l17.size() << std::endl;   
}   
