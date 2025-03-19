#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Services 
{
  int serviceId;
  char serviceDesc[30];
  int petType;
  float price;

};


struct Pet 
{
  char petName[30];
  int petType;
  char genderCode;
  char ownerName[30];

};

void readingserviceFile(struct Services allServices[15]);
int readPets(struct Pet allPets[]);
int findPetRecord (char petName[], char ownerName[], struct Pet allPets[], int currentNumberOfPets);
struct Pet createNewPetRecord(char petName[], char ownerName[]);
int selectServices(struct Services allServices[], struct Services customerServices[], struct Pet onePet);
void getPaymentInfo(long int *cardNumber, int *expireMotnh, int *expireYear, int *cvvCode);
float printReceipt (long int cardNumber, int expireMonth, int expireYear, int cvvCode, struct Services customerServices[], struct Pet onePet, int numServices);
int main ()
{



struct Services allServices[15];
struct Services customerServices[4];
struct Pet allPets[30];
int currentNumberOfPets, totalCustomers=0;
float totalCollected=0;
char petName[30], ownerName[30], another = 'Y'; //why did we use Y? QUESTION!
long int cardNumber; // the long int allows us to have a bigger range of numbers
int expireMonth, expireYear, cvvCode, location, numServices;

readingserviceFile(allServices);

currentNumberOfPets = readPets(allPets);

while ( another == 'Y' || another == 'y')
{
	//before entering the pets name we have to remove the extra null thingye!
	
	printf("Enter the pets name: ");
	fgets(petName, 30, stdin);
	
	//petName[strlen(petName)-1] = "\0"; COMNEBACK

	printf("\nEnter the owner name:  ");
	fgets(petName, 30, stdin);
	
	location = findPetRecord(petName, ownerName, allPets, currentNumberOfPets);
	if (location == -1)
	{
		location = currentNumberOfPets;
		allPets[location] = createNewPetRecord(petName,ownerName);
		currentNumberOfPets++;
	}
	
	numServices = selectServices(allServices, customerServices, allPets[location]);
	getPaymentInfo (&cardNumber, &expireMonth, &expireYear, &cvvCode);
	
	totalCollected += printreceipt(cardNumber, expireMonth, expireYear, cvvCode, customerServices, allPets[location], numServices);
	totalCustomers++;
	printf("Is there another customer (Y/N)");
	scanf("\n%c", &another);
	
	getchar(); //removing the enter key!
	
}

printf("\nTotal number of pets served today: %d", totalCustomers);
printf("Total amount collected today:     $%8.2f", totalCollected);


  return 0;
}
float printReceipt (long int cardNumber, int expireMonth, int expireYear, int cvvCode, struct Services customerServices[], struct Pet onePet, int numServices)
{
	float totalPaid =0;
	int x;
	
	printf("\nPayment receipet for services on %s:  \n\n", onePet.petName);
	for (x=0;x<numServices;x++)
	{
		printf("\n  \t\t%d %-25s   %8.2f", customerServices[x].serviceId, customerServices[x].serviceDesc, customerServices[x].price);
		totalPaid += customerServices[x].price;
	}
	printf("\n \t\tTotal Paid:     $8.2f\n", totalPaid);
	printf("\n\n \tcard number:   %1d", cardNumber);
	printf("\n \tExpiration Date:  %d%d", expireMonth, expireYear);
	printf("\n \tCVV code:  %d", cvvCode);
	
	return totalPaid;
}

void getPaymentInfo(long int *cardNumber, int *expireMonth, int *expireYear, int *cvvCode)
{
	
	printf("\nEnter Payment info: ");
	printf("\nEnter credit card number: ");
	scanf("1ld", cardNumber);
	printf("Enter card exp month: ");
	scanf("%d", expireMonth);
	printf("\nEnter card exp year: ");
	scanf("%d", expireYear);
	printf("\nEnter card cvv code: ");
	scanf("%d", cvvCode);	
}

