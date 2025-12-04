 📝 Account Management System in C

 📌 Overview
This project is a **basic account management system written in C**.  
It provides a simple menu-driven interface for managing user accounts with the following features:
- Sign up (create account)
- Login
- Forgot password (search account)
- Change password
- Delete account

All user data is stored in a **binary file (`account.dat`)** for persistence.

 ⚙️ Features
1. Sign Up
- Collects user details: first name, second name, gender, phone number, email, and password.
- Ensures password confirmation matches before saving.
- Stores account information in `account.dat`.

 2. Login
- Allows login using either **first name** or **email**.
- Verifies password against stored data.
- Displays user details upon successful login.

3. Forgot Password (Search Account)
- Provides three search options:
  - By username (first name)
  - By phone number
  - By email
- Displays stored account details if found.

4. Change Password
- User can update their password by providing:
  - Username or email
  - Old password
  - New password (with confirmation)
- Updates the record in `account.dat`.

5. Delete Account
- Confirms with the user before deletion.
- Removes `account.dat` file if confirmed.

6. Exit
- Gracefully terminates the program.
 🛠️ Technical Details

- **Data Structure:
  ```c
  struct account {
      char first_name[20];
      char second_name[20];
      char gender[20];
      unsigned long long phone_no;
      char email[20];
      char password[20];
      char conf_password[20];
  };
