# Travel Management System

A console-based travel booking application written in C++. Users can register, log in, select destinations across Rajasthan, choose hotel and vehicle preferences, and receive an itemized bill with GST. An admin panel allows viewing and cancelling bookings.

---

## Features

- User registration and login with file-based credential storage
- Single city and 3-city combo tour packages
- Hotel selection across three tiers: Budget, Premium, and Luxury
- Vehicle selection: Sedan, SUV, or Traveller
- Automatic route distance calculation using a pre-built distance matrix
- Itemized billing with 18% GST
- Booking cancellation with tiered refund policy
- Admin panel with protected access to view and manage all bookings
- Unique booking IDs using an incrementing counter

---

## Cities Covered

- Udaipur
- Jaipur
- Jaisalmer
- Bikaner
- Jodhpur

---

## Pricing

### Hotels (per person per day)

| Tier    | Rate       |
|---------|------------|
| Budget  | Rs 1,500   |
| Premium | Rs 3,000   |
| Luxury  | Rs 5,000   |

### Vehicles (per km)

| Type       | Rate    |
|------------|---------|
| Sedan      | Rs 12   |
| SUV        | Rs 18   |
| Traveller  | Rs 25   |

### Package Add-on

3-city combo package includes an additional charge of Rs 4,000 per person.

---

## Cancellation Policy

| Days Before Trip | Refund   |
|-----------------|----------|
| 7 or more days  | 90%      |
| 3 to 6 days     | 50%      |
| Less than 3 days| No refund|

---

## How to Compile and Run

### Requirements

- A C++ compiler supporting C++11 or later (e.g., g++)

### Compile

```bash
g++ -o travel_system main.cpp
```

### Run

```bash
./travel_system
```

On Windows:

```bash
travel_system.exe
```

---

## File Structure

```
travel_system/
├── main.cpp          # All source code
├── users.txt         # Stores registered user credentials (auto-created)
├── bookings.txt      # Stores all booking records (auto-created)
└── README.md
```

---

## Usage

### Main Menu

```
1. Register
2. Login and Book Trip
3. Admin Panel
4. Exit
```

### Booking Flow

1. Log in with a registered account
2. Enter customer name, number of persons, travel date, and number of days
3. Select a package (single city or 3-city combo)
4. Choose cities, hotel tier, and vehicle type
5. A bill is generated and saved automatically

### Admin Panel

Default credentials:

```
Username: admin
Password: 1234
```

The admin can view all bookings or cancel a booking by its ID.

---

## Known Limitations

- Passwords are stored in plaintext. This is not suitable for production use.
- Admin credentials are hardcoded in the source file.
- City list and distance matrix are hardcoded; adding a new city requires modifying the source code.
- No user-side booking lookup or cancellation — only admins can cancel bookings.
- Input validation uses infinite loops with no maximum attempt limit.

---

## Sample Output

```
===== FINAL BILL =====
Booking ID   : TRV1001
Customer     : Rahul Sharma
Travel Date  : 15/06/2025
Days         : 3
Cities       : Udaipur Jaipur Jaisalmer
Route Dist.  : 1044 KM

Hotel Cost   : Rs 27000
Vehicle Cost : Rs 12528
Package Cost : Rs 8000
Subtotal     : Rs 47528
GST (18%)    : Rs 8555.04
TOTAL BILL   : Rs 56083.04
```

---

## License

This project is for educational purposes.