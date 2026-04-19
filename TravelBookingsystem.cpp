#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

const string ADMIN_USER = "admin";
const string ADMIN_PASS = "1234";

int bookingCounter = 1000;

class User
{
public:
    string username, password;

    void registerUser()
    {
        cout << "\n===== USER REGISTRATION =====\n";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        file << username << " " << password << "\n";
        file.close();

        cout << "Registration Successful!\n";
    }

    bool loginUser()
    {
        string u, p;
        cout << "\n===== USER LOGIN =====\n";
        cout << "Enter Username: ";
        cin >> u;
        cout << "Enter Password: ";
        cin >> p;

        ifstream file("users.txt");
        string storedUser, storedPass;

        while (file >> storedUser >> storedPass)
        {
            if (u == storedUser && p == storedPass)
            {
                cout << "Login Successful!\n";
                return true;
            }
        }

        cout << "Invalid Credentials!\n";
        return false;
    }
};

class Booking
{
private:
    string customerName;
    vector<int> selectedCities;

    int hotel, vehicle, persons, packageChoice;
    int bookingID;

    string travelDate;
    int days;

    vector<string> cities = {
        "Udaipur", "Jaipur", "Jaisalmer", "Bikaner", "Jodhpur"};

    int distance[5][5] = {
        {0, 394, 492, 480, 250},
        {394, 0, 558, 335, 350},
        {492, 558, 0, 330, 285},
        {480, 335, 330, 0, 250},
        {250, 350, 285, 250, 0}};

public:
    Booking()
    {
        bookingID = ++bookingCounter;
    }

    void input()
    {
        cin.ignore();

        cout << "\nEnter Customer Name: ";
        getline(cin, customerName);

        do {
            cout << "Enter Number of Persons (1-20): ";
            cin >> persons;
        } while (persons < 1 || persons > 20);

        cout << "Enter Travel Date (DD/MM/YYYY): ";
        cin >> travelDate;

        // FIX #4: Validate days input
        do {
            cout << "Enter Number of Days (1-30): ";
            cin >> days;
        } while (days < 1 || days > 30);

        cout << "\nSelect Package:\n";
        cout << "1. Single City\n";
        cout << "2. 3 Places Combo\n";

        do {
            cin >> packageChoice;
        } while (packageChoice < 1 || packageChoice > 2);

        cout << "\nAvailable Cities:\n";
        for (int i = 0; i < (int)cities.size(); i++)
            cout << i + 1 << ". " << cities[i] << "\n";

        selectedCities.clear();

        if (packageChoice == 1)
        {
            int c;
            do {
                cout << "Select 1 City (1-5): ";
                cin >> c;
            } while (c < 1 || c > 5);
            selectedCities.push_back(c);
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                int c;
                bool duplicate;
                do
                {
                    duplicate = false;
                    // FIX #4: Validate range as well as duplicates
                    do {
                        cout << "City " << i + 1 << " (1-5): ";
                        cin >> c;
                    } while (c < 1 || c > 5);

                    for (int x : selectedCities)
                    {
                        if (x == c)
                        {
                            duplicate = true;
                            cout << "Already Selected! Choose a different city.\n";
                        }
                    }
                } while (duplicate);

                selectedCities.push_back(c);
            }
        }

        cout << "\nSelect Hotel:\n";
        cout << "1. Budget (Rs 1500/person/day)\n";
        cout << "2. Premium (Rs 3000/person/day)\n";
        cout << "3. Luxury (Rs 5000/person/day)\n";
        do {
            cin >> hotel;
        } while (hotel < 1 || hotel > 3);

        cout << "\nSelect Vehicle:\n";
        cout << "1. Sedan  (Rs 12/km)\n";
        cout << "2. SUV    (Rs 18/km)\n";
        cout << "3. Traveller (Rs 25/km)\n";
       
