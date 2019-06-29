#ifndef Business_H
#define Business_H

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

#include "LinkedList.h"
#include "Reservation.h"
#include "Day.h"

using namespace std;

class Business{
	private:
		vector<Day> Schedules; // Stores all the schedules for the next 7 days
		LinkedList<Reservation> AllReservations; // Stores all the reservations based on dates
		LinkedList<string> DateList; // Stores dates from today up to next week
		LinkedList<string> TimeList; // Stores time availables (for easy access)
		
	public:
		// Constructor
		Business();
		~Business();
		
		// Read and Write
		void WriteFile();
		void ReadFile();
		
		// LL methods
		void viewDateList();
		void viewTimeList(int index);
		int getDateIndex(string date);
		int getTimeIndex(string time);
		void viewAllReservations();
		void viewReservationsDate(string date); // Show reservations from that date
		
		// Calling methods from Day.h
		int getSeatsLeft(int dateindex, int timeindex);
		void viewSeats(int dateindex, int timeindex);
		void bookSeat(int dateindex, int timeindex, int seatnoindex);
		void cancelSeat(int dateindex, int timeindex, int seatnoindex);
		bool checkSeat(int dateindex, int timeindex, int seatnoindex);
		
		// Utility Methods
		void initDate();
		void initTime();
		int checkMonth(int day, int month, int year);
		bool isAlpha(string str);
		
		// CRUD methods
		void newReservation();
		void viewReservations();
		void editReservation();
		void cancelReservation();
		
		void run();
};

// Constructor Methods
Business::Business(){
	initDate();
	initTime();
	
	// Setting up Schedules
	Day day1(DateList.getData(0));
	Schedules.push_back(day1);
	Day day2(DateList.getData(1));
	Schedules.push_back(day2);
	Day day3(DateList.getData(2));
	Schedules.push_back(day3);
	Day day4(DateList.getData(3));
	Schedules.push_back(day4);
	Day day5(DateList.getData(4));
	Schedules.push_back(day5);
	Day day6(DateList.getData(5));
	Schedules.push_back(day6);
	Day day7(DateList.getData(6));
	Schedules.push_back(day7);
}

Business::~Business(){
	vector<Day>().swap(Schedules);
}

