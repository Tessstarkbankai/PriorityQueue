#include <iostream>
#include <cstdio>
#include "module.h"

using namespace std;

void print(const optional<Entry>& e) {
    if (e) cout << "{ " << e->val << ", " << e->pri << " }" << endl;
    else   cout << "null" << endl;
}

int main() {
    cout << "--- Persistent Priority Queue Demo ---\n" << endl;

    // start fresh
    remove("pq_data.txt");

    PriorityQueue pq;

    cout << "is_empty: " << pq.is_empty() << endl;

    pq.insert("taskA", 3);
    pq.insert("taskB", 1);
    pq.insert("taskC", 5);
    pq.insert("taskD", 2);
    pq.insert("taskE", 4);
    cout << "inserted 5 tasks with priorities 3,1,5,2,4" << endl;

    cout << "peek (min): ";   print(pq.peek());
    cout << "is_empty: " << pq.is_empty() << endl;

    cout << "extract_min: ";  print(pq.extract_min());
    cout << "extract_max: ";  print(pq.extract_max());

    pq.update("taskA", 0);
    cout << "updated taskA priority to 0" << endl;
    cout << "peek after update: ";  print(pq.peek());

    pq.remove("taskD");
    cout << "deleted taskD" << endl;
    //persis test
    cout << "\nextracting remaining:" << endl;
    while (!pq.is_empty()) {
        cout << "  ";
        print(pq.extract_min());
    }

    cout << "is_empty: " << pq.is_empty() << endl;
    cout << "\ndone" << endl;
    return 0;
}
