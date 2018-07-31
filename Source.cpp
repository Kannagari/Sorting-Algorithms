#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

//All sorting algorithms are in ascending order

void printHelper(vector<int> v) // Takes a single vector as a parameter and prints the contents
{
	for (int i = 0; i <=9; i++) //For every index in the vector parameter
		cout << v[i] << " "; // Print out the value at that index


}

vector<int> populateVector() //Returns a vector filled with random integers
{
	//Ask the user to pick the seed for the random numbers
	int seed;
	cout << "Pick a random seed value: ";
	cin >> seed;

	vector<int> v; // Create the vector to contain the randomized values
	srand(seed);

	for (int i = 0; i < 10; i++) // Generate random numbers to populate the vector
		v.push_back(rand() % 100); // Insert random numbers to the vector

	return v;
}

vector<int> insertionSort(vector<int> ins, int n)
{
	//Worst and Average case time complexity: O(N^2)
	//Similar to sorting a hand of cards while you hold them in your hands
	for (int i = 1; i < n; i++) //For every value inside the vector, starting at index 1
	{
		int j = i; //Keep a friend to track the places behind the current iteration

		while(j > 0 && ins[j - 1] > ins[j]) //While the tracking friend is > 0 and the previous index value is > the current index value
		{
			//Swap them
			int temp = ins[j];
			ins[j] = ins[j - 1];
			ins[j - 1] = temp;
			j--; //Decrement j to check all values in the vector
		}
	}


	return ins;

}

vector<int> bubbleSort(vector<int> bub, int n)
{
	//Worst and Average time complexity: O(N^2)
	//Compares values to the next value in order, letting the heavier numbers "bubble" up towards the end of the vector
	for(int i = 0; i < n - 1; i++) // For every element in the vector
		for(int j = 0; j < n - i - 1; j++) // Check the current value versus all the values after it
			if (bub[j] > bub[j+1]) // If the current value is greater than the one after it
			{
				//Swap them
				int temp = bub[j+1];
				bub[j+1] = bub[j];
				bub[j] = temp;


			}


	return bub;

}

vector<int> selectionSort(vector<int> sel, int n)
{
	//Worst and Average time complexity: O(N^2)
	//This essentially builds the array in order, piece by piece as you go
	for (int i = 0; i < n - 1; i++) //For every element in the array
	{
		int minLoc = i; //Call the current index the location of the smallest value
		for (int j = i + 1; j < n; j++) //For all the other elements in the array
			if (sel[j] < sel[minLoc]) // Compare to truly find the smallest value location
				minLoc = j;

		//Swap the smallest value location with the current location of i
		
		int temp = sel[minLoc];
		sel[minLoc] = sel[i];
		sel[i] = temp;
	}

	return sel;

}

int quickPart(vector<int> &quick, int low, int high)
{
	//Helper function of quickSort
	//Worst Case time complexity: O(N^2)
	//Average Case Time Complexity: O(N log(N))

	int i = low - 1; //Establish a low marker
	int pivot = quick[high]; //Create your pivot, in this case its the rightmost index in the vector

	for (int j = low; j <= high - 1; j++) // From the lowest index in the passed array
	{
		if (quick[j] <= pivot) // If the current index value is < the pivot
		{
			//Swap that value with the value at index i
			i++;
			int temp = quick[j];
			quick[j] = quick[i];
			quick[i] = temp;
		}
	}

	//After all swaps, make sure to put the pivot in its place
	int temp = quick[i+1];
	quick[i + 1] = quick[high];
	quick[high] = temp;

	//Return the updated location of i
	//This will serve as the division for the recursive calls of quickSort
	return(i + 1); 
}

vector<int> quickSort(vector<int> &quick, int low, int high)
{

	if (low < high)
	{
		int x = quickPart(quick, low, high); //X is the location of the previous pivot
		quickSort(quick, low, x - 1); //Recursively quickSort the subarray before the previous pivot
		quickSort(quick, x + 1, high); //Recursively quickSort the subarray after the previous pivot


	}


	return quick;

}

