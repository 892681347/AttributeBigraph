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
#include <ctime>
#include "bigraph.h"
#include "utility.h"
using namespace std;

pair<AttrsPair, BiGraph> mergeGraph(pair<AttrsPair, BiGraph>& attrGraph1, pair<AttrsPair, BiGraph>& attrGraph2, int q, int k1, int k2) {
	BiGraph sg(attrGraph1.second);
	for (int u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0 && attrGraph2.second.neighbor_v1[u].size() == 0) {
			sg.deleteVertex(1, u);
		}
	}
	for (int v = 0; v < sg.num_v2; v++) {
		if (sg.neighbor_v2[v].size() != 0 && attrGraph2.second.neighbor_v2[v].size() == 0) {
			sg.deleteVertex(0, v);
		}
	}
	bool flag = true;
	while (flag) {
		flag = false;
		for (vid_t u = 0; u < sg.num_v1; u++) {
			if (sg.neighbor_v1[u].size() != 0 && sg.neighbor_v1[u].size() < k1) {
				sg.deleteVertex(1, u);
				flag = true;
			}
		}
		for (int v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() != 0 && sg.neighbor_v2[v].size() < k2) {
				sg.deleteVertex(0, v);
				flag = true;
			}
		}
		if (!flag) break;
	}
	bool empty = true;
	for (int u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0) {
			empty = false;
			break;
		}
	}
	if (empty || sg.neighbor_v1[q].size()==0) return {attrGraph1.first,BiGraph()};
	AttrsPair attrsPair(attrGraph1.first);
	for (int n : attrGraph2.first.attrs1) {
		attrsPair.attrs1.insert(n);
	}
	for (int n : attrGraph2.first.attrs2) {
		attrsPair.attrs2.insert(n);
	}
	attrsPair.size = attrsPair.attrs1.size() + attrsPair.attrs2.size();
	return { attrsPair,sg };
}
BiGraph getSubgraph(BiGraph& g, int q, int k1, int k2, AttrsPair& attrsPair ) {
	BiGraph sg(g);
	for (int u = 0; u < sg.num_v1; u++) {
		for (int attr : attrsPair.attrs1) {
			if (find(sg.attribute_v1[u].begin(), sg.attribute_v1[u].end(), attr) == sg.attribute_v1[u].end()) {
				sg.deleteVertex(1, u);
			}
		}
	}
	for (int v = 0; v < sg.num_v2; v++) {
		for (int attr : attrsPair.attrs2) {
			if (find(sg.attribute_v2[v].begin(), sg.attribute_v2[v].end(), attr) == sg.attribute_v2[v].end()) {
				sg.deleteVertex(0, v);
			}
		}
	}
	bool flag = true;
	while (flag) {
		flag = false;
		for (vid_t u = 0; u < sg.num_v1; u++) {
			if (sg.neighbor_v1[u].size() != 0 && sg.neighbor_v1[u].size() < k1) {
				sg.deleteVertex(1,u);
				flag = true;
			}
		}
		for (int v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() != 0 && sg.neighbor_v2[v].size() < k2) {
				sg.deleteVertex(0, v);
				flag = true;
			}
		}
		if (!flag) break;
	}
	bool empty = true;
	for (int u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0) {
			empty = false;
			break;
		}
	}
	if (empty || sg.neighbor_v1[q].size()==0) return BiGraph();
	else return sg;
}
void printSimple(pair<AttrsPair, BiGraph>& tg) {
	cout << "{ ";
	for (int attr : tg.first.attrs1) cout << tg.second.num2key[attr];
	cout << " , ";
	for (int attr : tg.first.attrs2) cout << tg.second.num2key[attr];
	cout << " } ����";
	cout << "{ ";
	for (int n = 0; n < tg.second.num_v1; n++) if (tg.second.neighbor_v1[n].size() != 0) cout << n;
	cout << " , ";
	for (int n = 0; n < tg.second.num_v2; n++) if (tg.second.neighbor_v2[n].size() != 0) cout << n;
	cout << " }" << endl;
}
void printSimple(pair<AttrsPair, SubGraph>& tg, map<vid_t, string>& num2key) {
	cout << "{ ";
	for (int attr : tg.first.attrs1) cout << num2key[attr];
	cout << " , ";
	for (int attr : tg.first.attrs2) cout << num2key[attr];
	cout << " } ����";
	cout << "{ ";
	for (vid_t n: tg.second.v1) cout << n;
	cout << " , ";
	for (vid_t n: tg.second.v2) cout << n;
	cout << " }" << tg.first.p1 << " " << tg.first.p2 << endl;
}
BiGraph coreGraph(BiGraph& g, int q, int k1, int k2) {
	BiGraph sg(g);
	bool flag = true;
	while (flag) {
		flag = false;
		for (vid_t u = 0; u < sg.num_v1; u++) {
			if (sg.neighbor_v1[u].size() != 0 && sg.neighbor_v1[u].size() < k1) {
				sg.deleteVertex(1, u);
				flag = true;
			}
		}
		for (int v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() != 0 && sg.neighbor_v2[v].size() < k2) {
				sg.deleteVertex(0, v);
				flag = true;
			}
		}
		if (!flag) break;
	}
	bool empty = true;
	for (int u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0) {
			empty = false;
			break;
		}
	}
	if (empty || sg.neighbor_v1[q].size() == 0) return BiGraph();
	else return sg;
}
BiGraph coreGraphExp(BiGraph& g, int k1, int k2) {
	BiGraph sg(g);
	bool flag = true;
	while (flag) {
		flag = false;
		for (vid_t u = 0; u < sg.num_v1; u++) {
			if (sg.neighbor_v1[u].size() != 0 && sg.neighbor_v1[u].size() < k1) {
				sg.deleteVertex(1, u);
				flag = true;
			}
		}
		for (int v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() != 0 && sg.neighbor_v2[v].size() < k2) {
				sg.deleteVertex(0, v);
				flag = true;
			}
		}
		if (!flag) break;
	}
	bool empty = true;
	for (int u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0) {
			empty = false;
			break;
		}
	}
	if (empty) return BiGraph();
	else return sg;
}
BiGraph coreGraphOnce(BiGraph& g, int q, int k1, int k2) {
	BiGraph sg(g);
	//sg.connectedGraph(q);
	for (vid_t u = 0; u < sg.num_v1; u++) {
		if (sg.neighbor_v1[u].size() != 0 && sg.neighbor_v1[u].size() < k1) {
			sg.deleteVertex(1, u);
		}
	}
	vid_t minDegV;
	while (sg.neighbor_v1[q].size() != 0) {
		minDegV = 0xffffffff;
		for (vid_t v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() == 0) continue;
			if(sg.neighbor_v2[v].size()<minDegV) minDegV = sg.neighbor_v2[v].size();
		}
		if (minDegV >= k2) {
			//sg.connectedGraph(q);
			return sg;
		}
		for (vid_t v = 0; v < sg.num_v2; v++) {
			if (sg.neighbor_v2[v].size() == 0) continue;
			if (sg.neighbor_v2[v].size() < k2) {
				for (int i : sg.neighbor_v2[v]) {
					erase(sg.neighbor_v1[i], v);
					if (sg.neighbor_v1[i].size() < k1) {
						if (i == q) return BiGraph();
						sg.deleteVertex(1, i);
					}
				}
				sg.neighbor_v2[v].clear();
			}
		}
	}
	return BiGraph();
}


