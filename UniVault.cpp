#include <iostream>      // For input and output
#include <fstream>       // We used this header file for file handling
#include <iomanip>       // For setw etc
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

void loadingData(int& numofDepartments, int& floorsperDepartment, int& roomsperFloor)
{
    ifstream fin("config.txt");    // So that we can open data.txt to read it
   
    if(fin.is_open())            // To check the existence of file
    {
        fin>>numofDepartments>>floorsperDepartment>>roomsperFloor;   // if existence is true the 3 integers are read
        fin.close();     // It is also very importatnt to close the file, so that the system resources frees up

        // Data of the file is being diplayed
        cout<<"config.txt has been loaded successfully"<<endl;
        cout<<"Number of Departments : "<<numofDepartments<<endl;
        cout<<"Floors per Department : "<<floorsperDepartment<<endl;
        cout<<"Rooms Per Floor       : "<<roomsperFloor<<endl;
        cout<<endl;
    }

    // If the data.txt does not have existence
    else
    {
        cout<<"config.txt is not found. Kindly, enter the dimensions ofe your campus"<<endl;
       
        // The user will input the dimensions of his/her university campus
        cout<<"Enter the Number of Departments: "<<endl;
        cin>>numofDepartments;

        cout<<"Enter the Number of Floors per Department: "<<endl;
        cin>>floorsperDepartment;

        cout<<"Enter the Number of Rooms per Floor"<<endl;
        cin>>roomsperFloor;


        ofstream fout("config.txt");       // Creating a new file
        if(fout.is_open())               // Opening the file to write data into it
        {
            // Here we are feeding the data into the file
            fout<<numofDepartments<<endl;
            fout<<floorsperDepartment<<endl;
            fout<<roomsperFloor<<endl;
            fout.close();                // Finished feeding data
            cout<<endl;
            cout<<"config.txt has been created for future use"<<endl;   // Message
            cout<<endl;
        }
        else
        {
            cout<<endl;
            cout<<"Failed to feed data into data.txt"<<endl;
            cout<<endl;
        }
    }
}

int*** structure(int numofDepartments, int floorsperDepartment, int roomsperFloor)   // We used int*** because we want the entire 3D structure
{
    int*** layerOne = new int**[numofDepartments];        // This is actually the layer 1
   
   
    for(int i=0; i<numofDepartments; i++)         // This loop goes through each department
    {
        *(layerOne + i) = new int*[floorsperDepartment];   // Layer 2

        for(int j=0; j<floorsperDepartment; j++)        // This loop goes through each floor of department
        {
            *(*(layerOne + i) + j) = new int[roomsperFloor];    // Layer 3
       

        for(int k=0; k<roomsperFloor; k++)  
        {
            *(*(*(layerOne + i) + j) + k) = 0;        // Equating it equal to 0 so that it doesn't create garbage value
        }
        }
    }

    // Just a feedback
    cout<<"The Campus has: "<<endl;
    cout<<numofDepartments<<" number of departments, "<<endl;
    cout<<floorsperDepartment<<" number of floors per departments, and "<<endl;
    cout<<roomsperFloor<<" rooms per floor"<<endl;
   
   
    cout<<"The total "<<(numofDepartments * floorsperDepartment * roomsperFloor)<<" room slots are set to 0(vacant)"<<endl;
    cout<<endl;

    // this is the address of the memory i created on heap
    return layerOne;
 }  

 void deleteHeap(int*** layerOne, int numofDepartments, int floorsperDepartment)
 {
    for(int i=0; i<numofDepartments; i++)     // Looping through every department
    {
        for(int j=0; j<floorsperDepartment; j++)  // looping through all the floors per department
        {
            delete[] *(*(layerOne + i) + j);       // deleting the rooms array
        }

        delete[] *(layerOne + i);    // deleting the floors array
    }
    delete[] layerOne;    // deleting the departments array
   
    // Message
    cout<<"The heap data of Campus has been deleted successfully"<<endl;
}


