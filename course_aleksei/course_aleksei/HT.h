#pragma once
#include <functional>
#include "List.h"
#include "Pair.h"
#include "Vector.h"

namespace Aleksei {
	template <typename T, class Hash>
	class HashTable {
	public:
		HashTable() {

		}
		~HashTable() {
			for (int i = 0; i < N; i++) {
				~table[i];
			}
		}
		HashTable(const HashTable&) = delete;
		HashTable& operator = (const HashTable&) = delete;
		HashTable(HashTable&&) = default;
		HashTable& operator = (HashTable&&) = default;

		void Insert(T t) {
			table[Hash(t, N)].push(t);
		}
		void Remove(const T& t) {
			table[Hash(t, N)].Delete(t);
		}
		T* Find(const T& t) const {

		}
		Vector<Pair<T, size_t>> Lookup() const = 0;

		virtual size_t GetLastComparisonAmount() const = 0;
	private:
		unsigned short N = 1024;
		MyList<T>* table = new MyList<T>[N];
		size_t last_comparison_amount;
	};
}