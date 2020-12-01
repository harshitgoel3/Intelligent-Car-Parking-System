#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <windows.h>
using namespace std;
float Amount_earned_by_system=9637.78;

class Customer{
public:
    string customer_name;
    int contact_number;
    string vehicle_type;
    string vehicle_number;
    string vehicle_name;
    int time;
    int password;
    int arrival_time_hours;
    int arrival_time_minutes;
    int arrival_time_seconds;
    int departure_time_hours;
    int departure_time_minutes;
    int departure_time_seconds;
    float total_cost;
    int parking_space_number;

    Customer(){

    }
    Customer(string customer_name,int contact_number,string vehicle_type,string vehicle_name,string vehicle_number,int time){
        this->customer_name=customer_name;
        this->contact_number=contact_number;
        this->vehicle_type=vehicle_type;
        this->vehicle_name=vehicle_name;
        this->vehicle_number=vehicle_number;
        this->time=time;
        this->password=rand();
        this->arrival_time_hours=0;
        this->arrival_time_minutes=0;
        this->arrival_time_seconds=0;
        this->departure_time_hours=0;
        this->departure_time_minutes=0;
        this->departure_time_seconds=0;
        this->total_cost=0;
        this->parking_space_number=-1;
    }

};

class employee{
public:
    string employee_name;
    int age;
    string email_address;
    int contact_number;
    string post;
    int employee_id;

    employee(){

    }
    employee(string employee_name,int age,string email_address,int contact_number,string post,int employee_id){
        this->employee_name=employee_name;
        this->age=age;
        this->email_address=email_address;
        this->contact_number=contact_number;
        this->post=post;
        this->employee_id=employee_id;
    }

};

class Node{
public:
	Customer data;
	Node *next;
	Node(Customer data)
	{
		this->data = data;
		this->next = NULL;
	}
};
Node *insert_Customer_LL(Node *head,Customer C){
    Node *temp=head;
    Node *newNode=new Node(C);
    if(temp==NULL){
            head=newNode;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newNode;
    }
    return head;
}

class TreeNode{
public:
    int node_no;
    bool visited;
    string veh_number;
    vector<TreeNode *>children;

    //constructor
    TreeNode(int node_no){
        this->node_no=node_no;
        this->visited=false;
        veh_number="\0";
    }
};

void delete_car_from_system(TreeNode *root,string vehicle_number){
    queue<TreeNode *>pendingNodes;
    for(int i=0;i<4;i++){
        pendingNodes.push(root->children[i]);
    }
    while(pendingNodes.size()!=0){
        TreeNode *front=pendingNodes.front();
        if(front!=NULL){
            if(front->children.size()!=0){
                pendingNodes.push(front->children[0]);
            }
            pendingNodes.pop();
            if(front->veh_number==vehicle_number){
                front->veh_number="\0";
                front->visited=false;
                return ;
            }
       }
    }
}

Node *delete_car_details_from_system(Node *head,TreeNode *root,string vehicle_Num){     //deleting node through car number
    Node *temp=head;
    if(temp==NULL){
        return NULL;
    }
    else if(temp->data.vehicle_number==vehicle_Num){
        head=head->next;
        delete_car_from_system(root,vehicle_Num);
        return head;
    }
    else {
        while(temp->next!=NULL){
                if(temp->next->data.vehicle_number==vehicle_Num){
                    Node *a=temp->next;
                    Node *b=a->next;
                    delete a;
                    temp->next=b;
                    delete_car_from_system(root,vehicle_Num);
                    break;
                }
                temp=temp->next;
        }
    }
    return head;
}

void print(Node *head)
{
	Node *temp = head;
	while (temp != NULL)
	{
		cout <<temp->data.customer_name<<"\t\t"<<temp->data.vehicle_number<<"\t\t\t"<<temp->data.contact_number<<endl;
		temp = temp->next;
	}
	cout << endl;
}

