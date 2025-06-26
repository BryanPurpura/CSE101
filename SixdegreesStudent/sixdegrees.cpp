#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <cstring>
struct Pair{
	std::string movie;
	std::string other_actor;
};
class Graph{
        private:
		std::unordered_map<std::string, std::list<Pair>> actors_to_actor;
        public:
                void add_edge(std::string& u, Pair& p){
                        actors_to_actor[u].push_back(p);
                        actors_to_actor[p.other_actor].push_back(Pair{p.movie, u});
                }
                bool has_node(const std::string& u) const{
			return actors_to_actor.find(u) != actors_to_actor.end();
                }
		void bfs(const std::string& start, const std::string& end, FILE* output)const{
			std::queue<std::string> q;
			std::unordered_map<std::string, Pair > pred;
			std::unordered_set<std::string> visited;
	
			q.push(start);
			visited.insert(start);
	
			while (!q.empty()){
				std::string curr = q.front();
				q.pop();
				if (curr==end){
					std::vector<std::string> path;
					std::string node = end;
					while (node != start){
						auto [prev, movie] = pred[node];
						path.push_back(" -(" +movie+ ")- " +node);
						node = prev;
					}
					fprintf(output, "%s", start.c_str());
					for (auto iter = path.rbegin(); iter != path.rend(); iter++){
						fprintf(output,"%s",  iter->c_str());
					}
					fprintf(output, "\n");
					return;
				}
				for (const Pair& neighbor :  actors_to_actor.at(curr)){
					const std::string& next = neighbor.other_actor;
					if (visited.find(next) == visited.end()){
						visited.insert(next);
						pred[next] = {curr, neighbor.movie};
						q.push(next);
					}
				}
			}
			fprintf(output, "Not present\n");
			return;
		}
};
int main(int argc, char *argv[]){
	(void)argc;
	Graph actors_to_actor;
	FILE *infile=fopen("cleaned_movielist.txt","r");
	char buff[1000];
	while(fgets(buff, 1000, infile) != NULL){
		char *first = strtok(buff, " ");
		std::string movie(first);
		std::list<std::string> actor_list;
		char *a;
		while ((a = strtok(NULL, " \n")) != NULL){
			std::string actor(a);
			actor_list.push_back(actor);
		}
		for (auto it1 = actor_list.begin(); it1 != actor_list.end(); ++it1) {
    			for (auto it2 = actor_list.begin(); it2 != it1; ++it2) {
        			Pair p;
			        p.movie = movie;
			        p.other_actor = *it2;
			        actors_to_actor.add_edge(*it1, p);
			}
		}

	}
	fclose(infile);

	FILE *input = fopen(argv[1], "r");
        FILE *output = fopen(argv[2], "w");
	char buf[1000];
	while(fgets(buf, 1000, input) != NULL){
		char *f = strtok(buf, " ");
		std::string actor1(f);
		char *s = strtok(NULL, " \n");
		std::string actor2(s);
		if (actor1 == actor2){
			fprintf(output, "%s\n", actor1.c_str());
		}
		else if (!actors_to_actor.has_node(actor1) || !actors_to_actor.has_node(actor2)){
			fprintf(output, "Not present\n");
		}
		else{
			actors_to_actor.bfs(actor1, actor2, output);
		}
	}
	fclose(input);
	fclose(output);
	return 0;
}
