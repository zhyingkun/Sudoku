#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdbool.h>

#if defined(SUDOKU_BUILD_AS_DLL)
#if defined(SUDOKU_CORE)
#define SUDOKU_API __declspec(dllexport) // for sudoku.dll
#else
#define SUDOKU_API __declspec(dllimport) // for user who use sudoku.dll, with SUDOKU_BUILD_AS_DLL
#endif
#else
#define SUDOKU_API extern
#endif

// 9*9*2:num+' ', 9*2:every line has ' '*2, 9:every line has '\n', 2*'\n'+'\0'
#define RESULT_BUFFER_SIZE (9 * 9 * 2 + 9 * 2 + 9 + 2 + 1)
#define BOARD_SIZE (9 * 9)

// row col: 9, block panel: 3*3, board: 9*9
typedef struct Sudoku Sudoku;
typedef enum SolveType {
  None = 0,
  GridOnlyOnePosibility,
  RowNumberOnlyOneGrid,
  ColNumberOnlyOneGrid,
  BlockNumberOnlyOneGrid
} SolveType;
typedef enum ImproveType {
  DoNotImprove = 0,

  Row2GridWith2Posibility,
  Col2GridWith2Posibility,
  Block2GridWith2Posibility,

  Row3GridWith3Posibility,
  Col3GridWith3Posibility,
  Block3GridWith3Posibility,

  Row2NumberIn2Grid,
  Col2NumberIn2Grid,
  Block2NumberIn2Grid,

  Row3NumberIn3Grid,
  Col3NumberIn3Grid,
  Block3NumberIn3Grid,

  InBlockNumberInOneRow,
  InBlockNumberInOneCol,

  InRowNumberInBlock,
  InColNumberInBlock,

  TwoRowOneNumberInTwoCol,
  TwoColOneNumberInTwoRow,

  ThreeRowOneNumberInThreeCol,
  ThreeColOneNumberInThreeRow
} ImproveType;
typedef struct SolveProcedure {
  ImproveType type;
  int gridOneX; // [1, 9]
  int gridOneY;
  int gridTwoX;
  int gridTwoY;
  int gridThreeX;
  int gridThreeY;
  int numberOne; // [1, 9]
  int numberTwo;
  int numberThree;
  int panelRow; // [1, 3]
  int panelCol;
  int number; // [1, 9]
  int line; // [1, 9]
  int rowOne; // [1, 9]
  int rowTwo;
  int rowThree;
  int colOne;
  int colTwo;
  int colThree;
} SolveProcedure;

// row and col are in the range of 1-9
typedef int (*SudokuReadData)(void* data, int row, int col);
// row col and value are in the range of 1-9
typedef void (*SudokuWriteData)(void* data, int row, int col, int value, SolveType type);
typedef void (*SolveProcessCallback)(void* data, SolveProcedure* proc);
// ans is a null terminate char array
typedef void (*SudokuAnswerCallback)(void* data, const char* ans);

SUDOKU_API Sudoku* CreateSudoku(SudokuReadData readFunc, SudokuWriteData writeFunc, SolveProcessCallback procCallback,
                                void* data);
SUDOKU_API void DestroySudoku(Sudoku* sudo);
SUDOKU_API bool VerifySudoku(Sudoku* sudo);
SUDOKU_API int GetKnownCount(Sudoku* sudo);
// buffer must has size of RESULT_BUFFER_SIZE
SUDOKU_API void MakeResultString(Sudoku* sudo, char* buffer, int size);
SUDOKU_API int CalculateSudokuAll(Sudoku* sudo, bool dancing, SudokuAnswerCallback cb, void* data);

SUDOKU_API bool VerifySudokuBoard(const int* board);
SUDOKU_API const char* SolveTypeName(SolveType type);
SUDOKU_API const char* ImproveTypeName(ImproveType type);

#endif
