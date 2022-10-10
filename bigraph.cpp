#include <string>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <unordered_set>
#include <map>
#include <set>
#include <cstdlib>
#include <fstream>
#include <queue>
#include "utility.h"
#include "bigraph.h"
using namespace std;

static int attr_num = 0;


BiGraph::BiGraph(string dir, int option)
{
	num_v1 = 0;
	num_v2 = 0;
	num_edges = 0;

	neighbor_v1.clear();
	neighbor_v2.clear();

	attribute_v1.clear();
	attribute_v2.clear();

	degree_v1.clear();
	degree_v2.clear();

	core_v1.clear();
	core_v2.clear();

	//KKCore index left (x,*) right (*,x)
	left_index.clear();
	right_index.clear();
	v1_max_degree = 0;
	v2_max_degree = 0;
	v1_max_attr = 0;
	v2_max_attr = 0;
	this->dir = dir;
	if (option == 0) {
		loadGraph(dir);
	}
	else if (option == 1) {
		loadGraphNoAttr(dir);
	}
	else {
		loadGraphAttr(dir);
	}
}

BiGraph::BiGraph(string dir, string edge_dir, string attr_dir) {
	num_v1 = 0;
	num_v2 = 0;
	num_edges = 0;

	neighbor_v1.clear();
	neighbor_v2.clear();

	attribute_v1.clear();
	attribute_v2.clear();

	degree_v1.clear();
	degree_v2.clear();

	core_v1.clear();
	core_v2.clear();

	//KKCore index left (x,*) right (*,x)
	left_index.clear();
	right_index.clear();
	v1_max_degree = 0;
	v2_max_degree = 0;
	v1_max_attr = 0;
	v2_max_attr = 0;
	this->dir = dir;
	loadGraph(dir, edge_dir, attr_dir);
}

BiGraph::BiGraph() {
	dir = "";
	num_v1 = 0;
	num_v2 = 0;
	num_edges = 0;

	neighbor_v1.clear();
	neighbor_v2.clear();

	attribute_v1.clear();
	attribute_v2.clear();


	degree_v1.clear();
	degree_v2.clear();

	core_v1.clear();
	core_v2.clear();

	//KKCore index left (x,*) right (*,x)
	left_index.clear();
	right_index.clear();
	v1_max_degree = 0;
	v2_max_degree = 0;
	v1_max_attr = 0;
	v2_max_attr = 0;
}

void BiGraph::connectedGraph(int q) {
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
	for (int u = 0; u < num_v1; u++) {
		if (!connectu[u]) deleteVertex(1, u);
	}
	for (int v = 0; v < num_v2; v++) {
		if (!connectv[v]) deleteVertex(0, v);
	}
}


void BiGraph::print()
{
	string bigraphE = dir + "graph.e";
	string bigraphMeta = dir + "graph.meta";

	FILE* graphEF = fopen(bigraphE.c_str(), "w");
	FILE* graphMetaF = fopen(bigraphMeta.c_str(), "w");

	fprintf(graphMetaF, "%d\n%d\n%d\n", num_v1, num_v2, num_edges);
	fclose(graphMetaF);
	for (int i = 0; i < num_v1; ++i)
	{
		for (int j = 0; j < neighbor_v1[i].size(); ++j)
		{
			fprintf(graphEF, "%d %d\n", i, neighbor_v1[i][j]);
		}
	}
	fclose(graphEF);
}

void BiGraph::print(bool hash) {
	string bigraphE = dir + "graph.e";
	string bigraphMeta = dir + "graph.meta";

	FILE* graphEF = fopen(bigraphE.c_str(), "w");
	FILE* graphMetaF = fopen(bigraphMeta.c_str(), "w");

	fprintf(graphMetaF, "%d\n%d\n%d\n", neighborHash_v1.size(), neighborHash_v2.size(), num_edges);
	fclose(graphMetaF);
	for (int i = 0; i < neighborHash_v1.size(); ++i)
	{
		for (auto j = neighborHash_v1[i].begin(); j != neighborHash_v1[i].end(); ++j)
		{
			fprintf(graphEF, "%d %d\n", i, *j);
		}
	}
	fclose(graphEF);
}

