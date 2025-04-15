#include <iostream>
#include <string>
#include <sstream>

int main(){
	std::string valore,scrX,scrY;
	char risp;
	
	system("title avvio.exe");
	
	do{
		system("cls");
		//chiedo l'argomento del valore del vettore
		std::cout<<"Inserisci il primo argomento (valore del vettore: max 1024 / min 5):"<<'\n';
		std::cin>>valore;
		
		std::cout<<"Vuoi inserire le dimensioni dello schermo? [y/n] >> ";
		std::cin>>risp;
		std::cin.ignore(1,'\n');
		
		if(risp=='y'){
			//chiedo gli argomenti per la grandezza dello schermo
			std::cout<<"Inserisci la larghezza dello schermo):"<<'\n';
			std::cin>>scrX;
			std::cin.ignore(80,'\n');
			std::cout<<"Inserisci l\'alteza dello schermo):"<<'\n';
			std::cin>>scrY;
			std::cin.ignore(80,'\n');
		}else{
			scrX="1280";
			scrY="720";
		}
		
		std::ostringstream str;
		str<<"SortingAlgorithm.exe "<<valore;
		str<<" "<<scrX<<" "<<scrY;
		
		std::string cmd=str.str();
		std::cout<<cmd<<'\n';
		system(cmd.c_str());
		
		system("pause");
		
		//vuoi ripetere?
		std::cout<<"Vuoi ricaricare codesto programma? [y/n] >> ";
		std::cin>>risp;
		std::cin.ignore(1,'\n');
	}while(risp!='n');
	
	return 0;
}
