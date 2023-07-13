#include<iostream>
#include<fstream>
using namespace std;

class Shopping{
private:
    int productCode;
    float price;
    float discount;
    string productName;
public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void removing();
    void list();
    void receipt();
};

void Shopping::menu(){
    m://m is a label which is re-executed with the help of goto statement.
    int choice;
    string email;
    string password;
    cout<<"\t\t\t\t_______________________________\n";
    cout<<"\t\t\t\t                               \n";
    cout<<"\t\t\t\t        Supermarket Main Menu \n";
    cout<<"\t\t\t\t                               \n";
    cout<<"\t\t\t\t_______________________________\n";
    cout<<"\t\t\t\t                               \n";
    cout<<"\t\t\t\t|   1) Administrator   |\n";
    cout<<"\t\t\t\t|                      |\n";
    cout<<"\t\t\t\t|   2) Buyer           |\n";
    cout<<"\t\t\t\t|                      |\n";
    cout<<"\t\t\t\t|   3) Exit            |\n";
    cout<<"\t\t\t\t|                      |\n";
    cout<<"\n\t\t\t Please select!";
    cin>>choice;
    switch(choice)
    {
        case 1:
            cout<<"\t\t\t Please login \n";
            cout<<"\t\t\t Enter Email  \n";
            cin>>email;
            cout<<"\t\t\t Password     \n";
            cin>>password;

            if(email == "divyansh@gmail.com" && password == "divyansh@123"){
                administrator();
            }
            else{
                cout<<"INVALID EMAIL PASSWORD";
            }
            break;
        case 2:
        {
            buyer();
            break;
        }
         case 3:
        {
            exit(0);
            break;
        }
        default:
        {
            cout<<"Please select from the given options";
            break;
        }
    }
    goto m;// goto statement is an unconditional JUMP statement. Here as soon as the control reaches to line 71, then it will unconditionally jump to the label m.
}

void Shopping::administrator(){
    m:
    int choice;
    cout<<"\n\n\n\t\t\t Administrator menu";
    cout<<"\n\t\t\t|     1) Add the product      |";
    cout<<"\n\t\t\t|                             |";
    cout<<"\n\t\t\t|     2) Modify the product   |";
    cout<<"\n\t\t\t|                             |";
    cout<<"\n\t\t\t|     3) Delete the product   |";
    cout<<"\n\t\t\t|                             |";
    cout<<"\n\t\t\t|     4) Back to the menu     |";
    cout<<"\n\n\t Please enter your choice ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            removing();
            break;
        case 4:
            menu();
            break;
        default:
            cout<<"INVALID CHOICE";
    }
    goto m;
}

void Shopping:: buyer()
{
     m:
     int choice;
     cout<<"\t\t\t       Buyer     \n";
     cout<<"                       \n";
     cout<<"\t\t\t  1) Buy Product \n";
     cout<<"                       \n";
     cout<<"\t\t\t  2) Go Back     \n";
     cout<<"\t\t\t Enter your choice\n";
     cin>>choice;

     switch(choice)
     {
         case 1:
             receipt();
             break;
         case 2:
             menu();
         default:
             cout<<"Invalid choice";
     }
     goto m;
}

void Shopping:: add(){
    m:
    fstream data;
    int c;
    int exists=0;
    float p;
    float d;
    string n;

    cout<<"\n\n\t\t\t Add new Product";
    cout<<"\n\n\t Enter the product code";
    cin>>productCode;
    cout<<"\n\n\t Name of the Product ";
    cin>>productName;
    cout<<"\n\n\t Display price of product.";
    cin>>price;
    cout<<"\n\n\t Discount on product ";
    cin>>discount;
    //file opening (database file ko open karna in reading mode(ios::in).
    data.open("database.txt", ios::in);
    //if the file doesn't exists, then we are using app(append mode) else out(overwrite prev content).
    if(!data){
        //ios::app - append mode. ios::out - write mode.By combining these flags, the file "database1.txt" will be opened in output and append mode.
        //If the file already exists, new data will be added to the end of the file. If the file doesn't exist, a new file will be created.
        data.open("database.txt", ios::app|ios::out);
        data<<" "<< productCode<<" "<<productName<<" "<<price<<" "<<discount<<endl;
        data.close();
    }
    else{
        //we are reading from the file if it exists.
        data>>c>>n>>p>>d;
        while(!data.eof()){
            //if we find duplicacy in product code.
            if(c==productCode){
                exists++;
            }
            data>>c>>n>>p>>d;
        }
        data.close();

        //exists was incremented when we found the occurence of that token code previously in the file. So this is invalid.
        if(exists == 1){
            goto m;
        }
        else{
            //productCode is unique so it's valid - append in database file.
            data.open("database.txt", ios::app|ios::out);
            data<<" "<< productCode<<" "<<productName<<" "<<price<<" "<<discount<<endl;
            data.close();
        }
    }
    cout<<"\n\t\t\t Record Inserted:!";
}

