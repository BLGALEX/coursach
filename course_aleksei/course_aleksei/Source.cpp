#include"aleksei/RBTree.h"
#include"aleksei/HashTable.h"
#include"aleksei/Company.h" 
#include<iostream>



int main() {
	Customer test;
	while (true) {
		Aleksei::RBTree HT;
		for (int i = 0; i < 1000; i++) {
			test.SetCompanyName(std::to_string(i));
			test.SetName(std::to_string(i));
			test.SetService(std::to_string(i));
			test.SetVolume(i);
			HT.Insert(test);
		}

		for (int i = 0; i < 10; i++) {
			test.SetCompanyName(std::to_string(i));
			test.SetName(std::to_string(i));
			test.SetService(std::to_string(i));
			test.SetVolume(i);
			HT.Remove(test.GetName());
		}

	}
	
	return 0;
}