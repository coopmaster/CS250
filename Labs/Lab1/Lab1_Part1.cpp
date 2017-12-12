#include <iostream>
#include <vector>
#include <string>
using namespace std;

void addIngredients( vector<string>& ingredients){
	ingredients.push_back("lettuce");
	ingredients.push_back("tomato");
	ingredients.push_back("mayo");
	ingredients.push_back("bread");
}

void displayIngredients( const vector<string>& ingredients){
	for(int i = 0; i < ingredients.size(); i++){
		cout << ingredients[i] << endl;
	}
}

int main(){
	vector<string> ingredients;
	addIngredients(ingredients);
	displayIngredients(ingredients);
	return 0;
}