#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
struct items{
    char item[20];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int  numofItems;
    struct items itm[50];
};


//generate bills
void billheader(char name[50]){
    time_t t;
    time(&t);
    printf("\n\n");
    printf("\t     ABC. Restaurent");
    printf("\n\t   ------------------");
    printf("\nDate:%s",ctime(&t));
    printf("\nInvoice To:%s",name);
    printf("\n");
    printf("--------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t");
    printf("Total\t\t");
    printf("\n-------------------------------------");
    printf("\n\n");
}
void billbody(char item[20],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}





void billfoot(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
    printf("---------------------------------------\n");
    printf("sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------");
    
}
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill='y',contFlag='y';
    char name[50];
    FILE *fp;
    //dashboard
    while(contFlag=='y'){
        float total;
        int invoiceFound=0;
    printf("\t=========ABC.RESTAURENT========+");
    printf("\n\nPlease select your Option");
    printf("\n1.Generate Invoice");
    printf("\n2.Show all Invoice");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
        system("clear");
        printf("\nplease enter the name of the customer ");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
       // strcmp(ord.date,__DATE__);
        printf("\nplease enter the number of item:\t");
        scanf("%d",&n);
        ord.numofItems=n;
        for (int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("pleae enter the item%d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;
        }

        billheader(ord.customer);
        for(int i=0;i<ord.numofItems;i++){
            billbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        billfoot(total);
        
        printf("\nDo you want to save the invoice:\t");
        scanf("%s",&saveBill);
        if(saveBill=='y'){
            fp=fopen("Restaurant1.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite!=0)
            printf("\nSuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);

        }
        break;
        case 2:
        system("clear");
        fp=fopen("Restaurant1.dat","r");
        printf("\n ******Invoices of %s*******\n",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot=0;
        billheader(order.customer);
        for(int i=0;i<order.numofItems;i++)
        {
             billbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
             tot+=order.itm[i].qty*order.itm[i].price;
        }
        billfoot(tot);
        }
         fclose(fp);
         break;
         

         case 3:
        printf("\n Enter the name of the customer:\t");
       // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;
        system("clear");
        fp=fopen("Restaurant1.dat","r");
        printf("\n ******Your Previous Invoices*******\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot=0;
            if(!strcmp(order.customer,name)){
            billheader(order.customer);
        for(int i=0;i<order.numofItems;i++)
        {
             billbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
             tot+=order.itm[i].qty*order.itm[i].price;
        }
        billfoot(tot);
        }
            }
       
         fclose(fp);
         break;

         case 4:
         printf("\n\t\tBye Bye:)\n\n");
         exit(0);
         break;

         default:
         printf("Sorry invalid option");
         break;


    }
    printf("\n Do you want perform anothe operation?[y/n]:\t");
    scanf("%s",&contFlag);
    }
    printf("\n\n");

    return 0;
    

}