vector<pair<AttrsPair, SubGraph>> query_inc(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1) {
	BiGraph sg = coreGraphOnce(g, u, k1, k2);
	int attr_size = 0;
	vector<pair<AttrsPair, SubGraph>> ans;
	if (sg.neighbor_v1[u].size() == 0) {
		cout << u << " not in coreGraph" << endl;
		return ans;
	}
	//����attrs2,��u�����ھӽڵ�Ĺؼ��ֵĲ���
	vector<vid_t> attrs2;
	map<vid_t, bool> show2;
	for (int neighbor : sg.neighbor_v1[u]) {
		if(sg.neighbor_v2[neighbor].size()==0) continue;
		for (vid_t attr : sg.attribute_v2[neighbor]) {
			if (!show2[attr]) {
				attrs2.push_back(attr);
				show2[attr] = true;
			}
		}
	}


	map<vid_t, vector<vid_t>> attrVertexs1, attrVertexs2;
	map<vid_t, bool> show1;
	for (vid_t t : attrs1) show1[t] = true;
	for (vid_t i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		for (vid_t n : sg.attribute_v1[i]) {
			if (show1[n]) attrVertexs1[n].push_back(i);
		}
	}
	for (vid_t i = 0; i < sg.num_v2; i++) {
		if (sg.neighbor_v2[i].size() == 0) continue;
		for (vid_t n : sg.attribute_v2[i]) {
			if (show2[n]) attrVertexs2[n].push_back(i);
		}
	}

	//int k = 0;
	//cout << "Round" << k << ":" << endl;
	//k++;
	vector<pair<AttrsPair, SubGraph>> attrGraphs1, attrGraphs2;
	for (vid_t attr1 : attrs1) {
		for (vid_t attr2 : attrs2) {
			SubGraph subGraph(sg.num_v1, sg.num_v2, attrVertexs1[attr1], attrVertexs2[attr2], sg.neighbor_v1, sg.neighbor_v2);
			if (subGraph.exist_basic(u, k1, k2)) {
				AttrsPair attrsPair = AttrsPair(attr1, attr2);
				pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
				attrGraphs1.push_back(tg);
				//printSimple(tg, sg.num2key);
				if (attrsPair.size > attr_size) {
					ans.clear();
					attr_size = attrsPair.size;
					ans.push_back({ attrsPair, subGraph });
				}
				else if (attrsPair.size == attr_size) {
					ans.push_back({ attrsPair, subGraph });
				}
			}
		}
	}
	//cout << "number:" << attrGraphs1.size() << endl;
	//cout << endl;

	//����attrGraphs�е���������������ؼ��ֽ�����ͼ�Ľ�������Ϊ�ռ�����ȡ�����������µ�attrGraphs��ֱ��û�п�������������Ԫ��
	map<AttrsPair, bool> attrShow;
	while (attrGraphs1.size() != 0 || attrGraphs2.size() != 0) {
		//cout << "Round" << k << ":" << endl;
		//k++;
		if (attrGraphs1.size() != 0) {
			for (int i = 0; i < attrGraphs1.size(); i++) {
				for (int j = i + 1; j < attrGraphs1.size(); j++) {
					SubGraph subGraph = attrGraphs1[i].second.merge(attrGraphs1[j].second);
					if (subGraph.exist_basic(u, k1, k2)) {
						AttrsPair attrsPair = attrGraphs1[i].first.merge(attrGraphs1[j].first);
						attrsPair.p1 = i, attrsPair.p2 = j;
						pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
						if (!attrShow[attrsPair]) {
							attrShow[attrsPair] = true;
							attrGraphs2.push_back(tg);
							//printSimple(tg, sg.num2key);
							if (attrsPair.size > attr_size) {
								ans.clear();
								attr_size = attrsPair.size;
								ans.push_back(tg);
							}
							else if (attrsPair.size == attr_size) {
								ans.push_back(tg);
							}
						}
					}
				}
			}
			attrGraphs1.clear();
			//cout << "number:" << attrGraphs2.size() << endl;
			//cout << endl;
		}
		else {
			for (int i = 0; i < attrGraphs2.size(); i++) {
				for (int j = i + 1; j < attrGraphs2.size(); j++) {
					SubGraph subGraph = attrGraphs2[i].second.merge(attrGraphs2[j].second);
					if (subGraph.exist_basic(u, k1, k2)) {
						AttrsPair attrsPair = attrGraphs2[i].first.merge(attrGraphs2[j].first);
						attrsPair.p1 = i, attrsPair.p2 = j;
						pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
						if (!attrShow[attrsPair]) {
							attrShow[attrsPair] = true;
							attrGraphs1.push_back(tg);
							//printSimple(tg, sg.num2key);
							if (attrsPair.size > attr_size) {
								ans.clear();
								attr_size = attrsPair.size;
								ans.push_back(tg);
							}
							else if (attrsPair.size == attr_size) {
								ans.push_back(tg);
							}
						}
					}
				}
			}
			attrGraphs2.clear();
			//cout << "number:" << attrGraphs1.size() << endl;
			//cout << endl;
		}
	}
	//cout << "���������" << ans.size() << endl;
	return ans;
}