int match_password(unordered_map<string,int> ourMap,string vehicle_num){
    if(ourMap.count(vehicle_num)>0){
        cout<<"The vehicle is parked ."<<endl<<endl;
        for(int i=0;i<2;i++){
            cout<<"Enter security code generated at entry gate for verification."<<endl;
            int security_key;
            cin>>security_key;

            if(ourMap[vehicle_num]==security_key){
                cout<<"The security key is correct."<<endl;
                return 1;
            }
            else{
                cout<<"The security key is not correct."<<endl;
                cout<<1-i<<" try left."<<endl;
            }
        }
    }
    else{
        cout<<"This is no vehicle parked of this number."<<endl;
    }
    return 0;
}


void printTree(TreeNode *root){
    //edge case
    if(root==NULL){
        return;
    }
    const WORD colors[] ={0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6};

    //  HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    //  WORD   index = 0;

    SetConsoleTextAttribute(hstdout, colors[7]);
    cout<<root->node_no<<" :";
    for(int i=0;i<root->children.size();i++){
            if(root->children[i]->visited==true){
                const WORD colors[] ={0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6};

              //  HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
                HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
              //  WORD   index = 0;

                SetConsoleTextAttribute(hstdout, colors[5]);

                cout<<root->children[i]->node_no<<" "<<root->children[i]->visited<<","<<root->children[i]->veh_number<<"\t";
            }
            else{
                const WORD colors[] ={0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6};

              //  HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
                HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
              //  WORD   index = 0;

                SetConsoleTextAttribute(hstdout, colors[2]);

                cout<<root->children[i]->node_no<<" \t"<<root->children[i]->visited<<","<<root->children[i]->veh_number<<"\t";
            }
    }
    cout<<endl;
    for(int i=0;i<root->children.size();i++){
        printTree(root->children[i]);
    }
}

int search_nearest_empty_node(TreeNode *root){
    queue<TreeNode *>pendingNodes;
    for(int i=0;i<4;i++){
        pendingNodes.push(root->children[i]);
    }
    while(pendingNodes.size()!=0){
        TreeNode *front=pendingNodes.front();
        if(front!=NULL){
            if(front->children.size()!=0){
                pendingNodes.push(front->children[0]);
            }
            pendingNodes.pop();
            if(front->visited==true){
                continue;
            }
            front->visited=true;
            return front->node_no;
        }
    }
    return -1;
}

void add_car_to_system(TreeNode *root,int node_num,string vehicle_number){
    queue<TreeNode *>pendingNodes;
    for(int i=0;i<4;i++){
        pendingNodes.push(root->children[i]);
    }
    while(pendingNodes.size()!=0){
        TreeNode *front=pendingNodes.front();
        if(front!=NULL){
            if(front->children.size()!=0){
                pendingNodes.push(front->children[0]);
            }
            pendingNodes.pop();
            if(front->node_no==node_num){
                front->veh_number=vehicle_number;
                return ;
            }
       }
    }
}

int search_your_car(TreeNode *root,string vehicle_number){
    queue<TreeNode *>pendingNodes;
    for(int i=0;i<4;i++){
        pendingNodes.push(root->children[i]);
    }
    while(pendingNodes.size()!=0){
        TreeNode *front=pendingNodes.front();
        if(front!=NULL){
            if(front->children.size()!=0){
                pendingNodes.push(front->children[0]);
            }
            pendingNodes.pop();
            if(front->veh_number==vehicle_number){
                return front->node_no;
            }
        }
    }
    return -1;
}

void display_parking_ticket(int digit,Customer &c){
    cout<<"Your parking ticket is :- "<<endl;
    cout<<"Name of customer    :- "<<c.customer_name<<endl;
    cout<<"Contact number      :- "<<c.contact_number<<endl;
    if(c.vehicle_type=="E"){
        cout<<"Vehicle type        :- Electric"<<endl;
    }
    else{
        cout<<"Vehicle type        :- Non-Electric"<<endl;
    }
    cout<<"Vehicle name        :- "<<c.vehicle_name<<endl;
    cout<<"Vehicle number      :- "<<c.vehicle_number<<endl;
    cout<<"Arrival time        :- "<<c.arrival_time_hours<<":"<<c.arrival_time_minutes<<":"<<c.arrival_time_seconds<<endl;
    cout<<"Departure time      :- "<<c.departure_time_hours<<":"<<c.departure_time_minutes<<":"<<c.departure_time_seconds<<endl;
    cout<<"Total amount paid   :- Rs"<<c.total_cost<<endl;
    if(digit==1){
        cout<<"Payment mode        :- Net Banking"<<endl;
    }
    else if(digit==2){
        cout<<"Payment mode        :- Debit Card"<<endl;
    }
    else if(digit==3){
        cout<<"Payment mode        :- Credit Card"<<endl;
    }
    else{
        cout<<"Payment mode        :- Cash Payment"<<endl;
    }
}

