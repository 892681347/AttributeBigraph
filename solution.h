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
#include "bigraph.h"
using namespace std;

vector<pair<AttrsPair, SubGraph>> query_basic(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1);
vector<pair<AttrsPair, SubGraph>> query_dec_test(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1);
vector<pair<AttrsPair, SubGraph>> query_inc(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1);
vector<pair<AttrsPair, SubGraph>> query_inc_exp(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1);
vector<pair<AttrsPair, SubGraph>> query_dec(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1);
vector<pair<AttrsPair, SubGraph>> query_dec_exp(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1);
BiGraph coreGraphExp(BiGraph& g, int k1, int k2);