vector<pair<AttrsPair, SubGraph>> query_inc_exp(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1) {
	//cout << "query_inc_exp" << endl;
	BiGraph sg(g);
	int attr_size = 0;
	vector<pair<AttrsPair, SubGraph>> ans;
	if (sg.neighbor_v1[u].size() == 0) {
		cout << u << " not in coreGraph" << endl;
		return ans;
	}
	if (sg.num_v1 == 0) return ans;
	//����attrs2,��u�����ھӽڵ�Ĺؼ��ֵĲ���
	vector<vid_t> attrs2;
	map<vid_t, bool> show2;
	for (int neighbor : sg.neighbor_v1[u]) {
		if (sg.neighbor_v2[neighbor].size() == 0) continue;
		for (vid_t attr : sg.attribute_v2[neighbor]) {
			if (!show2[attr]) {
				attrs2.push_back(attr);
				show2[attr] = true;
			}
		}
	}


	map<vid_t, vector<vid_t>> attrVertexs1, attrVertexs2;
	map<vid_t, bool> show1;
	for (vid_t t : attrs1) show1[t] = true;
	for (vid_t i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		for (vid_t n : sg.attribute_v1[i]) {
			if (show1[n]) attrVertexs1[n].push_back(i);
		}
	}
	for (vid_t i = 0; i < sg.num_v2; i++) {
		if (sg.neighbor_v2[i].size() == 0) continue;
		for (vid_t n : sg.attribute_v2[i]) {
			if (show2[n]) attrVertexs2[n].push_back(i);
		}
	}

	int k = 0;
	//cout << "Round" << k << ":" << endl;
	k++;
	vector<pair<AttrsPair, SubGraph>> attrGraphs1, attrGraphs2;
	for (vid_t attr1 : attrs1) {
		for (vid_t attr2 : attrs2) {
			SubGraph subGraph(sg.num_v1, sg.num_v2, attrVertexs1[attr1], attrVertexs2[attr2], sg.neighbor_v1, sg.neighbor_v2);
			if (subGraph.exist_basic(u, k1, k2)) {
				AttrsPair attrsPair = AttrsPair(attr1, attr2);
				pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
				attrGraphs1.push_back(tg);
				//printSimple(tg, sg.num2key);
				if (attrsPair.size > attr_size) {
					ans.clear();
					attr_size = attrsPair.size;
					ans.push_back({ attrsPair, subGraph });
				}
				else if (attrsPair.size == attr_size) {
					ans.push_back({ attrsPair, subGraph });
				}
			}
		}
	}
	//cout << "number:" << attrGraphs1.size() << endl;
	//cout << endl;

	//����attrGraphs�е���������������ؼ��ֽ�����ͼ�Ľ�������Ϊ�ռ�����ȡ�����������µ�attrGraphs��ֱ��û�п�������������Ԫ��
	map<AttrsPair, bool> attrShow;
	while (attrGraphs1.size() != 0 || attrGraphs2.size() != 0) {
		//cout << "Round" << k << ":" << endl;
		k++;
		if (attrGraphs1.size() != 0) {
			for (int i = 0; i < attrGraphs1.size(); i++) {
				for (int j = i + 1; j < attrGraphs1.size(); j++) {
					SubGraph subGraph = attrGraphs1[i].second.merge(attrGraphs1[j].second);
					if (subGraph.exist_basic(u, k1, k2)) {
						AttrsPair attrsPair = attrGraphs1[i].first.merge(attrGraphs1[j].first);
						attrsPair.p1 = i, attrsPair.p2 = j;
						pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
						if (!attrShow[attrsPair]) {
							attrShow[attrsPair] = true;
							attrGraphs2.push_back(tg);
							//printSimple(tg, sg.num2key);
							if (attrsPair.size > attr_size) {
								ans.clear();
								attr_size = attrsPair.size;
								ans.push_back(tg);
							}
							else if (attrsPair.size == attr_size) {
								ans.push_back(tg);
							}
						}
					}
				}
			}
			attrGraphs1.clear();
			//cout << "number:" << attrGraphs2.size() << endl;
			//cout << endl;
		}
		else {
			for (int i = 0; i < attrGraphs2.size(); i++) {
				for (int j = i + 1; j < attrGraphs2.size(); j++) {
					SubGraph subGraph = attrGraphs2[i].second.merge(attrGraphs2[j].second);
					if (subGraph.exist_basic(u, k1, k2)) {
						AttrsPair attrsPair = attrGraphs2[i].first.merge(attrGraphs2[j].first);
						attrsPair.p1 = i, attrsPair.p2 = j;
						pair<AttrsPair, SubGraph> tg = { attrsPair , subGraph };
						if (!attrShow[attrsPair]) {
							attrShow[attrsPair] = true;
							attrGraphs1.push_back(tg);
							//printSimple(tg, sg.num2key);
							if (attrsPair.size > attr_size) {
								ans.clear();
								attr_size = attrsPair.size;
								ans.push_back(tg);
							}
							else if (attrsPair.size == attr_size) {
								ans.push_back(tg);
							}
						}
					}
				}
			}
			attrGraphs2.clear();
			/*cout << "number:" << attrGraphs1.size() << endl;
			cout << endl;*/
		}
	}
	//cout << "���������" << ans.size() << endl;
	return ans;
}



