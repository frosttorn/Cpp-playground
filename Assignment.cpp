#include <iostream> //Header files MUST be included to use from the library
#include <cmath>
#include <limits>  
#include <fstream>
#include <string>

using namespace std;

// Function declarations
void punching();
void Calpunching(double x, ofstream& outFile);

void notching(ofstream& outFile);
void squareNotch(ofstream& outFile, int pointOfNotch, int length);
void VNotch(ofstream& outFile, int pointOfNotch, int length);
void slantNotch(ofstream& outFile, int pointOfNotch, int length);

void angleShearing(ofstream& outFile);

void bending(ofstream& outFile);
double getPositiveInput(const string& prompt);
double degreeToRadian(double degree);

void cutting(ofstream& outFile); 
//Pass by reference is utilized
//ofstream& is used so that the data written can be still be stored in the file
//string& is used to avoid a second copy of the string data

const double PI = 3.142; // Unchanging variable throughout the whole process no matter what

int main() // Main process where everything goes
{
    char safety,selection, selection_2; // Identifying variables

    ofstream outFile("results.txt", ios::app); // Open file for appending results

    if (!outFile)
    {
        cout << "Error opening file for writing." << endl;
        return 1;
    }

    do // Execute the statement ONE TIME then only confirmation if they want to repeat or not
    {
        //Display menu for selection of what to do with the machine
        cout << "Please select the process you wish to execute:" << endl;
        cout << "Press A for punching" << endl;
        cout << "Press B for notching" << endl;
        cout << "Press C for angle shearing" << endl;
        cout << "Press D for bending" << endl;
        cout << "Press E for cutting" << endl;
        cout << "Your selection: ";
        cin >> selection;

        switch(selection) // Utilization of selection sequence
        {
            case 'a':
            case 'A':
                punching(); //Executes to call function punching()
                break; //Break is to exit the loop immediately
            case 'b':
            case 'B':
                notching(outFile); //Executes to call function notching(outFile)
                break;
            case 'c':
            case 'C':
                angleShearing(outFile); //Executes to call function angleShearing(outFile)
                break;
            case 'd':
            case 'D':
                bending(outFile); //Executes to call function bending(outFile)
                break;
            case 'e':
            case 'E':
                cutting(outFile); //Executes to call function cutting(outFile)
                break;
            default: //Default is executed when the other conditions are not met
                cout << "\nInvalid selection" << endl;
                break;
        }
        cout << "---------------------------------" << endl;
        cout << "\nDo you wish to repeat the process? (Y/N): ";
        cin >> selection_2;
    } while (selection_2 == 'Y' || selection_2 == 'y'); // Up to user if they want to repeat

    cout << "\nThanks for using! Bye bye!" << endl << endl; // Ending of the coding

    outFile.close(); // Closing the file is a MUST
    return 0; // Ensure NO errors.
}

void punching() // Punching is selected
{
    // Declaration of variables and their data types
    int numSelection;
    double thickness;
    
    // Sub-menu for punching
    cout << "----------------------------------" << endl;
    cout << "You have selected punching." << endl << endl;
    cout << "NOTE: This machine has a tonnage rating of 100 tons." << endl << endl;
    cout << "Please state the type of metal sheet you are operating on:" << endl;
    cout << "Press 1 for stainless steel (Max thickness = 9.5)" << endl;
    cout << "Press 2 for mild steel (Max thickness = 19.0)" << endl;
    cout << "Press 3 for aluminum (Max thickness = 12.7)" << endl;
    cout << "Type of metal sheet: ";
    cin >> numSelection;

    cout << "Please provide the thickness of the metal sheet in mm: ";
    cin >> thickness;

    // Open file for appending results
    ofstream outFile("results.txt", ios::app);

    if (!outFile)
    {
        cout << "Error opening file for writing." << endl;
        return;
    }

    if (thickness < 0) // Selection process
    {
        cout << "Error: Thickness cannot be negative. Please enter a valid value." << endl;
    }
    else if ((numSelection == 1 && thickness <= 9.5) ||
             (numSelection == 2 && thickness <= 19.0) ||
             (numSelection == 3 && thickness <= 12.7))
    {
        Calpunching(thickness, outFile); // Calling function if all the following conditions are met
    }
    else
    {
        // Machine will malfunction if metal is too thick or an invalid numSelection is being inputted
        cout << "Sorry, either the metal sheet is too thick or the selected metal sheet is invalid." << endl;
    }

    outFile.close(); // Close the file
}

