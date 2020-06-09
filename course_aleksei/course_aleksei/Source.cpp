#include"aleksei/RBTree.h"
#include"aleksei/HashTable.h"
#include"aleksei/Company.h" 
#include<iostream>



int main() {
	Customer test;
	
	while (true) {
		Aleksei::RBTree tree;
		for (int i = 0; i < 1000; i++) {
			test.SetCompanyName(std::to_string(i));
			test.SetName(std::to_string(i));
			test.SetService(std::to_string(i));
			test.SetVolume(i);
			tree.Insert(test);
		}

		for (int i = 0; i < 10; i++) {
			test.SetCompanyName(std::to_string(i));
			test.SetName(std::to_string(i));
			test.SetService(std::to_string(i));
			test.SetVolume(i);
			tree.Remove(test.GetName());
		}
	}


	return 0;
}