void pushAllCase(int u, int n, set<vid_t>& kind, set<vid_t>& s, set<set<vid_t>, setCmp>& attrSet,
	map<set<vid_t>, vector<vid_t>>& attrVertexs, map<set<vid_t>, vector<int>>& attrVertexTemp, map<set<vid_t>, int>& show, int k) {

	if (n == s.size()) return; 
	auto it = s.begin();
	advance(it, n);
	vid_t m = *it;
	//ѡȡ
	kind.insert(m);
	++show[kind];
	if (show[kind] == k) {
		attrSet.insert(kind);
		//��ÿһ�ֿ��ܶ������Ӧ�Ķ���
		for (int i : attrVertexTemp[kind]) {
			attrVertexs[kind].push_back(i);
		}
		attrVertexs[kind].push_back(u);
	}
	else if (show[kind] < k) {
		attrVertexTemp[kind].push_back(u);
	}
	else {
		attrVertexs[kind].push_back(u);
	}
	pushAllCase(u, n + 1, kind, s, attrSet, attrVertexs, attrVertexTemp, show, k);
	kind.erase(m);
	//��ѡȡ
	pushAllCase(u, n + 1, kind, s, attrSet, attrVertexs, attrVertexTemp, show, k);
}
//�ɸ���������ھ�ȷ��show�󣬽����øõ������Ķ��㼯�Ͽ��ǽ�
void pushAllCase(int u, int n, set<vid_t>& kind, set<vid_t>& s,
	map<set<vid_t>, vector<vid_t>>& attrVertexs, map<set<vid_t>, int>& show, int k) {

	if (n == s.size()) return;
	auto it = s.begin();
	advance(it, n);
	vid_t m = *it;
	//ѡȡ
	kind.insert(m);
	if (show[kind] >= k) {
		attrVertexs[kind].push_back(u);
	}
	pushAllCase(u, n + 1, kind, s, attrVertexs, show, k);
	kind.erase(m);
	//��ѡȡ
	pushAllCase(u, n + 1, kind, s, attrVertexs, show, k);
}
void printCandidates(set<set<vid_t>, setCmp>& attrSet1, set<set<vid_t>, setCmp>& attrSet2, map<set<vid_t>, vector<vid_t>>& attrVertexs1, map<set<vid_t>, vector<vid_t>>& attrVertexs2, map<vid_t, string>& num2key) {
	cout << "U:" << endl;
	for (set<vid_t> attrs : attrSet1) {
		for (vid_t i : attrs) {
			cout << num2key[i] << " ";
		}
		cout << "����";
		for (int i : attrVertexs1[attrs]) {
			cout << " " << i;
		}
		cout << "." << endl;
	}
	cout << "V:" << endl;
	for (set<vid_t> attrs : attrSet2) {
		for (vid_t i : attrs) {
			cout << num2key[i] << " ";
		}
		cout << "����";
		for (int i : attrVertexs2[attrs]) {
			cout << " " << i;
		}
		cout << "." << endl;
	}
}
set<vid_t> getSetByIndex(set<set<vid_t>, setCmp>& attrSet, int k) {
	auto it = attrSet.begin();
	advance(it, k);
	return *it;
}

