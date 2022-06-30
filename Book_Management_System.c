/**
  * File:    Book_Management_System.c
  *
  * Author:  Nigam Niraula
  * Date:     1st August 2021
  * Partner:  I worked alone
  * Course:   Computer Engineering 101
  * Language:  C
  * Summary of File:
  *
  *   This file contains program that lets user add, edit and delete book.
  */
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  struct user{
  char username[30];
  char password[30];
  char name[30];
 } user; // struct for storing user data
  struct book{
  int id;
  char title[100];
  char author[100];
  char isbn[20];

}book; //struct for storing book data
  FILE *user_details= NULL;
  void logininterface();
  void book_management_interface();

  /**
    *
    * The clear() function clears the interface.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void clear(){
    #ifdef _WIN32 //identifying the os of user and clearing the screen accordingly
    system("cls");
    #else
    system ("clear");
    #endif
  }


  /**
    *
    * The welcome() function prints a welcome interface on opening of the program.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void welcome(){
    char i;
    printf("*********************************************\n");
    printf("\nWelcome to the Book Managent System.\n");
    printf("\n*********************************************\n");
    printf("Press Enter to continue.\n");
    scanf("%c",&i);
    return;
  }
  /**
    *
    * The addbook() function adds books with it's detail in a file.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void addbook(){
    clear();

    FILE *fp;
  	char another='y';
  	fp=fopen("book_details.txt","a");// opening file in append mode
  	if(fp==NULL)
    {
  		printf("File Cannot Be Created !!");
}

  		printf("\nEnter Book Id:");
  		scanf("%d",&book.id);
  		printf("Enter Book  Name:");
  		scanf(" %[^\n]s",book.title);
          printf("Enter Author Name:");
  		scanf(" %[^\n]s",book.author);
           printf("Enter ISBN number:");
  		scanf(" %s",book.isbn);
  		fwrite(&book,sizeof(book),1,fp); //writing contents of struct in file


  	fclose(fp);
    clear();
    book_management_interface();
  }
  /**
    *
    * The editdetail() function edits details of a particular book stored in the given file.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void editdetail(){
    clear();
    FILE *fp,*fp1;
  	char another='y';
  	int bookid,isrecord=0;
  	fp=fopen("book_details.txt","r"); //opening file in read mode
  	fp1=fopen("temp.txt","w");  //opening file in append mode
  	printf("Enter Book Id to update:");
  	scanf("%d", &bookid);
  	if(fp==NULL)
  	{
  		printf("File Cannot Be Created !!");
  		exit(1);
  	}
  	while(fread(&book,sizeof(book),1,fp)) //reading the data from the file
  	{
  		if(book.id==bookid)
  		{
  		isrecord=1;

  		printf("Enter Edited Book Name:");
  		scanf(" %[^\n]s",book.title);
          printf("Enter Edited Author Name:");
  		scanf(" %[^\n]s",book.author);
          printf("Enter Edited ISBN:");
  		scanf("%s",book.isbn);
  		}
  		fwrite(&book,sizeof(book),1,fp1); //writing the data in file
  	}fclose(fp);
  	 fclose(fp1);

  	if(!isrecord)
  	{
  		printf("No record found\n");
  	}
  	else
  	{
  		fp1=fopen("temp.txt","r");
  		fp=fopen("book_details.txt","w");
  		while(fread(&book,sizeof(book),1,fp1))
  		{
  			fwrite(&book,sizeof(book),1,fp);
  		}
      fclose(fp1);
  	fclose(fp);

  }
  printf("\n\n\n*************************************************\n");
  printf("Press any key and enter to continue.\n");
  char i;
  scanf(" %c",&i);
  clear();

  book_management_interface();
}
  /**

    *
    * The display() function displays details of all books.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void display(){
    FILE *fp;
    char i;
    fp=fopen("book_details.txt","r"); //opening file in read mode
    if(fp==NULL)
    {
      printf("File Cannot Be Created !!");
      exit(1);
    }
    clear();
    printf("***Displaying each book as id-title-author-isbn.***\n");
    while(fread(&book,sizeof(book),1,fp)) //reading data from the file
    {

      printf("%d \t %s \t %s \t %s \n",book.id,book.title,book.author,book.isbn);
    }
    fclose(fp);
    printf("\n\n\n*************************************************\n");
    printf("Press any key and enter to continue.\n");
    scanf(" %c",&i);
    clear();
    book_management_interface();

  }
  /**

    *
    * The searchbook() function displays details of a particular book.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void searchbook(){
    clear();
    FILE *fp;
    char another='y';
  	int bookid,isrecord=0;
  	fp=fopen("book_details.txt","r"); //opening file in read mode
  	printf("Enter Book Id to search:");
  	scanf("%d", &bookid);
  	if(fp==NULL)
  	{
  		printf("File Cannot Be Created !!");
  		exit(1);
  	}
  	while(fread(&book,sizeof(book),1,fp)) //reading the data from files
  	{
  		if(book.id==bookid)
  		{
  			isrecord=1;
        printf("***Displaying each book as id-title-author-isbn.***\n");
  			printf("%d \t %s \t %s \t %s \n",book.id,book.title,book.author,book.isbn);
  		}
  	}
  	if(!isrecord)
  	{
  		printf("\nRecord Not Found\n");
  	}
  	fclose(fp);
    printf("\n\n\n*************************************************\n");
    printf("Press any key and enter to continue.\n");
    char i;
    scanf(" %c",&i);
    clear();
    book_management_interface();

  }




  /**
    *
    * The delete() function deletes all the details of a particular book.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void delete(){
    clear();
    FILE *fp,*fp1;
    char another='y';
    int bookid,isrecord=0;
    fp=fopen("book_details.txt","r"); //opening file in read mode
    fp1=fopen("temp.txt","w"); // opening file in write mode
    printf("Enter Book ID of book to delete:");
    scanf("%d", &bookid);
    if(fp==NULL){
      printf("File Cannot Be Created !!");
      exit(1);
    }
    while(fread(&book,sizeof(book),1,fp)==1)
    {
      if(book.id==bookid)
      {
        isrecord=1;
        }
      else
      {
        fwrite(&book,sizeof(book),1,fp1);
        }
      }
    fclose(fp);
    fclose(fp1);

    if(isrecord==0)
    {
      printf("No record found\n");
      printf("\n\n\n*************************************************\n");
      printf("Press any key and enter to continue.\n");
      char i;
      scanf(" %c",&i);
    }
    else
    {
      fp1=fopen("temp.txt","r"); //opening file in read mode
      fp=fopen("book_details.txt","w"); //opening file in write mode
      while(fread(&book,sizeof(book),1,fp1)){
        fwrite(&book,sizeof(book),1,fp);
      }
    fclose(fp);
    fclose(fp1);

  }

clear();
book_management_interface();
}
  /**
    *
    * The book_management_interface() function creates a interface and asks user to proceed further accordingly.
    *
    *
    * Parameters   : no parameter
    *xa
    * Return Value : null
    *
    */
  void book_management_interface(){

    printf("\n***Welcome to the Book Management System, %s***\n", user.username);
    printf("\n******************************************\n");
    printf("\n1.Add book\n");
    printf("2.Edit details of a book\n");
    printf("3.Display the detail of all books\n");
    printf("4.Delete a book\n");
    printf("5.Search a book\n");
    printf("6.Exit");
    printf("\n******************************************\n");
    printf("Enter the S.N of the task you want to perform:\t");
    int num;
    scanf("%d",&num);
    switch(num)
    {
      case 1:
      addbook();
      break;
      case 2:
      editdetail();
      break;
      case 3:
      display();
      break;
      case 4:
      delete();
      break;
      case 5:
      searchbook();
      case 6:
      exit(0);
      break;
    }
  }
  /**
    *
    * The login() function asks user to enter their username and password.Then,
    *it checks if the username and pasword match.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void login(){
  clear();
  int login=0;;
  char username[30];
  char password[30];
    printf("***********WELCOME TO LOGIN PORTAL***********");
    printf("\n\n");

      printf("\n Enter your Username:\t");
      scanf("%s",username);
      printf("\n Enter your Password: \t");
      scanf("%s",password);
      user_details= fopen("user_details.txt","r"); //opening file in reading mode
      if(user_details==NULL){
        printf("File Cannot Be Created !!");
        exit(1);
      }
      while(fread(&user,sizeof(user),1,user_details)) //reading the data from the file
      {
          if(strcmp(username,user.username)==0)
            { login++;
              if(strcmp(password,user.password)==0)
              {
                clear();
                book_management_interface();
              }
              else
              {
                clear();
                printf("Enter a valid password.\n");
                logininterface();
              }
            }

          }
      if(login!=1){
        clear();
        printf("Enter valid Username.\n");
        logininterface();
      }
      fclose(user_details);

return;
}
  /**
    *
    * The signup() function asks user to enter the details of user. Then,
    *it stores the detail in a file.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void signup(){
    clear();
    printf("***********WELCOME TO SIGNUP PORTAL***********");
    printf("\n\n");
    char username2[30];
    printf("\n Enter your name:\t");
    scanf(" %[^\n]s",user.name);
    re:
    printf("\nEnter the Username you desire(oneword): \t");
    scanf("%s",username2);
    user_details= fopen("user_details.txt","a+"); //opening file in append and read mode
    if(user_details==NULL){
      printf("File Cannot Be Created !!");
      exit(1);
    }
    while(fread(&user,sizeof(user),1,user_details)) //reading the data from the file
    {
      if(strcmp(user.username,username2)==0)
      {
        printf("Error the username already exists.Please choose another!\n");
          goto re;
      }
    }
    strcpy(user.username,username2);
    printf("\nEnter your Password: \t");
    scanf(" %[^\n]s",user.password);
    fwrite(&user,sizeof(user),1,user_details);
    fclose(user_details);
    clear();
    logininterface();
  }
  /**
    *
    * The logininterface() function asks user if user wants to login or signup and proceeds further.
    *
    * Parameters   : no parameter
    *
    * Return Value : null
    *
    */
  void logininterface(){
    int num;
    re:
    printf("\n***Login to the book Managent System***\n");
    printf("\n******************************************\n");
    printf("\n1.Login\n");
    printf("2.Signup\n");
    printf("3.Exit\n");
    printf("\n******************************************\n");
    printf("(1/2/3)?:\t");
    scanf("%d",&num);
    if(num==1)
    {
      login(); //calling login function
    }
    else if(num==2)
    {
      signup(); //calling signup function
    }
    else if(num==3)
    {
      exit(0);
    }
    else
    {
      printf("Enter a valid number.\n");
      goto re;
    }
    return;
}



  int main(){
    clear();
    welcome();  //calling welcome function
    clear();
    logininterface(); //calling logininterface dunction

  }
