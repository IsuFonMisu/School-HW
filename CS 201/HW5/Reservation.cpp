#include <iostream>
#include <vector>
#include <string>
#include "Reservation.h"
#include "strutils.h"
using namespace std;

Sailor::Sailor(int SailorID, string SailorName, double SailorAge, double SailorRank){

	id   = SailorID;
	name = SailorName;
	age  = SailorAge;
	rank = SailorRank;
}

Boat::Boat(int BoatID, string BoatName, string BoatColor){

	id    = BoatID;
	name  = BoatName;
	color = BoatColor;
}

Reservation::Reservation(Sailor mySailor, Boat myBoat, Date myDate){

	resDate= myDate;
	sailor = mySailor;
	boat   = myBoat;
}

/////
Date Reservation::get_Date(){
	return resDate;}

Sailor Reservation::get_Sailor(){
	return sailor;}

string Sailor::sName(){
	return name;}

int Sailor::sID(){
	return id;}

int Boat::bID(){
	return id;}

Boat Reservation::get_Boat(){
	return boat;}
double Sailor::sRank(){
	return rank;}
double Sailor::sAge(){
	return age;}
string Boat::bName(){
	return name;}
string Boat::bColor(){
	return color;}

void Reservations::AddReservation(Reservation reservation){ // sort etmeyi unutma !!

	// reservations is just a vector !!


	reservations.push_back(reservation);
	for (int i = reservations.size()-1; i>= 0 ;i--){
		if (i==0){
			reservations[0]=reservation;
			i= -2;
		}

		else if(reservations[i-1].get_Date().Absolute()==reservation.get_Date().Absolute() && reservations[i-1].get_Sailor().sID()==reservation.get_Sailor().sID() && reservations[i-1].get_Boat().bID()==reservation.get_Boat().bID()){
			i= -2;

		}
		else if (reservations[i-1].get_Date().Absolute() < reservation.get_Date().Absolute()){
				reservations[i]=reservation;
				i= -2;
			}
		else if(reservations[i-1].get_Date().Absolute() == reservation.get_Date().Absolute()){

			if (reservations[i-1].get_Sailor().sName() < reservation.get_Sailor().sName()){
				reservations[i] = reservation;
				i = -2;
			}
			else{
				reservations[i]=reservations[i-1];
			}
		}
		else{
			reservations[i]=reservations[i-1];
		}	
		}
}

void Reservations::DeleteReservations(Boat boat){
	bool deleted = false; ///// aptal triplere girme tek tek sil salak herif

	for (unsigned int i = 0; i< reservations.size(); i++){

		if (reservations.size()== i+1  &&  boat.bID() == reservations[i].get_Boat().bID()){
			reservations.pop_back();
		}
		else if(boat.bID()==reservations[i].get_Boat().bID()){
			for (unsigned int k = i; k< reservations.size()-1; k++){
				reservations[k]=reservations[k+1];
			}
			reservations.pop_back();
			deleted=true;
		}
	}
	
	if(deleted==false){
		cout << "Error: Could not delete reservation for boat id " << boat.bID() <<endl<<endl;
	}
}

void Reservations::DeleteReservations(Sailor sailor){
	bool deleted = false; ///// aptal triplere girme tek tek sil salak herif

	for (unsigned int i = 0; i< reservations.size(); i++){

		if (reservations.size()== i+1  &&  sailor.sID() == reservations[i].get_Sailor().sID()){
			reservations.pop_back();
			deleted=true;
		}
		else if(sailor.sID()==reservations[i].get_Sailor().sID()){
			for (unsigned int k = i; k< reservations.size()-1; k++){
				reservations[k]=reservations[k+1];
			}
			reservations.pop_back();
			deleted=true;
		}
	}
	if(deleted==false){
		cout << "Error: Could not delete reservation for sailor id " << sailor.sID() <<endl << endl;
	}
}

void Reservations::DeleteReservations(Boat boat, Sailor sailor, Date date){
	bool deleted=false;

	for (unsigned int i =0; i<reservations.size(); i++){
		
		if (reservations.size()== i+1  
			&&  sailor.sID() == reservations[i].get_Sailor().sID() 
			&& boat.bID()==reservations[i].get_Boat().bID()
			&& date.Absolute() == reservations[i].get_Date().Absolute()){

				reservations.pop_back();
				deleted=true;
		}
		else if(sailor.sID() == reservations[i].get_Sailor().sID() 
			&& boat.bID()==reservations[i].get_Boat().bID()
			&& date.Absolute() == reservations[i].get_Date().Absolute()){

			for (unsigned int k = i; k< reservations.size()-1; k++){
				reservations[k]=reservations[k+1];
			}
			reservations.pop_back();
			deleted=true;
		}
	}
	if(deleted==false){

		string month="", day="";

		if (date.Month()<10) {month += "0" + itoa(date.Month());}
		else { month += itoa(date.Month());}

		if (date.Day()<10) {day += "0" + itoa(date.Day());}
		else { day += itoa(date.Day());}

		cout << "Error: Could not delete reservation \"" << sailor.sID() << " " << boat.bID() << " " << date.Year() << "-" << month << "-" << day << "\"" <<endl << endl;
	}
}

void Reservations::Display(){
	cout <<"-----------" << endl;

	for (int i =0; i < reservations.size(); i++){

		reservations[i].Print();

	}


	cout <<"-----------" << endl;
}


vector<Reservation> Reservations::FindReservations(Date start, Date end){
	vector <Reservation> FoundRes;

	for (unsigned int i = 0; i< reservations.size(); i++){

		if(reservations[i].get_Date().Absolute() >= start.Absolute() && reservations[i].get_Date().Absolute() <= end){ 
			FoundRes.push_back(reservations[i]);
		}
	}
	return FoundRes;
}

vector<Reservation> Reservations::FindReservations(Boat boat, Date date){
	vector<Reservation> FoundRes;
	for (unsigned int i =0; i < reservations.size(); i++){

		if(reservations[i].get_Boat().bID()==boat.bID() && reservations[i].get_Date().Absolute()==date.Absolute()){
			FoundRes.push_back(reservations[i]);
		}
	}
	return FoundRes;
}

vector<Reservation> Reservations::FindReservations(Sailor sailor, Date date){

	vector<Reservation> FoundRes;
	for (unsigned int i =0; i < reservations.size(); i++){

		if(reservations[i].get_Sailor().sID()==sailor.sID() && reservations[i].get_Date().Absolute()==date.Absolute()){
			FoundRes.push_back(reservations[i]);
		}
	}
	return FoundRes;
}

void Reservation::Print(){
	cout << resDate.MonthName() << " " << resDate.Day() << " " << resDate.Year() <<" -> " 
		<< sailor.sName() <<"("<< sailor.sAge()<<","<<sailor.sRank()<<") has reserved "
		<< boat.bName() <<"("<<boat.bColor()<<")"<< endl;
}