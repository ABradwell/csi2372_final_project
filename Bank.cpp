
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

#include "Bank.h"

using namespace std;

double DepositAccount::rate = 6.50;
double totalAccounts = 0.0;

//******************************************************************
// Basic functions of the BankAccount class
//******************************************************************
inline BankAccount::BankAccount()
{
    accountId = type = updateDate = 0;
    clientName = new char[1];
    balance = 0.0;
}

inline BankAccount::BankAccount(long id, int newType,
                                    char * name, long newDate, double newBalance):
                                    accountId(id), type(newType),
                                    updateDate(newDate), balance(newBalance)
{
     clientName = new char[strlen(name) + 1];
     strcpy(clientName, name);
}

inline BankAccount::~BankAccount()
{
     if (clientName)
     {
          delete [] clientName;
     }
}

inline void BankAccount::setAccountId(long account)
{
     accountId = account;
}

inline void BankAccount::setType(int newType)
{
     type = newType;
}

inline void BankAccount::setClientName(char * name)
{
     if (clientName)
     {
          delete [] clientName;
     }
     clientName = new char[strlen(name) + 1];
     strcpy(clientName, name);
}

inline void BankAccount::setUpdateDate(long newDate)
{
     updateDate = newDate;
}

inline void BankAccount::setBalance(double newBalance)
{
     balance = newBalance;
}

void BankAccount::print() 
{
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << accountId << "\t\t\t" << type << "\t" << updateDate << "\t\t" << balance;
}

//******************************************************************
// Basic functions of the DepositAccount class
//******************************************************************
inline DepositAccount::DepositAccount(long id, int newType, char * name,
                                    long newDate, double balanceArg, int nbyear) :
                                    BankAccount(id, newType, name,
                                    newDate, balanceArg), nbyears(nbyear)
{}

inline void DepositAccount::setNbYears(int nbyear)
{
     nbyears = nbyear;
}

