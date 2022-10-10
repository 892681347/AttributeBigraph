#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include "utility.h"

struct AttrsPair {
	set<vid_t> attrs1, attrs2;
	vid_t p1=0, p2=0;
	size_t size;
	AttrsPair(set<vid_t> attrs1, set<vid_t> attrs2) {
		this->attrs1 = attrs1;
		this->attrs2 = attrs2;
		size = attrs1.size() + attrs2.size();
	}
	AttrsPair(vid_t attr1, vid_t attr2) {
		attrs1.insert(attr1);
		attrs2.insert(attr2);
		size = 2;
	}
	void print() {
		cout << "u关键字: ";
		for (vid_t n : attrs1) cout << n << " ";
		cout << endl;
		cout << "v关键字: ";
		for (vid_t n : attrs2) cout << n << " ";
		cout << endl;
		cout << "关键字大小: " << size << endl;
	}
	AttrsPair merge(AttrsPair& other) {
		AttrsPair attrPair(other);
		for (vid_t attr : attrs1) {
			attrPair.attrs1.insert(attr);
		}
		for (vid_t attr : attrs2) {
			attrPair.attrs2.insert(attr);
		}
		attrPair.size = attrPair.attrs1.size() + attrPair.attrs2.size();
		return attrPair;
	}
	void print(map<vid_t,string>& m) {
		cout << "u关键字: ";
		for (vid_t n : attrs1) cout << m[n] << " ";
		cout << endl;
		cout << "v关键字: ";
		for (vid_t n : attrs2) cout << m[n] << " ";
		cout << endl;
		cout << "关键字大小: " << size << endl;
	}
	bool operator < (const AttrsPair& other)  const {
		if (size != other.size) return size > other.size;
		if (attrs1 < other.attrs1) return true;
		if (attrs1 == other.attrs1 && attrs2 < other.attrs2) return true;
		return false;
	}
};
struct AttrsId {
	int num, index1, index2;
	AttrsId(int num, int index1, int index2) {
		this->num = num;
		this->index1 = index1;
		this->index2 = index2;
	}
	bool operator < (const AttrsId& other)  const {
		return num > other.num;
	}
	void print() {
		cout << num << " " << index1 << " " << index2 << endl;
	}
};
//class SubGraph {
//	vector<vid_t> v1, v2;
//	map<vid_t, vector<vid_t>> neighbor_v1, neighbor_v2;
//	SubGraph(vector<vid_t> v1, vector<vid_t> v2, BiGraph& g);
//	void deleteVertex(int is_u, vid_t u);
//	bool exist(int k1, int k2);
//};