void verificationcleanState(int*** layerOne, int numofDepartments, int floorsperDepartment, int roomsperFloor)
{
    // Preparing the Report
    cout<<"///////////////////////////////////////////////////"<<endl;
    cout<<"           VERIFICATION(all values must 0)         "<<endl;
    cout<<"///////////////////////////////////////////////////"<<endl;

    cout<<left<<setw(6)<<"Number of Departments"<<setw(7)<<"Floors per Department"<<setw(6)<<"Rooms per Floor"<<setw(16)<<"Adress"<<setw(6)<<"VALUE"<<endl;
    cout<<"///////////////////////////////////////////////////"<<endl;

    // Nested Structure so that we can visit every single memory address
    for(int i=0; i<numofDepartments; i++)
    {
        for(int j=0; j<floorsperDepartment; j++)
        {
            for(int k=0; k<roomsperFloor; k++)
            {
                int* room = *(*(layerOne + i) + j) + k;   // this is the exact meemory address where the room persists in the RAM

                cout<<left<<setw(6)<<i<<setw(7)<<j<<setw(6)<<k<<setw(16)<<(void*)room<<setw(6)<<*(*(*(layerOne + i) + j) + k)<<endl;    // heap address + value at taht address
            }
        }
    }
    cout<<"/////////////////////////////////////////////////////"<<endl;
    cout<<endl;
}


void enrollStudent(int***grid,char** &names,int* &ids,float* &gpas, int* &statuses, int &numstudents,int nd,int nf,int nr){
    cout<<"Enter student name: "<<endl;
    char temp[100];
    cin >> ws;
cin.getline(temp,100);
   
    char* allocname=new char[strlen(temp)+1];//a memory of the size of temp array is being allocated to allocname. we used strlen bcz we dont know the size of what the user input
    strcpy(allocname,temp);
    int newID=1000+numstudents+1;///we picked 1000 as a random starting point for id nums. so IDs will be 1000, 1001 1002 n so on
    int* newIds=new int[numstudents+1];
    for(int i=0;i<numstudents;i++)//make a new array, one slot bigger than before
        newIds[i]=ids[i];//copy all studnts into new array
     delete[] ids;
     ids=newIds;//ids points to the new bigger array
   
   
    float* newgpas=new float[numstudents+1];//a memory of the size of temp array is being allocated to allocname. we used strlen bcz we dont know the size of what the user input

    for(int i=0;i<numstudents;i++)//make a new array, one slot bigger than before
        newgpas[i]=gpas[i];
     delete[] gpas;
     gpas=newgpas;
   
   
    int* newstatuses=new int[numstudents+1];
    for(int i=0;i<numstudents;i++)//make a new array, one slot bigger than before
        newstatuses[i]=statuses[i];
     delete[] statuses;
     statuses=newstatuses;
     
    char** allocnames=new char*[numstudents+1];
    for(int i=0;i<numstudents;i++)
    allocnames[i]=names[i];
    delete[]names;
    names=allocnames;//redirects pointer.hasnt added data yet
   
    names[numstudents]=allocname;  
    ids[numstudents]=newID;
    gpas[numstudents]=0.0;
    statuses[numstudents]=0;
    numstudents=numstudents+1;
   
    int d=rand()%nd;
    int f=rand()%nf;
    int r=rand()%nr;
    bool roomassigned=false;
   
    if(*(*(*(grid+d)+f)+r)!=0){ //i.e: room is occupied, so HAVE to loop thru building to see k jagha kahan milay for room
    for(int i=0;i<nd;i++){
    for(int j=0;j<nf;j++){
    for(int k=0;k<nr;k++){
    if(*(*(*(grid+i)+j)+k)==0){
        *(*(*(grid+i)+j)+k)=newID;
        roomassigned=true;
        break; //escape innermost(k wala loop)
    }
    }
    if(roomassigned==true)//for j loop
    break;
   
}
if(roomassigned==true)
break;//break for i loop
}
}
else{
    *(*(*(grid+d)+f)+r)=newID; //the room was vacant, just assign it to the studetnt.
}
cout<<"Assigned Room: Dept "<<d<<" Floor "<<f<<" Room "<<r<<endl;

}


