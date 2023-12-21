#include "Board.h"

class GameController
{
private:
    int revealCount;
    Board *board;
    std::pair<int, int> currentInput;

public:
    GameController()
    {
        revealCount = 0;
        std::cout << "The game has started!\n\n";
    }

    void SetupGame(Player *p)
    {
        currentInput = p->TakeTurn();
        board->FillBoard(currentInput);
        revealCount = board->GetRows() * board->GetColumns() - board->GetMineCount();
        board->UpdateBoard(currentInput.first, currentInput.second);
        board->PrintBoard(false);
    }

    void PrintFinalOutcome(bool won)
    {
        std::string finalmessage = won ? "You won!\n" : "You lost\n";
        std::cout << finalmessage;
        board->PrintBoard(true);
    }

    bool InputValid(int i, int j)
    {
        if (!(i >= 0 && j >= 0 && i <= board->GetRows() - 1 && j <= board->GetColumns() - 1) || board->isFilled(i, j))
        {
            std::cout << "Invalid Input!\n";
            return false;
        }

        return true;
    }

    int WinCheck(std::pair<int, int> currentInput)
    {
        std::cout << "blocks to be revealed: " << revealCount << "\n";
        std::vector<std::vector<char>> currentBoard = board->GetBoard();
        if (board->GetPlayerScore() - revealCount == 0)
        {
            PrintFinalOutcome(true);
            return 1;
        }

        else if (currentBoard[currentInput.first][currentInput.second] == 'M')
        {
            PrintFinalOutcome(false);
            return 0;
        }

        return 2;
    }

    void StartGameLoop(Player *p)
    {
        while (true)
        {
            currentInput = p->TakeTurn();
            if (!InputValid(currentInput.first, currentInput.second))
                continue;
            board->UpdateBoard(currentInput.first, currentInput.second);
            board->PrintBoard(false);
            std::cout << "player score: " << board->GetPlayerScore() << "\n";
            if (WinCheck(currentInput) != 2)
                break;
        }
    }

    void PlayGame()
    {
        Player *p = new Player();
        Board *newBoard = new Board(9, 9);
        board = newBoard;
        SetupGame(p);
        StartGameLoop(p);
    }
};
