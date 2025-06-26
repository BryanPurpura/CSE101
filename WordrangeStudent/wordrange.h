#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

//Node, got it from class code
class Node{
        public:
                std::string key;
                Node *left, *right, *parent;
		int height;
		int sub_size;

                Node(){
                        left = right = parent = NULL;
                	height = 1;
			sub_size = 1;
		}
                Node(std::string val){
                        key = val;
                        left = right = parent = NULL;
                	height = 1;
			sub_size = 1;
		}
};
class BST{
        private:
                Node *root;
        public:
                BST();
                void insert(std::string);
                Node* insert(Node*, Node*);
                Node* find(std::string);
                Node* find(Node*, std::string);
                void range(std::string, std::string, int&);
                void range(Node*, std::string, std::string, int&);
		void updateNode(Node* node);
		int balance_factor(Node* node);
		Node* rotate_left(Node* node);
		Node* rotate_right(Node* node);
};
