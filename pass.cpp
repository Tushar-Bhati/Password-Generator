#include <iostream>
#include <fstream>
using namespace std;

short length;
char c[]={ '!', '@', '#', '$', '%', '^', '&', '*'};

/* get length of password from user
     * condition:-
     * 		lenght should be greater then 7*/
void getlength(){
	cout<<"PASSWORD LENGTH:";
	while(true){
		cin>>length;
		if(length>16||length<8){
			cout<<"PASSWORD LENGTH(8-16):";
			continue;
		}
		break;
	}
}

/*This function will decide the number of char, numbers & special character
 *  >first it takes the length of the password from the user
 *  >then randomly decide number of char, numbers & special character
 *  >randomly add char, numbers & special character
 *  >then swap the characters to randomize it */
string generatePassword(){
	getlength();
	
    short ulength=2+rand()%(length-7);    length-=ulength;
    short llength=2+rand()%(length-5);    length-=llength;
    short nlength=2+rand()%(length-3);    length-=nlength;
    short slength=length;
    
    
    //PASSWORD GENERATION (CHARACTER)
    string s="";
    while(ulength--){
        s+=char(rand()%26+65);
    }
    while(llength--){
        s+=char(rand()%26+97);
    }
    while(nlength--){
        s+=char(rand()%10+48);
    }
    while(slength--){
        s+=c[(rand()%8)];
    }
    
	//SWAPING so that we get completely random password
    short swapps=rand()%26 +25;
    while(swapps--){
        swap(s[(rand()%s.length())],s[(rand()%s.length())]);
    }
    
    return s;
}

void createfile(){
	ifstream passwordFile("password.txt");;
	ifstream nextLineFile("next.txt");
	
	if(!passwordFile.is_open()){
		ofstream newpasswordFile;
		newpasswordFile.open("password.txt");
		newpasswordFile.close();
	}
	
	if(!nextLineFile.is_open()){
		ofstream newnextLineFile;
		newnextLineFile.open("next.txt");
		newnextLineFile<<0;
		newnextLineFile.close();
	}
	
	passwordFile.close();
	nextLineFile.close();
}

/*Save the password to system in text format
 * two files are created
* 1.To save password 
* 2.To get position to save next password */
void Save(string pass){
	createfile();
	
	fstream passwordFile("password.txt");
	fstream nextLineFile("next.txt");
	
	string hint;
	cout<<"Enter hint (eg: fbpassword): ";
	cin>>hint;
	
	int nextLine;
	nextLineFile>>nextLine;
	
	passwordFile.seekg(nextLine);
	passwordFile<<hint;
	passwordFile<<(hint.length()<8?"\t\t":"\t");
	passwordFile<<pass<<endl;
	cout<<"Hint: "<<hint<<"\tPassowrd: "<<pass<<endl<<"Saved"<<endl;
	nextLineFile.seekg(0);
	nextLineFile<<passwordFile.tellg();
	
	passwordFile.close();
	nextLineFile.close();
}


void Help(){
	cout<<"-----------------------"<<endl;
	cout<<"1. Generate Password\n";
	cout<<"2. Save Password\n";
	cout<<"3. show All Password\n";
	cout<<"4. Clear All Password\n";
	cout<<"5. Help\n";
	cout<<"6. Exit\n";
	cout<<"-----------------------"<<endl;
}


void printlist(){
	fstream passwordFile("password.txt");
	string line;
	while(getline(passwordFile,line)){
		cout<<line<<endl;
	}
	passwordFile.close();
}


void Clear(){
	char c;
	while(true){
		cout<<"\nWARNING! \nConfirm to delete all save password(y/n):";
		cin>>c;
		if(c=='Y'||c=='y'){		
			ofstream file;
			file.open("password.txt");
			file.open("next.txt");
			file<<0;
			break;
		}
		else if(c=='n'||c=='N'){
			break;
		}
		else{
			cout<<"Invalid Input\n";
			continue;
		}
	}
}

	
int main(){
    srand(time(NULL));
    Help();
    string input,password="";
	while(true){
		cout<<"\nUser$:";
		cin>>input;
		
		if(input=="1"){
			password = generatePassword();
			cout<<password<<endl;
		}
		if(input=="2"){
			if(password==""){
				cout<<"No password generated\n";
			}
			else{
				Save(password);
			}
		}
		if(input=="3"){
			printlist();
		}
		if(input=="4"){
			Clear();
		}
		if(input=="5"||input=="help"||input=="Help"){
			Help();
		}
		if(input=="6"){
			break;
		}
		
	}
	return 0;
}
