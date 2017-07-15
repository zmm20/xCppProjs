//#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;


class Person {
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<shared_ptr<Person>> kids;
    Person(const string& n,
        shared_ptr<Person> m = nullptr,
        shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f) {
    }
    ~Person() {
        cout << "Person delete " << name << endl;
    }
};

shared_ptr<Person> initFamily(const string& name)
{
    shared_ptr<Person> mom(new Person(name + "’s mom"));
    shared_ptr<Person> dad(new Person(name + "’s dad"));
    shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

class Person2 {
public:
    string name;
    shared_ptr<Person2> mother;
    shared_ptr<Person2> father;
    vector<weak_ptr<Person2>> kids; // weak pointer !!!
    Person2(const string& n,
        shared_ptr<Person2> m = nullptr,
        shared_ptr<Person2> f = nullptr)
        : name(n), mother(m), father(f) {
    }
    ~Person2() {
        cout << "Person2 delete " << name << endl;
    }
};

shared_ptr<Person2> initFamily2(const string& name)
{
    shared_ptr<Person2> mom(new Person2(name + "’s mom"));
    shared_ptr<Person2> dad(new Person2(name + "’s dad"));
    shared_ptr<Person2> kid(new Person2(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

int main()
{
    cout << "test 1" << endl;
    {
        shared_ptr<Person> p = initFamily("nico");
        cout << "nico’s family exists" << endl;
        cout << "- nico is shared " << p.use_count() << " times" << endl;
        cout << "- name of 1st kid of nico’s mom: "
            << p->mother->kids[0]->name << endl;
        p = nullptr;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        shared_ptr<Person2> p = initFamily2("nico2");
        cout << "nico2’s family exists" << endl;
        cout << "- nico2 is shared " << p.use_count() << " times" << endl;
        // kids[0].lock() 会产生一个share_ptr 对象, 如果对象为nullptr, 则导致不明确行为, 所以在使用前可以用 expired() 检查
        cout << "- name of 1st kid of nico2’s mom: "
            << p->mother->kids[0].lock()->name << endl;
        p = nullptr;
    }
    cout << endl;


    cout << "test 3" << endl;
    {
        try
        {
            shared_ptr<string> sp(new string("hi")
                , [](string* p)
            {
                cout << "delete" << endl;
                delete p;
            }); // create shared pointer

            weak_ptr<string> wp = sp; // create weak pointer out of it
            sp.reset(); // release object of shared pointer
            cout << wp.use_count() << endl; // prints: 0
            cout << boolalpha << wp.expired() << endl; // prints: true
            shared_ptr<string> p(wp); // throws std::bad_weak_ptr
        }
        catch (const std::exception& e)
        {
            cerr << "exception: " << e.what() << endl; // prints: bad_weak_ptr
        }
    }
    cout << endl;
    
    return 0;
}
#endif