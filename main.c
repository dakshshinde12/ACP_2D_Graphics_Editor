#include<stdio.h>

#define ROWS 20
#define COLS 50

char canvas[ROWS][COLS];

void initializeCanvas();
void displayCanvas();

void drawRectangle(int row,int col);
void drawFilledRectangle(int row,int col);
void drawTriangle(int row,int col);
void drawCircle(int row,int col);
void drawDiagonalLine(int row,int col);
void drawDiamond(int row,int col);
void drawX(int row,int col);

void saveCanvas();
void loadCanvas();

int main()
{
    int choice;
    int row,col;

    initializeCanvas();

    while(1)
    {
        printf("\n===== ACP 2D Graphics Editor =====\n");
        printf("1. Rectangle\n");
        printf("2. Filled Triangle\n");
        printf("3. Circle\n");
        printf("4. Diagonal Line\n");
        printf("5. Filled Diamond\n");
        printf("6. X Shape\n");
        printf("7. Filled Rectangle\n");
        printf("8. Clear Canvas\n");
        printf("9. Save Canvas\n");
        printf("10. Load Canvas\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice>=1 && choice<=7)
        {
            printf("Enter row: ");
            scanf("%d",&row);

            printf("Enter column: ");
            scanf("%d",&col);
        }

        switch(choice)
        {
            case 1:
                drawRectangle(row,col);
                break;

            case 2:
                drawTriangle(row,col);
                break;

            case 3:
                drawCircle(row,col);
                break;

            case 4:
                drawDiagonalLine(row,col);
                break;

            case 5:
                drawDiamond(row,col);
                break;

            case 6:
                drawX(row,col);
                break;

            case 7:
                drawFilledRectangle(row,col);
                break;

            case 8:
                initializeCanvas();
                printf("Canvas Cleared!\n");
                break;

            case 9:
                saveCanvas();
                break;

            case 10:
                loadCanvas();
                break;

            case 11:
                printf("Exiting Program...\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }

        displayCanvas();
    }

    return 0;
}

/* Rectangle */
void drawRectangle(int row,int col)
{
    for(int j=col;j<col+10 && j<COLS;j++)
        canvas[row][j]='*';

    for(int j=col;j<col+10 && j<COLS;j++)
        canvas[row+4][j]='*';

    for(int i=row;i<row+5 && i<ROWS;i++)
        canvas[i][col]='*';

    for(int i=row;i<row+5 && i<ROWS;i++)
        canvas[i][col+9]='*';
}

/* Filled Rectangle */
void drawFilledRectangle(int row,int col)
{
    for(int i=row;i<row+5 && i<ROWS;i++)
    {
        for(int j=col;j<col+10 && j<COLS;j++)
        {
            canvas[i][j]='*';
        }
    }
}

/* Filled Triangle */
void drawTriangle(int row,int col)
{
    for(int i=0;i<5;i++)
    {
        for(int j=col-i;j<=col+i;j++)
        {
            if(row+i<ROWS && j>=0 && j<COLS)
                canvas[row+i][j]='*';
        }
    }
}

/* Circle */
void drawCircle(int row,int col)
{
    int radius=3;

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            int dx=j-col;
            int dy=i-row;

            if(dx*dx + dy*dy >= radius*radius-2 &&
               dx*dx + dy*dy <= radius*radius+2)
            {
                canvas[i][j]='*';
            }
        }
    }
}

/* Diagonal Line */
void drawDiagonalLine(int row,int col)
{
    for(int i=0;i<8;i++)
    {
        if(row+i<ROWS && col+i<COLS)
            canvas[row+i][col+i]='*';
    }
}

/* Filled Diamond */
void drawDiamond(int row,int col)
{
    for(int i=0;i<4;i++)
    {
        for(int j=col-i;j<=col+i;j++)
        {
            if(row+i<ROWS && j>=0 && j<COLS)
                canvas[row+i][j]='*';
        }
    }

    for(int i=2;i>=0;i--)
    {
        for(int j=col-i;j<=col+i;j++)
        {
            if(row+5-i<ROWS && j>=0 && j<COLS)
                canvas[row+5-i][j]='*';
        }
    }
}

/* X Shape */
void drawX(int row,int col)
{
    for(int i=0;i<7;i++)
    {
        if(row+i<ROWS && col+i<COLS)
            canvas[row+i][col+i]='*';

        if(row+i<ROWS && col+6-i<COLS && col+6-i>=0)
            canvas[row+i][col+6-i]='*';
    }
}

/* Save Canvas */
void saveCanvas()
{
    FILE *fp;

    fp = fopen("canvas.txt","w");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            fputc(canvas[i][j],fp);
        }
        fputc('\n',fp);
    }

    fclose(fp);

    printf("Canvas saved successfully!\n");
}

/* Load Canvas */
void loadCanvas()
{
    FILE *fp;

    fp = fopen("canvas.txt","r");

    if(fp == NULL)
    {
        printf("No saved canvas found!\n");
        return;
    }

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j] = fgetc(fp);
        }
        fgetc(fp);
    }

    fclose(fp);

    printf("Canvas loaded successfully!\n");
}

/* Initialize Canvas */
void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j]='_';
        }
    }
}

/* Display Canvas */
void displayCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}