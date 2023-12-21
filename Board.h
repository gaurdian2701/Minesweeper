#include "Player.h"

class Board
{
private:
    int rows;
    int cols;
    int playerScore;
    int mineCount;
    std::vector<std::vector<char>> mineMatrix;

    int CheckAdjacents(int rowInput, int colInput)
    {
        int mineNumber = 0;
        for (int i = std::max(0, rowInput - 1); i <= std::min(rows - 1, rowInput + 1); i++)
        {
            for (int j = std::max(0, colInput - 1); j <= std::min(cols - 1, colInput + 1); j++)
            {
                if (mineMatrix[i][j] == 'M')
                    mineNumber += 1;
            }
        }
        return mineNumber;
    }

public:
    Board(int r, int c) : rows(r), cols(c), mineMatrix(r, std::vector<char>(c, ' '))
    {
        playerScore = 0;
        mineCount = 0;
        std::cout << "The mine board is ready!\n";
    }

    int GetRows()
    {
        return rows;
    }

    int GetColumns()
    {
        return cols;
    }

    int GetMineCount()
    {
        return mineCount;
    }

    int GetPlayerScore()
    {
        return playerScore;
    }

    std::vector<std::vector<char>> GetBoard()
    {
        return mineMatrix;
    }

    bool isFilled(int i, int j)
    {
        if(isdigit(mineMatrix[i][j]))
            return true;
        return false;
    }

    void PrintBoard(bool showMines)
    {
        std::cout << "-------------------\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (mineMatrix[i][j] == 'M' && !showMines)
                    std::cout << "|" << ' ';
                else
                    std::cout << "|" << mineMatrix[i][j];
            }
            std::cout << "|\n-------------------\n";
        }
    }

    void UpdateBoard(int rowInput, int colInput)
    {
        int mineNumber = CheckAdjacents(rowInput, colInput);

        if (mineNumber)
            mineMatrix[rowInput][colInput] = mineNumber + '0';

        else
        {
            mineMatrix[rowInput][colInput] = '0';
            for (int i = std::max(0, rowInput - 1); i <= std::min(rows - 1, rowInput + 1); i++)
                for (int j = std::max(0, colInput - 1); j <= std::min(cols - 1, colInput + 1); j++)
                    if (!isdigit(mineMatrix[i][j]))
                        UpdateBoard(i, j);
        }
        playerScore++;
    }

    void FillBoard(std::pair<int, int> input) // Function to fill matrix on first input
    {
        srand(time(0));
        int minefill;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (abs(i - input.first) <= 1 && abs(j - input.second) <= 1)
                    continue;
                minefill = rand() % 5;

                if (minefill == 3)
                {
                    mineMatrix[i][j] = 'M';
                    mineCount++;
                }

                else
                    mineMatrix[i][j] = ' ';
            }
        }
        mineMatrix[input.first][input.second] = '0';
        std::cout << "minecount: " << mineCount << "\n";
    }
};