void Shopping::edit(){
    fstream data, data1;
    int productKey;
    int exists=0;
    int c;
    float p;
    float d;
    string n;
    cout<<"\n\t\t\t Modify the record";
    cout<<"\n\t\t\t Please enter the Product Code:";
    cin>>productKey;
    data.open("database.txt",ios::in);
    if(!data){
        cout<<"\n\n\t\tFile dosen't exist";
    }
    else{
        //we are saving edited details in this file - database1.txt.
        data1.open("database1.txt", ios::app|ios::out);

        data>>productCode>>productName>>price>>discount;
        //sab kuch database1.txt me update kar rhe h aur baadme hum database.txt ko remove karenge aur database1.txt ko rename karo - database.txt me.
        while(!data.eof()){
            if(productKey == productCode){
                cout<<"\n\t\t\t Product new Code: ";
                cin>>c;
                cout<<"\n\t\t\t Name of the product: ";
                cin>>n;
                cout<<"\n\t\t\t Price: ";
                cin>>p;
                cout<<"\n\t\t\t Discount: ";
                cin>>d;
                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<endl;
                cout<<"\n\n\t\t Record Edited!";
                exists++;
            }
            else{
                data1<<" "<<productCode<<" "<<productName<<" "<<price<<" "<<discount<<endl;
            }
            data>>productCode>>productName>>price>>discount;
        }
        data.close();
        data1.close();
        //database.txt ko remove karke database1.txt ko rename kar denge to database.txt..
        remove("database.txt");
        rename("database1.txt", "database.txt");
        //if that productCode was not there, then we need to display that record was not found.
        if(exists){
            cout<<"\n\n\t Record not found";
        }
    }
}

void Shopping::removing(){
    fstream data, data1;
    int productKey;
    int exists=0;
    cout<<"\n\n\t Delete Product";
    cout<<"\n\n\t Enter the product code :";
    cin>>productKey;
    data.open("database.txt", ios::in);
    if(!data){
        cout<<"\n\t\t File doesn't exists";
    }
    else{
        data1.open("database1.txt", ios::app|ios::out);
        data>>productCode>>productName>>price>>discount;
        while(!data.eof()){
            if(productCode == productKey){
                cout<<"\n\n\t Product deleted successfully";
                exists++;
            }else{
                //jisko remove karna h uske alawa saare products display honge.
                data1<<" "<<productCode<<" "<<productName<<" "<<price<<" "<<discount<<endl;
            }
            data>>productCode>>productName>>price>>discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(exists==0){
            cout<<"\n\n\t Record not found";
        }
    }
}

void Shopping:: list(){
    fstream data;
    data.open("database.txt", ios::in);
    cout<<"\n\n__________________________________________________________\n";
    cout<<"ProductNumber \t Name \t Price\n";
    cout<<"\n\n__________________________________________________________\n";
    data>>productCode>>productName>>price>>discount;
    while(!data.eof()){
        cout<<productCode<<"\t"<<productName<<"\t"<<price<<endl;
        data>>productCode>>productName>>price>>discount;
    }
    data.close();
}

void Shopping:: receipt(){
    fstream data;
    int arrayOfCode[100];
    int arrayOfQuantity[100];
    char choice;
    int c=0;
    float amount=0;
    float dis=0;
    float total = 0;
    cout<<"\n\n\t\t\t RECEIPT \n";
    data.open("database.txt", ios::in);
    if(!data){
        cout<<"\n\n Empty Database";
    }
    else{
        data.close();
        //is file exists, then we'll show the user the list of products available in supermarket.
        list();
        cout<<"\n_____________________________________________________\n";
        cout<<"\n             Please place the order                  \n";
        cout<<"\n_____________________________________________________\n";

        do{
            m:
            cout<<"\n\n Enter product code : ";
            cin>>arrayOfCode[c];
            cout<<"\n\n Enter the quantity: ";
            cin>>arrayOfQuantity[c];
            //we are checking that does this productCode has occurred previously.
            for(int i=0;i<c;i++){
                if(arrayOfCode[c] == arrayOfCode[i]){
                    cout<<"\n\n Duplicate product code. Please try again! ";
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Do you want to buy another product? if yes press y else no";
            cin>>choice;
        }
        while(choice == 'y');
        cout<<"\n\n\t\t\t____________________________RECEIPT_____________________________\n";
        cout<<"\nProduct Number \t Name \t Product Quantity \t price \t Amount \t Amount with discount\n";

        for(int i=0;i<c;i++){
            data.open("database.txt", ios::in);
            data>>productCode>>productName>>price>>discount;
            while(!data.eof()){
                if(productCode == arrayOfCode[i]){
                    amount = price * arrayOfQuantity[i];
                    dis = (amount) - (amount * dis/100);
                    total =+ dis;
                    cout<< "\n"<<productCode<<"\t"<<productName<<"\t"<<arrayOfCode[i]<<"\t"<<price<<"\t"<<amount<<"\t"<<dis;
                }
                data>>productCode>>productName>>price>>discount;
            }
        }
        data.close();
    }
    cout<<"\n\n_______________________________________________________\n";
    cout<<"\n\n Total Amount : "<<total;
}

int main(){
    Shopping obj;
    obj.menu();
    return 0;
}
