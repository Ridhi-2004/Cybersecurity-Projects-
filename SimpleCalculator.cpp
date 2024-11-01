#include <iostream>

using namespace std;

int main() {
    int choice; //The user picks a choice and is stored as an integer. 
    double amount; //The time will be entered by the user and stored in this. Ive used the double instead of a float because it has a larger range of values and more precise than a float.
    double StoH;//Seconds to hours, stored as a double for reasons mentioned above.  
    double StoM;//Seconds to minutes
    double MtoH; //Minutes to hours
    double HtoS; // Hours to seconds
    bool quit = false; //keeps the program running and looping unti the boolean value is set to true

    do { //Menu set uo for switch cases, allows users to see the options. 
        cout << "Option 1) Convert Seconds to Hours" << endl;
        cout << "Option 2) Convert Seconds to Minutes" << endl;
        cout << "Option 3) Convert Minutes to Hours" << endl;
        cout << "Option 4) Convert Hours to Seconds" << endl;
        cout << "Option 5) Exit" << endl;
        cout << "Enter Choice: "; 
        cin >> choice; //Stores the users input into the value named choice. 

        switch (choice) {
            case 1:
                cout << "Enter time in seconds: ";
                cin >> amount;//Time entered by user will be stored in the value called 'amount'
                StoH = amount / 3600; //The number the user inputs will be translated into hours by dividing it by 3600 (Logic)
                cout << "Time in hours: " << StoH << endl; //The answer will be outputted
                break;

            case 2:
                cout << "Enter time in seconds: ";
                cin >> amount;
                StoM = amount / 60; //The number the user inputs will be translated into minutes by dividing it (Seconds) by 60 (Logic conversion)
                cout << "Time in minutes: " << StoM << endl;
                break;

            case 3:
                cout << "Enter time in minutes: ";
                cin >> amount;
                MtoH = amount / 60;  //The number (Minutes) the user inputs will be translated into hours by dividing it by 60. 
                cout << "Time in hours: " << MtoH << endl;
                break;

            case 4:
                cout << "Enter time in hours: ";
                cin >> amount;
                HtoS = amount * 3600;  //The number (hours) the user inputs will be translated into seconds by multiplying it by 3600.
                cout << "Time in seconds: " << HtoS << endl;
                break;

            case 5:
                cout << "Goodbye!" << endl;
                quit = true; //The program will excecute if option 5 chosen as the boolean is set to true. Terminated. 
                break;

            default:
                cout << "Invalid option entered, please choose again from 1-5" << endl; //If the user chooses an option which is not presented, it will prompt them to choose again.
        }
    } while (!quit);

    return 0;
}