void payment_options(float price,Customer &c){
    cout<<"Press 1 for Net Banking."<<endl;
    cout<<"Press 2 for Debit Card."<<endl;
    cout<<"Press 3 for Credit Card."<<endl;
    cout<<"Press 4 for Cash Payment."<<endl;

    cout<<endl<<"10% discount is available on payment options other than cash."<<endl;
    int n;
    cin>>n;

    if(n==1||n==2||n==3){
        float x=price/10.0;
        c.total_cost=price-x;
        cout<<endl<<"Rs"<<c.total_cost<<" has been paid."<<endl<<endl;

        Amount_earned_by_system+=c.total_cost;
    }
    else if(n==4){
        c.total_cost=price;
        cout<<endl<<"Rs"<<price<<" has been paid."<<endl<<endl;

        Amount_earned_by_system+=price;
    }
    else{
        cout<<"No such mode of payment available."<<endl;
    }
    system("Pause");
    system("CLS");
    display_parking_ticket(n,c);

}

void calculate_parking_charges(Node *head,string vehicle_number){
    if(head==NULL){
        return ;
    }
    Node *temp=head;
    int cost=0;
    SYSTEMTIME a2;

    while(temp!=NULL){
        Customer c=temp->data;
        if(c.vehicle_number==vehicle_number){
            cout<<"The recorded arrival time was :";
            cout<<c.arrival_time_hours<<":";
            cout<<c.arrival_time_minutes<<":";
            cout<<c.arrival_time_seconds<<endl;

            cout<<endl<<"The recorded departure time is :";
            GetLocalTime(&a2);
            cout<<a2.wHour<<":";
            cout<<a2.wMinute<<":";
            cout<<a2.wSecond<<endl<<endl;

            c.departure_time_hours=a2.wHour;
            c.departure_time_minutes=a2.wMinute;
            c.departure_time_seconds=a2.wSecond;

            int parking_time=(c.departure_time_hours*60+c.departure_time_minutes)-(c.arrival_time_hours*60+c.arrival_time_minutes);

            if(c.vehicle_type=="E"){
                cost =parking_time*4;
                cout<<"Your parking charges are :- "<<cost<<endl<<endl;

                payment_options(cost,c);
            }
            else if(c.vehicle_type=="NE"){
                cost =parking_time*2;
                cout<<"Your parking charges are :- "<<cost<<endl<<endl;

                payment_options(cost,c);
            }
        }
        temp=temp->next;
    }
}

void admin(Node *head,employee *list_of_employees,int digit){
    if(digit==5){
        cout<<"Customer list :- "<<endl<<endl;
        cout<<"Name"<<"\t\t"<<"Vehicle number"<<"\t\t"<<"Contact number"<<endl;
        print(head);
    }
    else if(digit==6){
        cout<<"Employee list :- "<<endl<<endl;
        cout<<"Name\t\tAge\tEmail id\tContact number\tPost"<<endl;
        for(int i=0;i<8;i++){
            employee e=list_of_employees[i];
            cout<<e.employee_name<<"\t\t";
            cout<<e.age<<"\t";
            cout<<e.email_address<<"\t";
            cout<<e.contact_number<<"\t";
            cout<<e.post<<endl;
            cout<<endl;
        }
    }
}

