/*
    Author: William Sid (wilsi748)

    Problem solved: Interval cover (common problem, minimal set)

    Time complexity: O(n log n), where n is the number of intervals.

    Instructions:
            cover expects a Interval and you can define it like this:
            Interval interval = Interval(0.0, 2.0, -1);
    
            it will also expect a vector containing Intervals, 
            so add all Intervals you would like to use to cover in a vector.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

/*
    Small interval struct
    @param start:   left side of the interval
    @param end:     right side of the interval
    @param index:   the interval index
*/
struct Interval {
    double _start;
    double _end;
    int _index;
    Interval() : _start(0.0), _end(0.0), _index(-1) {};
    Interval(double start, double end, int index) : _start(start), _end(end), _index(index) {};
    bool operator < (const Interval& i) const { return (_end < i._end); }
    string toString() { return to_string(_start) + " " + to_string(_end) + " " + to_string(_index); } 
};

/*
    It will try to cover the given interval using the vector of "intervals".

    @param interval:    The given @interval to cover
    @param intervals:   The given @intervals that will be used to cover @interval
    return: vector<int> - vector of the indices used to cover the @interval.
*/
vector<int> cover(Interval interval, vector<Interval> intervals)
{
    vector<int> indices;

    sort(intervals.begin(), intervals.end()); // O(n log n)

    // Check for the special case A = B, Left = Right.
    if(interval._start == interval._end)
    {
        for(Interval iv : intervals) { // O(n) worst case
            if(iv._start <= interval._start && iv._end >= interval._end) 
            {
                indices.push_back(iv._index);
                break;
            }
        }
        return indices;
    }
    
    // Find the interval among vector<Interval> that cover as much as possible of the given @interval
    // and add its index to the vector<int> of indices.
    double start = interval._start;
    int i = 0;
    while(start < interval._end) // O(n log n)
    { 
        double best_cover = 0;
        int best_cover_index = -1;

        for(int i = 0; i < intervals.size(); i++) { 
            if(intervals[i]._start <= start) {
                double current_cover = intervals[i]._end - start;
                if(current_cover > best_cover)
                {
                    best_cover = current_cover;
                    best_cover_index = i;
                }
            }

        }
        // If none found return empty
        if(best_cover_index == -1) {
            return vector<int>();
        }
        indices.push_back(intervals[best_cover_index]._index);
        start = intervals[best_cover_index]._end;
        // remove intervals that is unnecessary to check.
        intervals.erase(intervals.begin() + best_cover_index); 
    }
    return indices;
}

int main () 
{
    int n;
    double a, b;
    while(cin >> a >> b >> n) {
        vector<Interval> intervals(n);
        
        for (int i = 0; i < n; i++) 
        {
            double c, d;
            cin >> c >> d;
            intervals.push_back(Interval(c, d, i));
        }
        vector<int> indices = cover(Interval(a, b, -1), intervals);
        
        if(indices.size() == 0) 
        {
            cout << "impossible" << endl;
        } 
        else 
        {
            cout << indices.size() << endl;
            for(auto& i : indices) cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}