void BiGraph::printCout()
{
	cout << "\nBiGraph: " << endl;
	for (int i = 0; i < num_v1; ++i)
	{
		cout << i << ": ";
		if (neighbor_v1[i].size() == 0)
		{
			cout << "compress error" << endl;
			exit(1);
		}
		for (int j = 0; j < neighbor_v1[i].size(); ++j)
		{
			cout << neighbor_v1[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;

}

void BiGraph::printSum()
{
	cout << "\nBiGraph Sum: " << endl;
	cout << "num_v1: " << num_v1 << endl;
	cout << "num_v2: " << num_v2 << endl;
	cout << "edge: " << num_edges << endl;

}
void BiGraph::printGraph() {
	cout << "u: " << endl;
	for (int u = 0; u < num_v1; u++) {
		if (neighbor_v1[u].size() != 0) {
			cout << u << ": ";
			for (int attr : attribute_v1[u]) cout << num2key[attr] << " ";
			cout << endl;
		}
		
	}
	cout << "v: " << endl;
	for (int v = 0; v < num_v2; v++) {
		if (neighbor_v2[v].size() != 0) {
			cout << v << ": ";
			for (int attr : attribute_v2[v]) cout << num2key[attr] << " ";
			cout << endl;
		}
	}
	for (int u = 0; u < num_v1; u++) {
		if (neighbor_v1[u].size() == 0) continue;
		cout << u << "的邻居: ";
		for (int v : neighbor_v1[u]) cout << v << " ";
		cout << endl;
	}
}

void BiGraph::init(unsigned int num1, unsigned int num2)
{
	num_v1 = num1;
	num_v2 = num2;
	num_edges = 0;

	neighbor_v1.resize(num_v1);
	neighbor_v2.resize(num_v2);

	attribute_v1.resize(num_v1);
	attribute_v2.resize(num_v2);

	degree_v1.resize(num_v1);
	degree_v2.resize(num_v2);

	fill_n(degree_v1.begin(), num_v1, 0);
	fill_n(degree_v2.begin(), num_v2, 0);

	left_delete.resize(num_v1);
	right_delete.resize(num_v2);
}

void BiGraph::loadGraph(string dir)
{
	unsigned int n1, n2;
	unsigned int edges = 0;
	int u, v, is_u;
	char chs[100];
	int r;

	string metaFile = dir + "graph.meta";
	string edgeFile = dir + "graph.e";
	string attrFile = dir + "graph.attr";

	FILE* metaGraph = fopen(metaFile.c_str(), "r");
	FILE* edgeGraph = fopen(edgeFile.c_str(), "r");
	FILE* attrGraph = fopen(attrFile.c_str(), "r");

	if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2)
	{
		fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
		exit(1);
	}

	fprintf(stdout, "n1: %d, n2: %d\n", n1, n2);

	init(n1, n2);

	while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
	{
		//fprintf(stderr, "%d, %d\n", u, v);
		if (r != 2)
		{
			fprintf(stderr, "Bad file format: u v incorrect\n");
			exit(1);
		}

		addEdge(u, v);
		//num_edges++;
	}
	while ((r = fscanf(attrGraph, "%d %d %s", &is_u, &u, chs)) != EOF)
	{
		if (r != 3)
		{
			fprintf(stderr, "Bad file format: u s incorrect\n");
			exit(1);
		}
		string s(chs);
		addAttr(is_u, u, s);
	}

	fclose(metaGraph);
	fclose(edgeGraph);
	fclose(attrGraph);

	for (int i = 0; i < num_v1; ++i)
	{
		neighbor_v1[i].shrink_to_fit();
		sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
		attribute_v1[i].shrink_to_fit();
		sort(attribute_v1[i].begin(), attribute_v1[i].end());

	}
	for (int i = 0; i < num_v2; ++i)
	{
		neighbor_v2[i].shrink_to_fit();
		sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
		attribute_v2[i].shrink_to_fit();
		sort(attribute_v2[i].begin(), attribute_v2[i].end());
	}
}
void BiGraph::loadGraph(string dir, string edge_dir, string attr_dir) {
	unsigned int n1, n2;
	unsigned int edges = 0;
	int u, v, is_u;
	char chs[100];
	int r;

	string metaFile = dir + "graph.meta";
	string edgeFile = edge_dir;
	string attrFile = attr_dir;

	FILE* metaGraph = fopen(metaFile.c_str(), "r");
	FILE* edgeGraph = fopen(edgeFile.c_str(), "r");
	FILE* attrGraph = fopen(attrFile.c_str(), "r");

	if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2)
	{
		fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
		exit(1);
	}

	fprintf(stdout, "n1: %d, n2: %d\n", n1, n2);

	init(n1, n2);

	while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
	{
		if (r != 2)
		{
			fprintf(stderr, "Bad file format: u v incorrect\n");
			exit(1);
		}

		addEdge(u - 1, v - 1);
	}
	while ((r = fscanf(attrGraph, "%d %d %s", &is_u, &u, chs)) != EOF)
	{
		if (r != 3)
		{
			fprintf(stderr, "Bad file format: u s incorrect\n");
			exit(1);
		}
		string s(chs);
		addAttr(is_u, u, s);
	}

	fclose(metaGraph);
	fclose(edgeGraph);
	fclose(attrGraph);

	for (int i = 0; i < num_v1; ++i)
	{
		neighbor_v1[i].shrink_to_fit();
		sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
		attribute_v1[i].shrink_to_fit();
		sort(attribute_v1[i].begin(), attribute_v1[i].end());

	}
	for (int i = 0; i < num_v2; ++i)
	{
		neighbor_v2[i].shrink_to_fit();
		sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
		attribute_v2[i].shrink_to_fit();
		sort(attribute_v2[i].begin(), attribute_v2[i].end());
	}
}
void BiGraph::loadGraphAttr(string dir)
{
	unsigned int n1, n2;
	unsigned int edges = 0;
	int u, v, is_u;
	char chs[100];
	int r;

	string metaFile = dir + "graph.meta";
	string edgeFile = dir + "graph.e";
	string attrFile = dir + "graph.attr";

	FILE* metaGraph = fopen(metaFile.c_str(), "r");
	FILE* edgeGraph = fopen(edgeFile.c_str(), "r");
	FILE* attrGraph = fopen(attrFile.c_str(), "r");

	if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2)
	{
		fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
		exit(1);
	}

	fprintf(stdout, "n1: %d, n2: %d\n", n1, n2);

	init(n1, n2);

	while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
	{
		if (r != 2)
		{
			fprintf(stderr, "Bad file format: u v incorrect\n");
			exit(1);
		}

		addEdge(u-1, v-1);
	}
	while ((r = fscanf(attrGraph, "%d %d %s", &is_u, &u, chs)) != EOF)
	{
		if (r != 3)
		{
			fprintf(stderr, "Bad file format: u s incorrect\n");
			exit(1);
		}
		string s(chs);
		addAttr(is_u, u, s);
	}

	fclose(metaGraph);
	fclose(edgeGraph);
	fclose(attrGraph);

	for (int i = 0; i < num_v1; ++i)
	{
		neighbor_v1[i].shrink_to_fit();
		sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
		attribute_v1[i].shrink_to_fit();
		sort(attribute_v1[i].begin(), attribute_v1[i].end());

	}
	for (int i = 0; i < num_v2; ++i)
	{
		neighbor_v2[i].shrink_to_fit();
		sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
		attribute_v2[i].shrink_to_fit();
		sort(attribute_v2[i].begin(), attribute_v2[i].end());
	}
}

