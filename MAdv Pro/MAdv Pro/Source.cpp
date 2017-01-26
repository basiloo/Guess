#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Room.h"
#include <fstream>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int main()
{

	std::ifstream room_file("rooms_original.txt");


	std::cout << "\t\t\t\t\t Guess!" << std::endl;
	std::string qMarks(40, '?');
	std::cout << "\t\t\t" << qMarks;
	std::cout << "\n\n";
	std::cout << "\tRules: \n\t1) You can't enter a room twice";
	std::cout << "\n\t2) You need 5 points to win";
	std::cout << "\n\t3) You have 3 guesses before you're kicked out of room";
	std::cout << "\n\t4) Answers will be lowercase and 1 word\n\n" << std::endl;

	Room room[9];


	std::string line;
	int i = 0;
	while (i < 9 && std::getline(room_file, line))
	{
		if (line.empty() || line[0] == ';')
		{
			continue;
		}

		room[i].setCorrectAnswer(line);

		std::getline(room_file, line);
		room[i].setWelcomeMessage(line);

		std::getline(room_file, line);
		room[i].setGuessSuccess(line);

		std::getline(room_file, line);
		room[i].setGuessFailure(line);
		++i;
	}



	int points = 0;
	int lives = 3;
	while (true)
	{
		int guesses = 3;
		DisplayMenu();
		int input;
		std::cin >> input;
		--input;
		for (int i = 0; i < 9; ++i)
		{
			if (input == i)
			{
				if (room[i].getEnteredRoom() == false)
				{
					room[i].setEnteredRoom(true);
					room[i].printWelcomeMessage();
					
					std::string answer;
					
					do
					{
						std::cin >> answer;
						if (answer == room[i].getCorrectAnswer())
						{
							Correct(points, room[i].getGuessSuccess());
							break;
						}
						else
						{
							Wrong(guesses, lives, room[i].getGuessFailure());
						}
					} while (guesses != 0);

				}
				
				else
				{
					std::cout << "You've already entered this room...\n" << std::endl;
					sleep_for(1s);
					break;
				}
			}
		}
	}
	return 0;
}


void DisplayMenu()
{

	std::cout << "Pick a room number 1 - 9." << std::endl << std::endl;
}



void Correct(int& points, std::string quote)
{
	std::cout << "\n" << quote << std::endl << std::endl;
	++points;
	sleep_for(1s);
	if (points > 4)
		Victory();
}

void Wrong(int& guesses, int& lives, std::string quote)
{
	std::cout << "Nope." << std::endl << std::endl;
	--guesses;
	if (guesses == 0)
	{ 
		--lives;
		std::cout << quote << std::endl << std::endl;
		sleep_for(1s);
		if (lives == 0)
			GameOver();
	}
}



void Room::printWelcomeMessage() const
{
	std::cout << "\n\n" << welcome_message_ << std::endl << std::endl;
}
std::string Room::getCorrectAnswer() const
{
	return correct_answer_;
}
bool Room::getEnteredRoom() const
{
	return entered_room_;
}
std::string Room::getGuessSuccess() const
{
	return guess_success_;
}
std::string Room::getGuessFailure() const
{
	return guess_failure_;
}


void Room::setCorrectAnswer(std::string quote)
{
	correct_answer_ = quote;
}

void Room::setWelcomeMessage(std::string quote)
{
	welcome_message_ = quote;
}
void Room::setEnteredRoom(bool room_condition)
{
	entered_room_ = room_condition;
}
void Room::setGuessSuccess(std::string quote)
{
	guess_success_ = quote;
}
void Room::setGuessFailure(std::string quote)
{
	guess_failure_=quote;
}


void Victory()
{
	std::cout << "\a";
	sleep_for(600ms);
	std::cout << "\a";
	sleep_for(600ms);
	std::cout << "\a";
	sleep_for(600ms);
	std::cout << "\a... .... ...";
	sleep_for(2s);

	std::cout << "\n\nCongratulations!!!\n\n";

	while (true) 
		std::cin.get();
}
void GameOver()
{
	std::cout << "\a... .... ...";
	sleep_for(2s);

	std::cout << "\n\nGame Over!!!   (>_< *) \n\n";

	while (true)
		std::cin.get();
}