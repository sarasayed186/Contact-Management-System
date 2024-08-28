#include <iostream>  
#include <vector>  
#include <string>  
#include <fstream>  

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
};

class ContactManager {
private:
    vector<Contact> contacts;

public:
    void addContact() {
        Contact newContact;
        cout << "Enter name: ";
        cin >> newContact.name;
        cout << "Enter phone number: ";
        cin >> newContact.phoneNumber;
        cout << "Enter email: ";
        cin >> newContact.email;
        contacts.push_back(newContact);
        cout << "Contact added successfully!" << endl;
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts available." << endl;
            return;
        }
        cout << "Contact List:" << endl;
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << i + 1 << ". Name: " << contacts[i].name
                << ", Phone: " << contacts[i].phoneNumber
                << ", Email: " << contacts[i].email << endl;
        }
    }

    void editContact() {
        int index;
        viewContacts();
        cout << "Enter the number of the contact to edit: ";
        cin >> index;
        if (index < 1 || index > contacts.size()) {
            cout << "Invalid contact number." << endl;
            return;
        }
        Contact& contact = contacts[index - 1];
        cout << "Editing contact: " << contact.name << endl;
        cout << "Enter new name (leave blank to keep current): ";
        string newName;
        cin.ignore();
        getline(cin, newName);
        if (!newName.empty()) contact.name = newName;

        cout << "Enter new phone number (leave blank to keep current): ";
        string newPhone;
        getline(cin, newPhone);
        if (!newPhone.empty()) contact.phoneNumber = newPhone;

        cout << "Enter new email (leave blank to keep current): ";
        string newEmail;
        getline(cin, newEmail);
        if (!newEmail.empty()) contact.email = newEmail;

        cout << "Contact updated successfully!" << endl;
    }

    void deleteContact() {
        int index;
        viewContacts();
        cout << "Enter the number of the contact to delete: ";
        cin >> index;
        if (index < 1 || index > contacts.size()) {
            cout << "Invalid contact number." << endl;
            return;
        }
        contacts.erase(contacts.begin() + index - 1);
        cout << "Contact deleted successfully!" << endl;
    }

    void saveContactsToFile() {
        ofstream outFile("contacts.txt");
        for (const auto& contact : contacts) {
            outFile << contact.name << "," << contact.phoneNumber << "," << contact.email << endl;
        }
        outFile.close();
        cout << "Contacts saved to file." << endl;
    }

    void loadContactsFromFile() {
        ifstream inFile("contacts.txt");
        if (!inFile) {
            cout << "No saved contacts found." << endl;
            return;
        }
        Contact contact;
        while (getline(inFile, contact.name, ',') &&
            getline(inFile, contact.phoneNumber, ',') &&
            getline(inFile, contact.email)) {
            contacts.push_back(contact);
        }
        inFile.close();
        cout << "Contacts loaded from file." << endl;
    }
};

int main() {
    ContactManager manager;
    manager.loadContactsFromFile();

    int choice;
    do {
        cout << "\nContact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Edit Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Save Contacts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: manager.addContact(); break;
        case 2: manager.viewContacts(); break;
        case 3: manager.editContact(); break;
        case 4: manager.deleteContact(); break;
        case 5: manager.saveContactsToFile(); break;
        case 6: cout << "Exiting..." << endl; break;
        default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}