// Write and Read
void Business::WriteFile(){
	ofstream outFile("data.txt");
	
	if (outFile.fail()){
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	
	if (outFile.is_open()){
		for (LinkedList<Reservation>::Iterator it = AllReservations.begin(); it != AllReservations.end(); it++){
			string first_name = (*it).GetFirstName();
			string last_name = (*it).GetLastName();
			string date = (*it).GetDate();
			string time = (*it).GetTime();
			int seatno = (*it).GetSeatNo();
			outFile << first_name << " " << last_name << " " << date << " " << time << " " << seatno << endl;
		}
	} else {
		cout << "Cannot open file" << endl;
	}
	
}

void Business::ReadFile(){
	int dateindex, timeindex;
	string first_name, last_name, date, time;
	int seatno;
	
	ifstream inFile("data.txt");
	
	if (inFile.fail()){
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	
	if (inFile.is_open()){
		while(inFile >> first_name >> last_name >> date >> time >> seatno) {
			if (getDateIndex(date) != -1){
				dateindex = getDateIndex(date);
				timeindex = getTimeIndex(time);
				bookSeat(dateindex, timeindex, seatno-1);
				Reservation tempData(first_name, last_name, date, time, seatno);
				AllReservations.addNode(tempData);
			}
		}
		
	} else {
		cout << "Cannot open file" << endl;
	}
	
}

// LL Methods
void Business::viewDateList(){
	int counter = 1;
	for (LinkedList<string>::Iterator it = DateList.begin(); it != DateList.end(); it++){
		cout << "[" << counter++ << "] " << *it << endl;
	}
}

void Business::viewTimeList(int index){
	int counter = 1;
	for(LinkedList<string>::Iterator it = TimeList.begin(); it != TimeList.end(); it++){
		cout << "[" << counter++ << "] " << *it << endl;
	}
}

int Business::getDateIndex(string date){
	int index = 0;
	for (LinkedList<string>::Iterator it = DateList.begin(); it != DateList.end(); it++){
		if (date == (*it)){
			return index;
		}
		index++;
	}
	return -1;
}

int Business::getTimeIndex(string time){
	int index = 0;
	for(LinkedList<string>::Iterator it = TimeList.begin(); it != TimeList.end(); it++){
		if (time == (*it)){
			return index;
		}
		index++;
	}
}

void Business::viewAllReservations(){
	int counter = 1;
	for(LinkedList<Reservation>::Iterator it = AllReservations.begin(); it != AllReservations.end(); it++){
		cout << "[" << counter++ << "] " << "Name: " << (*it).GetName() << "    Date: " << (*it).GetDate() << "    Time: " << (*it).GetTime() 
		<< "    Seat No: " << to_string((*it).GetSeatNo()) << endl;
	}
	if (counter == 1){ // No Reservations yet;
		cout << "No reservations available yet..." << endl;
	}
}

void Business::viewReservationsDate(string date){
	int counter = 1;
	for(LinkedList<Reservation>::Iterator it = AllReservations.begin(); it != AllReservations.end(); it++){
		if (date == (*it).GetDate()){
			cout << "[" << counter++ << "] " << "Name: " << (*it).GetName() << "    Date: " << (*it).GetDate() << "    Time: " << (*it).GetTime() 
			<< "    Seat No: " << to_string((*it).GetSeatNo()) << endl;	
		}
	}
	if (counter == 1){
		cout << "No reservations made on that date yet..." << endl;
	}
}

// Call methods from Day.h
int Business::getSeatsLeft(int dateindex, int timeindex){
	return Schedules.at(dateindex).checkSeatsAvailable(TimeList.getData(timeindex));
}

void Business::viewSeats(int dateindex, int timeindex){
	Schedules.at(dateindex).printSeats(TimeList.getData(timeindex));
}

void Business::bookSeat(int dateindex, int timeindex, int seatnoindex){
	Schedules.at(dateindex).reserveSeat(TimeList.getData(timeindex), seatnoindex);
}

void Business::cancelSeat(int dateindex, int timeindex, int seatnoindex){
	Schedules.at(dateindex).cancelSeat(TimeList.getData(timeindex), seatnoindex);
}

bool Business::checkSeat(int dateindex, int timeindex, int seatnoindex){
	if (Schedules.at(dateindex).checkSeat(TimeList.getData(timeindex), seatnoindex)){
		return false;
	} else {
		return true;
	}
}

// Utility Methods
void Business::initDate(){
	// Get current local time
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	string date;
	
	for (int i = 0; i < 7; i++){
		if(i != 0){
			day, month, year = checkMonth(day, month, year);
		}
		// Validate the date
		if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
			if(day > 31){
				if(month != 12){	
					day = 1;
					month++;
				} else{
					day = 1;
					month = 1;
					year++;
				}
			}
		}
		if(month == 4 || month == 6 || month == 9 || month == 11){
			if(day > 30){
				day = 1;
				month++;
			}
		}
		if(month == 2){
			if(day > 28){
				day = 1;
				month++;
			}
		}
		date = to_string(day++) + "/" + to_string(month) + "/" + to_string(year);
		DateList.addNode(date);
	}
}

void Business::initTime(){
	TimeList.addNode("08.00");
	TimeList.addNode("10.00");
	TimeList.addNode("14.00");
	TimeList.addNode("18.00");
	TimeList.addNode("20.00");
}

int Business::checkMonth(int day, int month, int year){
    int dDay = day, dMonth = month, dYear = year;
	
	if(month > 12) {
        dMonth = 1;
        dYear++;
    }
    
    switch(dMonth) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(day > 31) {
                dDay = 1;
                dMonth++;
                checkMonth(dDay, dMonth, dYear);
            }
            break;
    }
    
    switch(dMonth) {
        case 2:
            if(day > 28) {
                dDay = 1;
                dMonth++;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(day > 30) {
                dDay = 1;
                dMonth++;
            }
            break;        
	}
    return dDay, dMonth, dYear;
}

bool Business::isAlpha(string str){
	for (int i = 0; i < str.length(); i++){
		if (!isalpha(str[i])){
			return false;
		}
	}
	return true;
}


// CRUD Methods
void Business::newReservation(){
	int date_input, time_input; // index based inputs
	string date, time, first_name, last_name;
	int seatno;
	
	cout << endl;
	cout << "------- Shuttlezz New Reservation Menu -------" << endl;
	cout << "Important Notes: Reservation can only be made up to 7 days prior." << endl;
	
	// Date Input
	cout << "Available Dates:" << endl;
	viewDateList();
	cout << "Choose Date [1..7]: "; cin >> date_input;
	while(!cin || date_input < 1 || date_input > 7){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
			cout << "Please input between 1 to 7..." << endl;
		}
		cout << "Choose Date [1..7]: "; cin >> date_input;
	}
	cout << endl;
	date = DateList.getData(date_input-1);
	
	// Time Input
	cout << "Available Time: " << endl;
	viewTimeList(date_input-1);
	cout << "Choose Time [1..5]: "; cin >> time_input;
	while (!cin || time_input < 1 || time_input > 5){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
				cout << "Please input between 1 to 5..." << endl;
		}
		cout << "Choose Date [1..5]: "; cin >> date_input;
	}
	cout << endl;
	time = TimeList.getData(time_input-1);
	
	// Show no of seats available
	int seatsleft = getSeatsLeft(date_input-1, time_input-1);
	cout << "No of Avalable Seats: " << seatsleft << endl;
	if (seatsleft = 0){
		cout << "Theres no more seats left, please reserve with another schedule" << endl;
		return;
	}
	
	// Choose Seating Number
	cout << "Seats Available: ([!!] means seat are occupied)" << endl;
	viewSeats(date_input-1, time_input-1);
	cout << "Choose Seat [1..20] :"; cin >> seatno;
	while (!cin || seatno > 20 || seatno < 1 || checkSeat(date_input-1, time_input-1, seatno-1)){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else if(seatno > 20 || seatno < 1){
			cout << "Seat No must be between 1 till 20!" << endl;
		} else if (checkSeat(date_input-1, time_input-1, seatno-1)){
			cout << "Seat has been occupied..." << endl;
		}
		cout << "Choose Seat [1..20] :"; cin >> seatno;
	}
	cout << endl;
	bookSeat(date_input-1, time_input-1, seatno-1);
	
	// Getting Customer's info
	cout << "Please Fill in the Customer's Information" << endl;
	do{
		cout << "First Name: "; cin >> first_name;
		cout << "Last Name: "; cin >> last_name;
		if(!isAlpha(first_name) || !isAlpha(last_name)){
			cout << "Name must be alphabetic!" << endl;	
		}
	} while(!isAlpha(first_name) || !isAlpha(last_name));
	printf("Seat %i reserved for %s %s", seatno, first_name.c_str(), last_name.c_str()); cout << endl;
	
	Reservation customer(first_name, last_name, date, time, seatno);
	AllReservations.addNode(customer);
}

