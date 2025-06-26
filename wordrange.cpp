#include "wordrange.h"

//BST got it from class code
//
BST :: BST(){
	root = NULL;
}

void BST :: insert(std::string val ){
	Node *to_insert = new Node(val);
    	root = insert(root, to_insert);
	if (root) root->parent = nullptr;
}
Node* BST :: insert(Node* start, Node* to_insert){
	if (start == nullptr){
		return to_insert;
	}
	if (to_insert -> key < start -> key){
		start->left = insert(start->left, to_insert);
		start -> left ->parent = start;
	}
	else{
        	start->right = insert(start->right, to_insert);
       		start->right->parent = start;
    	}

	updateNode(start);
	int bf = balance_factor(start);
	if (bf>1){
		if (balance_factor(start->left) < 0){
			start->left = rotate_left(start->left);
                }
                return rotate_right(start);
        }
        if (bf<-1){
                if (balance_factor(start->right) > 0){
                        start->right = rotate_right(start->right);
		}
                return rotate_left(start);
        }
	return start;
}



Node* BST :: find(std::string val){

	return find(root, val);
}
Node* BST :: find(Node* start, std::string val){
	if (start == NULL || start->key == val){
        	return start;
	}
    	if(val < start->key){
        	return find(start->left, val);
	}
    	else{
        	return find(start->right, val);
	}
}

void BST :: range(std::string begin, std::string end, int& count){
	range(root, begin, end, count);
}
void BST :: range(Node* start, std::string begin, std::string end, int& count){
	if (start == nullptr){
		return;
	}
	if (begin <= start -> key && end >= start -> key){
		count++;
		if (start->parent){
			
			if(start->parent->key <= end && start->parent->key >= begin){
				if(start->key<start->parent->key && start->right){
					count+= start->right->sub_size;
					range(start->left, begin,end,count);
					return;
				}
				else if(start->key>start->parent->key && start->left){
					count+= start->left->sub_size;
					range(start->right, begin,end,count);
					return;
				}
				else{
					range(start->left, begin,end,count);
					range(start->right, begin, end, count);
					return;
				}
			}
			else{
				range(start -> left, begin, end, count);
		                range(start -> right, begin, end, count);
	        	        return;
			}
		}
		else{
			range(start -> left, begin, end, count);
			range(start -> right, begin, end, count);
			return;
		}
		return;
	}
	else if(start -> key > end){
		range(start -> left, begin, end, count);
		return;
	}
	else if (start -> key < begin){
		range(start -> right, begin, end, count);
		return;
	}
	return;
}

void BST :: updateNode(Node* node){
	int leftHeight = 0;
	int rightHeight = 0;
	if (node->left){
		leftHeight = node->left->height;
	}
	if (node->right){
                rightHeight = node->right->height;
        }
	node->height = 1 + std::max(leftHeight, rightHeight);
	
	int leftSize = 0;
	int rightSize = 0;
	if (node->left){
                leftSize = node->left->sub_size;
	}
        if (node->right){
                rightSize = node->right->sub_size;
	}
	node->sub_size = 1+leftSize+rightSize;
}

int BST :: balance_factor(Node* node){
	int lh = node -> left ? node->left->height: 0;
	int rh = node -> right ? node->right->height: 0;
	return lh-rh;
}

Node* BST :: rotate_left(Node* node){
	Node* parents_right = node->right;
	Node* left_grand = parents_right ->left;

	parents_right -> left = node;
	node -> right = left_grand;

	parents_right -> parent = node->parent;
	node -> parent = parents_right;
	if (left_grand){
		left_grand->parent = node;
	}

	updateNode(node);
	updateNode(parents_right);

	return parents_right;
}

Node* BST :: rotate_right(Node* node){
        Node* parents_left = node->left;
        Node* right_grand = parents_left ->right;

        parents_left -> right = node;
        node -> left = right_grand;

        parents_left -> parent = node->parent;
        node -> parent = parents_left;
        if (right_grand){
                right_grand->parent = node;
        }

        updateNode(node);
        updateNode(parents_left);

        return parents_left;
}

