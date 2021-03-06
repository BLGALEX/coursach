#include "Hashtable.h"
using namespace Aleksei;

HashTable::HashTable()noexcept {
	N = 4;
	table = new ForwardList[N];
	size = 0;
	last_comparison_amount = 0;
}
HashTable::~HashTable()noexcept {
	delete[] table;
}

bool HashTable::Insert(Company t)noexcept {
	if (Find(t) == nullptr) {
		table[Hash(t.GetName())].Push(t);
		size++;
		if (size >= (N / 4) * 3)
			ReHash();
		return true;
	}
	else return false;
}

bool HashTable::Remove(const std::string& t)noexcept {
	size_t s = table[Hash(t)].Size();
	if (table[Hash(t)].Erase(t)) {
		size = size - s + table[Hash(t)].Size();
		last_comparison_amount = table[Hash(t)].LastComparisonAmount();
		return true;
	}
	else return false;
}

const Company* HashTable::Find(const Company & t)noexcept {
	Company* result = table[Hash(t.GetName())].Find(t.GetName());
	last_comparison_amount = table[Hash(t.GetName())].LastComparisonAmount();
	return result;
}

Vector<Pair<const Company*, size_t>> HashTable::Lookup() const noexcept {
	Vector<Pair<const Company*, size_t>> v;
	Vector<const Company*> buf;
	Pair<Company, int> pair;
	for (size_t i = 0; i < N; i++) {
		buf = table[i].ToPointerVector();
		for (size_t j = 0; j < table[i].Size(); j++) {
			v.PushBack(Pair<const Company*, size_t>(buf[j], (size_t)Hash(buf[j]->GetName())));
		}
	}
	return v;
}

size_t HashTable::Buckets() const noexcept {
	return N;
}

size_t HashTable::Capacity() const {
	return size;
}

size_t HashTable::LastComparisonsAmount() const {
	return last_comparison_amount;
}


int HashTable::Hash(std::string s) const{
	float h = 0;
	float A = (float)0.6180339887;
	for (unsigned int i = 0; i < s.size(); i++) {
		h = (abs((int)s[i]) * A + h) - (int)(abs((int)s[i]) * A + h);
	}
	int result = (int)(N * h);
	return result;
}

Vector<Company> HashTable::GetData() const {
	Vector<Company> v, buf;
	v.Reserve(size);
	int k = 0;
	for (int i = 0; i < N; i++) {
			buf = table[i].ToVector();
			for (auto x : buf) {
				v.PushBack(x);
				k++;
			}
		}
	return v;
}

void HashTable::ReHash() {
	Vector<Company> v = GetData();
	N *= 2;
	delete[] table;
	table = new ForwardList[N];
	size = 0;
	for (int i = 0; i < v.Size(); i++)
		this->Insert(v[i]);
}