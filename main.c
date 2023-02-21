#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void matrixPrinter(int **matrix, int h, int w)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void saveHistory(int **matrix, int **history, int h, int w, int index)
{
    int k = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            history[index][k] = matrix[i][j];
            k++;
        }
    }
}
int **getHistory(int **history, int h, int w, int index)
{
    int **matrix = (int **)malloc(sizeof(int) * h);
    for (int i = 0; i < h; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * w);
    }
    int k = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            matrix[i][j] = history[index][k];
            k++;
        }
    }
    return matrix;
}
int **getMatrix(int height, int width, int identity)
{
    int **matrix = (int **)malloc(sizeof(int) * height);
    for (int i = 0; i < height; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * width);
    }
    if (identity == 0)
    {
        printf("Enter values in the matrix: \n");
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (identity == 0)
            {
                printf("[%d][%d] = ", i, j);
                scanf("%d", &matrix[i][j]);
            }
            if (identity >= 1)
                matrix[i][j] = 0;
        }
    }
    if (identity == 2)
    {
        for (int i = 0; i < height; i++)
        {
            matrix[i][i] = 1;
        }
    }
    return matrix;
}
void addTwoColumns(int **matrix, int height, int width, int column1, int column2, int constant)
{
    for (int i = 0; i < height; i++)
    {
        matrix[i][column1] += (constant * matrix[i][column2]);
    }
}
void subtractTwoColumns(int **matrix, int height, int width, int column1, int column2, int constant)
{
    for (int i = 0; i < height; i++)
    {
        matrix[i][column1] -= (constant * matrix[i][column2]);
    }
}

