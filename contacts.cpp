#include <iostream>
#include <vector>
#include <string>
#include <fstream>
const std::string PATH = "";  // DO NOT LEAVE THE PATH VARIABLE EMPTY!!!
struct DATA {
    std::string phone_number;
    std::string name;
    std::string last_name;
};


struct EDITED_DATA {
    std::string edited_phone_number;
    std::string edited_name;
    std::string edited_last_name;
};


class Contact {
    public:
    int insert_data(const std::string& name,const std::string& last_name,const std::string& phone) {
        std::string file_name = PATH + name + last_name + ".txt";
        std::ofstream out;
        out.open(file_name,std::ios_base::app);
        if (out.is_open()) {
            out << "[*] NAME : " << name << std::endl;
            out << "[*] LAST NAME : " << last_name << std::endl;
            out << "[*] PHONE : " << phone << std::endl;
            out.close();
        } else {
            std::cerr << "[*] Something went wrong." << std::endl;
            return 1;
        }
        return 0;
    }
};


class Customize_Contact : public Contact {
    public:
    bool check_if_file_exists(const std::string& name,const std::string& last_name) {
        std::string file_to_check = PATH + name + last_name + ".txt";
        std::ifstream check(file_to_check);
        if (check.is_open()) {
            std::cout << "[*] " <<  name + last_name + ".txt" << " exists." << std::endl;
        } else {
            std::cerr << "[*] ERROR: " << name + last_name + ".txt" << " does not exist. Try another option." << std::endl;
            return false;
        }
        return true;
    }

    int edit_contact(const std::string& name,const std::string& last_name,const EDITED_DATA& other,const DATA& me) {
        std::string file = PATH + name + last_name + ".txt";
        std::ofstream file_to_edit;
        file_to_edit.open(file,std::ios_base::out);
        if (file_to_edit.is_open()) {
            file_to_edit << "[*] NAME : " << me.name << std::endl;
            file_to_edit << "[*] LAST NAME : " << me.last_name << std::endl;
            file_to_edit << "[*] PHONE : " << other.edited_phone_number << std::endl;
            file_to_edit.close();
        }
        return 0;
    }

    int delete_contact(const std::string& name,const std::string& last_name) {
        std::string file_to_delete = PATH + name + last_name + ".txt";
        if (remove(file_to_delete.c_str()) != 0) {
            std::cerr << "[*] Remove operation failed." << std::endl;
            std::cerr << "[*] You might not have enough privileges to do this or " << name + last_name + ".txt" << " does not exist." << std::endl;
            return 1;
        } else {
            std::cout << "[*] " << name + last_name + ".txt" << " has been deleted." << std::endl;
        }
        return 0;
    }

};

int verify_cin() {
    if (std::cin.fail()) {
        std::cerr << "[*] ERROR: Something went wrong. Try again." << std::endl;
    }
    return 1;
}

int main(int argc,char* argv[])
{
    struct DATA new_data;
    struct EDITED_DATA edit;
    Customize_Contact* second = new Customize_Contact();
    Contact* first = new Contact();
    int choice;
    std::vector<std::string>phone_numbers;
    std::vector<std::string>::iterator phone_numbers_iterator;
    std::vector<std::string>all_names;
    std::vector<std::string>::iterator all_names_iterator;
    std::vector<std::string>all_last_names;
    std::vector<std::string>::iterator all_last_names_iterator;
    char answers[] = {'Y','n'};
    char second_choice,last_choice,confirm_delete;

    std::cout << "[*] Welcome to 'Your contacts!'" << std::endl;
    asm("start:;");
    std::cout << "[*] Choose one of the options below: " << std::endl;
    std::cout << "1: Create new contact." << std::endl;
    std::cout << "2: Edit existing contact." << std::endl;
    std::cout << "3: Remove an existing contact." << std::endl;
    std::cout << "[*] Option : ";
    std::cin >> choice;
    verify_cin();

    if (choice == 1) {
        std::cout << "[*] Phone number: ";
        std::cin >> new_data.phone_number;
        verify_cin();
        std::cout << "[*] Name: " ;
        std::cin >> new_data.name;
        verify_cin();
        std::cout << "[*] Last Name: ";
        std::cin >> new_data.last_name;
        verify_cin();

        std::cout << "[*] Name: " << new_data.name << std::endl;
        std::cout << "[*] Last Name: " << new_data.last_name << std::endl;
        std::cout << "[*] Phone Number: " << new_data.phone_number << std::endl;
        std::cout << "[*] Are you sure you want to save it? (Y/n) : ";
        std::cin >> second_choice;
        verify_cin();

        if (second_choice != answers[0]) {
            std::cerr << "[*] Exiting..." << std::endl;
            return 1;
        }

        phone_numbers_iterator = phone_numbers.begin();
        phone_numbers_iterator = phone_numbers.insert(phone_numbers_iterator,new_data.phone_number);
        all_names_iterator = all_names.begin();
        all_names_iterator = all_names.insert(all_names_iterator,new_data.name);
        all_last_names_iterator = all_last_names.begin();
        all_last_names_iterator = all_last_names.insert(all_last_names_iterator,new_data.last_name);
        for (int i = 0;i < phone_numbers.size();i++) {
            for (int j = 0;j < all_names.size();j++) {
                for (int k = 0;k < all_last_names.size();k++) {
                    std::cout << "Name: " << all_names[j] << " || Last Name: " << all_last_names[k] << " || Phone Number: " << phone_numbers[i] << std::endl;
                }
            }
        }
        first->insert_data(new_data.name,new_data.last_name,new_data.phone_number);
        std::cout << "[*] Saved." << std::endl;
    } else if (choice == 2) {
        std::cout << "[*] Insert the credentials of the contact you are trying to edit." << std::endl;
        std::cout << "[*] Name: " ;
        std::cin >> new_data.name;
        verify_cin();
        std::cout << "[*] Last Name: ";
        std::cin >> new_data.last_name;
        verify_cin();
        std::cout << "[*] Checking if " << new_data.name << " " << new_data.last_name << " exists in your contacts..." << std::endl;
        if (second->check_if_file_exists(new_data.name,new_data.last_name) == true) {
            std::cout << "[*] Insert new contact info." << std::endl;
            std::cout << "[*] Phone number: ";
            std::cin >> edit.edited_phone_number;
            verify_cin();
            second->edit_contact(new_data.name,new_data.last_name,edit,new_data);
            std::cout << "[*] Your contact has been edited with the new info." << std::endl;
        }
    } else if (choice == 3) {
        std::cout << "[*] Remember that the operation of deleting a contact is NOT reversible and you'll lose your contact forever." << std::endl;
        std::cout << "[*] Can you confirm you read this? (Y/n): ";
        std::cin >> confirm_delete;
        verify_cin();
        if (confirm_delete != answers[0]) {
            std::cerr << "[*] Exiting..." << std::endl;
            return 1;
        }
        std::cout << "[*] Name of the contact: " ;
        std::cin >> new_data.name ;
        std::cout << "[*] Last Name: " ;
        std::cin >> new_data.last_name;
        second->delete_contact(new_data.name,new_data.last_name);
    } else {
        std::cerr << "[*] No choices available." << std::endl;
        return 1;
    }
    std::cout << "[*] Thanks for using 'Contacts!'" << std::endl;
    std::cout << "[*] Press Y to continue or any other key for exiting the program: " ;
    std::cin >> last_choice;
    verify_cin();
    if (last_choice == answers[0]) {
        asm("jmp start;");
    } else {
        std::cerr << "[*] Exiting..." << std::endl;
        return 1;
    }
    return 0;
}
