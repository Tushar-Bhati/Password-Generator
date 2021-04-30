#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
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


/*This is required during the saving process*/
int string2int(string s){
	int n=0;
	for(int i=s.length()-1,j=0;i>=0;i--,j++){
		n+=pow(10,j)*int(s[i]-48);
	}
	return n;
}

/*Save the password to system in text format
 * two files are created
* 1.To save password 
* 2.To get position to save next password */
void toSave(string pass){
	fstream passwordFile("password.txt");
	fstream nextLineFile("next.txt");
	string wannaSave;
	cout<<"want to save password (y/n):";
	cin>>wannaSave;
	if(wannaSave=="Y"||wannaSave=="y"){
		
		string hint;
		cout<<"Enter hint (eg: fbpassword):";
		cin>>hint;
		string nextLineString;
		getline(nextLineFile,nextLineString);
		int nextLineInt=string2int(nextLineString);
		
		passwordFile.seekg(nextLineInt);
		passwordFile<<hint<<"\t\t"<<pass<<endl;
		
		nextLineFile.seekg(0);
		nextLineFile<<passwordFile.tellg();
	}
	
	passwordFile.close();
	nextLineFile.close();
}

		
int main(){
    srand(time(NULL));
    	
	while(true){
		
		string password;
		password = generatePassword();
		cout<<password<<endl;
		
		toSave(password);
		
		char generateMore;
		cout<<"Generate More (y/n):";
		cin>>generateMore;
		if(generateMore=='y'||generateMore=='Y'){
			cout<<endl;
			continue;
		}
		break;
		
	}
}
