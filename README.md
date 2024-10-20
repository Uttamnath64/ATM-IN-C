# ATM Management System

This is a simple ATM management system written in C. It allows users to log in, deposit money, withdraw money, view transaction history, and view account details. All account and transaction data is stored in CSV files.

## Features

-   **Login**: Enter card number and PIN to access the ATM.
-   **Deposit**: Add money to the account.
-   **Withdrawal**: Withdraw money from the account (if balance is sufficient).
-   **View Transactions**: Display a list of all transactions.
-   **Account Details**: View the account's balance, card number, and name.
-   **File-Based Storage**: All data is saved in `account.csv` and `atm_tran.csv` files.

## Files

The project consists of three files:

1.  **atm.c**: The source code of the ATM system.
2.  **account.csv**: CSV file that stores account information.
3.  **atm_tran.csv**: CSV file that stores transaction history.

## Setup Instructions

Follow these steps to set up and run the ATM system:

1.  **Download Turbo C**:  
    Make sure Turbo C is installed on your system. You can download Turbo C from [Turbo C Downloads](https://developerinsider.co/download-turbo-c-for-windows-7-8-8-1-and-windows-10-32-64-bit-full-screen/).
    
2.  **Copy the Files**:  
    Copy the following files to the Turbo C `BIN` directory:
    
    -   `atm.c`: The main C program file.
    -   `account.csv`: The CSV file containing account information.
    -   `atm_tran.csv`: The CSV file containing transaction history.
    
    **File Location**:
    
    -   Typically, Turbo C is installed in a directory like `C:\TURBOC3\`.
    -   Go to `C:\TURBOC3\BIN` and paste all three files (`atm.c`, `account.csv`, `atm_tran.csv`).
3.  **Opening the Project in Turbo C**:
    
    -   Launch Turbo C.
    -   Open the `atm.c` file by navigating to `File > Open` and selecting `atm.c` from the `C:\TURBOC3\BIN` directory.
4.  **Compile and Run**:
    
    -   After opening `atm.c`, compile the code by pressing `Alt + F9`.
    -   Run the program by pressing `Ctrl + F9`.
5.  **Account Setup**:
    
    -   The program reads user data from `account.csv`, which has the following format:
        ```
        1,1234567890,1234,Uttam Nath
        2,0987654321,5678,Ankit Nath
        ```
        
    -   Similarly, add a new account, open the account.csv file and add a new line with the format: `id,cardNo,pin,name`. Ensure the id is auto-incremented.
        
6.  **Using the ATM**:
    
    -   Once the program starts, you'll see the welcome screen.
    -   You will be prompted to log in using a valid card number and PIN from `account.csv`.
    -   After logging in, you can deposit, withdraw, view transactions, and view account information.

## UI Output

Below is a sample of what the program's user interface looks like in Turbo C:

### Welcome Screen

![image](https://github.com/user-attachments/assets/d8a57b8c-9346-4b94-91ab-03d90ff65e8b)


### Login Screen

![image](https://github.com/user-attachments/assets/def27abc-4514-490c-9e90-acb3dd5adbd8)


### Home Menu

![image](https://github.com/user-attachments/assets/9f005f22-5093-4d19-8b2b-643853ab5065)


### Deposit Screen

![image](https://github.com/user-attachments/assets/f3a0f8de-d05e-4eba-b5a8-f4e266372831)


### Withdrawal Screen

![image](https://github.com/user-attachments/assets/9f1217b8-3d4a-4f65-b5b4-f53a25a2f4d6)


### View Transactions

![image](https://github.com/user-attachments/assets/a62924fc-56d0-4d36-b37a-f8e45b48aa03)


### Account Details

![image](https://github.com/user-attachments/assets/ff80560a-d510-43a3-84f3-7f38bb8fdf4e)


### Logout Screen

![image](https://github.com/user-attachments/assets/d0333f5a-65b9-40c4-8271-89d5f9a15bb7)


## Demo Video

https://github.com/user-attachments/assets/bb44e9e2-a454-4043-8b8f-8920e9b71fd0