void BiGraph::loadGraphNoAttr(string dir)
{
	unsigned int n1, n2;
	unsigned int edges = 0;
	int u, v, is_u;
	int r;

	string metaFile = dir + "graph.meta";
	string edgeFile = dir + "graph.e";

	FILE* metaGraph = fopen(metaFile.c_str(), "r");
	FILE* edgeGraph = fopen(edgeFile.c_str(), "r");

	if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2)
	{
		fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
		exit(1);
	}

	fprintf(stdout, "n1: %d, n2: %d\n", n1, n2);

	init(n1, n2);

	while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
	{
		//fprintf(stderr, "%d, %d\n", u, v);
		if (r != 2)
		{
			fprintf(stderr, "Bad file format: u v incorrect\n");
			exit(1);
		}

		addEdge(u-1, v-1);
		//num_edges++;
	}

	fclose(metaGraph);
	fclose(edgeGraph);

	assignAttrs(dir);

	for (int i = 0; i < num_v1; ++i)
	{
		neighbor_v1[i].shrink_to_fit();
		sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
		attribute_v1[i].shrink_to_fit();
		sort(attribute_v1[i].begin(), attribute_v1[i].end());

	}
	for (int i = 0; i < num_v2; ++i)
	{
		neighbor_v2[i].shrink_to_fit();
		sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
		attribute_v2[i].shrink_to_fit();
		sort(attribute_v2[i].begin(), attribute_v2[i].end());
	}
	writeAttrToFile(dir);
}

