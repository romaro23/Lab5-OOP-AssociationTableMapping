#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Person {
public:
    int personId;
    string personName;
    string toString() {
        return "Id: " + to_string(personId) + " Name: " + personName;
    }
};
class Address {
public:
    int cityId;
    string cityName;
    string toString() {
        return "Id: " + to_string(cityId) + " City: " + cityName;
    }
};
class PersonAddress {
private:
    vector<pair<Person, Address>> associations;
public:
    void addAssociation(Person person, Address address) {
        associations.push_back(make_pair(person, address));
    }
    vector<Person> getAssociations(Address address) {
        vector<Person> result;
        for (auto& pair : associations) {
            if (pair.second.cityId == address.cityId) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
    vector<Address> getAssociations(Person person) {
        vector<Address> result;
        for (auto& pair : associations) {
            if (pair.first.personId == person.personId) {
                result.push_back(pair.second);
            }
        }
        return result;
    }
    ostream& saveToFile(ostream& os) {
        cout << "Id " << "   Name " << "      Id " << "   City" << endl;
        os << "Id " << "Name " << "Id " << "City" << endl;
        for (auto& pair : associations) {
            cout << pair.first.toString() << " " << pair.second.toString() << endl;
             os << pair.first.toString() << " " << pair.second.toString() << endl;
        }
        return os;
    }
};

int main() {
    vector<Person> persons;
    vector<Address> addresses;
    PersonAddress table;
    while (true) {
        cout << "1 - Create a person, 2 - Create an address, 3 - Watch lists, 4 - Create an association, 5 - Watch table, 6 - Watch addresses by a person, 7 - Watch persons by an address" << endl;
        int answer;
        cin >> answer;
        switch (answer) {
        case 1: 
        {
            cout << "Enter an id" << endl;
            int id;
            cin >> id;
            cout << "Enter a name" << endl;
            string name;
            cin >> name;
            persons.push_back(Person{ id, name });
            break;
        }         
        case 2: 
        {
            cout << "Enter an id" << endl;
            int id;
            cin >> id;
            cout << "Enter a city" << endl;
            string city;
            cin >> city;
            addresses.push_back(Address{ id, city });
            break;
        }
        case 3: 
            cout << "Persons: " << endl;
            for (auto person : persons) {
                cout << person.toString() << endl;
            }
            cout << "Addresses: " << endl;
            for (auto address : addresses) {
                cout << address.toString() << endl;
            }
            break;
        case 4: 
        {         
            cout << "Choose a person: " << endl;
            int person;
            cin >> person;
            while (person < 0 || person >= persons.size()) {
                cout << "Wrong number, try again" << endl;
                cin >> person;
            }
            cout << "Choose an address: " << endl;
            int address;
            cin >> address;
            while (address < 0 || address >= addresses.size()) {
                cout << "Wrong number, try again" << endl;
                cin >> address;
            }
            table.addAssociation(persons[person], addresses[address]);
            break;
        }
        case 5: 
        {
            ofstream file;
            file.open("example.txt");
            if (file) {
                table.saveToFile(file);
            }
            else {
                cout << "Error with the file" << endl;
            }
            break;
        }
        case 6:
        {
            cout << "Choose a person: " << endl;
            int person;
            cin >> person;
            while (person < 0 || person >= persons.size()) {
                cout << "Wrong number, try again" << endl;
                cin >> person;
            }
            vector<Address> associations = table.getAssociations(persons[person]);
            for (auto address : associations) {
                cout << address.toString() << endl;
            }
            break;
        }
        case 7: 
        {
            cout << "Choose an address: " << endl;
            int address;
            cin >> address;
            while (address < 0 || address >= addresses.size()) {
                cout << "Wrong number, try again" << endl;
                cin >> address;
            }
            vector<Person> associations = table.getAssociations(addresses[address]);
            for (auto person : associations) {
                cout << person.toString() << endl;
            }
            break;
        }
        }
    }
}