/*
* ȥ��attrSet���ظ���Ԫ��
* attrSet�ɴ�С���У���ÿһ�����е����Լ��������ҵ���Ӧ�ĵ㼯
* ����õ㼯�Ķ�Ӧ���Լ�֮ǰ��¼�����ұȵ�ǰ���Լ������ʾ��ǰ���Լ�����֮ǰ��¼�����Լ���
* �������Լ���Ӧ�ĵ㼯������ͼ�����еĵ㣬��������������Լ���Ӧ�ĵ㼯��ͬ�������ɾȥС�Ĳ���Ӱ�������ĵ㣬��Ϊ������û�и����Լ�
*/
void RemoveRedundance(set<set<vid_t>, setCmp>& attrSet, map<set<vid_t>, vector<vid_t>>& attrVertexs) {
	map<set<vid_t>, vid_t> vertexAttrSize;
	for (auto it = attrSet.begin(); it != attrSet.end();) {
		set<vid_t> vs(attrVertexs[*it].begin(), attrVertexs[*it].end());
		if (vertexAttrSize[vs] > (*it).size()) {
			set<set<vid_t>, setCmp>::iterator tip = it;
			it++;
			attrSet.erase(tip);
		}
		else {
			vertexAttrSize[vs] = (*it).size();
			it++;
		}
	}
}
vector<pair<AttrsPair, SubGraph>> query_dec_test(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1) {
	clock_t startTime, endTime;
	startTime = clock();
	vector<pair<AttrsPair, SubGraph>> ans;
	BiGraph sg = coreGraphOnce(g, u, k1, k2);
	if (sg.neighbor_v1[u].size() == 0) {
		cout << u << " not in coreGraph" << endl;
		return ans;
	}
	set<set<vid_t>, setCmp> attrSet1, attrSet2; //�ؼ��ּ�
	map<set<vid_t>, vector<vid_t>> attrVertexs1, attrVertexs2; //�ؼ��ּ���Ӧ�Ķ��㼯
	endTime = clock();
	cout << "pretreatment:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//����attrs1��U������attrSet1��attrVectexs1
	startTime = clock();
	map<vid_t, bool> showAttrs1;
	for (vid_t n : attrs1) showAttrs1[n] = true;
	map<set<vid_t>, vector<int>> attrVertexTemp;
	map<set<vid_t>, int> show;
	for (int i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		set<vid_t> s;
		for (vid_t m : sg.attribute_v1[i]) {
			if (showAttrs1[m]) s.insert(m);
		}
		if (s.size() != 0) {
			set<vid_t> kind = set<vid_t>();
			pushAllCase(i, 0, kind, s, attrSet1, attrVertexs1, attrVertexTemp, show, k2);
		}
	}
	RemoveRedundance(attrSet1, attrVertexs1);
	endTime = clock();
	cout << "get attrSet1 and attrVectexs1:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//����u���ھӽڵ�Ĺؼ�����V������attrSet2��attrVectexs2
	startTime = clock();
	attrVertexTemp.clear();
	show.clear();
	map<vid_t, bool> used;
	for (int i : sg.neighbor_v1[u]) {
		used[i] = true;
		set<vid_t> kind = set<vid_t>();
		set<vid_t> s(sg.attribute_v2[i].begin(), sg.attribute_v2[i].end());
		pushAllCase(i, 0, kind, s, attrSet2, attrVertexs2, attrVertexTemp, show, k1);
	}
	map<vid_t, bool> candidate;
	for (set<vid_t> s : attrSet2) {
		for (vid_t i : s) candidate[i] = true;
	}
	for (int i = 0; i < sg.num_v2; i++) {
		if (!used[i] && sg.neighbor_v2[i].size() != 0) {
			set<vid_t> kind = set<vid_t>();
			set<vid_t> s;
			for (vid_t attr : sg.attribute_v2[i]) {
				if (candidate[attr]) s.insert(attr);
			}
			pushAllCase(i, 0, kind, s, attrVertexs2, show, k1);
		}
	}
	RemoveRedundance(attrSet2, attrVertexs2);
	endTime = clock();
	cout << "get attrSet2 and attrVectexs2:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//�Ӵ�С����ÿ�������������֤�Ƿ����Gab
	startTime = clock();
	vector<AttrsId> attrPairsVec;
	int n1 = 0, n2 = 0;
	for (set<vid_t> s1 : attrSet1) {
		n2 = 0;
		for (set<vid_t> s2 : attrSet2) {
			attrPairsVec.push_back(AttrsId(s1.size() + s2.size(), n1, n2));
			++n2;
		}
		++n1;
	}
	sort(attrPairsVec.begin(), attrPairsVec.end());
	endTime = clock();
	cout << "get sorting attrPairsVec:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	startTime = clock();
	int maxn = 0;
	int count = 0;
	cout <<"total candidates: " << attrPairsVec.size() << endl;
	for (AttrsId attrsId : attrPairsVec) {
		count++;
		//if(count%100==0) cout << count << endl;
		if (maxn != 0 && attrsId.num < maxn) break;
		set<vid_t> attr1 = getSetByIndex(attrSet1, attrsId.index1), attr2 = getSetByIndex(attrSet2, attrsId.index2);
		SubGraph subGraph(sg.num_v1, sg.num_v2, attrVertexs1[attr1], attrVertexs2[attr2], sg.neighbor_v1, sg.neighbor_v2);
		if (subGraph.exist(u, k1, k2)) {
			maxn = attrsId.num;
			AttrsPair attrsPair(attr1, attr2);
			ans.push_back({ attrsPair,subGraph });
		}
	}
	cout<<"execution: "<< count << endl;
	endTime = clock();
	cout << "final deal time:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	return ans;
}
vector<pair<AttrsPair, SubGraph>> query_dec(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1) {
	//clock_t startTime, endTime;
	//startTime = clock();
	vector<pair<AttrsPair, SubGraph>> ans;
	BiGraph sg = coreGraphOnce(g, u, k1, k2);
	if (sg.neighbor_v1[u].size() == 0) {
		cout << u << " not in coreGraph" << endl;
		return ans;
	}
	set<set<vid_t>, setCmp> attrSet1, attrSet2; //�ؼ��ּ�
	map<set<vid_t>, vector<vid_t>> attrVertexs1, attrVertexs2; //�ؼ��ּ���Ӧ�Ķ��㼯
	//endTime = clock();
	//cout << "pretreatment:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//����attrs1��U������attrSet1��attrVectexs1
	//startTime = clock();
	map<vid_t, bool> showAttrs1;
	for (vid_t n : attrs1) showAttrs1[n] = true;
	map<set<vid_t>, vector<int>> attrVertexTemp;
	map<set<vid_t>, int> show;
	for (int i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		set<vid_t> s;
		for (vid_t m : sg.attribute_v1[i]) {
			if (showAttrs1[m]) s.insert(m);
		}
		if (s.size() != 0) {
			set<vid_t> kind = set<vid_t>();
			pushAllCase(i, 0, kind, s, attrSet1, attrVertexs1, attrVertexTemp, show, k2);
		}
	}
	RemoveRedundance(attrSet1, attrVertexs1);
	//endTime = clock();
	//cout << "get attrSet1 and attrVectexs1:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//����u���ھӽڵ�Ĺؼ�����V������attrSet2��attrVectexs2
	//startTime = clock();
	attrVertexTemp.clear();
	show.clear();
	map<vid_t, bool> used;
	for (int i : sg.neighbor_v1[u]) {
		used[i] = true;
		set<vid_t> kind = set<vid_t>();
		set<vid_t> s(sg.attribute_v2[i].begin(), sg.attribute_v2[i].end());
		pushAllCase(i, 0, kind, s, attrSet2, attrVertexs2, attrVertexTemp, show, k1);
	}
	//������u��������V�е㿼�ǣ�����attrVertexs2
	map<vid_t, bool> candidate;
	for (set<vid_t> s : attrSet2) {
		for (vid_t i : s) candidate[i] = true;
	}
	for (int i = 0; i < sg.num_v2; i++) {
		if (!used[i] && sg.neighbor_v2[i].size()!=0) {
			set<vid_t> kind = set<vid_t>();
			set<vid_t> s;
			for (vid_t attr : sg.attribute_v2[i]) {
				if (candidate[attr]) s.insert(attr);
			}
			pushAllCase(i, 0, kind, s, attrVertexs2, show, k1);
		}
	}
	RemoveRedundance(attrSet2, attrVertexs2);
	//endTime = clock();
	//cout << "get attrSet2 and attrVectexs2:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//�Ӵ�С����ÿ�������������֤�Ƿ����Gab
	//startTime = clock();
	vector<AttrsId> attrPairsVec;
	int n1 = 0, n2 = 0;
	for (set<vid_t> s1 : attrSet1) {
		n2 = 0;
		for (set<vid_t> s2 : attrSet2) {
			attrPairsVec.push_back(AttrsId(s1.size() + s2.size(), n1, n2));
			++n2;
		}
		++n1;
	}
	sort(attrPairsVec.begin(), attrPairsVec.end());
	//endTime = clock();
	//cout << "get sorting attrPairsVec:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	//startTime = clock();
	int maxn = 0;
	//int count = 0;
	//cout <<"total candidates: " << attrPairsVec.size() << endl;
	for (AttrsId attrsId : attrPairsVec) {
		//count++;
		//if(count%100==0) cout << count << endl;
		if (maxn != 0 && attrsId.num < maxn) break;
		set<vid_t> attr1 = getSetByIndex(attrSet1, attrsId.index1), attr2 = getSetByIndex(attrSet2, attrsId.index2);
		SubGraph subGraph(sg.num_v1, sg.num_v2, attrVertexs1[attr1], attrVertexs2[attr2], sg.neighbor_v1, sg.neighbor_v2);
		if (subGraph.exist(u, k1, k2)) {
			maxn = attrsId.num;
			AttrsPair attrsPair(attr1, attr2);
			ans.push_back({ attrsPair,subGraph });
		}
	}
	//cout<<"execution: "<< count << endl;
	//endTime = clock();
	//cout << "final deal time:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	return ans;
}