struct SubGraph {
	vector<vid_t> v1, v2;
	//int edge_num, v_num;
	map<vid_t, vector<vid_t>> neighbor_v1, neighbor_v2;
	SubGraph(long long n1, long long n2, vector<vid_t>& v1, vector<vid_t>& v2, vector<vector<vid_t>>& gneighbor_v1, vector<vector<vid_t>>& gneighbor_v2) {
		/*this->v1.resize(v1.size());
		this->v2.resize(v2.size());
		copy(v1.begin(), v1.end(), this->v1.begin());
		copy(v2.begin(), v2.end(), this->v2.begin());*/
		this->v1 = v1;
		this->v2 = v2;
		if (v1.size() * n2 <= v2.size() * n1) {
			map<vid_t, bool> show2;
			for (vid_t i : v2) show2[i] = true;
			for (vid_t i : v1) {
				for (vid_t k : gneighbor_v1[i]) {
					if (show2[k]) {
						neighbor_v1[i].push_back(k);
						neighbor_v2[k].push_back(i);
					}
				}
			}
		}
		else {
			map<vid_t, bool> show1;
			for (vid_t i : v1) show1[i] = true;
			for (vid_t i : v2) {
				for (vid_t k : gneighbor_v2[i]) {
					if (show1[k]) {
						neighbor_v2[i].push_back(k);
						neighbor_v1[k].push_back(i);
					}
				}
			}
		}
		
	}
	void connectedGraph(int q) {
		map<int, bool> connectu, connectv;
		queue<int> que;
		bool is_u = true;
		connectu[q] = true;
		que.push(q);
		que.push(-1);
		while (!que.empty()) {
			int t = que.front();
			que.pop();
			if (t == -1) {
				if (!que.empty()) {
					is_u = !is_u;
					que.push(-1);
				}
			}
			else if (is_u) {
				for (int k : neighbor_v1[t]) {
					if (!connectv[k]) {
						connectv[k] = true;
						que.push(k);
					}
				}
			}
			else {
				for (int k : neighbor_v2[t]) {
					if (!connectu[k]) {
						connectu[k] = true;
						que.push(k);
					}
				}
			}
		}
		for (vector<vid_t>::iterator it = v1.begin(); it != v1.end();) {
			if (!connectu[*it]) {
				it = deleteVertex(1, *it);
			}
			else {
				it++;
			}
		}
		for (vector<vid_t>::iterator it = v2.begin(); it != v2.end();) {
			if (!connectv[*it]) {
				it = deleteVertex(0, *it);
			}
			else {
				it++;
			}
		}
	}
	vector<vid_t>::iterator deleteVertex(int is_u, vid_t u) {
		if (is_u) {
			for (int i : neighbor_v1[u]) {
				erase(neighbor_v2[i], u);
			}
			neighbor_v1[u].clear();
			return erase(v1, u);
		}
		else {
			for (int i : neighbor_v2[u]) {
				erase(neighbor_v1[i], u);
			}
			neighbor_v2[u].clear();
			return erase(v2, u);
		}
	}
	SubGraph merge(SubGraph& other) {
		SubGraph subGraph(other);
		map<vid_t, bool> mapv1, mapv2;
		for (vid_t i : v1) mapv1[i] = true;
		for (vid_t i : v2) mapv2[i] = true;
		for (vector<vid_t>::iterator it = subGraph.v1.begin(); it != subGraph.v1.end();) {
			if (!mapv1[*it]) {
				it = subGraph.deleteVertex(1, *it);
			}
			else {
				it++;
			}
		}
		for (vector<vid_t>::iterator it = subGraph.v2.begin(); it != subGraph.v2.end();) {
			if (!mapv2[*it]) {
				it = subGraph.deleteVertex(0, *it);
			}
			else {
				it++;
			}
		}
		return subGraph;
	}
	bool exist_basic(vid_t q, int k1, int k2) {
		bool flag = true;
		while (flag) {
			flag = false;
			for (vector<vid_t>::iterator it = v1.begin(); it != v1.end();) {
				if (neighbor_v1[*it].size() < k1) {
					flag = true;
					it = deleteVertex(1, *it);
				}
				else {
					it++;
				}
			}
			for (vector<vid_t>::iterator it = v2.begin(); it != v2.end();) {
				if (neighbor_v2[*it].size() < k2) {
					flag = true;
					it = deleteVertex(0, *it);
				}
				else {
					it++;
				}
			}
			if (neighbor_v1[q].size() == 0) return false;
		}
		if (v1.size() == 0 || neighbor_v1[q].size()==0) return false;
		return true;
	}
	bool exist(vid_t q, int k1, int k2) {
		/*bool flag = true;
		if (edge_num - v_num < k1 * k2 - k1 - k2) {
			cout << "use lemmea" << endl;
			flag = false;
		}*/
		//connectedGraph(q);
		for (vector<vid_t>::iterator it1 = v1.begin(); it1 != v1.end();) {
			if (neighbor_v1[*it1].size() < k1) {
				it1 = deleteVertex(1, *it1);
			}
			else {
				it1++;
			}
		}
		vid_t minDegV;
		while (v1.size() != 0 && neighbor_v1[q].size() != 0) {
			minDegV = 0xffffffff;
			for (vid_t i : v2) {
				if (neighbor_v2[i].size() < minDegV) minDegV = neighbor_v2[i].size();
			}
			if (minDegV >= k2) {
				//if (!flag) cout << "Error " << edge_num << " " << v_num << endl;
				//connectedGraph(q);
				return true;
			}
			for (vector<vid_t>::iterator it2 = v2.begin(); it2 != v2.end();) {
				if (neighbor_v2[*it2].size() < k2) {
					//it2 = deleteVertex(0, *it2);
					for (int i : neighbor_v2[*it2]) {
						erase(neighbor_v1[i], *it2);
						if (neighbor_v1[i].size() < k1) {
							if (i == q) return false;
							deleteVertex(1, i);
						}
					}
					neighbor_v2[*it2].clear();
					it2 = v2.erase(it2);
				}
				else {
					it2++;
				}
			}
		}
		return false;
	}
	void print() {
		cout << "节点：{";
		for (int n : v1) cout << n << " ";
		cout << ",";
		for (int n : v2) cout << " " << n;
		cout << "}" << endl;;
	}
	void printDetail() {
		cout << "U:" << endl;
		for (int n : v1) {
			cout << n << " 连接：";
			for (int m : neighbor_v1[n]) cout << m << " ";
			cout << endl;
		}
		cout << "V: " << endl;
		for (int n : v2) {
			cout << n << " 连接：";
			for (int m : neighbor_v2[n]) cout << m << " ";
			cout << endl;
		}
	}
};
class BiGraph
{

public:

