# C++ ATM System

A console-based ATM application written in C++ that supports client authentication via account number and PIN code, quick and normal withdrawals, deposits, balance checks, and flat-file balance persistence (`Client.txt`).

## Why I Built This

After building the Bank Management System, I wanted to implement a focused, client-facing ATM workflow centered on a single authenticated session (`Current_Clinet`), balance validation before withdrawals, and immediate persistence back to `Client.txt` using `#//#`-delimited records.

## Key Capabilities

- **Authentication & Session Flow:** Starts at `LoginScreen()`, verifies credentials (`Account_Number` and `PIN_Code`) against `Client.txt`, and maintains the active client in `Current_Clinet` with `Logout` support.
- **Quick Withdraw:** Offers preset withdrawal tiers (`20`, `50`, `100`, `200`, `400`, `600`, `800`, `1000`) plus exit option `[9]`, checking available balance before updating the file.
- **Normal Withdraw:** Prompts for withdrawal amounts in multiples of `5` and blocks requests that exceed the current balance[cite: 14, 16].
- **Deposit & Balance Inquiry:** Allows depositing funds into the active client account and inspecting the current balance (`ShowCheckBalanceScreen`)[cite: 14, 16].
- **File Persistence:** Reads and rewrites client records in `Client.txt` using `#//#` delimiters via `fstream`[cite: 14, 16].

## Project Structure & Data Files

- `ATMSystem.cpp` — Console ATM application containing record parsing/serialization, file helpers, transaction workflows, and menu navigation[cite: 14, 16].
- `Client.txt` — Read/updated at runtime to store serialized client records (`Account_Number`, `PIN_Code`, `Client_Name`, `Client_Phone`, `Account_Balance`)[cite: 14, 16].

## Build & Run

Compile with a C++ compiler (for example `g++`)[cite: 14, 16]:

```bash
g++ -std=c++17 ATMSystem.cpp -o ATMSystem
./ATMSystem
```
(Note: The application uses Windows console commands such as system("cls") and system("pause>0") for screen transitions[cite: 14, 16].)

## Honest Limitations & Next Steps
- **Plain-Text PIN Storage:** Client PINs are stored in plain text inside `Client.txt`, suitable for learning file I/O and control flow rather than production banking security.
- **Console & Edge-Case Handling:** Some prompts and loops (such as non-numeric input handling, quick-withdraw menu bounds/exit handling, and `system("paose>0")` typo in `PerformQuikWithDrawMenue`) can be tightened and cleaned up.
- **Future Direction:** Refactor duplicated transaction/file-update logic into cleaner helpers and separate core logic from console I/O.
