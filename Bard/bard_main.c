#include "bard.h"
int main (int argc, char *argv[]){
	
	create_table();
	rank_ll();
	
	//read from input file first line, get first thing until whitespace, turn to int, store it, go after whitespace, turn to int store it. Then find it and write it
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");	
	
	char buf[100];
	while(fgets(buf, 100, input) != NULL){
		
		char *first = strtok(buf, " ");
		int first_int = atoi(first);

		char *second = strtok(NULL, "\n");
		int second_int = atoi(second);
		
		bool found = false;
		if (table[first_int] != NULL){
			Node *curr = table[first_int];
			while (curr){
				if(curr->rank == second_int){
					fprintf(output, "%s\n", curr -> word);
					found = true;
				}
				curr = curr->next;
			}
			if(!found){
				fprintf(output, "-\n");
			}
		}
		else{
			fprintf(output, "-\n");
		}
	}
	fclose(input);
	fclose(output);
	// free everything
	for (int i = 0; i < 27; i++){
		Node *curr = table[i];
		while(curr){
			Node *after = curr->next;
			if (curr -> word){
				free(curr -> word);
			}
			free(curr);
			curr = after;
		}
		table[i] = NULL;		
	}
	
}