void deletedataofStudents(char** &namesofallStudents, int* &identity, float* &marks, int* &conditions, int& numofStudents, int i)  // here we are modifying the orignal pointers that is why we have passed them by reference
{
    delete[] namesofallStudents[i];  //deleting the name of the student who is graduating
    namesofallStudents[i] = 0;       // setting it equal to zero

    for(int a=i; a<numofStudents-1; a++)   // i started the loop from the graduated student and stooped it at numofStudents - 1, so that i do not go out of bounds
    {
        // we shifted all so that our list remain compact when one leaves from it, he can leave from middle or what so ever, but we fill that space
        namesofallStudents[a] = namesofallStudents[a+1];  
        identity[a] = identity[a+1];
        marks[a] = marks[a+1];
        conditions[a] = conditions[a+1];
    }

    int newCapacity = numofStudents - 1;   // Because we are removing one student at a time, that is why, the new capcaity newStudents - 1
    char** namesofnewStudents = new char*[newCapacity];

    for(int i=0; i<newCapacity; i++)   // looping through the new capacity
    {
        namesofnewStudents[i] = namesofallStudents[i];  // bascally we are copying the addrresses from old to the new ones
    }
    delete[] namesofallStudents;  // for the prevention of memory leak, i am deleting the larger array from the RAM
    namesofallStudents = namesofnewStudents;   // So, here we are pointing the origanl variable to a resixed array

    int* newIdentity = new int[newCapacity]; // this is the new block of memeory for Identities
   
    for(int i=0; i<newCapacity; i++)   // loopin through the new capacity
    {
        newIdentity[i] = identity[i];  // this is done to copy identities from old to the new one
    }
       
    delete[] identity;   // deleting the older larger array
    identity = newIdentity;   // copying the adresses from old to the new


    float* newMarks = new float[newCapacity];   // creation of the new mwmory block for the gpa
   
    for(int i=0; i<newCapacity; i++)
    {
        newMarks[i] = marks[i];            // we are copying the gpas from the old to the new one
    }

    delete[] marks;    // here we are deallocating the older array which is bigger
   
    marks = newMarks;    // here we are redirecting the the older larger array to the new smaller array

    int* newCondition = new int[newCapacity];   // here we are allocating new block of memory for the capacity
   
    for(int i=0; i<newCapacity; i++)    // looping through the new capacity
    {
        newCondition[i] = conditions[i];    // copying thr conditions from old to the new ones
    }

    delete[] conditions;   // we are deallocating the older larder array

    conditions = newCondition; // we are redirecting the larger pointer to the smaller array

    numofStudents--;   // We are doing it so that it is known in the rest of the program that we have one less student now

}




