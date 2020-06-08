#include "Hashtable.h"
using namespace Aleksei;

HashTable::HashTable(){}
HashTable::~HashTable(){}

void HashTable::Insert(Company t) {
	table[Hash(t.GetName())].push(t);
	size++;
}

void HashTable::Remove(const Company & t) {
	size_t s = table[Hash(t.GetName())].get_size();
	table[Hash(t.GetName())].Delete(t);
	size = size - s + table[Hash(t.GetName())].get_size();
}

Company* HashTable::Find(const Company & t) {
	Company* result = table[Hash(t.GetName())].Find(t.GetName());
	last_comparison_amount = table[Hash(t.GetName())].GetLastComparisonAmount();
	return result;
}

Vector<Pair<Company, size_t>> HashTable::Lookup() {
	Vector<Pair<Company, size_t>> v;
	Vector<Company> buf;
	Pair<Company, int> pair;
	for (size_t i = 0; i < N; i++) {
		buf = table[i].GetAllCompanies();
		for (size_t j = 0; j < table[i].get_size(); j++) {
			v.PushBack(Pair<Company, size_t>(buf[j], (size_t)Hash(buf[j].GetName())));
		}
	}
	return v;
}

int HashTable::Size() const {
	return size;
}

size_t HashTable::GetLastComparisonAmount() const {
	return last_comparison_amount;
}


int HashTable::Hash(std::string s) {
	float h = 0;
	float A = (float)0.6180339887;
	for (unsigned int i = 0; i < s.size(); i++) {
		h = (abs((int)s[i]) * A + h) - (int)(abs((int)s[i]) * A + h);
	}
	int result = (int)(N * h);
	return result;
}