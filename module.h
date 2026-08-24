#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include <optional>

struct Entry {
    std::string val;
    int pri;
};

class PriorityQueue {
    std::vector<Entry> h;
    std::string file;

    void load();
    void save();
    void up(int i);
    void down(int i);

public:
    PriorityQueue(const std::string& path = "pq_data.txt");

    void insert(const std::string& val, int pri);
    std::optional<Entry> extract_min();
    std::optional<Entry> extract_max();
    std::optional<Entry> peek();
    bool update(const std::string& val, int newPri);
    bool remove(const std::string& val); // 'delete' is a C++ keyword
    bool is_empty();
};

#endif
