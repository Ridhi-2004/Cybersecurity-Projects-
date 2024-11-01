#include <iostream>
#include <fstream>//used for reading from and writing to files used later in my code. 
#include <string>
#include <cstdlib> // This library is needed for the random password generation for this specific function: rand()

using namespace std;

class PasswordManager {
private:
    string MasterPassword; //MasterPassword cannot be altered outside the class.

public:
    PasswordManager() {
        MasterPassword = ""; //obviously the contents of whatever the user chooses the master password to be can be inputted.
    }

    void MPsetting() {
        cout << "Please enter your master password: ";//The user chooses their masterpassword and it is stored. 
        cin >> MasterPassword;
    }

    bool authenticate() { //This specific use of boolean allows the master password to be authenticated, and later on in the code the rest of the code can only proceed if the master password is correct
        string AuthenticPassword;
        cout << "To proceed, please enter your master password: ";
        cin >> AuthenticPassword;
        return AuthenticPassword == MasterPassword; // authenticates the password the user has put against the real master password
    }

    void Menu() { //I have utilised switch statements rather than if else statements as theyre simpler, and allows functions to be called up easier
        int options;
        while (true) {
            cout << "----PASSWORD MANAGER MENU----" << endl;
            cout << "Option 1. Add credentials" << endl;
            cout << "Option 2. Get credentials" << endl;
            cout << "Option 3. Delete credentials" << endl;
            cout << "Option 4. Save to file" << endl;
            cout << "Option 5. Load from file" << endl;
            cout << "Option 6. Exit program" << endl;
            cin >> options;

            if (!authenticate()) { // the authenticate function is called up, so the user can only pick an option if the master password is correct.
              cout <<"The master password is incorrect. "<<endl;
              continue;
            }

            switch (options) { //I learnt how to implement switch cases by watching a youtube video by portfolio classes called "Creating a menu using a switch statement"
            case 1: //If option 1 chosen by the user, then the AddCredents function will be called allowing the user to add their credentials.
                AddCredents();
                break;
            case 2: //If option21 chosen by the user, then the GetCredents function will be called allowing the user to get their credentials
                GetCredents();
                break;
            case 3:
                DeleteCredents(); //If option 3 chosen by the user, then the DeleteCredents function will be called allowing the user to delete their credentials
                break;
            case 4:
                SaveCredents(); //If option 4 chosen by the user, then the SaveCredents function will be called allowing the user to save their credentials
                break;
            case 5:
                LoadCredents(); //If option 5 chosen by the user, then the LoadCredents function will be called allowing the user to Load their credentials
                break;
            case 6:
                cout << "Goodbye!"; //If case 6 chosen, it will exit the program 
                return;
            default: //If none of the options from 1-6 are chosen then it will prompt the user to choose again.
                cout << "This is not a choice. Pick from 1-6.";
            }
        }
    }

    void AddCredents() {
        string username; //The user enters any username theyd like and it is stored in cin
        cout << "Please enter a username: ";
        cin >> username;
        string password = RandomPassword(); //A password will be associated with the username and will be encrypted
        encrypted(password);
        ofstream file; //both the encrypted password and username is stored in a file called PasswordManager.
        file.open("PasswordManager.txt", ios::app); //I used lecture 11 of week 15 labelled file handling, it will store username in a file called password manager. Also look at some research from a website called she.codes
        file << username << " " << password << endl;
        file.close();
        cout << "Details added successfully." << endl;
    }

    void GetCredents() { //Creates a get credentials function
        string InputtedUsername;
        string username;
        string password;
        ifstream inFile("PasswordManager.txt");
        cout << "Enter the username to retrieve password: "; //the username will get the associated password
        cin >> InputtedUsername;
        while (inFile >> username >> password) {
            if (InputtedUsername == username) { //if the username the user entered is the same as the stored one, the password will be decrypted and presented to the user
                decrypted(password);
                cout << "The password for user " << username << " is: " << password << endl;
                inFile.close();
                return;
            }
        }
        cout << "Username not found." << endl; //If the user inputs a username which is not stored in the file, this line will be presented. 
    }

    void DeleteCredents() {
      string InputtedUsername;
      string username;
      string password;
      cout <<"Enter the correct username to delete the credentials: ";
      cin >> InputtedUsername;
      ifstream inFile("PasswordManager.txt");
      ofstream tempFile("TempLocation.txt"); //This moves all credentials into a temporary file, except for the credentials the user wants to delete.
      while (inFile >> username >> password) {
          if (InputtedUsername != username) {
              tempFile << username << " " << password << endl;
          }
      }
      inFile.close();
      tempFile.close();
      remove("PasswordManager.txt");
      rename("TempLocation.txt", "PasswordManager.txt"); //this essentially updates the file to a new passwordmanager.txt so that it contains the credentials now without the deleted credentials.
      cout << "Credentials for " <<InputtedUsername << " have been deleted" <<endl;
    }

