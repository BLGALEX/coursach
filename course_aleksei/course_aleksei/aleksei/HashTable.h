#pragma once
#include <functional>
#include "../helper/Pair.h"
#include "../helper/List.h"
#include "../helper/Vector.h"

namespace Aleksei {
	class HashTable {
	public:
		HashTable();
		~HashTable();

		HashTable(const HashTable&) = delete;

		HashTable& operator = (const HashTable&) = delete;
		
		HashTable(HashTable&&) = default;
		
		HashTable& operator = (HashTable&&) = default;

		void Insert(Company t);

		void Remove(const Company& t);

		Company* Find(const Company& t);

		Vector<Pair<Company, size_t>> Lookup();

		int Size() const;

		size_t GetLastComparisonAmount() const;

	private:

		size_t N = 4;
		MyList* table = new MyList[N];
		size_t last_comparison_amount = 0;
		size_t size = 0;

		int Hash(std::string s);
	};
}