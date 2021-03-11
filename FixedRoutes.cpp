#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int n, k, x, y, m;
string name;
vector<pair<string, pair<int,int>>> systemRoutes, temp;
vector<pair<string, pair<int,int>>> usersStations;
int lowX,upX,lowY,upY;

/*
	sort according to x axis 
*/
bool compareX(pair<string, pair<int,int>>  a, pair<string, pair<int,int>>  b) {
    return a.second.first < b.second.first;
}

/*
	sort according to y axis 
*/
bool compareY(pair<string, pair<int,int>>  a, pair<string, pair<int,int>>  b) {
    return a.second.second < b.second.second;
}

/*
	calculate distance between two points
*/
double getDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

int lowerBound(vector<pair<string, pair<int,int>>> v, int x, bool isX) 
{ 
    int mid; 
    int low = 0; 
    int high = v.size(); 
    while (low < high) { 
		mid = low + (high - low) / 2;

		int val = 0;
		if(isX) 
			val = v[mid].second.first;
		else 
			val = v[mid].second.second;

        if (x <= val) { 
            high = mid; 
        } 
        else { 
            low = mid + 1; 
        } 
    } 
    return low; 
} 

int upperBound(vector<pair<string, pair<int,int>>> v, int x, bool isX) 
{ 
    int mid; 
    int low = 0; 
    int high = v.size(); 
    while (low < high) { 
        mid = low + (high - low) / 2; 
		int val = 0;
		if(isX) 
			val = v[mid].second.first;
		else 
			val = v[mid].second.second;
		
        if (x >= val) { 
            low = mid + 1; 
        } 
        else { 
            high = mid; 
        } 
    } 
    return low; 
} 

pair<string,double> getMinDistance(vector<pair<string, pair<int,int>>> v, int l, int r,pair<string, pair<int,int>> usersStation) {
	string s;
	double minDistance = 10000000;
	for(int j = l; j < r; ++j) {
		int x = v[j].second.first;
		int y = v[j].second.second;
		double dist = getDistance(x,y,usersStation.second.first, usersStation.second.second);
		if(dist < minDistance) {
			s = v[j].first;
			minDistance = dist;
		}
	}
	return make_pair(s,minDistance);
}

/*
	check if there are points around user station in distance range
*/
bool isOk(int distance, pair<string, pair<int,int>> userStation) {
	if(distance == 0) return false;
	int tempLowX, tempUpX, tempLowY, tempUpY; 
	int x = userStation.second.first;
	int y = userStation.second.second;
	tempLowX = lowerBound(systemRoutes, x-distance, true);
	tempUpX = upperBound(systemRoutes, x+distance, true);
	tempLowY = lowerBound(temp, y-distance, false);
	tempUpY = upperBound(temp, y+distance, false);

	if((tempUpX-tempLowX)+(tempUpY-tempLowY) != 0) {
		lowX = tempLowX;
		upX = tempUpX;
		lowY = tempLowY;
		upY = tempUpY;
		return true;
	} else {
		return false;
	}
}

void solve() {
    sort(systemRoutes.begin(), systemRoutes.end(), compareX);
    sort(temp.begin(), temp.end(), compareY);
	
	
	for(int i = 0; i < usersStations.size(); ++i) {
		lowX = 0;
		lowY = 0;
		upX = systemRoutes.size();
		upY = systemRoutes.size();
		int distance= 1000000;
		while(isOk(distance, usersStations[i])) {
			distance/=2;
		}
		pair<string, double> ans = make_pair("",10000000);
		
		if(upX-lowX <= upY-lowY) {
			if(upX-lowX!=0)
				ans = getMinDistance(systemRoutes, lowX, upX,usersStations[i]);
			else
				ans = getMinDistance(temp, lowY, upY,usersStations[i]);
		} else {
			if(upY-lowY!=0)
				ans = getMinDistance(temp, lowY, upY,usersStations[i]);
			else
				ans = getMinDistance(systemRoutes, lowX, upX,usersStations[i]);
			
		}
		cout << usersStations[i].first << " " << ans.first << endl;
		
	}
}

void readInput() {
	scanf("%d", &n);
    while (n--) {
        scanf("%d", &k);
        while(k--) {
            cin >> name >> x >> y;
            systemRoutes.push_back(make_pair(name,make_pair(x, y)));
            temp.push_back(make_pair(name,make_pair(x, y)));	
        }
    }
		
    scanf("%d", &m);
    while(m--) {
        cin >> name >> x >> y;
        usersStations.push_back(make_pair(name,make_pair(x, y)));
    }
}

int main() {
  	// freopen("input.in", "rt", stdin);
	readInput();
	solve();
}