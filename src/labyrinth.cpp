#include<bits/stdc++.h>

using namespace std;

class Labyrinth{
    vector<vector <char>> schema;
    int rows, cols;

    public:
        Labyrinth(){
            rows = 0;
            cols = 0;
        } 
        bool readSchema(const char* filename);
        bool isValid(int i, int j){
            return 0 <= i && i < rows && 0 <= j && j <= cols;
        }
        bool isSafe(int i, int j, vector<vector<bool>> &visited){
            return (visited[i][j] != true) && (schema[i][j] != '#');
        }
        void findLongestPathFromNode(int i, int j, int dist, int &max_dist, vector<vector<bool>> &visited,
                                    vector<pair<int, int>> &path, vector<pair<int, int>> &max_path);
        vector<pair<int, int>> findLongestPath();
        void outputSchema(const char* filename, vector<pair<int, int>> &path);

};

bool Labyrinth::readSchema(const char* filename){
    ifstream file(filename);
    string line;

    if(!file){
        return false;
    }

    while (getline(file, line))
    {   
        vector <char> temp;
        rows++;
        for(int i=0; i < line.length(); i++){
            temp.push_back(line[i]);
        }
        schema.push_back(temp);
    }
    cols = line.length();

    cout << "\nInput Labyrinth" << endl;
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            cout << schema[i][j] ;
        }
        cout << endl;
    }

    file.close();
    return true;
}

void Labyrinth::outputSchema(const char* filename, vector<pair<int, int>> &path){
    ofstream f(filename);

    vector<vector <char>> output = schema;
    
    for(int i=0; i < path.size(); i++){
        output[path[i].first][path[i].second] = i + '0';
    }

    //Display Output
    cout << "\n" << path.size() << "\n";
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            cout << output[i][j];
        }
        cout << "\n";
    }
    cout << endl;

    //Save to file
    f << path.size() << "\n";
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            f << output[i][j];
        }
        f << "\n";
    }
    cout << "Output saved to " << filename << endl;

}

void Labyrinth::findLongestPathFromNode(int i, int j, int dist, int &max_dist, vector<vector<bool>> &visited,
                                        vector<pair<int, int>> &path, vector<pair<int, int>> &max_path){
    if(schema[i][j] == '#')
        return;
    
    int counter = 0;
    visited[i][j] = true;
    path.push_back(pair<int, int>(i, j));
    
    //left
    if(isValid(i, j-1) && isSafe(i, j-1, visited)){
        counter++;
        findLongestPathFromNode(i, j-1, dist+1, max_dist, visited, path, max_path);
    }
    //bottom
    if(isValid(i+1, j) && isSafe(i+1, j, visited)){
        counter++;
        findLongestPathFromNode(i+1, j, dist+1, max_dist, visited, path, max_path);
    }
    //right
    if(isValid(i, j+1) && isSafe(i, j+1, visited)){
        counter++;
        findLongestPathFromNode(i, j+1, dist+1, max_dist, visited, path, max_path);
    }
    //up
    if(isValid(i-1, j) && isSafe(i-1, j, visited)){
        counter++;
        findLongestPathFromNode(i-1, j, dist+1, max_dist, visited, path, max_path);
    }

    if(counter == 0){ //deadend
        if(max_dist < dist){
            max_dist = dist;
            max_path = path;
        }
    }

    visited[i][j] = false;
    path.pop_back();
}

vector<pair<int, int>> Labyrinth::findLongestPath(){

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> path;
    vector<pair<int, int>> max_path;
    
    int max_dist = 0;
    
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            findLongestPathFromNode(i, j, 0 , max_dist, visited, path, max_path);
        }
    }

    return max_path;
}

int main(int argc, char * argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if(argc < 3){
        cout << "\nEnter input file\n";
        cout << "Usage: labyrinth input.txt output.txt" << endl;
        return -1;
    }

    Labyrinth l;
    l.readSchema(argv[1]);
    vector<pair<int, int>> path = l.findLongestPath();
    l.outputSchema(argv[2], path);

    return 0;
}
