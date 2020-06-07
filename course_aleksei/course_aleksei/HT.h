#pragma once
#include <functional>
#include "List.h"
#include "Pair.h"
#include "Vector.h"

template <typename T, class Hash>
class IHashTable {
public:
	IHashTable();
	//IHashTable(InputIt first, InputIt last);
	~IHashTable() {
		for (int i = 0; i < N; i++) {
			~table[i];
		}
	}
	IHashTable(const IHashTable&) = delete;
	IHashTable& operator = (const IHashTable&) = delete;
	IHashTable(IHashTable&&) = default;
	IHashTable& operator = (IHashTable&&) = default;

	void Insert(T t) {
		table[Hash(t, N)].push(t);
	}
	void Remove(const T& t) {
		table[Hash(t, N)].Delete(t);
	}
	T Find(const T& t) const {
		
	}
	Vector<Pair<T, size_t>> Lookup() const = 0;

	virtual size_t GetLastComparisonAmount() const = 0;
private:
	static const unsigned short N = 1024;
	MyList<T> table[N];
	Hasher = Hash();
	size_t last_comparison_amount;
};