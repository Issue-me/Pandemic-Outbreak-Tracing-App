# Pandemic Outbreak Tracing App (POTA) - C++ Simulation

## 📌 Project Overview

The **Pandemic Outbreak Tracing App (POTA)** is a C++ console simulation designed to assist **Digital Fiji** in tracking and modeling the spread of a highly contagious disease, such as COVID-19. This simulation helps visualize the movement of individuals and how infections can spread within a population over time.

---

## 🧠 Features

- 👤 Models a population of 100 individuals.
- 🦠 Randomly infects 10% of the population at the start.
- 🧭 Tracks each person's position on a 2D Cartesian plane.
- 🚶 Simulates daily movements within ±1 unit in both X and Y directions.
- 🧬 Infections spread if a healthy person comes within √2 meters of an infected individual (90% probability).
- 🧮 Reports total infections after `n` simulated days.
- 🗺️ Visual grid display of population movement.
- 📈 Logs all movements and infection status into a CSV file.
- 🎨 Color-coded output (Red = Infected, Green = Healthy).
- 🖥️ Console animation using `system("cls")` (Windows).

---

## 🔧 How It Works

- Each day:
  - All individuals move randomly within the grid.
  - Infections are calculated based on proximity.
  - The console displays:
    - A list of people and their infection status.
    - A 2D visual grid.
- All movement and infection history is saved in `pota_output.csv`.

---

## ✅ Requirements

- C++11 or higher
- Windows OS (for `system("cls")` and `Sleep()`)
- Terminal that supports ANSI colors (CMD, PowerShell, or compatible terminal)

---

## 🚀 How to Run

 1. Compile
```bash
g++ -o pota pota.cpp

2. Run
pota

3. Output
Daily simulation will display grid and movement.
After the simulation, check:
pota_output.csv for detailed trace logs.

Output Files
pota_output.csv — Contains:
Person ID
Day number
X and Y coordinates
Infection status (INFECTED or HEALTHY)

This project is for academic and educational purposes only.