void DepositAccount::print() 
{
    Bonus();
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

//******************************************************************
// Functions of the class DepositAccount. It allows to calculate
// the annual bonus on deposit accounts.
// Inputs: Nothing
// Outputs: Nothing
//******************************************************************
void DepositAccount::Bonus()
{
  setBalance(getBalance() + (getBalance()* getRate() * (getNbYears())/36000.00));
}



//******************************************************************
// Basic functions of the LoanAccount class
//******************************************************************
inline LoanAccount::LoanAccount(long id, int newType, char * name,
                                    long newDate, double newBalance, int nbyear,
                                    double newRate) : BankAccount(id, newType,
                                    name, newDate, newBalance), nbyears(nbyear), rate(newRate)
{ }

inline void LoanAccount::setNbYears(int nbyear)
{
     nbyears = nbyear;
}

inline void LoanAccount::setRate(double newRate)
{
     rate = newRate;
}

void LoanAccount::print() 
{
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

//******************************************************************
// Basic functions of the Transaction class
//******************************************************************
inline Transaction::Transaction(long idTr, int typeTr, long dateTr,
                                    int codeTr = 01, double amountTr):
                                    accountId(idTr), type(typeTr),
                                    date(dateTr), code(codeTr),
                                    amount(amountTr)
{ }

inline void Transaction::setAccountId(long compteTr)
{
     accountId = compteTr;
}

inline void Transaction::setType(int typeTr)
{
     type = typeTr;
}

inline void Transaction::setDate(long dateTr)
{
     date = dateTr;
}

inline void Transaction::setCode(int codeTr)
{
     code = codeTr;
}

inline void Transaction::setAmount(double amountTr)
{
     amount = amountTr;
}




//****************************************************************************
// Purpose: Sort a list of bank accounts in ascending order of ids and types.
//
// WARNING: This sort leaves the last account (of id 0) of the list which has 
// its position to assure the tests of end of list later !!!
//
// Inputs: listAccount(BankAccount *), a list of bank accounts.
// Outputs: listAccount(BankAccount *), sorted list of bank accounts.
//****************************************************************************
void sortAccounts(BankAccount ** list)
{

     cout << "SORTING METHOD" << endl;

     BankAccount *pAccount;
     for (int i = 0; list[i + 1]->getAccountId() != 0; i++)
     {
          for (int j = i + 1; j >= 1; j--)
          {

               if (list[j]->getAccountId() < list[j - 1]->getAccountId())
               {
                    pAccount = list[j];
                    list[j] = list[j - 1];
                    list[j - 1] = pAccount;
               }
               else if (list[j]->getAccountId() == list[j - 1]->getAccountId() && list[j]->getType() < list[j - 1]->getType())
               {
                    pAccount = list[j];
                    list[j] = list[j - 1];
                    list[j - 1] = pAccount;
               }
               else
               {
                    break;
               }
          }
     }
}

//******************************************************************
// Purpose: This function reads the file 'clients.txt' and builds 
// an array containing the different bank accounts of customers.
//
// Inputs: Nothing
// Output: listAccount(type: BankAccount *), the list of bank 
//         accounts read from the file 'clients.txt'.
//******************************************************************
BankAccount ** readAccounts()
{
    ifstream inputFile("clients.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        cout << "File not found !!!" << endl;
        exit(0);
    }

    BankAccount ** listAccounts = new BankAccount*[K_SizeMax];
    if (!listAccounts) {
        cout << "Full memory. !!!" << endl;
        return listAccounts;
    }

    BankAccount ** pAccount = listAccounts;
	 
    long accountRead, dateRead;
    int TypeRead, nbyearRead, counter = 0;
    double balanceRead, RateRead;
    char nameRead[60];
	 
    inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
    inputFile.getline(nameRead, 60);
	 
    while (inputFile && (counter < K_SizeMax - 1)){

          // YOU HAVE TO DO SOMETHING FROM HERE !!!
          BankAccount *temp_core;
          if (TypeRead == 01)
          {    
               temp_core = new BankAccount{accountRead, TypeRead, nameRead, dateRead, balanceRead};
          }
          else if (TypeRead == 02)
          {
               temp_core = new BankAccount{accountRead, TypeRead, nameRead, dateRead, balanceRead};
          }
          else if (TypeRead == 03)
          {
               temp_core = new DepositAccount{accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead};
          }
          else if (TypeRead == 04)
          {
               balanceRead = balanceRead + ((balanceRead * nbyearRead * RateRead)/36000);
               temp_core = new LoanAccount{accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead, RateRead};
          }

          *pAccount = temp_core;

          // UNTIL THIS POINT.

          inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
          inputFile.getline(nameRead, 60);
          pAccount++;
          counter++;
     }

     *pAccount = new BankAccount();

     return listAccounts;
}





//*****************************************************************************************
// Purpose: This function validates whether the transaction code 
//          corresponds to the correct account:
//              - 01 ==> account (01: Check, 02: Savings, 03: Deposit and 04: Loan)
//              - 02 ==> account (01: Check, 02: Savings)
//              - 03 ==> account (01: Check).
//
// Inputs: trans (Type: Transaction) an instance of the Transaction class.
// Outputs: true (Type bool) if the transaction matches one of the accounts listed above.
// false (Type bool) otherwise.
//*****************************************************************************************
Bool BankAccount::validateTransaction(const Transaction trans) const
{
    if ( ( (trans.getCode() == 02) && ( isDepositAccount() || isLoanAccount()) ) ||
         ( (trans.getCode() == 03) && ( isDepositAccount() || isLoanAccount() || isSavingsAccount() ) ) )
      {
       return FALSE;
      }
    else
      {
       return TRUE;
      }
        
}





//******************************************************************************
// Purpose: This function is used to execute the transaction already performed 
// (update the balance of an account).
//
// Inputs: trans (Transaction Type), instance of Transaction class
// Outputs: Nothing
//*******************************************************************************
void BankAccount::executeTransaction(const Transaction trans)
{
     if (validateTransaction(trans))
       {
         if (trans.getCode() == 01)    // Deposit
           {
             setBalance(getBalance() + trans.getAmount());
           }
         else 
           { if (trans.getCode() == 02)    // Withdrawal
                {
                  if (getBalance() >= trans.getAmount())
                     { setBalance(getBalance() - (trans.getAmount() + 0.50)); }
                  else {cout << " insufficient balance!! " << endl; }
                }
             else 			// Check
                {
                  if (getBalance() >= trans.getAmount())
                     { 
                       setBalance(getBalance() - trans.getAmount());
                     }
                  else {cout << " insufficient balance!! " << endl; }
                }
           }
                 
       }   
 
}

//***********************************************************************
// Purpose: This function is used to execute a read transaction
// (updating the balance of the loan account).
//
// Inputs: trans (Transaction Type), instance of the Transaction class
// Outputs: Nothing
//***********************************************************************
void LoanAccount::executeTransaction(const Transaction trans)
{
     if (validateTransaction(trans))
     {
        if (trans.getCode() == 01)    // Deposit
        {
          setBalance(getBalance() - trans.getAmount());
         
        }
     }
}





//*************************************************************************
// Purpose: This function allows to read the file 'transact.txt' 
//          and to update the accounts concerned by the transactions read.
//
// Inputs: listAccount (type BankAccount *), the list of bank accounts.
// Output: Nothing.
//*************************************************************************
void updateAccounts(BankAccount ** listAccounts) {

     string line;

     ifstream inputFile("transact.txt");	// Opening the input file

     if (!inputFile.is_open()) {
          cout << "WARNING. TRANSACT FILE NOT PRESENT." << endl;
          exit(0);       // Fatal Error opening transction log
     }

    int accountId, accountType, date_of_trans, trans_code;
    double amount;
    

    while (inputFile){
          
          // Load information from file, and convert it into a transaction object
          inputFile >> accountId >> accountType >> date_of_trans >> trans_code >> amount;
          Transaction new_transaction{accountId, accountType, date_of_trans, trans_code, amount};
          
          // Iterate through each account, for each new transaction. When the correct account is found, apply transaction IF VALID
          int i = 0;
          for (int i = 0; i < K_SizeMax; i++) {
               
               BankAccount *b_p = *(listAccounts + i);

               // Last null-account found. All accounts have been searched. Move on to next transactions
               if (b_p->getAccountId() == 0 && b_p->getBalance() == 0) {
                    cout << "No account found for account #" << accountId << " Type " << accountType << endl;
                    break;
               }

               // If the equivilant account is correctly found.
               if (b_p->getAccountId() == accountId && b_p->getType() == accountType) {
                    
                    // If transaction is valid for the found account, execute it
                    if (!b_p->validateTransaction(new_transaction)) {
                         cout << "Invalid transaction on account #" << b_p->getAccountId() << endl;
                         break;
                    }

                    b_p->executeTransaction(new_transaction);
                    break;
               }
          }
    } 
}

//******************************************************************************
// Purpose: This function displays the list of bank accounts for all customers.
//
// Inputs: listAccount (type: BankAccount *), the list of bank accounts.
// Outputs: Nothing
//******************************************************************************
void displayAccounts(BankAccount ** listAccounts)
{
     cout << endl << endl << endl;
     
     Bool find[K_SizeMax];
     for(int k = 0; k < K_SizeMax; k++) {find[k] = FALSE;}
 
     cout << "                       THE REPORT OF THE BANK ACCOUNTS OF CLIENTS" << endl;
     cout << "                       ------------------------------------------" << endl << endl;
     

     float client_total_sum;
     for (int j = 0; listAccounts[j]->getAccountId() != 0; j++) {
          
          BankAccount *cn_p = *(listAccounts + j);

          if (find[j] ==  TRUE) {
               continue;      // Client already printed
          }

          cout << "Client Name: " << cn_p->getClientName() << endl;
          client_total_sum = 0;
         
          // For each bank account, use the overloaded builtin-print method defined above
          for (int i = 0; listAccounts[i]->getAccountId() != 0; i++) {

               BankAccount *b_p = *(listAccounts + i);

               if (strcmp(cn_p->getClientName(), b_p->getClientName()) == 0 && find[i] == FALSE) {
                    b_p->print(); cout << endl;
                    find[i] = TRUE;
                    client_total_sum = client_total_sum + b_p->getBalance();

               }
          }

          cout << "TOTAL ACCOUNTS: " << client_total_sum << endl;
          cout << "----------------------------------------" << endl<<endl;
     }
}




int main()
{    
    BankAccount ** list = readAccounts();
    sortAccounts(list);
    displayAccounts(list);
    updateAccounts(list);
    cout << endl << endl;
    cout << "               ************************************************" << endl;
    cout << "               * RE-DISPLAY OF DATA AFTER THE UPDATE *" << endl;
    cout << "               ************************************************" << endl;
    displayAccounts(list);
    cout << endl;

	system("PAUSE");
	return 0;
}