vector<pair<AttrsPair, SubGraph>> query_dec_exp(BiGraph& g, int u, int k1, int k2, vector<vid_t>& attrs1) {
	//cout << "query_dec_exp" << endl;
	//cout << u << " " << k1 << " " << k2 << endl;
	vector<pair<AttrsPair, SubGraph>> ans;
	BiGraph sg(g);
	if (sg.neighbor_v1[u].size() == 0) {
		cout << u << " not in coreGraph" << endl;
		return ans;
	}
	set<set<vid_t>, setCmp> attrSet1, attrSet2; //�ؼ��ּ�
	map<set<vid_t>, vector<vid_t>> attrVertexs1, attrVertexs2; //�ؼ��ּ���Ӧ�Ķ��㼯
	//cout << "pretreatment:"<< endl;

	//����attrs1��U������attrSet1��attrVectexs1
	map<vid_t, bool> showAttrs1;
	for (vid_t n : attrs1) showAttrs1[n] = true;
	map<set<vid_t>, vector<int>> attrVertexTemp;
	map<set<vid_t>, int> show;
	for (int i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		set<vid_t> s;
		for (vid_t m : sg.attribute_v1[i]) {
			if (showAttrs1[m]) s.insert(m);
		}
		if (s.size() != 0) {
			set<vid_t> kind = set<vid_t>();
			pushAllCase(i, 0, kind, s, attrSet1, attrVertexs1, attrVertexTemp, show, k2);
		}
	}
	RemoveRedundance(attrSet1, attrVertexs1);
	//cout << "get attrSet1 and attrVectexs1:" << endl;

	//����u���ھӽڵ�Ĺؼ�����V������attrSet2��attrVectexs2
	attrVertexTemp.clear();
	show.clear();
	map<vid_t, bool> used;
	for (int i : sg.neighbor_v1[u]) {
		used[i] = true;
		set<vid_t> kind = set<vid_t>();
		set<vid_t> s(sg.attribute_v2[i].begin(), sg.attribute_v2[i].end());
		pushAllCase(i, 0, kind, s, attrSet2, attrVertexs2, attrVertexTemp, show, k1);
	}
	map<vid_t, bool> candidate;
	for (set<vid_t> s : attrSet2) {
		for (vid_t i : s) candidate[i] = true;
	}
	for (int i = 0; i < sg.num_v2; i++) {
		if (!used[i] && sg.neighbor_v2[i].size() != 0) {
			set<vid_t> kind = set<vid_t>();
			set<vid_t> s;
			for (vid_t attr : sg.attribute_v2[i]) {
				if (candidate[attr]) s.insert(attr);
			}
			pushAllCase(i, 0, kind, s, attrVertexs2, show, k1);
		}
	}
	RemoveRedundance(attrSet2, attrVertexs2);
	//cout << "get attrSet2 and attrVectexs2:" << endl;

	//�������
	//printCandidates(attrSet1, attrSet2, attrVertexs1, attrVertexs2, sg.num2key);

	//�Ӵ�С����ÿ�������������֤�Ƿ����Gab
	vector<AttrsId> attrPairsVec;
	int n1 = 0, n2 = 0;
	for (set<vid_t> s1 : attrSet1) {
		n2 = 0;
		for (set<vid_t> s2 : attrSet2) {
			attrPairsVec.push_back(AttrsId(s1.size() + s2.size(), n1, n2));
			++n2;
		}
		++n1;
	}
	sort(attrPairsVec.begin(), attrPairsVec.end());
	//cout << "get sorting attrPairsVec:" << endl;
	//cout << attrPairsVec.size() << endl;
	int maxn = 0;
	int count = 0;
	for (AttrsId attrsId : attrPairsVec) {
		//count++;
		//if(count%10000==0) cout << count << endl;
		if (maxn != 0 && attrsId.num < maxn) break;
		//attrsId.print();
		set<vid_t> attr1 = getSetByIndex(attrSet1, attrsId.index1), attr2 = getSetByIndex(attrSet2, attrsId.index2);
		SubGraph subGraph(sg.num_v1, sg.num_v2, attrVertexs1[attr1], attrVertexs2[attr2], sg.neighbor_v1, sg.neighbor_v2);
		//subGraph.print();
		if (subGraph.exist(u, k1, k2)) {
			//subGraph.print();
			maxn = attrsId.num;
			AttrsPair attrsPair(attr1, attr2);
			ans.push_back({ attrsPair,subGraph });
		}
	}
	//cout << "final deal time:" << endl;
	return ans;
}



