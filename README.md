# DateLibraryFP 📅

A modern C++ Date Utility Library built completely from scratch to understand how date systems work internally without relying on built-in date libraries.

---

# 📌 Overview

**DateLibraryFP** is a functional-style C++ project that provides a complete set of utilities for handling:

- dates
- years
- months
- weeks
- calendars
- date arithmetic
- date validation
- business day calculations
- period operations

This project was built to deeply understand the algorithms and mathematics behind real-world date systems instead of depending on ready-made libraries.

The focus of the project is on:

- problem solving
- clean code organization
- reusable functions
- edge-case handling
- manual implementation of date logic

---

# ⚙️ Features

## 🗓️ Year Utilities

- Detect leap years
- Get number of days in a year
- Get number of hours in a year
- Get number of minutes in a year
- Get number of seconds in a year

---

## 📆 Month Utilities

- Get number of days in any month
- Get month names
- Detect last month in the year
- Calculate month hours, minutes, and seconds

---

## 📅 Date Validation & Day Utilities

- Validate full dates safely
- Read validated user input
- Get day index using Zeller’s Formula
- Get day order in the week
- Calculate passed days in the year
- Calculate remaining days in the year
- Detect last day in month
- Detect weekends
- Detect business days
- Calculate remaining days until:
  - end of week
  - end of month
  - end of year

---

## ➕ Date Arithmetic

### Addition Operations

- Add one day
- Add multiple days
- Add weeks
- Add months
- Add years
- Add decades
- Add centuries
- Add millennium

### Subtraction Operations

- Subtract one day
- Subtract multiple days
- Subtract weeks
- Subtract months
- Subtract years

---

## 🔍 Date Comparison

- Compare two dates
- Check if dates are equal
- Check if one date is before another
- Check if one date is after another
- Calculate difference between two dates
- Calculate age in days from current system date

---

## 🗂️ Period Operations

- Read period input
- Validate periods
- Check if a date belongs to a period
- Check if two periods overlap
- Calculate overlap days between periods

---

## 🏖️ Business Day & Vacation Calculations

- Detect business days
- Detect weekends
- Calculate vacation return date
- Add business days while skipping weekends
- Count vacation days between two dates

---

## 🗓️ Calendar System

- Print monthly calendar
- Print yearly calendar

---

## 💻 System Date Integration

- Read current system date from device time
- Perform real-time date calculations using `<ctime>`

---

# 🧠 Concepts & Algorithms Used

This project includes practical implementation of:

- Functional Programming principles
- Zeller’s Congruence
- Leap year calculations
- Date normalization
- Modular arithmetic
- Calendar generation algorithms
- Date comparison algorithms
- Period overlap logic
- Input validation systems
- Edge-case handling
- Reusable function design

---

# 🚀 Project Goals

This project was built to:

- deeply understand date systems internally
- improve algorithmic thinking
- strengthen problem-solving skills
- practice clean and modular C++ design
- build software engineering thinking through manual implementation

The core philosophy behind this project:

> Think like a software engineer, not just a code writer.

---

# 🔮 Future Improvements

Planned future upgrades include:

- Full OOP version using a `Date` class
- Operator overloading (`+`, `-`, `<`, `>`, `==`)
- Absolute day number system
- Holiday support
- Advanced business-day calculations
- Time support (hours / minutes / seconds)
- Unit testing
- Performance optimizations
- Better file separation using `.h` and `.cpp`
- Cross-platform improvements

---

# 🛠️ Technologies

- C++
- Visual Studio 2022

### Standard Library

- `<iostream>`
- `<iomanip>`
- `<ctime>`
- `<string>`
- `<algorithm>`

---

# ▶️ How to Run

1. Open the project in **Visual Studio 2022**
2. Build the solution
3. Run the application
4. Enter date values
5. Test calculations and calendar utilities

---

# 👤 Author

**Developed by Sidi Abdullah**

---

# ⭐ Final Note

This project is not intended to replace professional date libraries such as `std::chrono`.

Its purpose is to deeply understand the internal logic behind real-world date systems and strengthen software engineering fundamentals by building everything manually from scratch.