void Business::viewReservations(){
	int date_input; // index based inputs
	string date;
	string menu_input;
	
	cout << endl;
	cout << "------- Shuttlezz View Reservation Menu -------" << endl;
	
	// Ask if view all or view by date
	cout << "[1] View All Reservations\n[2] View By Date" << endl;
	cout << "Choose Option [1..2] : "; cin >> menu_input;
	if (menu_input == "1"){
		viewAllReservations();
	} else if (menu_input == "2"){
		// Date Input
		cout << "Available Dates:" << endl;
		viewDateList();
		cout << "Choose Date [1..7]: "; cin >> date_input;
		while(!cin || date_input < 1 || date_input > 7){
			if (!cin){
				cout << "Please input an integer..." << endl;
				cin.clear();
				cin.ignore();
			} else {
				cout << "Please input between 1 to 7..." << endl;
			}
			cout << "Choose Date [1..7]: "; cin >> date_input;
		}
		cout << endl;
		date = DateList.getData(date_input-1);
		viewReservationsDate(date);
		
	} else {
		cout << "wrong input" << endl;
		return;
	}
}

void Business::editReservation(){
	int date_input, reservation_input, dateindex, timeindex;
	string date, time, first_name, last_name;
	int oldseatno, newseatno;
	
	cout << endl;
	cout << "------- Shuttlezz Edit Reservation Menu -------" << endl;
	cout << "Important Notes: Only name and seat numbers are editable." << endl;
	
	// Date Input
	cout << "Available Dates:" << endl;
	viewDateList();
	cout << "Choose Date [1..7]: "; cin >> date_input;
	while(!cin || date_input < 1 || date_input > 7){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
			cout << "Please input between 1 to 7..." << endl;
		}
		cout << "Choose Date [1..7]: "; cin >> date_input;
	}
	cout << endl;
	date = DateList.getData(date_input-1);
	
	// Printing Reservations for that particular date
	int index = 0, counter = 1;
	vector<int> temp; // stores index of reservations
	for(LinkedList<Reservation>::Iterator it = AllReservations.begin(); it != AllReservations.end(); it++){
		if (date == (*it).GetDate()){
			cout << "[" << counter++ << "] " << "Name: " << (*it).GetName() << "    Date: " << (*it).GetDate() << "    Time: " << (*it).GetTime() 
			<< "    Seat No: " << to_string((*it).GetSeatNo()) << endl;
			temp.push_back(index);
		}
		index++;
	}
	if (counter == 1){
		cout << "No reservations made on that date yet..." << endl;
		vector<int>().swap(temp);
		return;
	}
	
	// Choosing which reservation
	cout << "Choose Option: "; cin >> reservation_input;
	while (!cin || reservation_input < 1 || reservation_input > (counter-1)){
		cout << "test";
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
			cout << "Number must be between " << 1 << " to " << counter-1 << endl;
		}
		cout << "Choose Option: "; cin >> reservation_input;
	}
	index = temp.at(reservation_input-1);
	vector<int>().swap(temp);
	
	// Getting Old Data and Reset seat value
	time = AllReservations.getData(index).GetTime();
	oldseatno = AllReservations.getData(index).GetSeatNo();
	Schedules.at(date_input-1).cancelSeat(time, oldseatno-1);
	
	// Getting index of reservation date and time;
	dateindex = getDateIndex(date);
	timeindex = getTimeIndex(time);
	
	// Choose Seating Number
	cout << "Seats Available: ([!!] means seat are occupied)" << endl;
	viewSeats(dateindex, timeindex);
	cout << "Choose Seat [1..20] :"; cin >> newseatno;
	while (!cin || newseatno > 20 || newseatno < 1 || checkSeat(dateindex, timeindex, newseatno-1)){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else if(newseatno > 20 || newseatno < 1){
			cout << "Seat No must be between 1 till 20!" << endl;
		} else if (checkSeat(dateindex, timeindex, newseatno-1)){
			cout << "Seat has been occupied..." << endl;
		}
		cout << "Choose Seat [1..20] :"; cin >> newseatno;
	}
	cout << endl;
	bookSeat(dateindex, timeindex, newseatno-1);
	
	// Getting Customer's info
	cout << "Please Fill in the Customer's Information" << endl;
	do{
		cout << "First Name: "; cin >> first_name;
		cout << "Last Name: "; cin >> last_name;
		if(!isAlpha(first_name) || !isAlpha(last_name)){
			cout << "Name must be alphabetic!" << endl;	
		}
	} while(!isAlpha(first_name) || !isAlpha(last_name));
	printf("Seat %i reserved for %s %s", newseatno, first_name.c_str(), last_name.c_str()); cout << endl;
	
	AllReservations.deleteNode(index);
	Reservation newData(first_name, last_name, date, time, newseatno);
	AllReservations.addNode(newData);
}