int selectServices(struct Services allServices[], struct Services customerServices[], struct Pet onePet)
{
	int x, y=0, serviceId;
	for (y=0;y<4;y++)
	{
		for (x=0;x<15;x++)
		{
			if (allServices[x].petType == onePet.petType || allServices[x].petType == 3)
			printf("\n %d %-25s $%10.2f", allServices[x].serviceId, allServices[x].serviceDesc, allServices[x].price);
		}
		printf("\nChoose a service code or 0 to quit: ");
		scanf("%d", &serviceId);
		if (serviceId == 0)
		
			break;
		for (x=0;x<15;x++)
		{
			if (serviceId == allServices[x].serviceId)
			customerServices[y] = allServices[x];
		} 
	}
	return y;
}

void readingserviceFile(struct Services allServices[])
{
  FILE *fp;
  fp=fopen("allServices.csv", "r");
  if (fp == NULL)
  {
    printf("Error reading file.\n");
    exit(0);
  }

  char line[100]; //These three lines should be after each file opening!
  char *sp; //These three lines should be after each file opening!
  int x=0; //These three lines should be after each file opening!

  while (fgets(line, 100, fp) != NULL)  
    {
    sp = strtok (line, ",");
    allServices[x].serviceId= atoi(sp);
    sp = strtok(NULL,",");
    strcpy(allServices[x].serviceDesc,sp);
    sp = strtok(NULL, ",");
    allServices[x].petType = atoi(sp);
    sp = strtok(NULL, ",");
    allServices[x].price = atof(sp);
    x++;
  }

fclose(fp);
}

int readPets(struct Pet allPets[])
{
  FILE *fp;
  fp=fopen("allPets.csv", "r");
  if (fp == NULL)
  {
    printf("Error reading file.\n");
    exit(0);
  }

  char line[100]; //These three lines should be after each file opening!
  char *sp; //These three lines should be after each file opening!
  int x=0; //These three lines should be after each file opening!

  while (fgets(line,100,fp)!=NULL)
  {
    sp= strtok(line, ",");
    strcpy(allPets[x].petName,sp); //Remember that when you use a char as a string USE string copy strcpy!!!!!

  sp= strtok(line, ",");
    allPets[x].petType= atoi(sp); 

    sp= strtok(line, ",");
    allPets[x].genderCode = *sp; //also for charectars only!

    sp= strtok(line,",");
    strcpy(allPets[x].ownerName, sp);
    x++;

  }

  fclose(fp);
  return x; //we need to return the amount of pets!!!!!
}

int findPetRecord (char petName[], char ownerName[], struct Pet allPets[], int currentNumberOfPets)
{
	int x;
	for (x=0; x<currentNumberOfPets; x++)
	{
		if (strcmp(petName, allPets[x].petName) == 0 && strcmp( ownerName, allPets[x].ownerName)==0)
		return x;
	}
	return -1;
}

struct Pet createNewPetRecord(char petName[], char ownerName[])
{
	struct Pet newPet;
	printf("Owner and pet not found in the system, creating a new account for you! :D");
	strcpy(newPet.petName, petName);
	strcpy(newPet.ownerName, ownerName);
	
	printf("\n Please enter the number 1 for Dog or the number 2 for Cat: ");
	scanf("%d", &newPet.petType);
	
	while (newPet.petType <1 || newPet.petType > 2)
	{
		printf("You have entered an invalid type, please try again!");
		printf("\n Please enter the number 1 for Dog or the number 2 for Cat: ");
		scanf("%d", &newPet.petType);
	}
	printf("Please enter M for Male or F for Female: ");
	scanf("\n%c", &newPet.genderCode);
	if (newPet.genderCode > 96) 
	
		newPet.genderCode -= 32;
	
	
	while (newPet.genderCode != 'M' && newPet.genderCode != 'F')
	{
		printf("You have entered an invalid gender type");
		printf("Please enter M for Male or F for Female: ");
		scanf("\n%c", &newPet.genderCode);
		if (newPet.genderCode > 96) 
	
		newPet.genderCode += 32;
	
	}
	
	return newPet;
}