void academicSimulation(int*** map, char** &namesofallStudents, int* &identity, float* &marks, int* &conditions, int &numofStudents, int numberofDepartments, int floorsperDepartment, int roomsperfloor, int logIns)  // Function for academic Simulation
{
cout<<"///////////////////////////////////////////////////////////"<<endl;
cout<<"LOG-IN "<<logIns<<" Results"<<endl;
cout<<"///////////////////////////////////////////////////////////"<<endl;

if(numofStudents == 0)                 // Input Validation
{
    cout<<"No students have been enrolled. There is nothing to simulate"<<endl;
    return;
}

unsigned char decider = 0;         // The bit 0 is used to represent progress, bit 1 for warning and bit 2 for graduation

for(int i=numofStudents-1; i>=0; i--)   // this loops through all the students but in the backward manner
{
    int randomNumber = (rand() % 10) + 1;  // for a random number generation between 1 to 10


    // menu printing
    cout<<" Student: "<<left<<setw(20)<<namesofallStudents[i]
        <<" | ID: "<<identity[i]
        <<" | Result: "<<randomNumber<<" >>> ";   // fate of the student

        // progress of academics

        if(randomNumber >= 1 && randomNumber <= 5)
        {
            marks[i] += 0.1f;          // let's increase the gpa
            if(marks[i] > 4.0f)
            {
                marks[i] = 4.0f;       // Makes the threshold as 4
            }
            conditions[i] = 0;         // Sets the staus to studying

            decider |= (1 << 0);       // Sets the 0th bit (Progress)

            // Printing
            cout<<"PROGRESS | Gpa now "<<fixed<<setprecision(2)<<marks[i]<<endl;
        }

        else if(randomNumber >= 6 && randomNumber <= 8)   // under this range, no change happens
        {
            cout<<"STEADY | No Alteration"<<endl;
        }

        else if(randomNumber == 9)
        {
            conditions[i] = 1;          // it sets the status to warning
            marks[i] -= 0.2f;              // decrementing thr gpa

            if(marks[i] < 0.0f)         // So that the answer does not get in negative
            {
                marks[i] = 0.0f;        // setting it equal to 0
            }

            decider |= (1 << 1);        // setting the 1th bit as Warning

            // Displaying it on the screen
            cout<<"WARNING | gpa now "<<fixed<<setprecision(2)<<marks[i]<<endl;
        }

        else
        {
            conditions[i] = 2;    // Setting the staus to graduating
            decider |= (1<<2);    // setting the 2th bit, this will use for graduation  
       
            bool cleaned = 0; // created a boolean

            // We are using nested loops so that we can scan the 3D structire and delete the data at student's rooms
            for(int j=0; j<numberofDepartments && !cleaned; j++)
            {
                for(int k=0; k<floorsperDepartment && !cleaned; k++)
                {
                    for(int l=0; l<roomsperfloor && !cleaned; l++)
                    {
                        if(*(*(*(map + j)+k)+l) == identity[i])   // condition to check if the identity at the specific room matches the students who is actually graduating
                        {
                            *(*(*(map + j) + k) + l) = 0;      // Seting the room equal to zero
                            cleaned = 1;
                            cout<<"GRADUATING| room ["<<j<<"]["<<k<<"]["<<l<<"] is cleared"<<endl;
                        }
                    }
                }
            }

            // Deleting the students from each and every parallel array
            deletedataofStudents(namesofallStudents, identity, marks, conditions, numofStudents, i);
               
        }
}

cout<<endl;
cout<<"/// Log In: "<<logIns<<" Summary";
cout<<"(FLAGS = )"<<(int)decider<<"///"<<endl;   // We are using int becaus eit helps in debugging, suppose it is 5 we know it is 101 so we knoe that progress and graduation are active

if(decider & (1<<0))  // when the 0th bit and decider both are 1
{
    cout<<"(+) Atleast one student made prgress academically"<<endl;
}

if(decider & (1 << 1))  // when the 1st bit is 1 and so on
{
cout<<"(!): At least one student received warning"<<endl;
}

if(decider & (1<<2))  // when the 2nd bit is 1
{
    cout<<"(*) Atleast one student graduates at this log-in"<<endl;
}

if(decider == 0)     // when the decider is 0
{
cout<<"(-)All the students remained without any alteration"<<endl;
}

// Prints the number of remaining students
cout<<"Remaining Students: "<<numofStudents<<endl;
cout<<"//////////////////////////////////////////////////////////"<<endl;

}

