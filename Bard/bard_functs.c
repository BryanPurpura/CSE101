#include "bard.h"

Node *table[100] = {NULL};

//going through file, counting each char in word, and either putting it in the array at the len index if that spot is null, or doesn't have that word, or increasing occurences if it does exist
void create_table(void){
	char buff[100];        
	FILE *infile = fopen("shakespeare-cleaned5.txt", "r");
        while( fgets( buff, 100, infile) != NULL){

                buff[strcspn(buff, "\n")] = 0;
                int len = strlen(buff);

                //if there is nothing in that size, add this node
                if (table[len] == NULL){
                        Node *node = calloc(1,sizeof(Node));
                        node -> word = strdup(buff);
                        node -> len = len;
                        node -> rank = 0;
                        node -> times = 0;
                        node -> next = NULL;
                        table[len] = node;
                }
                Node *curr = table[len];
                Node *prev = NULL;
                bool found = false;
                //see if the word is in the list
                while (curr){

                        if (strcmp(curr->word, buff) == 0){
                                curr -> times++;
                                found = true;
                                break;
                        }
                        prev = curr;
                        curr = curr ->next;
                }
                //if not add the node
                if (!found){
                        Node *node = calloc(1, sizeof(Node));
                        prev -> next = node;
                        node -> word = strdup(buff);
                        node -> len = len;
                        node -> rank = 0;
                        node -> times = 1;
		}
        }
        fclose(infile);
}

//Next go through linked list and compare each word to each other word in its linked list, using two loops. A words rank can be computed by seeing how many other words have more occurences. so for each word that has more occurences increment rank. Make sure not to check it against it self.If occurences are equal, we must compare the strings first letter, and so on.
void rank_ll(void){
        for ( int i = 0; i < 100; i++){

                Node *curr_node = table[i];

                while (curr_node != NULL){
                        Node *curr_ll = table[i];

                        while(curr_ll != NULL){
                                bool found = false;
                                if (strcmp(curr_node ->word, curr_ll -> word) == 0){
                                        found = true;
                                }
                                if (!found){
                                        if( curr_node->times < curr_ll->times){
                                                curr_node->rank++;
                                        }
                                        if ( curr_node->times == curr_ll->times){
                                                if (strcmp(curr_node ->word, curr_ll -> word) > 0){
                                                        curr_node->rank++;
                                                }
                                        }
                                }
                                curr_ll = curr_ll->next;

                        }
                        curr_node = curr_node->next;
                }
        }
}
