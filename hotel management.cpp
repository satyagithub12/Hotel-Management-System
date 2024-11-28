#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Room Class
class Room {
public:
    int roomNumber;
    string roomType;
    double price;
    bool isAvailable;

    // Constructor
    Room(int rNo, string rType, double p)
        : roomNumber(rNo), roomType(rType), price(p), isAvailable(true) {}

    // Book the room
    void bookRoom() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Room " << roomNumber << " is booked.\n";
        } else {
            cout << "Room " << roomNumber << " is already booked.\n";
        }
    }

    // Cancel booking
    void cancelBooking() {
        isAvailable = true;
        cout << "Booking for room " << roomNumber << " is canceled.\n";
    }

    // Display room information
    void displayInfo() const {
        cout << "Room " << roomNumber << " (" << roomType << ") - Price: $" << price
             << (isAvailable ? " [Available]" : " [Booked]") << endl;
    }
};

// Guest Class
class Guest {
public:
    string guestName;
    string guestID;
    string phoneNumber;

    // Constructor
    Guest(string name, string id, string phone)
        : guestName(name), guestID(id), phoneNumber(phone) {}

    // Display guest information
    void displayInfo() const {
        cout << "Guest: " << guestName << " (ID: " << guestID << ", Phone: " << phoneNumber << ")\n";
    }
};

// Reservation Class
class Reservation {
public:
    int reservationID;
    Guest guest;
    Room* room;  // Changed from Room& to Room* (pointer)
    string checkInDate;
    string checkOutDate;
    bool isCanceled;

    // Constructor
    Reservation(int resID, Guest g, Room* r, string checkIn, string checkOut)
        : reservationID(resID), guest(g), room(r), checkInDate(checkIn), checkOutDate(checkOut), isCanceled(false) {
        if (room) {
            room->bookRoom();
        }
    }

    // Cancel reservation
    void cancelReservation() {
        if (!isCanceled && room) {
            room->cancelBooking();
            isCanceled = true;
            cout << "Reservation " << reservationID << " is canceled.\n";
        } else {
            cout << "Reservation " << reservationID << " is already canceled or room is invalid.\n";
        }
    }

    // Display reservation details
    void displayReservation() const {
        if (isCanceled) {
            cout << "\nReservation ID: " << reservationID << " [Canceled]\n";
        } else {
            cout << "\nReservation ID: " << reservationID << "\n";
            guest.displayInfo();
            if (room) {
                cout << "Room Number: " << room->roomNumber << ", Type: " << room->roomType << "\n";
                cout << "Check-in: " << checkInDate << ", Check-out: " << checkOutDate << "\n";
            }
        }
    }
};

// Main Function
int main() {
    vector<Room> rooms;
    rooms.push_back(Room(101, "Single", 100.0));
    rooms.push_back(Room(102, "Double", 150.0));
    rooms.push_back(Room(103, "Suite", 200.0));

    vector<Reservation> reservations;

    while (true) {
        int choice;
        cout << "\nHotel Management System\n";
        cout << "1. View Available Rooms\n";
        cout << "2. Make Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. View Reservation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nAvailable Rooms:\n";
                for (size_t i = 0; i < rooms.size(); i++) {
                    rooms[i].displayInfo();
                }
                break;
            }
            case 2: {
                // Input guest details
                string guestName, guestID, phoneNumber;
                cout << "\nEnter guest name: ";
                cin.ignore();
                getline(cin, guestName);
                cout << "Enter guest ID: ";
                cin >> guestID;
                cout << "Enter phone number: ";
                cin >> phoneNumber;

                Guest guest1(guestName, guestID, phoneNumber);

                // Select room
                int roomChoice;
                cout << "\nEnter the room number you want to book: ";
                cin >> roomChoice;

                Room* selectedRoom =  NULL;
                for (size_t i = 0; i < rooms.size(); i++) {
                    if (rooms[i].roomNumber == roomChoice && rooms[i].isAvailable) {
                        selectedRoom = &rooms[i];
                        break;
                    }
                }

                if (selectedRoom == NULL) {
                    cout << "Invalid or unavailable room selection.\n";
                    break;
                }

                // Input reservation details
                string checkInDate, checkOutDate;
                cout << "Enter check-in date (YYYY-MM-DD): ";
                cin >> checkInDate;
                cout << "Enter check-out date (YYYY-MM-DD): ";
                cin >> checkOutDate;

                // Create reservation and add to vector
                Reservation reservation(reservations.size() + 1, guest1, selectedRoom, checkInDate, checkOutDate);
                reservations.push_back(reservation);
                reservation.displayReservation();
                break;
            }
            case 3: {
                // Cancel reservation
                int reservationID;
                cout << "\nEnter Reservation ID to cancel: ";
                cin >> reservationID;

                if (reservationID <= 0 || reservationID > reservations.size()) {
                    cout << "Invalid Reservation ID.\n";
                } else {
                    reservations[reservationID - 1].cancelReservation();
                }
                break;
            }
            case 4: {
                // View reservation details
                int reservationID;
                cout << "\nEnter Reservation ID to view: ";
                cin >> reservationID;

                if (reservationID <= 0 || reservationID > reservations.size()) {
                    cout << "Invalid Reservation ID.\n";
                } else {
                    reservations[reservationID - 1].displayReservation();
                }
                break;
            }
            case 5:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}