// this function is taking arrays to students data arrays
void printingDashboard (char** namesofallStudents, int* identities, float* marks, int* conditions, int numofStudents)
{
    // Here we are saying 0, 1, 2 are represented as follows
    const char* elaboration[] = {"Studying", "Warning", "Graduating"};

    // This is the top border of out table
    cout<<"/////////////////////////////////////////////////////////"<<endl;
   
    // Giving headings
    cout<<left<<setw(5)<<"Idx"<<setw(8)<<"Id"<<setw(20)<<"Name"<<setw(8)<<"Gpa"<<"Status"<<endl;

    // Printing the seperator of my table of my table
    cout<<"/////////////////////////////////////////////////////////"<<endl;

    if(numofStudents == 0)         // When there are no students
    {
        cout<<"      (No Students are enrolled)"<<endl;
    }
    else
    {
        // Aligning data in a presentable way

        for(int i=0; i<numofStudents; i++)   // here we are looping through all the students
        {
            cout<<left<<setw(5)<<i<<setw(8)<<identities[i]<<setw(20)<<namesofallStudents[i]<<setw(8)<<fixed<<setprecision(2)<<marks[i]<<elaboration[conditions[i]]<<endl;   // Here er will print the word based on 0, 1, 2
        }

    }

    cout<<"/////////////////////////////////////////////////////////"<<endl;

}

// Function for the display
void displaying (int*** map, char** namesofallStudents, int* identity, float* marks, int* condition, int numofStudents, int numberofStudents, int floorsperDepartment, int roomsperFloor, int* departmnetIndex, int* floorIndex, int logIn)
{

    // for Windows we check if it is compilable
    #ifdef _WIN32
    system("cls");//this is used to clear the screen

    // This is for Linux and Mac
    #else
    system("clear");    // this is used to clear thr screen

    // here we are ending the conditional block of preprocessing
    #endif


    // This is the borderline I ma using as a seperator
    cout<<"//////////////////////////////////////////////////////"<<endl;
   
    cout<<"               The Live Resource Dashboard"<<endl;   // This is my title
 
    cout<<"//////////////////////////////////////////////////////"<<endl;   // Another border

    // These are the lines for information
    // We are using setfill('0') because if the number we woulld make it 05 because setw(2) ensures it that the number will take 2 spaces
    cout<<"(Dept: "<<setfill('0')<<setw(2)<<*departmnetIndex<<")"
        <<"(Floor: "<<setfill('0')<<setw(2)<<*floorIndex<<")"
        <<"(Rooms: "<<setfill('0')<<setw(2)<<roomsperFloor<<")"
        <<"(LogIn: "<<setfill('0')<<setw(3)<<logIn<<")"
        <<setfill(' ')<<endl;   // Here we arae filling with sapces so that the other text is not full of zeros
   
    cout<<"////////////////////////////////////////////////////////////////////"<<endl;   // border
    // It'll be displayed on the screen
    cout<<left
        <<setw(18)<<"Room addr"
        <<setw(8)<<"Id"
        <<setw(22)<<"Name"
        <<setw(8)<<"Gpa"
        <<"Status"
        <<endl;
    cout<<"////////////////////////////////////////////////////////////////////"<<endl;   // border


    // So, it basically loops through each and every loop, when we choose a department as well as a floor
    for(int i=0; i<roomsperFloor; i++)
    {
        // here we are calculating the address of the room
        int* roomAddress = *(*(map + *departmnetIndex) + *floorIndex) + i;
       
        // Here we are getting the student id inside that room
        int studentId = *(*(*(map + *departmnetIndex) + *floorIndex) + i);

        // here we are printing the hexadecimal address
        cout<<left<<setw(18)<<(void*)roomAddress;

        // Here we are checking if the room is empty
        if(studentId == 0)
        {
            cout<<setw(8)<<"////"<<setw(22)<<"//////////"<<setw(8)<<"0.00"<<"Empty"<<endl;
        }

        else
        {
            // We will do the linear search here, to find the GPA/ names of studemts in te parallel arrays
            int caughtIndex = -1;

            for(int i=0; i<numofStudents; i++)
            {
                if(identity[i] == studentId)  // Found the match
                {
                    caughtIndex = i;        // This is the index stored in the variable
                    break;
                }
            }

            // when we find the index then we print this
            if(caughtIndex != -1)
            {
                // Here we are using ternary so that 0 is Studying, 1 is Warning, otherwise it is graduating
                const char* labelofCondition = (condition[caughtIndex] == 0) ? "Studying" :
                                               (condition[caughtIndex] == 1) ? "Warning"  : "Graduating";

                                               // For displaying
                                               cout<<setw(8)<<identity[caughtIndex]
                                                   <<setw(22)<<namesofallStudents[caughtIndex]
                                                   <<fixed<<setprecision(2)
                                                   <<setw(8)<<marks[caughtIndex]
                                                   <<labelofCondition<<endl;
            }
        }
    }

    cout<<"/////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"KEY BUTTONS: E: enroll, T: step, J: jump, F: find, S: save, X: exit"<<endl;
    cout<<"/////////////////////////////////////////////////////////////////////////"<<endl;
   
}

