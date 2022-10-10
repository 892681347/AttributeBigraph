#pragma once
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
using namespace std;

//#include <stdint.h> //needed to use uint64_t

//typedef unsigned short vid_t;
typedef unsigned int vid_t;
typedef int num_t;



#define MIN(a, b) (a <= b ? a : b)
#define MAX(a, b) (a >= b ? a : b)

bool vectorCompare(vector<int> v1, vector<int> v2);
vector<vid_t>::iterator erase(vector<vid_t>& v, int value);

struct setCmp {
	bool operator()(const set<vid_t>& s1, const set<vid_t>& s2) const {
		if (s1.size() != s2.size()) return s1.size() > s2.size();
		return s1 < s2;
	}
};
