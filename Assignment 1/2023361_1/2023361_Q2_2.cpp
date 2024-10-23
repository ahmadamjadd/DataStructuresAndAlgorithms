#include<iostream>
#include<windows.h>
using namespace std;

struct UniverseCoordinate{ // Structure to hold the coordinates and snake info
    int s_number; // Snake number
    int x_position; // X position in the grid
    int y_position; // Y position in the grid
    bool is_snake; // Flag to check if there's a snake
};

void update(UniverseCoordinate **&universe, int x_rows, int y_columns); // Updating array size
void drawTable(UniverseCoordinate **universe, int x_rows, int y_columns); // drawing 2D world in the end


int main(){
    UniverseCoordinate **universe = new UniverseCoordinate*[2]; // Initial 2D array
    for(int i = 0; i<2; i++){
        universe[i] = new UniverseCoordinate[2]; // Initialize rows
    }

    cout<<"Welcome to 2D World of Snakes!"<<endl;
    char choice;
    int x_rows, y_columns;
    cout<<"Do you want to update size of your 2D World or would go with the standard 2x2 size? y/n: ";
    cin>>choice;
    system("cls");
    if(choice == 'Y' || choice == 'y'){
        cout<<endl<<"Enter number of rows: ";
        cin>>x_rows;
        cout<<endl<<"Enter number of columns: ";
        cin>>y_columns;
        cout<<endl;
        update(universe, x_rows, y_columns); // Update the universe size
    } else {
        x_rows = 2; // Default size
        y_columns = 2;
    }

    cout<<"Press S where you find snakes: "<<endl;
    system("pause");
    int snake = 0;
    for(int i = 0; i<x_rows; i++){
        for(int j = 0; j<y_columns; j++){
            system("cls");
            universe[i][j].x_position = i; // Set positions
            universe[i][j].y_position = j;
            cout<<"Can you see snake at this position: ("<<i<<", "<<j<<"). s/n: ";
            char choice2;
            cin>>choice2;
            if(choice2 == 'S' || choice2 == 's'){
                snake++;
                universe[i][j].s_number = snake; // Assign snake number
                universe[i][j].is_snake = true; // Mark as snake
            } else {
                universe[i][j].is_snake = false; // No snake
                universe[i][j].s_number = 0;
            }
        }
    }
    drawTable(universe, x_rows, y_columns); // Draw the final table
    for(int i = 0; i<x_rows; i++) {
        delete[] universe[i]; // Deallocate each row
    }
    delete[] universe; // Deallocate the universe
    return 0;
}

void update(UniverseCoordinate **&universe, int x_rows, int y_columns){ // Update function to resize the universe
    UniverseCoordinate **tmp = new UniverseCoordinate*[x_rows]; // Create a new 2D array
    for(int i = 0; i<x_rows; i++){
        tmp[i] = new UniverseCoordinate[y_columns]; // Initialize each row
    }
    for(int i = 0; i<2; i++) { // Deallocate old universe
        delete[] universe[i];
    }
    delete[] universe; // Delete old universe
    universe = tmp; // Point to the new universe
    cout<<"Updated Successfully!"<<endl;
}


void drawTable(UniverseCoordinate **universe, int x_rows, int y_columns) { // Function to display the universe
    system("cls");
    cout<<endl<<"2D World of Snakes:\n";

    for(int j = 0; j<y_columns; j++) {
        cout<<"+-------"; // Print top border
    }
    cout<<"+"<<endl;

    for(int i = 0; i<x_rows; i++) {
        for(int j = 0; j<y_columns; j++) {
            if(universe[i][j].is_snake) {
                cout<<"|  S"<<universe[i][j].s_number<<"   "; // Print snake
            } else {
                cout<<"|       "; // Empty space
            }
        }
        cout<<"|"<<endl;

        for(int j = 0; j<y_columns; j++) {
            cout<<"+-------"; // Print bottom border
        }
        cout<<"+"<<endl;
    }
}