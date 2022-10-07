#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Here use as function declaration, function above need used in project
void readFile(FILE**, char[]);
void writeFile(FILE**, char[]);
int compareAnswer(char[],char[]);
void printMissQuestion(int);
void displayReport(char[],char[],char[],char[],int);
void printReport(char[],char[],char[],char[]);

int main(void){

    char Name[20];
    char ID[20];
    char askID[20];
    char studentans[20];
    char correctans[20];
    int i,qmiss = 0;
    float percentage;
    char grade;
    char line[100];

    FILE *Canswer,*Sanswer,*Output;

    readFile(&Canswer, "CorrectAnswers.dat");//open correct answer
    readFile(&Sanswer, "StudentAnswers.dat");//open student answer
    writeFile(&Output,"Output_file.out");//generate a output file

    printf("Enter the student ID: ");
    scanf("%s",&askID);

    while (fgets(line, sizeof(line),Sanswer))
    {
        fscanf(Sanswer,"%s",Name);
        fscanf(Sanswer,"%s",ID);

        if(strcmp(askID,ID) == 0){
        for(i=0;i<20;i++){
            fscanf(Sanswer,"\n%c",&studentans[i]); //read student answer
        }

        for(i=0;i<20;i++){
            fscanf(Canswer,"%c\n",&correctans[i]);//read correct answer
        }

        //compare answer correct or not and counting the number of wrong questions
        qmiss = compareAnswer(studentans,correctans);

        //here for output display
        displayReport(Name,ID,studentans,correctans,qmiss);//this function used to print report
        break;
        }
    }

      if(strcmp(askID,ID) == 1){
            printf("\nError! Please enter the correct ID\n");
    }




    //print output report
    printReport(Name,ID,studentans,correctans);

    fclose(Canswer);
    fclose(Sanswer);
    fclose(Output);
    return 0;
}

//here used for function definition

void readFile(FILE** file, char fileName[]){
    *file = fopen(fileName, "r");

    return;
}

void writeFile(FILE** file, char fileName[]){
    *file = fopen(fileName, "w");

    return;
}

int compareAnswer(char sa[20],char ca[20]){
    int i,miss = 0;//reset qmiss
    for(i=0;i<20;i++){
        if(sa[i] != ca[i]){
            miss++; // wrong then qmiss is increase by 1
        }
    }

    return (miss);
}

void printMissQuestion(int miss){

    printf("Number of question missed: %d\n",miss);
    return;
}

void displayReport(char n[20],char id[20],char sa[20],char ca[20],int q){
        int i;
        float percentage;
        char grade;
        printf("\nEXAM RESULT\n");

        printf("Name\t\t\t: %s\n",n);
        printf("Enter the student ID: %s\n",id);

        printMissQuestion(q);//function used to print qmiss

        printf("List of the questions missed\n");
        printf("Question\tCorrect Answer\t\tStudent Answer\n");

        for(i=0;i<20;i++){
             if(sa[i] != ca[i]){
                printf("%d\t\t\t%c\t\t\t%c\n",i+1,ca[i],sa[i]);

            }
        }

        //used qmiss above and formula given in question to calculate the student percentage
        percentage =((20.0-q)/20.0)*100.0;


        //check the grade of the student
        if(percentage >= 80 && percentage <= 100 ){
            grade = 'A';
        }
        else if(percentage >= 70 && percentage < 80){
            grade = 'B';
        }
        else if(percentage >= 60 && percentage < 70){
            grade = 'C';
        }
        else if(percentage < 60){
            grade = 'F';
        }

        printf("Percentage: %.0f%% , GRED : %c\n",percentage,grade);
        return;
}

void printReport(char n[],char id[],char sa[20],char ca[20]){
    float percentage;
    char grade;
    int miss = 0;
    int i;
    char line[100];
    FILE *Canswer,*Sanswer,*Output;

    readFile(&Canswer, "CorrectAnswers.dat");//open correct answer
    readFile(&Sanswer, "StudentAnswers.dat");//open student answer
    writeFile(&Output,"Output_file.out");//generate a output file


    fprintf(Output,"LIST OF STUDENTS AND GRADES\n");
    fprintf(Output,"NAME\t\t\t\tID\t\t\t\tPERCENTAGE\t\tGRADE\n");

    while (fgets(line, sizeof(line),Sanswer))
    {
        fscanf(Sanswer,"%s",n);
        fscanf(Sanswer,"%s",id);

        for(i=0;i<20;i++){
            fscanf(Sanswer,"\n%c",&sa[i]); //read student answer
        }

        for(i=0;i<20;i++){
            fscanf(Canswer,"%c\n",&ca[i]);//read correct answer
        }

        miss = compareAnswer(sa,ca);

        //used qmiss above and formula given in question to calculate the student percentage
        percentage =((20.0-miss)/20.0)*100.0;


        //check the grade of the student
        if(percentage >= 80 && percentage <= 100 ){
            grade = 'A';
        }
        else if(percentage >= 70 && percentage < 80){
            grade = 'B';
        }
        else if(percentage >= 60 && percentage < 70){
            grade = 'C';
        }
        else if(percentage < 60){
            grade = 'F';
        }

        fprintf(Output,"\n%-20s%s\t\t%.0f\t\t\t\t  %c\n",n,id,percentage,grade);
    }
    return;
}