	BiGraph(std::string dir, int option);
	BiGraph(std::string dir, std::string edge_dir, std::string attr_dir);
	BiGraph();
	~BiGraph() {}

	void connectedGraph(int q);
	void addEdge(vid_t u, vid_t v);
	void addAttr(int is_u, vid_t u, std::string s);
	void deleteEdge(vid_t u, vid_t v);
	void deleteAttr(int is_u, vid_t u, std::string s);
	void deleteVertex(int is_u, vid_t u);
	bool isEdge(vid_t u, vid_t v);
	num_t getV1Num() { return num_v1; }
	num_t getV2Num() { return num_v2; }
	num_t getV1Degree(vid_t u) { return degree_v1[u]; }
	num_t getV2Degree(vid_t u) { return degree_v2[u]; }
	std::vector<vid_t>& getV2Neighbors(vid_t u) { return neighbor_v2[u]; }
	std::vector<vid_t>& getV1Neighbors(vid_t u) { return neighbor_v1[u]; }
	void print();
	void print(bool hash);
	void printSum();
	void printCout();
	void printGraph();

public:

	void init(unsigned int num_v1, unsigned int num_v2);
	void loadGraph(std::string dir);
	void loadGraph(std::string dir, std::string edge_dir, std::string attr_dir);
	void loadGraphAttr(std::string dir);
	void loadGraphNoAttr(std::string dir);
	void writeAttrToFile(std::string dir);
	void assignAttrs(std::string dir);
	void compressGraph();

	static BiGraph NullBigraph();

	std::string dir;
	num_t num_v1;
	num_t num_v2;
	num_t num_edges;

	std::vector<std::vector<vid_t>> neighbor_v1;
	std::vector<std::vector<vid_t>> neighbor_v2;

	std::vector<std::vector<vid_t>> attribute_v1;
	std::vector<std::vector<vid_t>> attribute_v2;

	std::vector<std::unordered_set<vid_t>> neighborHash_v1;
	std::vector<std::unordered_set<vid_t>> neighborHash_v2;

	std::vector<int> degree_v1;
	std::vector<int> degree_v2;

	std::vector<num_t> core_v1;
	std::vector<num_t> core_v2;

	map<string, vid_t> key2num;
	map<vid_t, string> num2key;

public:

	//KKCore index left (x,*) right (*,x)
	std::vector<std::vector<int>> left_index;
	std::vector<std::vector<int>> right_index;
	int v1_max_degree;
	int v2_max_degree;
	int v1_max_attr;
	int v2_max_attr;
	std::vector<bool> left_delete;
	std::vector<bool> right_delete;
	// for dynamic update
	std::vector<std::vector<int>> left_index_old;
	std::vector<std::vector<int>> right_index_old;
	//BiGraph operator=(const BiGraph& g);
};

