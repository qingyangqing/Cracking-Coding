// Qing

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void ChooseMedian (vector<int>& num_list, int front, int back) {
    int a = num_list[front];
    int b = num_list[back-1];
    int c = num_list[front+(back-front-1)/2];
    // if a is median, do nothing
    // if b is median
    if((b<c && a<b) || (b<a && c<b)) {
        num_list[back-1] = num_list[front];
        num_list[front] = b;
    }
    // if c is median
    if((c<a && b<c) || (c<b && a<c)) {
        num_list[front+(back-front-1)/2] = num_list[front];
        num_list[front] = c;
    }
}

// front is the starting index
// back is the ending index + 1
long CountComparisonsQuickSort(vector<int>& num_list, int front, int back) {
    // case only 1 number
    if((back-front)==1) return 0;
    // case more than 1 number
    long counts = back-front-1;
    // choose pivot
    int pivot = num_list[front]; // always the 1st element

    //int pivot = num_list[back-1]; // always the last element
    //num_list[back-1] = num_list[front]; num_list[front] = pivot; // put the pivot at the front

    //ChooseMedian(num_list, front, back); // choose the median as pivot, and put the median at the front
    //int pivot = num_list[front];

    // use in-place partition
    // i is for partition boundary, i.e., the first element larger than pivot
    // j is for iterating the num_list
    int i = front+1; int j = front+1;
    for(; j<back; j++) {
        if(num_list[j]<pivot) { // swap elements at j and i if the one at j is smaller
            int temp = num_list[i];
            num_list[i] = num_list[j]; num_list[j] = temp;
            i++;
        }
    }
    num_list[front] = num_list[i-1]; num_list[i-1] = pivot; // put pivot in the correct position
    // recursive calls
    if((i-1)>front) counts += CountComparisonsQuickSort(num_list, front, i-1);
    if(back>i) counts += CountComparisonsQuickSort(num_list, i, back);

    return counts;
}

int main() {
    ifstream infile("QuickSort.txt");
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course1/assignment3Quicksort/input_dgrcode_15_20.txt");
    //ifstream infile("in.txt");
    int data;
    vector<int> num_list;
    while(infile>>data) {
        num_list.push_back(data);
    }

    long counts = CountComparisonsQuickSort(num_list, 0, num_list.size());
    cout << counts << endl;
    
    ofstream outfile("out.txt");
    for(int i=0; i<num_list.size(); i++) outfile << num_list[i] << endl;

    return 0;
}

