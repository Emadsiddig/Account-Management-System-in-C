#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct account{
   
   char first_name[20];
   char second_name[20];
   char gender[20];
   unsigned long long phone_no;
   char email[20];
   char password[20];
   char conf_password[20];

};
void signup(){
    struct account u;
    FILE *fp;
    printf("\n**welcome in our wepsite****\n");
    printf("\nenter your first name:");
    scanf("%s",u.first_name);
    printf("\nenter your second name:");
    scanf("%s",u.second_name);
    printf("\nenter your gender:");
    scanf("%s",u.gender);
    printf("\nenter your phone number:");
    scanf("%d",&u.phone_no);  
    printf("\nenter your email:");
    scanf("%s",u.email);
    printf("\nenter your password:");
    scanf("%s",u.password);
    printf("\nenter your password agin to confirm:");
    pass:
    scanf("%s",u.conf_password);
    if(strcmp(u.conf_password,u.password)!=0){
        printf("\nincorrect !!.try to enter the same password\n");
        goto pass;
    } 

    fp=fopen("account.dat","ab");
    if(fp==NULL){
        printf("failed to open file.");
        return ;
    }
    fwrite(&u,sizeof(u),1,fp);
    fclose(fp);
    printf("successfully created your account.\n");
}
void login(){
    printf("\nwelcome to login — please enter your information\n");
    char pass[50], user_name[50];
    struct account u, found;
    int found_flag = 0;
    FILE *fp;

    printf("\nenter your username (first name or email): ");
    scanf("%49s", user_name);

    fp = fopen("account.dat", "rb");
    if (fp == NULL) {
        printf("No user database found. Please signup first.\n");
        return;
    }

    /* Search for matching username (first_name OR email) */
    while (fread(&u, sizeof(u), 1, fp) == 1) {
        if (strcmp(user_name, u.first_name) == 0 || strcmp(user_name, u.email) == 0) {
            found = u;
            found_flag = 1;
            break;
        }
    }
    fclose(fp);

    if (!found_flag) {
        printf("\nUSER NOT FOUND.\n");
        return;
    }

    printf("\nenter the password: ");
    scanf("%49s", pass);

    if (strcmp(pass, found.password) == 0) {
        printf("\n********** successfully logged in ************\n");
        printf("\nWelcome %s %s\n", found.first_name, found.second_name);
        printf("Gender: %s\n", found.gender);
        printf("Phone: %d\n", found.phone_no);
        printf("Email: %s\n", found.email);
    } else {
        printf("\nIncorrect password\n");
    }
}
void forget(){
    struct account f;
    char name[20],email[20];
    int phone;
    FILE *fp=fopen("account.dat","r");
    fread(&f,sizeof(f),1,fp);
    printf("\n1.search by username");
    printf("\n2.search by phone number");
    printf("\n3.search by email");
    int choice;
    printf("\nenter your choice:");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
      printf("\nenter the name:");
      scanf("%s",name);
      if(strcmp(f.first_name,name)){
        printf("\ncan't found your data");
      }
      else{
        printf("\n********** SUCSSESSFULLY FOUND YOUR  DATA ************\n");
        printf("\nWelcome %s %s\n", f.first_name, f.second_name);
        printf("\nGender: %s\n", f.gender);
        printf("\nPhone: %d\n", f.phone_no);
        printf("\nEmail: %s\n", f.email);
      }
        break;
     case 2:
      printf("\nenter your phone number:");
      scanf("%d",&phone);
      if(phone != f.phone_no){
        printf("\ncan't found your data");
      }
      else{
        printf("\n********** SUCSSESSFULLY FOUND YOUR  DATA ************\n");
        printf("\nWelcome %s %s\n", f.first_name, f.second_name);
        printf("\nGender: %s\n", f.gender);
        printf("\nPhone: %d\n", f.phone_no);
        printf("\nEmail: %s\n", f.email);
      }
        break;
      case 3:
      printf("\nenter the email:");
      scanf("%s",email);
      if(strcmp(f.email,email)){
        printf("\ncan't found your data");
      }
      else{
        printf("\n********** SUCSSESSFULLY FOUND YOUR  DATA ************\n");
        printf("\nWelcome %s %s\n", f.first_name, f.second_name);
        printf("\nGender: %s\n", f.gender);
        printf("\nPhone: %d\n", f.phone_no);
        printf("\nEmail: %s\n", f.email);
      }
        break;
        
    default:
    printf("\ninvalid choice.");
        break;
    }
}
void changePass(){
 
  FILE *fp=fopen("account.dat","r+b");
  if (fp == NULL) {
     printf("No user database found. Please signup first.\n");
   }
  struct account u;
   char name[20],oldpass[20],newpass[20],conferm_pass[20];
  int found =0;
  int record_pos;
  //fread(&u,sizeof(struct account),1,fp);
  rewind(fp);
  try:
  printf("ENTER YOUR INFORMATION TO CHANGE THE PASSWORD\nENTET YOUR NAME OR YOUR EMAIL:");
  scanf("%s",name);
  while (fread(&u, sizeof(u), 1, fp) == 1) {
       if (strcmp(name, u.first_name) == 0 || strcmp(name, u.email) == 0) {
            found = 1;
             
           break;
       }
   }
   record_pos = ftell(fp) - (long)sizeof(u); /* position of start of matched struct */
   if (found == 0) {   
     printf("User not found.\n");
       goto try;

   }
  pass:
  printf("\nEnter old password:");
  scanf("%s",oldpass);
  if(strcmp(oldpass,u.password)!=0){
    printf("\nUncorrect password,..try agine");
    goto pass;
  }
  printf("Enter new password(letters):");
  scanf("%s",newpass);
  printf("Enter new password to confaim:");
  conf:
  scanf("%s",conferm_pass);
  if(strcmp(newpass,conferm_pass)!=0){
    printf("the confirm password does't correct ,try agine..");

  }

 strncpy(u.password, newpass, sizeof(u.password) - 1);
  u.password[sizeof(u.password)-1] = '\0';
   /* overwrite the matched record */

if (fseek(fp, record_pos, SEEK_SET) != 0) {
      perror("fseek failed");
  } else if (fwrite(&u, sizeof(u), 1, fp) != 1) {
      perror("Failed to update password");
  } else {
      fflush(fp);
      printf("Password changed successfully.\n");
  }

  fclose(fp); 
}  

void delete(){
  char x;
  FILE *fp=fopen("account.dat","r");
   
  char ch =fgetc(fp);
  if(ch == EOF){
    printf("\nNO ACCOUNT TO DELETE.\n");
  }
  else{
    printf("ARE YOU SURE(Y/N)?");
    scanf(" %c",&x);
    if(x == 'y' || x == 'Y'){
      fp =fopen("account.dat","w");
        remove("account.dat");
      printf("\n DELETE ACCOUNT SUCSSUFLY.\n");
      getch();
    }
    else{
      printf(".ACCOUNT DELETE STOPPED.\n");
      getch();
    }
  }
}
int main(){
    int choice;
    while(1) {
        printf("\n===== ACCOUNT MANAGEMENT MENU =====\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("3. Forgot password\n");
        printf("4. Change password\n");
        printf("5. Delete account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                forget();
                break;
            case 4:
                changePass();
                break;
            case 5:
                delete();
                break;
            case 6:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}    