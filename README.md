# GymMS — Gym Management System

A C++ console application for managing gym memberships with admin and member portals.

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Storage](https://img.shields.io/badge/storage-File%20I%2FO-green)
![Type](https://img.shields.io/badge/type-Console%20App-grey)

---

## Table of contents

- [Overview](#overview)
- [Project structure](#project-structure)
- [Getting started](#getting-started)
- [Usage](#usage)
- [Data model](#data-model)
- [Known issues & limitations](#known-issues--limitations)
- [Suggested improvements](#suggested-improvements)

---

## Overview

GymMS is a file-backed, single-file C++ console application that lets a gym administrator manage member records, and lets members register and update their own profiles. Member data is persisted to a binary flat file (`Member.dat`) using raw struct serialization.

Two modes are available at startup:

- **Admin mode** — requires a username/password, then provides full CRUD access to all records.
- **Member mode** — open access for self-registration, profile editing, and deletion.

---

## Project structure

| Component | Type | Responsibility |
|---|---|---|
| `ADMINISTRATION` | Class | Login/authentication logic; trainer availability display |
| `Candidate` | Class | Member data model; create, display, fee and timeslot selection |
| `AddMember` / `DisplayMembers` / `DisplayRecord` / `EditMember` / `DeleteMember` | Free functions | File-backed CRUD operations on `Member.dat` |
| `Fmanage()` | Function | Admin menu loop |
| `Member()` | Function | Member-facing menu loop |

**Runtime files (auto-created):**

```
Member.dat        # binary flat-file database
Temp.dat          # scratch file used during deletions
fitness_tips.txt  # optional tips file read by Fitness()
```

---

## Getting started

### Prerequisites

- A C++ compiler supporting C++11 or later (`g++`, `clang++`, MSVC)
- On Windows: `system("cls")` calls require a CMD/PowerShell terminal

### Build

```bash
g++ -std=c++11 -o gymms Gym.cpp
```

### Run

```bash
./gymms       # Linux / macOS
gymms.exe     # Windows
```

> **Note:** `Member.dat` is created in the current working directory. Run the binary from a directory where you have write permission.

---

## Usage

### Admin login

Default credentials (hardcoded in source):

| Field | Value |
|---|---|
| Username | `admin` |
| Password | `pass` |

### Admin workflow

```
Select mode: 1 → Enter credentials → Fmanage menu → CRUD operations
```

### Admin menu options

| Option | Description |
|---|---|
| 1 | Add a new member (name, phone, membership number, tier, time slot) |
| 2 | Display all members |
| 3 | Search for a member by membership number |
| 4 | Edit an existing member's details |
| 5 | Delete a member by membership number |
| 6 | Return to main menu |

### Member workflow

```
Select mode: 2 → Member menu → Join / Edit / Quit
```

### Member menu options

| Option | Description |
|---|---|
| 1 | Join gym programme (register as new member) |
| 2 | Delete membership ("Give up on fitness") |
| 3 | Edit gym profile |

---

## Data model

Each member record is stored as a raw binary dump of the `Candidate` struct:

| Field | Type | Notes |
|---|---|---|
| `sc_no` | `int` | Membership number (user-supplied, not auto-incremented) |
| `name` | `char[20]` | Max 19 characters |
| `std` | `char[20]` | `"Gold"` or `"Silver"` |
| `timings` | `char[20]` | Selected time slot string |
| `phone_no` | `long int` | Contact number |
| `Fees` | `float` | Monthly fee determined by tier |

### Membership tiers

| Tier | Monthly fee | Group |
|---|---|---|
| Gold | 5,000 | Gold trainer sessions |
| Silver | 3,000 | Silver trainer sessions |

### Time slots

| Option | Slot |
|---|---|
| 1 | Early Morning — 6:00 AM to 7:00 AM |
| 2 | Morning — 7:00 AM to 8:00 AM |
| 3 | Mid-Morning — 8:00 AM to 9:00 AM |
| 4 | Afternoon — 12:00 PM to 1:00 PM |
| 5 | Evening — 5:00 PM to 6:00 PM |
| 6 | Late Evening — 6:00 PM to 7:00 PM |

---

## Known issues & limitations

| Issue | Details |
|---|---|
| Hardcoded credentials | Username `admin` and password `pass` are stored in plaintext in the source code |
| Infinite recursion on wrong password | `encrypt()` calls itself recursively on every failed attempt with no exit path, risking a stack overflow |
| Buffer overflows | `char` arrays (`name[20]`, `timings[20]`) can overflow if input exceeds the declared size; `strcpy` is used without bounds checking |
| Binary struct serialization | `Member.dat` is not portable across compilers, platforms, or if the struct layout changes |
| Duplicate membership numbers | No uniqueness check on `sc_no` at insertion time |
| Global mutable state | `fp` and `M1` are global variables shared across all operations |
| Windows-only clear screen | `system("cls")` does not work on Linux or macOS terminals |
| Unused `FUNCS` overload | The free function `FUNCS(char*)` decrements local-scope counters that reset on each call, so trainer slot counts have no persistent effect |

---

## Suggested improvements

- Replace hardcoded credentials with a hashed password stored in a config file
- Convert `encrypt()` recursion to an iterative retry loop with a lockout after N failed attempts
- Use `std::string` and `std::cin` with length validation instead of raw `char` arrays and `strcpy`
- Serialize member data as delimited text or CSV instead of raw binary for portability
- Add a unique auto-incrementing ID to prevent duplicate membership numbers
- Replace `system("cls")` with a cross-platform solution (e.g. ANSI escape codes: `\033[2J\033[H`)
- Move `fp` and `M1` out of global scope — pass them as parameters or encapsulate in a manager class
- Add input validation for phone numbers, numeric fields, and out-of-range menu choices

---

*Built with C++ · File-backed binary storage · Console interface*
