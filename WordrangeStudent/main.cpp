#include "wordrange.h"
using namespace std;

std::string trim(const std::string& str){
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
                ++start;
        }

        auto end = str.end();
        do{
                --end;
        }while (end != start && std::isspace(*end));
        return std::string(start, end+1);
}

int main (int argc, char *argv[]){
        BST tree;
        FILE *input = fopen(argv[1], "r");
        FILE *output = fopen(argv[2], "w");
        char buff[100];
	std::string word;
        while(fgets(buff, 100, input) != NULL)
        {
		std::string line(buff);
		std::istringstream iss(line);
		std::string command, word, range_begin, range_end;
		iss >> command;
		if (command == "i"){
			iss >> word;
			word = trim(word);
			if (!tree.find(word)) {
    			        tree.insert(word);
		        }
		    
		}
		else if (command == "r"){
			iss >> range_begin >> range_end;
			int count = 0;
			
			tree.range(range_begin,range_end,count);
			fprintf(output, "%d\n", count);
		}
	}
        fclose(input);
        fclose(output);
        return 0;

}