void Business::cancelReservation(){
	int date_input, reservation_input; // index based inputs
	string date, time;
	int seatno = 0;
	
	cout << endl;
	cout << "------- Shuttlezz Cancel Reservation Menu -------" << endl;
	
	// Date Input
	cout << "Available Dates:" << endl;
	viewDateList();
	cout << "Choose Date [1..7]: "; cin >> date_input;
	while(!cin || date_input < 1 || date_input > 7){
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
			cout << "Please input between 1 to 7..." << endl;
		}
		cout << "Choose Date [1..7]: "; cin >> date_input;
	}
	cout << endl;
	date = DateList.getData(date_input-1);
	
	// Printing Reservations for that particular date
	int index = 0, counter = 1;
	vector<int> temp; // stores index of reservations
	for(LinkedList<Reservation>::Iterator it = AllReservations.begin(); it != AllReservations.end(); it++){
		if (date == (*it).GetDate()){
			cout << "[" << counter++ << "] " << "Name: " << (*it).GetName() << "    Date: " << (*it).GetDate() << "    Time: " << (*it).GetTime() 
			<< "    Seat No: " << to_string((*it).GetSeatNo()) << endl;
			temp.push_back(index);
		}
		index++;
	}
	if (counter == 1){
		cout << "No reservations made on that date yet..." << endl;
		vector<int>().swap(temp);
		return;
	}
	
	// Choosing which reservation
	cout << "Choose Option: "; cin >> reservation_input;
	while (!cin || reservation_input < 1 || reservation_input > (counter-1)){
		cout << "test";
		if (!cin){
			cout << "Please input an integer..." << endl;
			cin.clear();
			cin.ignore();
		} else {
			cout << "Number must be between " << 1 << " to " << counter-1 << endl;
		}
		cout << "Choose Option: "; cin >> reservation_input;
	}
	index = temp.at(reservation_input-1);
	vector<int>().swap(temp);
	
	// Getting data
	time = AllReservations.getData(index).GetTime();
	seatno = AllReservations.getData(index).GetSeatNo();
	
	Schedules.at(date_input-1).cancelSeat(time, seatno-1); // reset seat value in Day.h
	AllReservations.deleteNode(index); // Delete reservation from LL
}


// Main function to run the program
void Business::run(){
	ReadFile();
	while(true){
		int menu_input;
		system("cls");
		cout << "------- Welcome to Shuttlezz -------" << endl;
		cout << "[1] New Reservation\n[2] View Reservations\n[3] Cancel Reservation\n[4] Edit Reservation\n[0] Exit Application" << endl;
		cout << "Choose Option [0..4] : "; cin >> menu_input;
		if (menu_input == 0){
			WriteFile();
			return;
		} else if (menu_input == 1){
			newReservation();
		} else if (menu_input == 2){
			viewReservations();
		} else if (menu_input == 3){
			cancelReservation();
		} else if (menu_input == 4){
			editReservation();
		} else {
			cout << "Wrong Input" << endl;
		}
		cout << "Press Enter to continue..." << endl;
		cin.sync();
		cin.ignore();
	}
}
	
#endif