// We are using this function so that we do not remain stuck at one department, floor, etc
void changeofState(int* departmentIndex, int* floorIndex, int numberofDepartments, int floorsperDepartment)
{
    int rockyDepartment = -1;   // This is the variable in which user will enter the choice for the new department

    int rockyFloor = -1;   // This is the variable in ehich the user will enetr the choice for the new floor

    cout<<"Enter the index of department (0 to "<<numberofDepartments-1<<"): ";   // Here we are asking the user for the index of the department
    cin>>rockyDepartment;

    if(rockyDepartment < 0 || rockyDepartment >= numberofDepartments)
    {
        cout<<"The index is of invalid department. The jump is cancelled."<<endl;
        return;         // we are exiting the function, we are doing this so that the variables in the main remain unchanged
    }

    // Here we are sking the user for the index of floor
    cout<<"Enter the index of Floor (0 to "<<floorsperDepartment-1<<"): ";
    // Taking input from the user
    cin>>rockyFloor;

    // Input Validation
    if(rockyFloor < 0 || rockyFloor >= floorsperDepartment)
    {
        cout<<"The floor index is invalid. The jump is cancelled."<<endl;
        return;  // we want the variables to remain unchanged in main that is why we are terminating from the function
    }

    // Here we are updating the pointers
    *departmentIndex = rockyDepartment;
    *floorIndex = rockyFloor;

}

// This function is used to update the position only if it is valid
void updatePosition(int* departmentIndex, int* floorIndex, int numberofDepartments, int floorsperDepartment)
{
    // This is the variable which will store user choice for new department
    int rockyDepartment = -1;

    // This is the variable which will store user cjhoice for new floor
    int rockyFloor = -1;

    // Asking the user
    cout<<"Enter the index of department (0 to"<<numberofDepartments-1<<"): "<<endl;
    cin>>rockyDepartment;   // Taking Input

    // Input Validation
    if(rockyDepartment < 0 || rockyDepartment >= numberofDepartments)
    {
        cout<<"The input is not valid. That is why we can't switch to it"<<endl;
        return;        // If this function we are terminatung from the function straightly
    }

    // Taking input from the user
    cout<<"Enter the index of floor (0 to "<<floorsperDepartment-1<<"): "<<endl;
    cin>>rockyFloor;

    if(rockyFloor < 0 || rockyFloor >= floorsperDepartment)
    {
        cout<<"The index of floor is invalid. That is wehy the switch is cancelled"<<endl;
        return;   // In this case we will terminate from the function
    }

    // We are derefernecing the orignal variable of main and assigning the validated department of index to it
    *departmentIndex = rockyDepartment;

    // We are dereferencing the new index of floor to the variable in the main
    *floorIndex = rockyFloor;

    cout<<"The view jumped to the department: "<<rockyDepartment
        <<",Floor "<<rockyFloor<<"."<<endl;

}