void merge(vector<int> &mer, int left, int Lmid, int Rmid, int right)
{
	//Helper function of mergeSort
	//Worst and Average case Time Complexity: O(N log(N))

	int length = right - left + 1; //Calculate the length of the current vector being operated on

	vector<int> temp(length); //Create a temporary vector of the calculated size
	int l = left; //
	int r = Rmid; //
	for (int i = 0; i < length; i++) //For every index in the current vector
	{
		//Build the temp vector
		if (l > Lmid) 
			temp[i] = mer[r++];

		else if (r > right)
			temp[i] = mer[l++];
		else if (mer[l] <= mer[r])
			temp[i] = mer[l++];
		else
			temp[i] = mer[r++];
	}
	
	//Set all values in the passed vector equal to the values of the sorted temp vector
	for (int i = 0; i < length; i++)
		mer[left++] = temp[i];
}

vector<int> mergeSort(vector<int> &mer, int left, int right)
{
	if (left < right)
	{
		// Calculate the value of mid, so you can split the big vector into smaller sub-vectors
		//"Divide and Conquer" algorithm
		int mid = (left + right) / 2; 

		mergeSort(mer, left, mid); //Recursively call for the lower sub-array
		mergeSort(mer, mid + 1, right); //Recursively call for the upper sub-array

		merge(mer, left, mid, mid+1, right);

	}
	
	return mer;


}

int main()
{

	vector<int> V; //Create an initial vector to be sorted, will be filled with random numbers
	vector<int> cat; //Create a vector to catch the returning, sorted vectors

	V = populateVector(); // Populate the vector with random numbers
	int N = V.size(); // Get the number of elements in the vector
	cout << "The size of the vector is: " << N << endl;
	cout << "\n\n";

	cout << "The initial vector is: \n";
	printHelper(V); // Print the vector
	cout << "\n";

	cout << "Insertion Sort Test\n";
	cat = insertionSort(V, N); // Call insertion sort, returning the sorted vector
	printHelper(cat); //Print the sorted vector
	cout << "\n";
	system("pause");
	cout << "\n\n";

	V = populateVector(); // Re-randomize the vector for the next sort
	N = V.size(); // Get the number of elements in the vector
	cout << "The size of the vector is: " << N << endl;
	cout << "\n\n";

	cout << "The initial vector is: \n";
	printHelper(V);
	cout << "\n";

	cout << "Bubble Sort Test\n";
	cat = bubbleSort(V, N); // Call Bubble sort, and catch the returned, sorted vector
	printHelper(cat);// Print the sorted vector.
	cout << "\n";
	system("pause");
	cout << "\n\n";
	

	V = populateVector(); // Re-randomize the vector for the next sort
	N = V.size(); // Get the number of elements in the vector
	cout << "The size of the vector is: " << N << endl;
	cout << "\n\n";

	cout << "The initial vector is: \n";
	printHelper(V);
	cout << "\n";

	cout << "Selection Sort Test\n";
	cat = selectionSort(V, N); //Call selection sort, catching the returned, sorted vector
	printHelper(cat); // Print the sorted vector.
	cout << "\n";
	system("pause");
	cout << "\n\n";


	V = populateVector(); // Re-randomize the vector for the next sort
	N = V.size(); // Get the number of elements in the vector
	cout << "The size of the vector is: " << N << endl;
	cout << "\n\n";
	int low = 0; //Value used for quick sort
	int high = N - 1; // Pivot location used in quick sort


	cout << "The initial vector is: \n";
	printHelper(V);
	cout << "\n";

	cout << "Testing Quick Sort\n";
	cat = quickSort(V, low, high); //Calls quickSort and catches the returned, sorted vector
	printHelper(cat); // Print the sorted vector.
	cout << "\n";
	system("pause");
	cout << "\n\n";


	V = populateVector(); // Re-randomize the vector for the next sort
	N = V.size(); // Get the number of elements in the vector
	cout << "The size of the vector is: " << N << endl;
	cout << "\n\n";

	cout << "The initial vector is: \n";
	printHelper(V);
	cout << "\n";

	cout << "Testing Merge Sort\n";
	cat = mergeSort(V, low, high); //Call mergeSort, catching the returned, sorted vector.
	printHelper(cat); // Print the sorted vector.
	cout << "\n";
	system("pause");


	return 0;
}