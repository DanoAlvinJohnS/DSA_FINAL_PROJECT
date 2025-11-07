
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string name;
    int order_id;
    Node* next;

    Node(string name, int order_id)
        : name(move(name)), order_id(order_id), next(nullptr) {}
};

class SeatList {
private:
    Node* head;
    int count;
    const int max_seats = 16;

public:
    SeatList() : head(nullptr), count(0) {}

    void add_order(const string& name) {
        if (count >= max_seats) {
            cout << "[ERROR] | No more seats" << endl;
            return;
        }

        Node* new_node = new Node(name, count + 1);

        if (!head) {
            head = new_node;
        } else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = new_node;
        }

        count++;
        cout << "[ADDED] " << name << " → Seat #" << new_node->order_id << endl;
    }

    void take_out(int order_id) {
        Node* temp = head;
        Node* prev = nullptr;

        while (temp) {
            if (temp->order_id == order_id) {
                if (prev)
                    prev->next = temp->next;
                else
                    head = temp->next;

                cout << "[REMOVED] Seat #" << order_id << " (" << temp->name << ")" << endl;
                delete temp;
                count--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "[ERROR] | Order ID not found" << endl;
    }

    vector<pair<int, string>> to_list() const {
        vector<pair<int, string>> data;
        Node* temp = head;
        while (temp) {
            data.emplace_back(temp->order_id, temp->name);
            temp = temp->next;
        }
        return data;
    }

    ~SeatList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void display(const vector<pair<int, string>>& seat_data) {
    vector<vector<string>> seats(4, vector<string>(4, "Empty"));

    for (auto& [order_id, name] : seat_data) {
        int row = (order_id - 1) / 4;
        int col = (order_id - 1) % 4;
        seats[row][col] = name;
    }

    cout << endl;
    for (const auto& row : seats) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << setw(10) << left << row[i];
            if (i < row.size() - 1) cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    SeatList s;

    s.add_order("Alice");
    s.add_order("Bob");
    s.add_order("Charlie");
    s.add_order("Diana");
    s.add_order("Eve");
    display(s.to_list());

    s.take_out(3);
    display(s.to_list());

    for (int i = 0; i < 20; ++i)
        s.add_order("Order" + to_string(i + 6));

    display(s.to_list());

    return 0;
}