void BiGraph::writeAttrToFile(string dir) {
	string attrFile = dir + "graph.attr";
	ofstream ofile;               //定义输出文件
	ofile.open(attrFile);     //作为输出文件打开
	//ofile << setw(6) << i << setw(10) << j << setw(10) << k << endl;
	for (int i = 0; i < num_v1; i++) {
		for (int j : attribute_v1[i]) {
			ofile << 0 <<" " << i << " " << num2key[j] << endl;
		}
	}
	for (int i = 0; i < num_v2; i++) {
		for (int j : attribute_v2[i]) {
			ofile << 1 << " " << i << " " << num2key[j] << endl;
		}
	}
	ofile.close();
}

void BiGraph::assignAttrs(string dir) {
	vector<vid_t> attr1, attr2;
	char chs[100];
	int r;
	string attrFile1 = dir + "graph_v1.attr";
	string attrFile2 = dir + "graph_v2.attr";
	FILE* attrGraph1 = fopen(attrFile1.c_str(), "r");
	FILE* attrGraph2 = fopen(attrFile2.c_str(), "r");
	while ((r = fscanf(attrGraph1, "%s", chs)) != EOF)
	{
		if (r != 1)
		{
			fprintf(stderr, "Bad file format: u s incorrect\n");
			exit(1);
		}
		string s(chs);
		if (key2num.find(s) == key2num.end()) {
			key2num[s] = attr_num;
			num2key[attr_num] = s;
			attr_num++;
		}
		attr1.push_back(key2num[s]);
	}
	while ((r = fscanf(attrGraph2, "%s", chs)) != EOF)
	{
		if (r != 1)
		{
			fprintf(stderr, "Bad file format: u s incorrect\n");
			exit(1);
		}
		string s(chs);
		if (key2num.find(s) == key2num.end()) {
			key2num[s] = attr_num;
			num2key[attr_num] = s;
			attr_num++;
		}
		attr2.push_back(key2num[s]);
	}
	srand(time(0));
	for (int i = 0; i < num_v1; i++) {
		int attr_num = rand() % 5 + 8;
		while (attr_num) {
			int m = attr1[rand() % attr1.size()];
			if (find(attribute_v1[i].begin(), attribute_v1[i].end(), m) == attribute_v1[i].end()) {
				attribute_v1[i].push_back(m);
				attr_num--;
			}
			else {
				continue;
			}
		}
		//cout << "属性个数：" << i << " " << attribute_v1[i].size() << endl;
	}
	for (int i = 0; i < num_v2; i++) {
		int attr_num = rand() % 5 + 1;
		while (attr_num) {
			int m = attr2[rand() % attr2.size()];
			if (find(attribute_v2[i].begin(), attribute_v2[i].end(), m) == attribute_v2[i].end()) {
				attribute_v2[i].push_back(m);
				attr_num--;
			}
			else {
				continue;
			}
		}
		//cout << "属性个数：" << i << " " << attribute_v2[i].size() << endl;
	}
	fclose(attrGraph1);
	fclose(attrGraph2);
}