int main(){

    employee e1("Vansh",31,"Va1@gmail.com",863456703 ,"Manager",210);
    employee e2("Vaanya",24,"Va@gmail.com",783589773 ,"Cashier",220);
    employee e3("Abeer",33,"Ab@gmail.com",863277703 ,"Registrar",230);
    employee e4("Nikita",27,"Ni@gmail.com",782377773 ,"Engineer",240);
    employee e5("Kshitij",24,"Ks@gmail.com",89957883 ,"Technician",250);
    employee e6("Nihar",38,"Ni1@gmail.com",999845773 ,"Technician",260);
    employee e7("Armaan",31,"Ar@gmail.com",973456703 ,"Security head",270);
    employee e8("Sonali",23,"So@gmail.com",773589773 ,"Parking caretaker",280);

    employee list_of_employees[8];

    list_of_employees[0]=e1;
    list_of_employees[1]=e2;
    list_of_employees[2]=e3;
    list_of_employees[3]=e4;
    list_of_employees[4]=e5;
    list_of_employees[5]=e6;
    list_of_employees[6]=e7;
    list_of_employees[7]=e8;

    Node *head=NULL;

    TreeNode *root=new TreeNode(0);
    root->visited=true;

    int node_number=1;

    queue<TreeNode *>pendingNodes;

    for(int i=0;i<4;i++){       //As of now parking spots closest to gate are 4.
        TreeNode *child=new TreeNode(node_number);   //creating a new node
        root->children.push_back(child);    //making a connection
        pendingNodes.push(child);
        node_number++;
    }
    while(pendingNodes.size()!=0){
        if(node_number==52){
            break;
        }
        TreeNode *front=pendingNodes.front();
        pendingNodes.pop();
        TreeNode *child=new TreeNode(node_number);
        front->children.push_back(child);
        pendingNodes.push(child);
        node_number++;
    }

    unordered_map<string,int> ourMap;

    Node*ans_Head=NULL;
    int empty_slot=-1;

    Customer c1("Avi",987659,"E","AudiA4","HR1245",2);
    c1.arrival_time_hours=01;   c1.arrival_time_minutes=10;  c1.arrival_time_seconds=23;  c1.parking_space_number=1;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR1245");
    ans_Head=insert_Customer_LL(head,c1);  head=ans_Head;
    pair<string,int>p1("HR1245",c1.password);    ourMap.insert(p1);

    Customer c2("Chetan",997554,"NE","HONDA CITY","HR4297",1);
    c2.arrival_time_hours=02;   c2.arrival_time_minutes=15;  c2.arrival_time_seconds=23;  c2.parking_space_number=2;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR4297");
    ans_Head=insert_Customer_LL(head,c2);  head=ans_Head;
    pair<string,int>p2("HR4297",c2.password);    ourMap.insert(p2);

    Customer c3("Naman",887660,"E","MG HECTOR","HR9241",2);
    c3.arrival_time_hours=01;   c3.arrival_time_minutes=56;  c3.arrival_time_seconds=23;  c3.parking_space_number=3;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR9241");
    ans_Head=insert_Customer_LL(head,c3);  head=ans_Head;
    pair<string,int>p3("HR9241",c3.password);    ourMap.insert(p3);

    Customer c4("Mayank",917513,"NE","Mahindra XUV","HR8097",7);
    c4.arrival_time_hours=02;   c4.arrival_time_minutes=53;  c2.arrival_time_seconds=23;  c4.parking_space_number=4;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR8097");
    ans_Head=insert_Customer_LL(head,c4);  head=ans_Head;
    pair<string,int>p4("HR8097",c4.password);    ourMap.insert(p4);

    Customer c5("Rahul",787657,"E","ZS EV","HR7243",9);
    c5.arrival_time_hours=03;   c5.arrival_time_minutes=17;  c5.arrival_time_seconds=23;  c5.parking_space_number=5;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR7243");
    ans_Head=insert_Customer_LL(head,c5);  head=ans_Head;
    pair<string,int>p5("HR7243",c5.password);    ourMap.insert(p5);

    Customer c6("Palak",937672,"NE","FORD ECOSPORT","HR0074",10);
    c6.arrival_time_hours=04;   c6.arrival_time_minutes=19;  c6.arrival_time_seconds=23;  c6.parking_space_number=6;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR0074");
    ans_Head=insert_Customer_LL(head,c6);  head=ans_Head;
    pair<string,int>p6("HR0074",c6.password);    ourMap.insert(p6);

    Customer c7("Kashish",882368,"E","TATA NEXON","HR1291",4);
    c7.arrival_time_hours=01;   c7.arrival_time_minutes=36;  c7.arrival_time_seconds=23;  c7.parking_space_number=7;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR1291");
    ans_Head=insert_Customer_LL(head,c7);  head=ans_Head;
    pair<string,int>p7("HR1291",c7.password);    ourMap.insert(p7);

    Customer c8("Pulkit",715513,"NE","HONDA CRV","HR3063",2);
    c8.arrival_time_hours=02;   c8.arrival_time_minutes=23;  c8.arrival_time_seconds=23;  c8.parking_space_number=8;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR3063");
    ans_Head=insert_Customer_LL(head,c8);  head=ans_Head;
    pair<string,int>p8("HR3063",c8.password);    ourMap.insert(p8);

    Customer c9("Amit",987631,"E","HYUNDAI KONA","HR3071",5);
    c9.arrival_time_hours=04;   c9.arrival_time_minutes=43;  c9.arrival_time_seconds=23;  c9.parking_space_number=9;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR3071");
    ans_Head=insert_Customer_LL(head,c9);  head=ans_Head;
    pair<string,int>p9("HR3071",c9.password);    ourMap.insert(p9);

    Customer c10("Nikita",837178,"NE","HONDA CIVIC","HR4764",5);
    c10.arrival_time_hours=03;   c10.arrival_time_minutes=32;  c10.arrival_time_seconds=23;  c10.parking_space_number=10;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR4764");
    ans_Head=insert_Customer_LL(head,c10);  head=ans_Head;
    pair<string,int>p10("HR4764",c10.password);    ourMap.insert(p10);

    Customer c11("Anish",992315,"E","TESLA MODEL S","HR3786",2);
    c11.arrival_time_hours=05;   c11.arrival_time_minutes=33;  c11.arrival_time_seconds=23;  c11.parking_space_number=11;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR3786");
    ans_Head=insert_Customer_LL(head,c11);  head=ans_Head;
    pair<string,int>p11("HR3786",c11.password);    ourMap.insert(p11);

    Customer c12("Sanyam",835234,"NE","TOYOTA FORTUNER","HR4863",8);
    c12.arrival_time_hours=05;   c12.arrival_time_minutes=43;  c12.arrival_time_seconds=34;  c12.parking_space_number=12;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR4863");
    ans_Head=insert_Customer_LL(head,c12);  head=ans_Head;
    pair<string,int>p12("HR4863",c12.password);    ourMap.insert(p12);

    Customer c13("Tanvi",903463,"NE","TOYOTA COROLLA","HR9724",6);
    c13.arrival_time_hours=06;   c13.arrival_time_minutes=23;  c13.arrival_time_seconds=23;  c13.parking_space_number=13;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR9724");
    ans_Head=insert_Customer_LL(head,c13);  head=ans_Head;
    pair<string,int>p13("HR9724",c13.password);    ourMap.insert(p13);

    Customer c14("Gopal",997112,"NE","FORD ENDEAVOUR","HR5623",5);
    c14.arrival_time_hours=07;   c14.arrival_time_minutes=22;  c14.arrival_time_seconds=23;  c14.parking_space_number=14;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR5623");
    ans_Head=insert_Customer_LL(head,c14);  head=ans_Head;
    pair<string,int>p14("HR5623",c14.password);    ourMap.insert(p14);

    Customer c15("Nirpha",792214,"E","TATA TIGOR EV","HR9367",6);
    c15.arrival_time_hours=03; c15.arrival_time_minutes=51;  c15.arrival_time_seconds=23;  c15.parking_space_number=15;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR9367");
    ans_Head=insert_Customer_LL(head,c15);  head=ans_Head;
    pair<string,int>p15("HR9367",c15.password);    ourMap.insert(p15);

    Customer c16("Nandini",925294,"NE","HYUNDAI VERNA","HR7629",8);
    c16.arrival_time_hours=04;   c16.arrival_time_minutes=39;  c16.arrival_time_seconds=34;  c16.parking_space_number=16;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR7629");
    ans_Head=insert_Customer_LL(head,c16);  head=ans_Head;
    pair<string,int>p16("HR7629",c16.password);    ourMap.insert(p16);

    Customer c17("Lakshay",943469,"NE","TOYOTA CAMRY","HR2704",6);
    c17.arrival_time_hours=07;   c17.arrival_time_minutes=33;  c17.arrival_time_seconds=23;  c17.parking_space_number=17;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR2704");
    ans_Head=insert_Customer_LL(head,c17);  head=ans_Head;
    pair<string,int>p17("HR2704",c17.password);    ourMap.insert(p17);

    Customer c18("Shruti",897312,"NE","FORD FIGO","HR3681",3);
    c18.arrival_time_hours=04;   c18.arrival_time_minutes=29;  c18.arrival_time_seconds=23;  c18.parking_space_number=18;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR3681");
    ans_Head=insert_Customer_LL(head,c18);  head=ans_Head;
    pair<string,int>p18("HR3681",c18.password);    ourMap.insert(p18);

    Customer c19("Afreen",822810,"E","MAHINDRA E VERITO","HR6727",6);
    c19.arrival_time_hours=04;   c19.arrival_time_minutes=31;  c19.arrival_time_seconds=23;  c19.parking_space_number=19;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR6727");
    ans_Head=insert_Customer_LL(head,c19);  head=ans_Head;
    pair<string,int>p19("HR6727",c19.password);    ourMap.insert(p19);

    Customer c20("Chirag",845294,"NE","MERCEDES","HR1679",8);
    c20.arrival_time_hours=03;   c20.arrival_time_minutes=54;  c20.arrival_time_seconds=34;  c20.parking_space_number=20;
    empty_slot=search_nearest_empty_node(root);
    add_car_to_system(root,empty_slot,"HR1679");
    ans_Head=insert_Customer_LL(head,c20);  head=ans_Head;
    pair<string,int>p20("HR1679",c20.password);    ourMap.insert(p20);

    ans_Head=delete_car_details_from_system(head,root,"HR3063");
    head=ans_Head;

    ans_Head=delete_car_details_from_system(head,root,"HR3071");
    head=ans_Head;

    ans_Head=delete_car_details_from_system(head,root,"HR5623");
    head=ans_Head;

    ans_Head=delete_car_details_from_system(head,root,"HR6727");
    head=ans_Head;

    SYSTEMTIME a,a1,a2;
    GetLocalTime(&a);

    int choice=0;

    while(choice!=8){
        system("Color F3");
        cout<<"\t\tIntelligent Car Parking System\t"<<endl<<endl;
        cout<<"DATE:"<<a.wDay<<"/"<<a.wMonth<<"/"<<a.wYear<<endl;
        cout<<"Time:"<<a.wHour<<":"<<a.wMinute<<":"<<a.wSecond<<endl<<endl;
        cout<<"For non-electric vehicle, the parking charges are 2 rupees per minute."<<endl;
        cout<<"For electric vehicle, the parking charges are 4 rupees per minute."<<endl<<endl;

        cout<<"Press 1 to add new car in the system."<<endl;
        cout<<"Press 2 to search your car in the system."<<endl;
        cout<<"Press 3 to view the parking slots or parking area(tree)."<<endl;
        cout<<"Press 4 for exit model."<<endl;
        cout<<"Press 5 to view customer details."<<endl;
        cout<<"Press 6 to view employee details."<<endl;
        cout<<"Press 7 to see total amount earned by system."<<endl;
        cout<<"Press 8 to terminate the program."<<endl<<endl;
        cout<<"Enter your choice :- ";
        cin>>choice;
        if(choice==1){
            system("CLS");
            int empty_slot=search_nearest_empty_node(root);
            if(empty_slot==-1){
                cout<<"No empty parking space is available."<<endl;
                system("PAUSE");
                system("CLS");
            }
            else{
                cout<<"The nearest empty slot is :- "<<empty_slot<<endl;

                string cust_name,veh_type,veh_name,veh_num;
                int contact_no,time;

                cout<<"Enter name of Customer :- ";
                cin>>cust_name;
                cout<<"Enter contact number :- ";
                cin>>contact_no;
                cout<<"Press E for electric vehicle."<<endl;
                cout<<"Press NE for non-electric vehicle."<<endl;
                cin>>veh_type;
                cout<<"Enter vehicle name :- ";
                cin>>veh_name;
                cout<<"Enter vehicle number :- ";
                cin>>veh_num;
                cout<<"Enter approximate number of hours for which vehicle needs to be parked :- ";
                cin>>time;

                add_car_to_system(root,empty_slot,veh_num);

                Customer C(cust_name,contact_no,veh_type,veh_name,veh_num,time);
                C.parking_space_number=empty_slot;

                system("CLS");
                cout<<"The recorded arrival time is :";
                GetLocalTime(&a1);
                    cout<<a1.wHour<<":";
                    cout<<a1.wMinute<<":";
                    cout<<a1.wSecond<<endl<<endl;

                C.arrival_time_hours=a1.wHour;
                C.arrival_time_minutes=a1.wMinute;
                C.arrival_time_seconds=a1.wSecond;

                cout<<"Your security code is "<<C.password<<endl<<endl;

                Node *ansHead=insert_Customer_LL(head,C);
                head=ansHead;
                pair<string,int>p(C.vehicle_number,C.password);
                ourMap.insert(p);
                cout<<"Your car has been added to the system."<<endl<<endl;
                system("PAUSE");
                system("CLS");
            }
        }
        else if(choice==2){
            system("CLS");
            string V_num;
            cout<<"Enter your vehicle number which is to be searched."<<endl;
            cin>>V_num;
            int node_number=search_your_car(root,V_num);
            if(node_number!=-1){
                cout<<"Your car is parked at number "<<node_number<<" position."<<endl<<endl;
            }
            else{
                cout<<"There is no car parked of this vehicle number."<<endl<<endl;
            }
            system("PAUSE");
            system("CLS");
        }
        else if(choice==3){
            system("CLS");
            cout<<"The parking slots or parking area(tree) :"<<endl<<endl;
            printTree(root);
            cout<<endl;
            system("PAUSE");
            system("CLS");
        }
        else if(choice==4){
            system("CLS");
            string V_num;
            cout<<"Enter your vehicle number for exit process."<<endl;
            cin>>V_num;
            int ans=match_password(ourMap,V_num);
            if(ans==1){
                ourMap.erase(V_num);
                int digit;
                cout<<endl<<"Press 0 for calculation of parking charges."<<endl;
                cin>>digit;

                if(digit==0){
                    system("CLS");
                    calculate_parking_charges(head,V_num);
                    cout<<endl;
                    system("PAUSE");
                    system("CLS");
                    Node *head1=delete_car_details_from_system(head,root,V_num);
                    head=head1;
                }
                else{
                    system("CLS");
                }
            }
            else if(ans==0){
                system("PAUSE");
                system("CLS");
            }
        }
        else if(choice==5){
            system("CLS");
            admin(head,list_of_employees,5);
            system("PAUSE");
            system("CLS");
        }
        else if(choice==6){
            system("CLS");
            admin(head,list_of_employees,6);
            system("PAUSE");
            system("CLS");
        }
        else if(choice==7){
            system("CLS");
            cout<<"Total amount earned by system :- Rs"<<Amount_earned_by_system<<endl<<endl;
            system("PAUSE");
            system("CLS");
        }
        else if(choice!=8){
            system("CLS");
            cout<<"Wrong choice entered."<<endl<<endl;
            system("PAUSE");
            system("CLS");
        }
    }
    system("CLS");
    cout<<"Termination of program."<<endl;

}
