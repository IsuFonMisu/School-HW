#include <iostream>
#include <vector>
#include <string>
#include "date.h"

class Sailor
{
	public:
		Sailor()
		{
			id = 0;
			name = "Jane Doe";
			age = 0;
			rank = 0;
		}

		Sailor(int SailorID, string SailorName, double SailorAge, double SailorRank);//

		string sName();
		int sID();
		double sRank();
		double sAge();
	private:
		int id;
		string name;
		double age;
		double rank;
};

class Boat
{
	public:
		Boat()
		{
			id = 0;
			name = "Default";
			color = "Default";
		}

		Boat(int id, string name, string color);//
		int bID();
		string bName();
		string bColor();
	private:
		int id;
		string name;  
		string color;
};

class Reservation
{
	public:
		Reservation()
		{
			Sailor s;
			sailor = s;
			Boat b;
			boat = b;
			Date d(1,1,1900);
			resDate = d;
		}

		Reservation(Sailor mySailor, Boat myBoat, Date myDate); //

		Date get_Date();//
		Sailor get_Sailor();//
		Boat get_Boat();

		// Add here the Print function

		void Print();

	private:
		Date resDate;
		Sailor sailor;
		Boat boat;
};

class Reservations
{
	public:
		// Fill this part with the member functions

		void Display();
		
		// 1. Add a Reservation

		void AddReservation(Reservation reservation);

		// 2. Delete a Reservation

		void DeleteReservations(Boat boat); // if fails, display error**
		void DeleteReservations(Sailor sailor);
		void DeleteReservations(Boat boat, Sailor sailor, Date date);
		// 3.1. Find a Reservation (sailor and boat ids are 0)

		vector<Reservation> FindReservations(Date start, Date end);

		// 3.2. Find a Reservation (only sailor id is 0)

		vector<Reservation> FindReservations(Boat boat, Date date);

		// 3.3. Find a Reservation (only boat id is 0)

		vector<Reservation> FindReservations(Sailor sailor, Date date);



	private:
		vector<Reservation> reservations;
};



