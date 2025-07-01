#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <windows.h>  // Only for Windows

using namespace std;

const int POPULATION_SIZE = 100;
const int GRID_MIN = -100;
const int GRID_MAX = 100;
const double INFECTION_RADIUS = sqrt(2);
const double INFECTION_CHANCE = 0.9;
int totalInfected = 0;

const int VISUAL_MIN = -20;
const int VISUAL_MAX = 20;

struct Position {
    int x, y;
};

struct Person {
    int id;
    Position pos;
    bool infected;
    vector<Position> movementLog;
};

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool isWithinInfectionRadius(Position a, Position b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return (dx * dx + dy * dy) <= INFECTION_RADIUS * INFECTION_RADIUS;
}

void movePerson(Person& p) {
    int dx = randomInRange(-1, 1);
    int dy = randomInRange(-1, 1);
    p.pos.x = max(GRID_MIN, min(GRID_MAX, p.pos.x + dx));
    p.pos.y = max(GRID_MIN, min(GRID_MAX, p.pos.y + dy));
    p.movementLog.push_back(p.pos);
}

void displayGrid(const vector<Person>& people) {
    cout << "\n--- Grid (Range: -20 to 20) ---\n";
    for (int y = VISUAL_MAX; y >= VISUAL_MIN; --y) {
        for (int x = VISUAL_MIN; x <= VISUAL_MAX; ++x) {
            bool found = false;
            for (const Person& p : people) {
                if (p.pos.x == x && p.pos.y == y) {
                    // Color output
                    if (p.infected)
                        cout << "\033[1;31mI\033[0m";  // Red I
                    else
                        cout << "\033[1;32mH\033[0m";  // Green H
                    found = true;
                    break;
                }
            }
            if (!found) cout << ".";
        }
        cout << "  y=" << setw(3) << y << "\n";
    }

    for (int i = 0; i < (VISUAL_MAX - VISUAL_MIN + 1); ++i)
        cout << "-";
    cout << "\n";

    for (int x = VISUAL_MIN; x <= VISUAL_MAX; ++x)
        cout << ((x % 5 == 0) ? "|" : " ");
    cout << "  x-axis\n";
}

void displayPopulation(const vector<Person>& people, int day) {
    cout << "\n--- Day " << day << " ---\n";
    for (const Person& p : people) {
        cout << "Person " << setw(3) << p.id << ": (" << setw(3) << p.pos.x << ", " << setw(3) << p.pos.y << ") ";
        cout << (p.infected ? "[\033[1;31mINFECTED\033[0m]" : "[\033[1;32mHEALTHY\033[0m]") << endl;
    }
}

void exportCSV(const vector<Person>& people) {
    ofstream fout("pota_output.csv");
    fout << "ID,Day,X,Y,Status\n";
    for (const Person& p : people) {
        for (size_t i = 0; i < p.movementLog.size(); ++i) {
            fout << p.id << "," << i << "," << p.movementLog[i].x << "," << p.movementLog[i].y << "," << (p.infected ? "INFECTED" : "HEALTHY") << "\n";
        }
    }
    fout.close();
    cout << "\n✅ Movement & Infection data exported to pota_output.csv\n";
}

int main() {
    srand(time(0));
    vector<Person> people;

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Person p;
        p.id = i + 1;
        p.pos.x = randomInRange(GRID_MIN, GRID_MAX);
        p.pos.y = randomInRange(GRID_MIN, GRID_MAX);
        p.infected = (i < POPULATION_SIZE / 10);
        p.movementLog.push_back(p.pos);
        if (p.infected) totalInfected++;
        people.push_back(p);
    }

    int n;
    cout << "Enter number of days to simulate: ";
    cin >> n;

    for (int day = 1; day <= n; ++day) {
        system("cls"); // Clear screen (Windows only)

        for (Person& p : people) {
            movePerson(p);
        }

        vector<int> newlyInfected;
        for (size_t i = 0; i < people.size(); ++i) {
            if (!people[i].infected) {
                for (size_t j = 0; j < people.size(); ++j) {
                    if (i != j && people[j].infected &&
                        isWithinInfectionRadius(people[i].pos, people[j].pos)) {
                        if ((rand() % 100) < (INFECTION_CHANCE * 100)) {
                            newlyInfected.push_back(i);
                            break;
                        }
                    }
                }
            }
        }

        for (int index : newlyInfected) {
            if (!people[index].infected) {
                people[index].infected = true;
                totalInfected++;
            }
        }

        displayPopulation(people, day);
        displayGrid(people);

        Sleep(1000); // Pause for 1 second (Windows only)
    }

    cout << "\nTotal Infected after " << n << " days: " << totalInfected << " out of " << POPULATION_SIZE << endl;
    exportCSV(people);

    return 0;
}
