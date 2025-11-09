#ifndef EMPLOYEEGENERATOR_H
#define EMPLOYEEGENERATOR_H
#include <string>
#include <vector>
#include <random>

struct Employee {
    int id;
    std::string name;
    std::string position;
    int weight;
    int parentId;
};

class EmployeeGenerator {
public:
    std::vector<Employee> generate() {
        std::vector<std::string> names = {
            "Alice", "Bob", "Charlie", "Diana", "Ethan", "Fiona",
            "George", "Hannah", "Ivan", "Julia", "Kevin", "Laura",
            "Mike", "Nina", "Oscar", "Paula", "Quincy", "Rachel",
            "Sam", "Tina", "Uma", "Victor", "Wendy", "Xavier", "Yara", "Zane"
        };

        std::vector<Employee> employees;
        int idCounter = 1;

        // Owner
        employees.push_back({ idCounter++, "Owner Alpha", "Owner", 0, 0 });
        int ownerId = 1;

        // 5 CEOs
        std::vector<int> ceoIds;
        for (int i = 0; i < 5; ++i) {
            employees.push_back({ idCounter, names[i] + " CEO", "CEO", 1, ownerId });
            ceoIds.push_back(idCounter++);
        }

        // 10 Managers (2 per CEO)
        std::vector<int> managerIds;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 2; ++j) {
                employees.push_back({ idCounter, names[(i * 2 + j) % names.size()] + " Manager", "Manager", 2, ceoIds[i] });
                managerIds.push_back(idCounter++);
            }
        }

        // 50 Employees (5 per Manager)
        for (int i = 0; i < managerIds.size(); ++i) {
            for (int j = 0; j < 5; ++j) {
                employees.push_back({
                    idCounter,
                    names[(i * 5 + j) % names.size()] + " Employee",
                    "Employee",
                    3,
                    managerIds[i]
                    });
                idCounter++;
            }
        }

        return employees;
    }
};
#endif
#pragma once