//M5
void findStudent(int ***grid,char**names,int*ids,float* gpas,int* statuses,int numStudents,int nd,int nf,int nr){
    int enteredID;
    cout<<"Enter student ID: "<<endl;
    cin>>enteredID;
   
   

bool found=false;
int index_found=-1;
for(int i=0;i<numStudents;i++){
    if(ids[i]==enteredID){
    found=true;
    index_found=i;
    break;//the req ID hs been found so,stop searching now and exit the loop
}
}
if(found==false)
cout<<"not found"<<endl;

if(found==true){
    cout<<"Name: "<<names[index_found]<<endl;//prniting req student info
    cout<<"GPA: "<<gpas[index_found]<<endl;
   const char* statusLabel[]={"Studying","Warning","Graduating"};
   cout<<"Status: "<<statusLabel[statuses[index_found]]<<endl;
 
 for(int d=0;d<nd;d++){
     for(int f=0;f<nf;f++){
         for(int r=0;r<nr;r++)
         if(*(*(*(grid+d)+f)+r)==enteredID)
         cout<<"Room: Dept "<<d<<" Floor "<<f<<" Room "<<r<<endl;
     }
 }  
}
   
}

//m6
void saveData(int***grid,char**names,int*ids,float*gpas,int* statuses,int numstudents,int nd,int nf,int nr){

ofstream fout("database.txt"); //this fn is basically saving all student records &occupied room data from 3d campus grid into data.txt
if(fout.is_open()){
    fout<<numstudents<<endl;
   

    for(int i=0;i<numstudents;i++){
        int dI = -1, fI = -1, rI=-1;
    for(int d=0;d<nd;d++)
    for(int f=0;f<nf;f++)
    for(int r=0;r<nr;r++)
    if(*(*(*(grid+d)+f)+r)==ids[i])
    {
        dI = d;
        fI = f;
        rI = r;
    }
    fout<<ids[i]<<"|"<<names[i]<<"|"<<gpas[i]<<"|"<<statuses[i]<<"|"<<dI<<"|"<<fI<<"|"<<rI<<endl;
}
fout.close();
cout<<"saved!"<<endl;
}
}

void loadData(int***grid,char**&names,int*&ids,float*&gpas,int*&statuses,int&numstudents,int nd,int nf,int nr){//loads studentrecords and grid occupancy from database.txt on startup
    int id;
    char name[100];
    float gpa;
    int status;
    int dI, fI, rI;
    ifstream fin("database.txt");
    if(fin.is_open()){
        fin>>numstudents;
        names=new char*[numstudents]; //allocating array for each one 
        ids=new int[numstudents];
        gpas=new float[numstudents];
        statuses=new int[numstudents];
        
        for(int i=0;i<numstudents;i++){
        char sep; 
        fin>>id>>sep;
        fin.getline(name,100,'|');
        fin>>gpa>>sep>>status>>sep>>dI>>sep>>fI>>sep>>rI;
        fin.ignore(1000,'\n');
        ids[i]=id;
        gpas[i]=gpa;
        statuses[i]=status;
        names[i]=new char[strlen(name)+1]; //+1 bcz one greater than normal array size in char usually
        strcpy(names[i],name);

        if(dI >= 0 && fI >= 0 && rI >= 0)
        {
        *(*(*(grid+dI)+fI)+rI) = id;
        }
    }
    fin.close();
}
}