void Calpunching(double x, ofstream& outFile)
{
    // Again, declaration of variables and data type
    double diameter, punchHole, VolumeRemoved;

    cout << "\nYour metal sheet is approved to be punched within the available range." << endl;
    cout << "Now select your desired punching hole diameter (in mm): "; // Prompt to read how big of a hole does the user want
    cin >> diameter;
    punchHole = PI * pow((diameter / 2), 2); // Utilization of the header file <cmath>
    cout << "The area of the punched hole is: " << punchHole << " mm^2" << endl; // Unit must be shown
    VolumeRemoved = PI * pow((diameter / 2), 2) * x;
    cout << "The volume of the removed metal sheet is: " << VolumeRemoved << " mm^3" << endl; // Allow user to know how much is subtracted

    // Write results to file
    outFile << "Punching Results:" << endl;
    outFile << "Hole diameter: " << diameter << " mm" << endl;
    outFile << "Area of punched hole: " << punchHole << " mm^2" << endl;
    outFile << "Volume of removed metal: " << VolumeRemoved << " mm^3" << endl;
    outFile << "---------------------------------" << endl;
}

void notching(ofstream& outFile)
{
    cout << "----------------------------------" << endl;
    cout << "You have selected notching." << endl;
    
    // Variable to store input values
    int length, pointOfNotch, notchChoice;
    
    // Asking user for input
    cout << "Enter the length of workpiece (in cm): ";
    cin >> length;

    cout << "Enter the point of the notch (in cm): ";
    cin >> pointOfNotch;

    if (pointOfNotch >= length || pointOfNotch < 0 || length <= 0)
    {
        cout << "ERROR: Invalid input. Point of notch cannot be more than or equal to length, or negative." << endl;
        return;
    }

    // Asking user to enter type of notch
    cout << "(1 for square notch, 2 for V notch, 3 for slant notch)" << endl;
    cout << "Enter the type of notch: ";
    cin >> notchChoice;

    // Branching based on user's choice
    switch (notchChoice)
    {
        case 1:
            squareNotch(outFile, pointOfNotch, length);
            break;
        case 2:
            VNotch(outFile, pointOfNotch, length);
            break;
        case 3:
            slantNotch(outFile, pointOfNotch, length);
            break;
        default:
            cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
    }
}

// Function to create a square notch
void squareNotch(ofstream& outFile, int pointOfNotch, int length)
{
    // Calculating the depth
    int depth = length - pointOfNotch;
    // Display the output
    cout << "Square notch added with depth " << depth << " cm." << endl;
    // Write results to file
    outFile << "Notching Results:" << endl;
    outFile << "Point of notch: " << pointOfNotch << " cm" << endl;
    outFile << "Length of workpiece: " << length << " cm" << endl;
    outFile << "Type of notch: Square notch" << endl;
    outFile << "Depth of notch: " << depth << " cm" << endl;
    outFile << "---------------------------------" << endl;
}

// Function to create a V notch
void VNotch(ofstream& outFile, int pointOfNotch, int length)
{
    // Calculating the depth
    int depth = length - pointOfNotch;
    // Display the output
    cout << "V notch added with depth " << depth << " cm." << endl;
    // Write results to file
    outFile << "Notching Results:" << endl;
    outFile << "Point of notch: " << pointOfNotch << " cm" << endl;
    outFile << "Length of workpiece: " << length << " cm" << endl;
    outFile << "Type of notch: V notch" << endl;
    outFile << "Depth of notch: " << depth << " cm" << endl;
    outFile << "---------------------------------" << endl;
}

// Function to create a slant notch
void slantNotch(ofstream& outFile, int pointOfNotch, int length)
{
    // Calculating the depth
    int depth = length - pointOfNotch;
    // Display the output
    cout << "Slant notch added with depth " << depth << " cm." << endl;
    // Write results to file
    outFile << "Notching Results:" << endl;
    outFile << "Point of notch: " << pointOfNotch << " cm" << endl;
    outFile << "Length of workpiece: " << length << " cm" << endl;
    outFile << "Type of notch: Slant notch" << endl;
    outFile << "Depth of notch: " << depth << " cm" << endl;
    outFile << "---------------------------------" << endl;
}


void angleShearing(ofstream& outFile)
{
    // Declaring data variables with identifiers
    int thick, thickcut, thicknew;
    
    cout << "----------------------------------" << endl;
    cout << "You have selected angle shearing." << endl;
    cout << "NOTE: This machine has a thickness cutting limit of 16mm." << endl << endl; 
    cout << "Please input the thickness of the workpiece in mm: ";//Read user's metal sheet thickness
    cin >> thick;
    
    //Selection process and to eliminate potential errors
    if(thick <= 16)
    {
        cout << "Thickness of the workpiece to be reduced in mm: ";
        cin >> thickcut;
        thicknew = thick - thickcut;//Calculates the new cut thickness of the material

        //Optimal range to prevent over cutting the needed workpiece    
        if(thickcut > thick)
        {
            cout << "\nERROR: Thickness reduction exceeded original workpiece thickness." << endl;
        }
        else
        {
            cout << "\nNew thickness of workpiece is " << thicknew << " mm." << endl;
            // Writes results to file
            outFile << "Angle Shearing Results:" << endl;
            outFile << "Original thickness: " << thick << " mm" << endl;
            outFile << "Thickness reduction: " << thickcut << " mm" << endl;
            outFile << "New thickness: " << thicknew << " mm" << endl;
            outFile << "---------------------------------" << endl;
        }
    }
    else
    {
        //Thickness can't exceed 16, thus it will display an error
        cout << "\nERROR: Workpiece thickness exceeded machine capability." << endl;
    }
}

