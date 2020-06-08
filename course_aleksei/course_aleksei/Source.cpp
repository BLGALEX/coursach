#include"aleksei/RBTree.h"
#include"aleksei/HashTable.h"
#include"aleksei/Company.h" 
#include<iostream>



int main() {

	Vector<std::string> services;
	Company first("fвапро", services, "f");
	services.PushBack("Polochka");
	Company second("sап", services, "s");
	services.PushBack("Palochka");
	services[0] = "Polochka1";
	Company third("t", services, "t");
	
	Aleksei::HashTable HT;
	HT.Insert(first);
	HT.Insert(second);
	HT.Insert(third);

	Pair<Company, size_t> pair;
	Vector<Pair<Company, size_t>> v = HT.Lookup();
	for (int i = 0; i < v.Size(); i++) {
		pair = v[i];
	}
	return 0;
}