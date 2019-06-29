#ifndef Reservation_H
#define Reservation_H

#include <iostream>

using namespace std;

class Reservation{
	private:
		string first_name;
		string last_name;
		string date;
		string time;
		int seatno;
		
	public:
		// Constructor
		Reservation();
		Reservation(string first_name, string last_name, string date, string time, int seatno);
		
		// Getter Methods
		string GetFirstName();
		string GetLastName();
		string GetName();
		string GetDate();
		string GetTime();
		int GetSeatNo();
		
		// Setter Methods
		void SetFirstName(string first_name);
		void SetLastName(string last_name);
		void SetDate(string date);
		void SetTime(string time);
		void SetSeatNo(int seatno);
		
};


// Constructor
Reservation::Reservation(){
	this->first_name = "";
	this->last_name = "";
	this->date = "";
	this->time = "";
	this->seatno = -1;
}

Reservation::Reservation(string first_name, string last_name, string date, string time, int seatno){
	this->first_name = first_name;
	this->last_name = last_name;
	this->date = date;
	this->time = time;
	this->seatno = seatno;
}

// Getter Methods
string Reservation::GetFirstName(){
	return this->first_name;
}

string Reservation::GetLastName(){
	return this->last_name;
}

string Reservation::GetName(){
	string temp = this->first_name + " " + this->last_name;
	return temp;
}

string Reservation::GetDate(){
	return this->date;
}

string Reservation::GetTime(){
	return this->time;
}

int Reservation::GetSeatNo(){
	return this->seatno;
}

// Setter Methods
void Reservation::SetFirstName(string first_name){
	this->first_name = first_name;
}

void Reservation::SetLastName(string last_name){
	this->last_name = last_name;
}

void Reservation::SetDate(string date){
	this->date = date;
}

void Reservation::SetTime(string time){
	this->time = time;
}

void Reservation::SetSeatNo(int seatno){
	this->seatno = seatno;
}


#endif