void pushAllCase_basic(int n, set<vid_t>& kind, vector<vid_t>& s, set<set<vid_t>, setCmp>& attrSet) {
	if (n == s.size()) return;
	vid_t m = s[n];
	//ѡȡ
	kind.insert(m);
	attrSet.insert(kind);
	pushAllCase_basic(n + 1, kind, s, attrSet);
	kind.erase(m);
	//��ѡȡ
	pushAllCase_basic(n + 1, kind, s, attrSet);
}
//����basic�������ǳ��ִ�����ֻ��¼�ؼ�����ϺͶ�Ӧ�Ķ��㼯
void pushAllCase_basic_pro(int u, int n, set<vid_t>& kind, set<vid_t>& s, set<set<vid_t>, setCmp>& attrSet,
	map<set<vid_t>, vector<vid_t>>& attrVertexs, map<set<vid_t>, int>& show, int k) {
	if (n == s.size()) return;
	auto it = s.begin();
	advance(it, n);
	vid_t m = *it;
	//ѡȡ
	kind.insert(m);
	attrSet.insert(kind);
	attrVertexs[kind].push_back(u);
	pushAllCase_basic_pro(u, n + 1, kind, s, attrSet, attrVertexs, show, k);
	kind.erase(m);
	//��ѡȡ
	pushAllCase_basic_pro(u, n + 1, kind, s, attrSet, attrVertexs, show, k);
}

/*
* ʵ��˼·��
* 1���õ�U�����п��ܵĹؼ��ּ���s1��V�����п��ܵĹؼ��ּ���s2
* 2����s1��s2�õ��ؼ������S
* 3����S��ȡ��Ӧ�Ķ����Լ���ͼ
* 4������ͼ�������(a,��)-core
* 5������������ؼ��ֵ�(a,��)-core
*/

