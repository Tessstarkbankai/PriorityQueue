#include "module.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

PriorityQueue::PriorityQueue(const string& path) : file(path) {}

//  persist

void PriorityQueue::load() {
    h.clear();
    ifstream f(file);
    if (!f) return;
    int pri;
    string val;
    while (f >> pri && getline(f >> ws, val)) {
        h.push_back({val, pri});
    }
}

void PriorityQueue::save() {
    ofstream f(file);
    for (auto& e : h)
        f << e.pri << " " << e.val << "\n";
}

// min heap

void PriorityQueue::up(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[p].pri <= h[i].pri) break;
        swap(h[i], h[p]);
        i = p;
    }
}

void PriorityQueue::down(int i) {
    int n = h.size();
    while (true) {
        int s = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && h[l].pri < h[s].pri) s = l;
        if (r < n && h[r].pri < h[s].pri) s = r;
        if (s == i) break;
        swap(h[i], h[s]);
        i = s;
    }
}

// apii

void PriorityQueue::insert(const string& val, int pri) {
    load();
    h.push_back({val, pri});
    up(h.size() - 1);
    save();
}

optional<Entry> PriorityQueue::extract_min() {
    load();
    if (h.empty()) return nullopt;
    Entry min = h[0];
    h[0] = h.back();
    h.pop_back();
    if (!h.empty()) down(0);
    save();
    return min;
}

optional<Entry> PriorityQueue::extract_max() {
    load();
    if (h.empty()) return nullopt;
    int idx = 0;
    for (int i = 1; i < (int)h.size(); i++)
        if (h[i].pri > h[idx].pri) idx = i;
    Entry mx = h[idx];
    h[idx] = h.back();
    h.pop_back();
    if (idx < (int)h.size()) {
        up(idx);
        down(idx);
    }
    save();
    return mx;
}

optional<Entry> PriorityQueue::peek() {
    load();
    if (h.empty()) return nullopt;
    return h[0];
}

bool PriorityQueue::update(const string& val, int newPri) {
    load();
    int idx = -1;
    for (int i = 0; i < (int)h.size(); i++)
        if (h[i].val == val) { idx = i; break; }
    if (idx == -1) return false;
    h[idx].pri = newPri;
    up(idx);
    down(idx);
    save();
    return true;
}

bool PriorityQueue::remove(const string& val) {
    load();
    int idx = -1;
    for (int i = 0; i < (int)h.size(); i++)
        if (h[i].val == val) { idx = i; break; }
    if (idx == -1) return false;
    h[idx] = h.back();
    h.pop_back();
    if (idx < (int)h.size()) {
        up(idx);
        down(idx);
    }
    save();
    return true;
}

bool PriorityQueue::is_empty() {
    load();
    return h.empty();
}