        do {
            cin >> vehicle;
        } while (vehicle < 1 || vehicle > 3);
    }

    int hotelCost()
    {
        int rate = (hotel == 1) ? 1500 : (hotel == 2) ? 3000 : 5000;
        return rate * persons * days;
    }

    int routeDistance()
    {
        int total = 0;
        for (int i = 0; i < (int)selectedCities.size() - 1; i++)
        {
            int a = selectedCities[i] - 1;
            int b = selectedCities[i + 1] - 1;
            total += distance[a][b];
        }
        return total;
    }

    int vehicleCost()
    {
        int rate = (vehicle == 1) ? 12 : (vehicle == 2) ? 18 : 25;
        return routeDistance() * rate;
    }

    int packageCost()
    {
        return (packageChoice == 2) ? 4000 * persons : 0;
    }

    void generateBill()
    {
        int subtotal = hotelCost() + vehicleCost() + packageCost();
        double gst = subtotal * 0.18;
        double total = subtotal + gst;

        cout << "\n===== FINAL BILL =====\n";
        cout << "Booking ID   : TRV" << bookingID << "\n";
        cout << "Customer     : " << customerName << "\n";
        cout << "Travel Date  : " << travelDate << "\n";
        cout << "Days         : " << days << "\n";
        cout << "Cities       : ";
        for (int x : selectedCities)
            cout << cities[x - 1] << " ";
        cout << "\n";
        cout << "Route Dist.  : " << routeDistance() << " KM\n";
        cout << "\nHotel Cost   : Rs " << hotelCost() << "\n";
        cout << "Vehicle Cost : Rs " << vehicleCost() << "\n";
        cout << "Package Cost : Rs " << packageCost() << "\n";
        cout << "Subtotal     : Rs " << subtotal << "\n";
        cout << "GST (18%)    : Rs " << fixed << setprecision(2) << gst << "\n";
        cout << "TOTAL BILL   : Rs " << fixed << setprecision(2) << total << "\n";

        string cityStr = "";
        for (int x : selectedCities)
            cityStr += cities[x - 1] + "_";

        ofstream file("bookings.txt", ios::app);
        file << "TRV" << bookingID << "|"
             << customerName << "|"
             << cityStr << "|"
             << fixed << setprecision(2) << total << "\n";
        file.close();
    }
};

void viewBookings()
{
    ifstream file("bookings.txt");

    if (!file.is_open())
    {
        cout << "No bookings found.\n";
        return;
    }

    string line;
    bool anyBooking = false;

    cout << "\n=========================================================\n";
    cout << left << setw(12) << "BOOKING ID"
         << setw(20) << "CUSTOMER"
         << setw(25) << "CITIES"
         << "TOTAL\n";
    cout << "=========================================================\n";

    while (getline(file, line))
    {
        if (line.empty()) continue;
        anyBooking = true;

        vector<string> parts;
        string token;
        for (char ch : line)
        {
            if (ch == '|') { parts.push_back(token); token = ""; }
            else token += ch;
        }
        parts.push_back(token);

        if (parts.size() < 4) continue;

        string id       = parts[0];
        string name     = parts[1];
        string cityData = parts[2];
        string totalStr = parts[3];

        for (char& ch : cityData)
            if (ch == '_') ch = ' ';

        cout << left << setw(12) << id
             << setw(20) << name
             << setw(25) << cityData
             << "Rs " << totalStr << "\n";
    }

    if (!anyBooking)
        cout << "No bookings found.\n";

    cout << "=========================================================\n";
    file.close();
}

void cancelBooking()
{
    string cancelID;
    int daysBefore;

    cout << "\nEnter Booking ID to Cancel: ";
    cin >> cancelID;

    cout << "How many days before trip are you cancelling? ";
    cin >> daysBefore;

    ifstream file("bookings.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        vector<string> parts;
        string token;
        for (char ch : line)
        {
            if (ch == '|') { parts.push_back(token); token = ""; }
            else token += ch;
        }
        parts.push_back(token);

        if (parts.size() < 4) continue;

        string id       = parts[0];
        string totalStr = parts[3];
        double total    = stod(totalStr);

        if (id == cancelID)
        {
            found = true;
            double refund = 0;

            if (daysBefore >= 7)
                refund = total * 0.90;
            else if (daysBefore >= 3)
                refund = total * 0.50;
            else
                refund = 0;

            cout << "Booking Cancelled!\n";
            cout << "Refund Amount: Rs " << fixed << setprecision(2) << refund << "\n";
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (!found)
        cout << "Booking ID not found!\n";
}

void adminPanel()
{
    string user, pass;

    cout << "\n===== ADMIN LOGIN =====\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user != ADMIN_USER || pass != ADMIN_PASS)
    {
        cout << "Invalid Admin Credentials!\n";
        return;
    }

    int ch;
    do
    {
        cout << "\n===== ADMIN PANEL =====\n";
        cout << "1. View All Bookings\n";
        cout << "2. Cancel Booking\n";
        cout << "3. Exit Admin Panel\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1: viewBookings();  break;
        case 2: cancelBooking(); break;
        case 3: cout << "Exiting Admin Panel.\n"; break;
        default: cout << "Invalid Choice!\n";
        }
    } while (ch != 3);
}

int main()
{
    User u;
    int choice;

    do
    {
        cout << "\n===== TRAVEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login & Book Trip\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            u.registerUser();
            break;

        case 2:
        {
            bool success = u.loginUser();
            if (success)
            {
                Booking b;
                b.input();
                b.generateBill();
            }
            else
            {
                cout << "Returning to main menu...\n";
            }
            break;
        }

        case 3:
            adminPanel();
            break;

        case 4:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}