void bending(ofstream& outFile)//Function to perform bending calculations
{
    cout << "----------------------------------" << endl;
    cout << "You have selected bending." << endl;
    // Getting value input from the user
    double length = getPositiveInput("Enter workpiece length (cm): ");
    double bendPoint = getPositiveInput("Enter the point of bend of the workpiece (cm): ");
    double bendAngle = getPositiveInput("Enter angle bend of the workpiece (degrees): "); 
    // Making sure if the point of bend is valid
    if (bendPoint > length)
    {
        cout << "ERROR! The point of bend can't be greater than the length of the workpiece." << endl;
    } 
    else if (bendPoint <= length)
    {
    // Calculating the remaining length and effective length after the bending
        double remainingLength = length - bendPoint;
        double effectiveLength = bendPoint + remainingLength * cos(degreeToRadian(bendAngle));
    // Displaying results to the console
        cout << "Remaining length of the workpiece after bending: " << remainingLength << " cm" << endl;
        cout << "Effective length of the workpiece after bending: " << effectiveLength << " cm" << endl;

        // Write results to output file
        outFile << "Bending Results:" << endl;
        outFile << "Length of workpiece: " << length << " cm" << endl;
        outFile << "Point of bend: " << bendPoint << " cm" << endl;
        outFile << "Bend angle: " << bendAngle << " degrees" << endl;
        outFile << "Remaining length after bend: " << remainingLength << " cm" << endl;
        outFile << "Effective length after bend: " << effectiveLength << " cm" << endl;
        outFile << "---------------------------------" << endl;
    }
}

// Function to get positive input from the user
double getPositiveInput(const string& prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0)// Checking if the input is valid
        {
            cin.clear();// clearing error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// ignore invalid input
            cout << "ERROR!!! INVALID INPUT. PLEASE ENTER A POSITIVE NUMBER." << endl;
        }
        else
        {
            break;// Break the loop if the input is valid
        }
    }
    return value;// Returning the valid input value
}

//Calculation function for degree
double degreeToRadian(double degree)
{
    return degree * M_PI / 180.0;
}

void cutting(ofstream& outFile)
{
    cout << "----------------------------------" << endl;
    cout << "You have selected cutting." << endl;
    int totalLengths;
    int numPieces;
    
    // Asking user to enter total length
    cout << "Enter the total length of the steel beam/rod (in cm): ";
    cin >> totalLengths;
    
    // Asking user to enter the number of pieces 
    cout << "Enter the number of pieces to cut: ";
    cin >> numPieces;
    
    // An array is created to store the length of each piece
    int pieceLengths[numPieces];
    
    // Asking the user to input the lengths of each piece
    int sumLengths = 0;
    for (int i = 0; i < numPieces; i++)
    {
        cout << "Enter the length for piece " << i + 1 << " (in cm): ";
        cin >> pieceLengths[i];
        sumLengths += pieceLengths[i];
    }
    
    // Formula to calculate leftover steel
    int leftover = totalLengths - sumLengths;
    
    // Parameter to see if the pieces are more than the total length
    if (leftover < 0)
    {
        cout << "Error: The total length of the pieces is more than the length of the steel beam." << endl;
    }
    else
    {
        // Displaying the lengths of each piece and leftover steel
        cout << "\nLengths of the pieces: ";
        for (int i = 0; i < numPieces; ++i) //for loop is a very useful for accessing array elements
        {
            cout << pieceLengths[i];
            if (i < numPieces - 1)
            {
                cout << ", ";
            }
        }
        cout << "\nThere will be " << leftover << " cm of steel left over." << endl;

        // Write results to file (outFile)
        outFile << "Cutting Results:" << endl;
        outFile << "Total length of steel beam: " << totalLengths << " cm" << endl;
        outFile << "Number of pieces: " << numPieces << endl;
        outFile << "Lengths of pieces: ";
        for (int i = 0; i < numPieces; ++i)
        {
            outFile << pieceLengths[i];
            if (i < numPieces - 1)
            {
                outFile << ", ";
            }
        }
        outFile << endl;
        outFile << "Leftover steel: " << leftover << " cm" << endl;
        outFile << "---------------------------------" << endl;
    }
}