void BiGraph::addEdge(vid_t u, vid_t v)
{
	neighbor_v1[u].push_back(v);
	++degree_v1[u];
	if (degree_v1[u] > v1_max_degree) v1_max_degree = degree_v1[u];
	neighbor_v2[v].push_back(u);
	++degree_v2[v];
	if (degree_v2[v] > v2_max_degree) v2_max_degree = degree_v2[v];
	num_edges++;
}

void BiGraph::addAttr(int is_u, vid_t u, string s)
{
	if (key2num.find(s) == key2num.end()) {
		key2num[s] = attr_num;
		num2key[attr_num] = s;
		attr_num++;
	}
	if (is_u == 0) {
		attribute_v1[u].push_back(key2num[s]);
		if (attribute_v1[u].size() > v1_max_attr) v1_max_attr = attribute_v1[u].size();
	}
	else {
		attribute_v2[u].push_back(key2num[s]);
		if (attribute_v2[u].size() > v2_max_attr) v2_max_attr = attribute_v2[u].size();
	}
}

// not change max_degree
void BiGraph::deleteEdge(vid_t u, vid_t v)
{
	for (int i = 0; i < degree_v1[u]; ++i)
	{
		int vv = neighbor_v1[u][i];
		if (vv == v)
		{
			swap(neighbor_v1[u][i], neighbor_v1[u][degree_v1[u] - 1]);
			--degree_v1[u];
			neighbor_v1[u].pop_back();
			break;
		}
	}

	for (int i = 0; i < degree_v2[v]; ++i)
	{
		int uu = neighbor_v2[v][i];
		if (uu == u)
		{
			swap(neighbor_v2[v][i], neighbor_v2[v][degree_v2[v] - 1]);
			--degree_v2[v];
			neighbor_v2[v].pop_back();
			break;
		}
	}

}

void BiGraph::deleteAttr(int is_u, vid_t u, string s)
{
}

void BiGraph::deleteVertex(int is_u, vid_t u) {
	if (is_u) {
		for (int v : neighbor_v1[u]) {
			erase(neighbor_v2[v], u);
		}
		neighbor_v1[u].clear();
	}
	else {
		for (int v : neighbor_v2[u]) {
			erase(neighbor_v1[v], u);
		}
		neighbor_v2[u].clear();
	}
}


bool BiGraph::isEdge(vid_t u, vid_t v)
{
	/*if (binary_search(neighbor_v1[u].begin(),
		neighbor_v1[u].begin() + degree_v1[u], v))
		return true;
	else
		return false;*/
		/*if (neighborHash_v1[u].find(v) == neighborHash_v1[u].end())
		{
		return false;
		}
		else
		return true;*/
	for (auto it = neighbor_v1[u].begin(); it != neighbor_v1[u].end(); it++) {
		if (*it == v) return true;
	}
	return false;
}

void BiGraph::compressGraph()
{
	vector<unordered_set<vid_t>> n_neighborHash_v1;
	vector<unordered_set<vid_t>> n_neighborHash_v2;

	n_neighborHash_v1.resize(num_v1);
	n_neighborHash_v2.resize(num_v2);

	for (int i = 0; i < num_v1; ++i)
	{
		n_neighborHash_v1[i].reserve(10 * neighbor_v1[i].size());
		for (int j = 0; j < neighbor_v1[i].size(); ++j)
		{
			int v = neighbor_v1[i][j];
			n_neighborHash_v1[i].insert(v);
		}
	}

	for (int i = 0; i < num_v2; ++i)
	{
		n_neighborHash_v2[i].reserve(2 * neighbor_v2[i].size());
		for (int j = 0; j < neighbor_v2[i].size(); ++j)
		{
			int v = neighbor_v2[i][j];
			n_neighborHash_v2[i].insert(v);
		}
	}

	swap(n_neighborHash_v1, neighborHash_v1);
	swap(n_neighborHash_v2, neighborHash_v2);

	for (int i = 0; i < num_v1; ++i)
	{
		if (neighbor_v1[i].size() != degree_v1[i])
			cout << "degree error" << endl;
	}

	for (int i = 0; i < num_v2; ++i)
	{
		if (neighbor_v2[i].size() != degree_v2[i])
			cout << "degree error" << endl;
	}

	cout << "degree correct" << endl;

}