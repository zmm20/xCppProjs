#define MAIN
#ifdef MAIN

#include <iostream>
#include <fstream>
#include <string>
#include "AddressBook_v2.pb.h"
using namespace std;

// test 2
// This function fills in a Person message based on user input.
void PromptForAddress(tutorial_v2::Person* person);
// test 3
// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const tutorial_v2::AddressBook& address_book);

int main()
{
    cout << "test 2, protobuf 写消息" << endl;
    {
        std::string fileName = "addressBook.dat";

        tutorial_v2::AddressBook address_book;
        {
            // Read the existing address book.
            fstream input(fileName.c_str(), ios::in | ios::binary);
            if (!input)
            {
                cout << fileName << ": File not found.  Creating a new file." << endl;
            }
            else if (!address_book.ParseFromIstream(&input))
            {
                cerr << "Failed to parse address book." << endl;
                return -1;
            }
        }

        // Add an address.
        PromptForAddress(address_book.add_person());
        {
            // Write the new address book back to disk.
            fstream output(fileName.c_str(), ios::out | ios::trunc | ios::binary);
            if (!address_book.SerializeToOstream(&output))
            {
                cerr << "Failed to write address book." << endl;
                return -1;
            }
        }

        // Optional:  Delete all global objects allocated by libprotobuf.
        google::protobuf::ShutdownProtobufLibrary();
    }
    cout << endl;

    cout << "test 2, protobuf 读消息" << endl;
    {
        std::string fileName = "addressBook.dat";

        tutorial_v2::AddressBook address_book;

        {
            // Read the existing address book.
            fstream input(fileName.c_str(), ios::in | ios::binary);
            if (!address_book.ParseFromIstream(&input)) {
                cerr << "Failed to parse address book." << endl;
                return -1;
            }
        }
        ListPeople(address_book);

        // Optional:  Delete all global objects allocated by libprotobuf.
        google::protobuf::ShutdownProtobufLibrary();
    }
    cout << endl;


    return EXIT_SUCCESS;
}



// This function fills in a Person message based on user input.
void PromptForAddress(tutorial_v2::Person* person)
{
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial_v2::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial_v2::Person::MOBILE);
        }
        else if (type == "home") {
            phone_number->set_type(tutorial_v2::Person::HOME);
        }
        else if (type == "work") {
            phone_number->set_type(tutorial_v2::Person::WORK);
        }
        else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}


// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const tutorial_v2::AddressBook& address_book)
{
    for (int i = 0; i < address_book.person_size(); i++) {
        const tutorial_v2::Person& person = address_book.person(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.has_email()) {
            cout << "  E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phone_size(); j++)
        {
            const tutorial_v2::Person::PhoneNumber& phone_number = person.phone(j);

            switch (phone_number.type())
            {
            case tutorial_v2::Person::MOBILE:
                cout << "  Mobile phone #: ";
                break;
            case tutorial_v2::Person::HOME:
                cout << "  Home phone #: ";
                break;
            case tutorial_v2::Person::WORK:
                cout << "  Work phone #: ";
                break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

#endif