void multiplyColumnByConstant(int **matrix, int height, int width, int column, int constant)
{
    for (int i = 0; i < height; i++)
    {
        matrix[i][column] *= constant;
    }
}
void swapColumns(int **matrix, int height, int width, int column1, int column2)
{
    int temp;
    for (int i = 0; i < height; i++)
    {
        temp = matrix[i][column1];
        matrix[i][column1] = matrix[i][column2];
        matrix[i][column2] = temp;
    }
}
void addTwoRows(int **matrix, int height, int width, int row1, int row2, int constant)
{
    for (int i = 0; i < width; i++)
    {
        matrix[row1][i] += (constant * matrix[row2][i]);
    }
}
void subtractTwoRows(int **matrix, int height, int width, int row1, int row2, int constant)
{
    for (int i = 0; i < width; i++)
    {
        matrix[row1][i] -= (constant * matrix[row2][i]);
    }
}
void multiplyRowByConstant(int **matrix, int height, int width, int row, int constant)
{
    for (int i = 0; i < width; i++)
    {
        matrix[row][i] *= constant;
    }
}
void swapRows(int **matrix, int height, int width, int row1, int row2)
{
    int temp;
    for (int i = 0; i < width; i++)
    {
        temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}
void historyPrinter(int **history, int height, int width, int index)
{
    for (int i = 0; i < index; i++)
    {
        printf("Step %d: \n", i + 1);
        matrixPrinter(getHistory(history, height, width, i), height, width);
    }
}
void elementaryTranformations(int **matrix, int **history, int height, int width, int *index)
{
    int choice = 0, row, column, constant;
    do
    {
        printf("\n\nSelect\n1) Row Operations\n2) Column Operations: \n3) Undo\n\nInput: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int option;
            printf("Select from one of the following options:\n1) R(i) <-> R(j)\n2) R(i) -> kR(i)\n3) R(i) -> R(i) + k X R(j)\n4) Exit\n\nInput: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                printf("Enter row numbers to swap:\n R(i) <-> R(j) --- i, j: ");
                scanf("%d %d", &row, &column);
                row = row - 1;
                column = column - 1;
                swapRows(matrix, height, width, row, column);
                break;
            case 2:
                printf("Enter row number and constant: \n  R(i) -> kR(i) --- i, k:");
                scanf("%d %d", &row, &constant);
                row = row - 1;
                multiplyRowByConstant(matrix, height, width, row, constant);
                break;
            case 3:
                printf("Enter row numbers to add: \n R(i) -> R(i) + k X R(j) --- i, j, k: ");
                scanf("%d %d %d", &row, &column, &constant);
                row = row - 1;
                column = column - 1;
                addTwoRows(matrix, height, width, row, column, constant);
                break;
            case 4:
                printf("Finalizing...");
                break;
            default:
                printf("Invalid choice. Try again.");
                break;
            }
            saveHistory(matrix, history, height, width, *index);
            *index++;
            system("cls");
            printf("Matrix after operation: \n");
            matrixPrinter(matrix, height, width);
        }
        if (choice == 2)
        {
            int option;
            printf("Select from one of the following options:\n1) C(i) <-> C(j)\n2) C(i) -> kC(i)\n3) C(i) -> C(i) + C(j)\n4) Exit\n\nInput: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                printf("Enter column numbers to swap:\n C(i) <-> C(j) --- i, j: ");
                scanf("%d %d", &row, &column);
                row = row - 1;
                column = column - 1;
                swapColumns(matrix, height, width, row, column);
                break;
            case 2:
                printf("Enter column number and constant: \n  C(i) -> k X (i) --- i, k:");

                scanf("%d %d", &row, &constant);
                row = row - 1;
                multiplyColumnByConstant(matrix, height, width, row, constant);
                break;
            case 3:
                printf("Enter column numbers to add: \n R(i) -> C(i) + k X C(j) --- i, j, k: ");
                scanf("%d %d %d", &row, &column, &constant);
                row = row - 1;
                column = column - 1;
                addTwoColumns(matrix, height, width, row, column, constant);
                break;
            case 4:
                printf("Finalizing...");
                break;
            default:
                printf("Invalid choice. Try again.");
                break;
            }
            saveHistory(matrix, history, height, width, *index);
            *index++;
            system("cls");
            printf("Matrix after operation: \n");
            matrixPrinter(matrix, height, width);
        }
        if (choice == 3)
        {
            int option;
            printf("Select from: \n1) Go back to Step \n2) View History \n3) Exit \n\nInput: ");
            scanf("%d", &option);
            if (option == 1)
            {

                char confirmation;
                system("cls");
                printf("Are you sure you want to go back to a previous step?\nChange will be permanent...\n(y/n): ");
                scanf(" %c", &confirmation);
                if (confirmation == 'y')
                {
                    historyPrinter(history, height, width, *index);

                    int step;
                    printf("Enter step number: ");
                    scanf("%d", &step);
                    *index = step;
                    matrix = getHistory(history, height, width, *index);
                }
                else
                {
                    printf("Operation cancelled.\n\nContinuing with current Step...\n");
                    matrixPrinter(matrix, height, width);
                }
            }
            if (option == 2)
            {
                historyPrinter(history, height, width, *index);
            }
        }
    } while (choice != 4);
    printf("\n\nFinalizing...\nResult: \n");
    matrixPrinter(matrix, height, width);
}

int main()
{
    int height, width, choice = -1;
    int index = 0;
    int **matrix, **history, **identity;
    int row, column, constant;

    printf("Enter width and height of Matrix.\n");
    scanf("%d %d", &height, &width);
    matrix = getMatrix(height, width, 0);

    history = getMatrix(500, height * width, 1);
    saveHistory(matrix, history, height, width, index);
    index++;
    system("cls");
    matrixPrinter(matrix, height, width);
    do
    {
        int choice;
        printf("\n\nSelect\n1) Elementary Transformations\n2) Inverse of Matrix Helper\n3) Exit\n\nInput: ");
        scanf("%d", &choice);
        if (choice == 1)
        {

            elementaryTranformations(matrix, history, height, width, &index);
        }
        if (choice == 2)
        {
            identity = getMatrix(height, width, 2);
            matrixPrinter(identity, height, width);
        }
    } while (choice != 3);
    getch();
    return 0;
}