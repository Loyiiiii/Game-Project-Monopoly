# 🎲 Watopoly – A C++ University-Themed Monopoly Game

**Watopoly** is a C++-based command-line Monopoly-style board game set on the University of Waterloo campus. This is a term project for **CS246 (Winter 2025)** that involves applying object-oriented programming, modular design, and design patterns in a complete, playable game system.

---

## 📚 Overview

In Watopoly, players move around a custom board representing familiar campus buildings like DC, MC, and SLC. The goal is to be the last player remaining (i.e., not bankrupt), achieved by buying properties, collecting tuition, and outlasting your opponents.

The game supports 2–6 players with unique tokens such as 🦢 (Goose), 💻 (Laptop), or 🍩 (Tim Hortons Donut).

---

## 🧩 Key Features

- 🧭 **40 custom board tiles** based on UWaterloo campus
- 🏫 **Ownable properties**: academic buildings, residences, gyms
- 💸 **Economic system** with buying, rent, tuition, mortgaging, and bankruptcy
- 🏗️ **Improvements**: Add bathrooms and cafeterias to buildings
- 🎲 **Randomized movement** using dice
- 📦 **Game save & load** support via command-line argument
- 🗂️ **Command interpreter**: User inputs like `roll`, `trade`, `mortgage`, `improve`
- 🎓 **Roll Up the Rim** mechanic to escape detention (DC Tims Line)
- 🔁 **SLC & Needles Hall** simulate chance events with randomness
- 🛠️ Uses **C++20 Modules**, RAII, and design patterns (Observer, Decorator)

---

## 🖥️ How to Build & Run

### ✅ Requirements:
- C++ compiler with C++20 support (e.g., `g++-13` or newer)
- Unix-like terminal or Windows PowerShell

### 🔧 Compile:
```bash
please check Makefile in final_version

---

### 💡 Example Commands:
roll: Roll dice and move
trade Alice DC MC: Offer DC for MC from Alice
improve EV3 buy: Buy improvement for EV3
mortgage ESC: Mortgage ESC
bankrupt: Declare bankruptcy
save game1.txt: Save game to file
