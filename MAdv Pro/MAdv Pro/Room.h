#ifndef ROOM_H_
#define ROOM_H_

class Room
{
private:
	std::string correct_answer_;
	std::string incorrect_answer_;
	std::string welcome_message_;
	std::string guess_success_;
	std::string guess_failure_;

	bool entered_room_ = false;

public:
	bool getEnteredRoom() const;
	std::string getCorrectAnswer() const;
	void printWelcomeMessage() const;
	std::string getGuessSuccess() const;
	std::string getGuessFailure() const;

	void setEnteredRoom(bool room_condition);
	void setCorrectAnswer(std::string quote);
	void setWelcomeMessage(std::string quote);
	void setGuessSuccess(std::string quote);
	void setGuessFailure(std::string quote);
};
void DisplayMenu();
void Wrong(int& guesses, int& lives, std::string quote);
void Correct(int& points, std::string quote);
void Victory();
void GameOver();




#endif