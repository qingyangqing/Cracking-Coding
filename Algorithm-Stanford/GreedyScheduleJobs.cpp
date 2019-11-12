// Qing

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Job {
    int weight;
    int length;
    float priority;
};

// customize the greater function for sorting job list
struct customGreater {
    bool operator() (Job& j1, Job& j2) {
        if(j1.priority>j2.priority) return true;
        if(j1.priority<j2.priority) return false;
        if(j1.priority==j2.priority) {
            if(j1.weight>j2.weight) return true;
            else return false;
        }
    }
};

void print_Job (Job& job) {
    cout << job.weight << ' ' << job.length << ' ' << job.priority << endl;
}

int main () {
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course3/assignment1SchedulingAndMST/questions1And2/input_random_44_10000.txt");
    ifstream infile("jobs.txt");

    int job_num;
    string Line;
    getline(infile, Line);
    stringstream ss(Line);
    ss >> job_num;

    vector<Job> job_list;
    while(getline(infile, Line)) {
        stringstream ss(Line);
        int w, l;
        ss >> w >> l;
        Job job_elem;
        job_elem.weight = w; job_elem.length = l;
        //job_elem.priority = w-l; // use (weight-length) for scheduling
        job_elem.priority = float(w)/float(l); // use (weight/length) for scheduling
        job_list.push_back(job_elem);
    }

    // sort
    sort(job_list.begin(), job_list.end(), customGreater());
    //for(int i=0; i<10; i++) print_Job(job_list[i]);
    // sum of weighted completion time
    long complete_time = 0;
    long weighted_time = 0;
    for(auto job: job_list) {
        complete_time += job.length;
        weighted_time += job.weight*complete_time;
    }

    cout << weighted_time << endl;
    return 0;
}