    void SaveCredents() {
      string username;
      string password;
      ifstream inFile("PasswordManager.txt");
      ofstream outFile("TempLocation.txt"); //A backup of the credentials is made into this temporary file.
      while (inFile >> username >> password) {
        outFile << username << " " << password << endl;
      }
      cout << "Credentials are saved." << endl;
      inFile.close();
      outFile.close();
    }

   void LoadCredents() {
        string ChosenUsername;
        cout << "Enter the username to load information: "; //The user is asked for what username do they want the password/credentials to be loaded for as there could be many users created.
        cin >> ChosenUsername;

        string username;
        string password;
        ifstream inFile("PasswordManager.txt");
        if (!inFile) {
            cout << "No data found." << endl; //the username is checked in the file and if it is not found then no data found is outputted
            return;
        }

        bool found = false;
        while (inFile >> username >> password) {
            if (username == ChosenUsername) { // if the username matches as to the one in file then the password will be outputted
                cout << "Password for username " << username << ": " << password << endl;
                found = true;
                break;
            }
        }

        inFile.close();

        if (!found) {
            cout << "No password found for username: " << ChosenUsername << endl; //if the username is not found, then there will consequently be no password associated.
        }
   }

private:
    string RandomPassword() { //the generated password is obviously in a private member because we do not want to change it outside the class.
        const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" //the generated password will include these characters
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789"
                                   "!£$%^&*";
        const int len = 15; //the password will be up to a length of 15
        string password = "";
        for (int i = 0; i < len; ++i) {
            password += characters[rand() % characters.length()]; //The password consists of random characters and a random length.
        }
        return password;
    }

    void encrypted(string& password) { //All of this code is adapted from lecture 17 basic cryptography, in which I used the caesar cipher.
        int key;
        cout << "Please type in a number for the private key: ";
        cin >> key; //When the user enters a number, this is how much the digits and characters will be shifted (in the ASCII table) for the encrypted password.
        for (char& specialcharacters : password) {
            if (specialcharacters >= 'a' && specialcharacters <= 'z') { //So, if the shifting causes the value to be out of the range of a-z, then z will go back to a.
                specialcharacters = specialcharacters + key;
                if (specialcharacters > 'z') {
                    specialcharacters = specialcharacters - 'z' + 'a' - 1;
                }
            } else if (specialcharacters >= 'A' && specialcharacters <= 'Z') {
                specialcharacters = specialcharacters + key;
                if (specialcharacters > 'Z') {
                    specialcharacters = specialcharacters - 'Z' + 'A' - 1; //In the same concept, Z will be brought back to A.
                }
            } else if (specialcharacters >= '0' && specialcharacters <= '9') {//The range here is limited to 0-9
                specialcharacters = specialcharacters + key;
                if (specialcharacters > '9') {
                    specialcharacters = specialcharacters - '9' + '0' - 1; //If the shifting goes beyond this, then 9 will come back to 0. 
                }
            } else if (specialcharacters >= '!' && specialcharacters <= '*') { //The range is limited from the special character '!' to '*'.m
                specialcharacters = specialcharacters + key;
                if (specialcharacters > '*') {
                    specialcharacters = specialcharacters - '*' + '!' - 1;//! will return to *, if shifting goes beyond range. 
                }
            }
        }
    }

    void decrypted(string& password) { //The decryption is essentially the inversion of the encryption. 
        int key;
        cout << "Please type in the private key: ";
        cin >> key;
        for (char& specialcharacters : password) {
            if (specialcharacters >= 'a' && specialcharacters <= 'z') {
                specialcharacters = specialcharacters - key; //essentially if the subtraction of the key causes the characters to go beyond valid range, then z will go back to a. Same for the other characters below. 
                if (specialcharacters < 'a') {
                    specialcharacters = specialcharacters - 'a' + 'z' + 1;
                }
            } else if (specialcharacters >= 'A' && specialcharacters <= 'Z') {
                specialcharacters = specialcharacters - key;
                if (specialcharacters < 'A') {
                    specialcharacters = specialcharacters - 'A' + 'Z' + 1;
                }
            } else if (specialcharacters >= '0' && specialcharacters <= '9') {
                specialcharacters = specialcharacters - key;
                if (specialcharacters < '0') {
                    specialcharacters = specialcharacters - '0' + '9' + 1;
                }
            } else if (specialcharacters >= '!' && specialcharacters <= '*') {
                specialcharacters = specialcharacters - key;
                if (specialcharacters < '!') {
                    specialcharacters = specialcharacters - '!' + '*' + 1;
                }
            }
        }
    }
};

int main() {
    PasswordManager start;
    start.MPsetting(); //This is called first so that the master password is set first
    start.Menu();//Then the menu is called, and the user has to pick from options 1-6.
    return 0;
}