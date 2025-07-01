#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

class Person {
public:
    int id;
    int x, y; // Position in 2D Cartesian plane
    bool isInfected;

    Person(int id, int x, int y, bool isInfected) : id(id), x(x), y(y), isInfected(isInfected) {}

    void move() {
        // Move to a neighboring position
        int direction = rand() % 8; // 8 possible directions
        switch (direction) {
        case 0: x = std::max(-100, x - 1); break; // Move left
        case 1: x = std::min(100, x + 1); break; // Move right
        case 2: y = std::max(-100, y - 1); break; // Move down
        case 3: y = std::min(100, y + 1); break; // Move up
        case 4: x = std::max(-100, x - 1); y = std::max(-100, y - 1); break; // Move down-left
        case 5: x = std::min(100, x + 1); y = std::max(-100, y - 1); break; // Move down-right
        case 6: x = std::max(-100, x - 1); y = std::min(100, y + 1); break; // Move up-left
        case 7: x = std::min(100, x + 1); y = std::min(100, y + 1); break; // Move up-right
        }
    }
};

double distance(const Person& p1, const Person& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

void simulateDay(std::vector<Person>& people) {
    for (auto& person : people) {
        person.move();
    }

    // Check for infections
    for (size_t i = 0; i < people.size(); ++i) {
        if (!people[i].isInfected) {
            for (size_t j = 0; j < people.size(); ++j) {
                if (people[j].isInfected && distance(people[i], people[j]) <= std::sqrt(2)) {
                    if (rand() % 100 < 90) { // 90% chance to get infected
                        people[i].isInfected = true;
                    }
                }
            }
        }
    }
}

void printStatus(const std::vector<Person>& people, int day) {
    std::cout << "Day " << day << " Status:\n";
    for (const auto& person : people) {
        std::cout << "Person ID: " << person.id << " Position: (" << person.x << ", " << person.y << ") "
            << (person.isInfected ? "Infected" : "Healthy") << "\n";
    }
    std::cout << "-----------------------------------\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    const int populationSize = 100;
    std::vector<Person> people;

    // Create 100 people with random positions and 10% infected
    for (int i = 0; i < populationSize; ++i) {
        int x = rand() % 201 - 100; // Random x in [-100, 100]
        int y = rand() % 201 - 100; // Random y in [-100, 100]
        bool isInfected = (rand() % 10 == 0); // 10% chance to be infected
        people.emplace_back(i, x, y, isInfected);
    }

    const int days = 10; // Simulate for n days
    for (int day = 1; day <= days; ++day) {
        simulateDay(people);
        printStatus(people, day);
    }

    // Count infected people at the end
    int infectedCount = 0;
    for (const auto& person : people) {
        if (person.isInfected) {
            infectedCount++;
        }
    }
    std::cout << "Total infected at the end of " << days << " days: " << infectedCount << "\n";

    return 0;
}
