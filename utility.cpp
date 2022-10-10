#include <string>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_set>
#include <map>
#include <set>
#include <cstdlib>
#include "utility.h"
using namespace std;

bool vectorCompare(vector<int> v1, vector<int> v2) {
	map<int, bool> show;
	for (int n : v1) show[n] = true;
	for (int n : v2) if (!show[n]) return false;
	show.clear();
	for (int n : v2) show[n] = true;
	for (int n : v1) if (!show[n]) return false;
	return true;
}
vector<vid_t>::iterator erase(vector<vid_t>& v, int value) {
	auto it = find(v.begin(), v.end(), value);
	return v.erase(it);
}