vector<pair<AttrsPair, SubGraph>> query_basic(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1) {
	BiGraph sg(g);
	set<set<vid_t>, setCmp> attrSet1, attrSet2; //�ؼ��ּ�
	map<set<vid_t>, vector<vid_t>> attrVertexs1, attrVertexs2; //�ؼ��ּ���Ӧ�Ķ��㼯

	map<vid_t, bool> showAttrs1;
	for (vid_t n : attrs1) showAttrs1[n] = true;
	map<set<vid_t>, int> show;
	for (int i = 0; i < sg.num_v1; i++) {
		if (sg.neighbor_v1[i].size() == 0) continue;
		set<vid_t> s;
		for (vid_t m : sg.attribute_v1[i]) {
			if (showAttrs1[m]) s.insert(m);
		}
		if (s.size() != 0) {
			set<vid_t> kind = set<vid_t>();
			pushAllCase_basic_pro(i, 0, kind, s, attrSet1, attrVertexs1, show, k2);
		}
	}

	//cout << "attrSet1:" << attrSet1.size() << endl;
	show.clear();
	map<vid_t, bool> used;
	for (int i : sg.neighbor_v1[u]) {
		used[i] = true;
		set<vid_t> kind = set<vid_t>();
		set<vid_t> s(sg.attribute_v2[i].begin(), sg.attribute_v2[i].end());
		pushAllCase_basic_pro(i, 0, kind, s, attrSet2, attrVertexs2, show, k1);
	}
	//������u��������V�е㿼�ǣ�����attrVertexs2
	map<vid_t, bool> candidate;
	for (set<vid_t> s : attrSet2) {
		for (vid_t i : s) candidate[i] = true;
	}
	for (int i = 0; i < sg.num_v2; i++) {
		if (!used[i] && sg.neighbor_v2[i].size() != 0) {
			set<vid_t> kind = set<vid_t>();
			set<vid_t> s;
			for (vid_t attr : sg.attribute_v2[i]) {
				if (candidate[attr]) s.insert(attr);
			}
			pushAllCase(i, 0, kind, s, attrVertexs2, show, k1);
		}
	}
	//cout << "attrSet2:" << attrSet2.size() << endl;
	
	vector<AttrsId> attrsPairsVec;
	int n1 = 0, n2 = 0;
	for (set<vid_t> s1 : attrSet1) {
		n2 = 0;
		for (set<vid_t> s2 : attrSet2) {
			attrsPairsVec.push_back(AttrsId(s1.size() + s2.size(), n1, n2));
			++n2;
		}
		++n1;
	}
	sort(attrsPairsVec.begin(), attrsPairsVec.end());
	//cout << "total candidates: " << attrsPairsVec.size() << endl;
	vector<pair<AttrsPair, SubGraph>> ans;
	int maxn = 0;
	int count = 0;
	for (AttrsId attrsId : attrsPairsVec) {
		count++;
		//cout << count << endl;
		//if(count%5000==0) cout << count << endl;
		if (maxn != 0 && attrsId.num < maxn) break;
		set<vid_t> s1 = getSetByIndex(attrSet1, attrsId.index1), s2 = getSetByIndex(attrSet2, attrsId.index2);
		vector<vid_t> v1 = attrVertexs1[s1], v2 = attrVertexs2[s2];
		//cout << "s1: " << s1.size() << endl;
		//cout << "s2: " << s2.size() << endl;
		//cout << "v2: " << v2.size() << endl;
		SubGraph subGraph(sg.num_v1, sg.num_v2, v1, v2, sg.neighbor_v1, sg.neighbor_v2);
		if (subGraph.exist(u, k1, k2)) {
			maxn = attrsId.num;
			AttrsPair attrsPair(getSetByIndex(attrSet1, attrsId.index1), getSetByIndex(attrSet2, attrsId.index2));
			ans.push_back({ attrsPair,subGraph });
		}
	}
	
	return ans;
}
/*
vector<pair<AttrsPair, SubGraph>> query_basic(BiGraph& g, int u, int k1, int k2, vector<vid_t> attrs1) {
	BiGraph sg(g);
	set<set<vid_t>, setCmp> attrSet1, attrSet2; //�ؼ��ּ�
	set<vid_t> kind1 = set<vid_t>();
	pushAllCase_basic(0, kind1, attrs1, attrSet1);
	//cout << "attrSet1:" << attrSet1.size() << endl;
	for (int i = 0; i < sg.num_v2; i++) {
		set<vid_t> kind = set<vid_t>();
		pushAllCase_basic(0, kind, sg.attribute_v2[i], attrSet2);
	}
	//cout << "attrSet2:" << attrSet2.size() << endl;

	vector<AttrsId> attrsPairsVec;
	int n1 = 0, n2 = 0;
	for (set<vid_t> s1 : attrSet1) {
		n2 = 0;
		for (set<vid_t> s2 : attrSet2) {
			attrsPairsVec.push_back(AttrsId(s1.size() + s2.size(), n1, n2));
			++n2;
		}
		++n1;
	}
	sort(attrsPairsVec.begin(), attrsPairsVec.end());
	//cout << "total candidates: " << attrsPairsVec.size() << endl;
	vector<pair<AttrsPair, SubGraph>> ans;
	int maxn = 0;
	int count = 0;
	for (AttrsId attrsId : attrsPairsVec) {
		count++;
		//cout << count << endl;
		//if(count%5000==0) cout << count << endl;
		if (maxn != 0 && attrsId.num < maxn) break;
		vector<vid_t> v1, v2;
		set<vid_t> s1 = getSetByIndex(attrSet1, attrsId.index1), s2 = getSetByIndex(attrSet2, attrsId.index2);
		//cout << "s1: " << s1.size() << endl;
		//cout << "s2: " << s2.size() << endl;
		for (vid_t i = 0; i < sg.num_v1; i++) {
			bool flag = true;
			for (vid_t attr : s1) {
				if (find(sg.attribute_v1[i].begin(), sg.attribute_v1[i].end(), attr) == sg.attribute_v1[i].end()) {
					flag = false;
					break;
				}
			}
			if (flag) v1.push_back(i);
		}
		//cout << "v1: " << v1.size() << endl;
		for (vid_t i = 0; i < sg.num_v2; i++) {
			bool flag = true;
			for (vid_t attr : s2) {
				if (find(sg.attribute_v2[i].begin(), sg.attribute_v2[i].end(), attr) == sg.attribute_v2[i].end()) {
					flag = false;
					break;
				}
			}
			if (flag) v2.push_back(i);
		}
		//cout << "v2: " << v2.size() << endl;
		SubGraph subGraph(sg.num_v1, sg.num_v2, v1, v2, sg.neighbor_v1, sg.neighbor_v2);
		if (subGraph.exist(u, k1, k2)) {
			maxn = attrsId.num;
			AttrsPair attrsPair(getSetByIndex(attrSet1, attrsId.index1), getSetByIndex(attrSet2, attrsId.index2));
			ans.push_back({ attrsPair,subGraph });
		}
	}

	return ans;
}*/

