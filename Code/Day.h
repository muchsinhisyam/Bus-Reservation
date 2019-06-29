#ifndef Day_H
#define Day_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Day{
	private:
		string date;
		map<string, vector<int> > Schedule;
	
	public:	
		// Constructor & Destructor
		Day(string date);
		Day(const Day& data);
		
		// Getter
		string getDate();
		
		// Seat Controls
		bool checkSeat(string time, int index);
		void reserveSeat(string time, int index);
		void cancelSeat(string time, int index);
	
		// Utility Methods
		int checkSeatsAvailable(string time);
		void viewTime();
		void printSeats(string time);
		
		// Check Vector inside map
		void checkVector(string time);
};

Day::Day(string date){
	this->date = date;
	
	vector<int> vec;
	vec.assign(20, 0);
	
	this->Schedule["08.00"] = vec;
	this->Schedule["10.00"] = vec;
	this->Schedule["14.00"] = vec;
	this->Schedule["18.00"] = vec;
	this->Schedule["20.00"] = vec;
}

Day::Day(const Day& data){
	this->date = data.date;
	this->Schedule = data.Schedule;
}

string Day::getDate(){
	return date;
}

bool Day::checkSeat(string time, int seatnoindex){
	if (Schedule[time][seatnoindex] == 1){
		return false;
	} else {
		return true;
	}
}

void Day::reserveSeat(string time, int seatnoindex){
	Schedule[time][seatnoindex] = 1;
}

void Day::cancelSeat(string time, int seatnoindex){
	Schedule[time][seatnoindex] = 0;
}

int Day::checkSeatsAvailable(string time){
	int counter = 20;
	for (int i = 0; i < 20; i++){
		if (Schedule[time][i] == 1){
			counter--;
		}
	}
	return counter;
}

void Day::printSeats(string time){
	int counter = 1;
	string temp;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 4; j++){
			// First Row
			if (i == 0){
				if (Schedule[time][counter-1] == 1){
					cout << "[!!][----------]" << endl;
					counter++;
					break;
				} else {
					printf("[%02i][----------]", counter); cout << endl;
					counter++;
					break;
				}
			// Second Row
			} else if (i == 1){
				if (j == 0){
					cout << "    ";
				} else {
					if (Schedule[time][counter-1] == 1){
						if (j == 3){
							cout << "[!!]" << endl;
							counter++;
						} else {
							cout << "[!!]";
							counter++;
						}
					} else {
						if (j == 3){
							printf("[%02i]", counter); cout << endl;
							counter++;
						} else {
							printf("[%02i]", counter);
							counter++;
						}
					}
				}
			} else if (i == 2 || i == 3 || i == 4 || i == 5){
				if (j == 1){
					cout << "    ";
				} else {
					if (Schedule[time][counter-1] == 1){
						if (j == 3){
							cout << "[!!]" << endl;
							counter++;
						} else {
							cout << "[!!]";
							counter++;
						}
					} else {
						if (j == 3){
							printf("[%02i]", counter); cout << endl;
							counter++;
						} else {
							printf("[%02i]", counter);
							counter++;
						}
					}
				}
			// Last row
			} else if (i == 6){
				if (Schedule[time][counter-1] == 1){
					if (j == 3){
						cout << "[!!]" << endl;
						counter++;
					} else {
						cout << "[!!]";
						counter++;
					}
				} else {
					if (j == 3){
						printf("[%02i]", counter); cout << endl;
						counter++;
					} else {
						printf("[%02i]", counter);
						counter++;
					}
				}
			}
		}
	}
}

void Day::checkVector(string time){
	for (int i = 0; i < 20; i++){
		cout << Schedule[time][i] << ", ";
	}
	cout << endl;
}

#endif