int main()
{
    srand(time(0));//to ensure we have a diff room ever run
    cout<<"//////////////////////////////////////////////////////"<<endl;
    cout<<"        UniVault, Module-1: Initialiser (Test)"<<endl;
    cout<<"/////////////////////////////////////////////////////"<<endl;
    cout<<endl;

    // Initialsing the variables
    int numofDepartments = 0;
    int floorsperDepartment = 0;
    int roomsperFloor = 0;
   
    char** names=nullptr;
    int* ids=nullptr;
    float* gpas=nullptr;
    int* statuses=nullptr;
    int numstudents=0;

    // This Function is being used to read or create the data.txt file
    loadingData(numofDepartments, floorsperDepartment, roomsperFloor);
    int*** storeAddress= structure(numofDepartments, floorsperDepartment, roomsperFloor);   // This function actually reserves the memory in the heap and it returns the address of meemory i created on heap
    
   loadData(storeAddress,names,ids,gpas,statuses,numstudents,numofDepartments,floorsperDepartment,roomsperFloor); 
     

    // verificationcleanState(storeAddress, numofDepartments, floorsperDepartment, roomsperFloor); // It verifies that all the values are set to 0, it is also used to print every cell's address + value
 
   

    char key;   // it is a varaiable and its value will be determined by user
   
    int logIn = 0; // it counts the total number of logIns during the simulation

    int currentDepartment = 0;   // this tells what department is currently displayed
    int currentFloor = 0;  // this tells what floor is currently displayed
   

    displaying(storeAddress, names, ids, gpas, statuses, numstudents, numofDepartments, floorsperDepartment, roomsperFloor, &currentDepartment, &currentFloor, logIn);
   
    while(1)
    {

    // Printing this for the help of the user    
    cout<<"Please enter 'E' to Enroll, 'T' to step, 'S' to save, 'F' to find, 'J' to jump, 'X' to exit"<<endl;
    cin>>key;

    // when user enters E
    if(key == 'E' || key == 'e')
    {
        enrollStudent(storeAddress,names,ids,gpas,statuses,numstudents,numofDepartments,floorsperDepartment,roomsperFloor);
       
        displaying(storeAddress, names, ids, gpas, statuses, numstudents, numofDepartments, floorsperDepartment, roomsperFloor, &currentDepartment, &currentFloor, logIn);   // for updating the display
    }

    //when user presses enter
    else if(key =='T'||key=='t')
    {
        logIn++;   // Increasing the log in by 1
        academicSimulation(storeAddress, names, ids, gpas, statuses, numstudents, numofDepartments, floorsperDepartment, roomsperFloor, logIn);  // it starts the simulation
          // it is used to show the results

        displaying(storeAddress, names, ids, gpas, statuses, numstudents, numofDepartments, floorsperDepartment, roomsperFloor, &currentDepartment, &currentFloor, logIn);   // for updating the display
    }

    else if(key=='J' || key == 'j')
    {
        updatePosition(&currentDepartment, &currentFloor, numofDepartments, floorsperDepartment);   // Calling the jump view function
       
        displaying(storeAddress, names, ids, gpas, statuses, numstudents, numofDepartments, floorsperDepartment, roomsperFloor, &currentDepartment, &currentFloor, logIn);  // Calling the function to diplay the dashboard
    }



    else if(key == 'X' || key == 'x')//for ending/exiting program
    {
        cout<<"Termininating the Program"<<endl;
        break;
    }
   
    else if(key=='F'||key=='f'){//for findig the req student
        findStudent(storeAddress,names,ids,gpas,statuses,numstudents,numofDepartments,floorsperDepartment,roomsperFloor);
    }
    else if(key=='s'||key=='S'){
    saveData(storeAddress,names,ids,gpas,statuses,numstudents,numofDepartments,floorsperDepartment,roomsperFloor);
    }
    else
    {
        cout<<"Invalid Input! Input AGAIN!!!"<<endl;
    }
    }

    // Deleting the individual student bnames in string form
    for(int i=0; i<numstudents; i++)
    {
        delete[] names[i];
    }
   
    // deleting the array of pointers for the names of students
        delete[] names;

    // Also deleting other parallael arrays to prevent the memory leak    
        delete[] ids;
        delete[] gpas;
        delete[] statuses;

    // Here I am freeing up the Campus grid
        deleteHeap(storeAddress, numofDepartments, floorsperDepartment);
        storeAddress = 0;   // putting it equal to zero to prevent it to be used again
   
       

    return 0;
}
