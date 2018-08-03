/*
Secure Account System
Luke Clark Andrada

Objectives
	[1] to save a collection of account information
	[2] to generate a random password
	[3] to automatically secure the collection
	[4] to automatically encrypt the information
	[5] to provide convenience and security in handling several accounts
*/

// preprocessor directives
#include<stdafx.h>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<conio.h>
#include<ctime>

using namespace std;

class SECURE
{
	private:
		char password[50];
		char tryAgain[30];
		int length, i, x, attempt;
		ofstream file;
		string stamp;
		char OLD[100], NEW[100];
	public:		
		char folderUnlock[100], folderUnlockNew[100];

		// function for custom color
		void COLOR(int code)
		{
			HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(text, code);
		}

		// function for single character input
		void SINGLE(char answer[30])
		{
			x = 0;

			while(1)
			{
				answer[x] = _getch();

				if(answer[x] == 13)	// terminate character string when Enter key is pressed
				{
					answer[x] = '\0'; // insert terminating character
					break;
				} else if(answer[x] == 8 && x >= 0) // erase previously entered character when Backspace key is pressed
				{
					if(x > 0)
					{
						cout << "\b \b"; // erase previous character
						x--;
					} else if(x == 0)
					{
						// display nothing
					}
				} else if(answer[x] == 32) // display nothing when Space key is pressed
				{
					// display nothing
				} else if(x < 1)// display the characters
				{
					cout << answer[x];
					x++;
				}
			}

			x = 0;
		}

		// function for ignoring space in input
		void NOSPACE(char user[50])
		{
			START:
			x = 0;

			// loop for storing the input and forcing to ignore space
			while(1)
			{
				user[x] = _getch(); // store character without echo

				if((user[x] >= 0 && user[x] <= 7) || (user[x] >= 9 && user[x] <= 12) || (user[x] >= 14 && user[x] <= 45) || user[x] == 47 ||
					(user[x] >= 58 && user[x] <= 63) || (user[x] >= 91 && user[x] <= 94) || user[x] == 96 || user[x] >= 123)
				{
					// display nothing
				} else
				{
					if(user[x] == 13)	// terminate character string when Enter key is pressed
					{
						user[x] = '\0'; // insert terminating character
						if(user[0] == '\0')
							goto START;
						break;
					} else if(user[x] == 8 && x >= 0) // erase previously entered character when Backspace key is pressed
					{
						if(x > 0)
						{
							cout << "\b \b"; // erase previous character
							x--;
						} else if(x == 0)
						{
							// display nothing
						}
					} else if(x < 50) // display the characters
					{
						cout << user[x];
						x++;
					}
				}
			}

			x = 0;
		}

		// function for displaying asterisk instead of actual password
		void ASTERISK(char actualPass[50])
		{
			START:
			x = 0;

			// loop for storing actual password and displaying asterisk
			while(1)
			{
				actualPass[x] = _getch(); // store character without echo

				if(actualPass[x] == 13)	// terminate character string when Enter key is pressed
				{
					actualPass[x] = '\0'; // insert terminating character
					if(actualPass[0] == '\0')
							goto START;
					break;
				} else if(actualPass[x] == 8 && x >= 0) // erase previously entered character when Backspace key is pressed
				{
					if(x > 0)
					{
						cout << "\b \b"; // erase previous character
						x--;
					} else if(x == 0)
					{
						// display nothing
					}
				} else if(actualPass[x] == 32) // display nothing when Space key is pressed
				{
					// display nothing
				} else if(x < 50)// display asterisk
				{
					cout << "*";
					x++;
				}
			}

			x = 0;
		}

		// function for automatic directory lock
		void LOCK(char folder[50], char folderNew[50])
		{	
			// declare and initialize folder names
			for(i = 0; i < 100; i++)
				OLD[i] = folder[i];
			for(i = 0; i < 100; i++)
				NEW[i] = folderNew[i];
			i = 0;

			// rename original folder to lock
			rename(OLD, NEW);
		}
		
		// function for automatic directory unlock
		void UNLOCK(char folder[50], char folderNew[50])
		{
			// declare and initialize folder names
			for(i = 0; i < 100; i++)
				OLD[i] = folderNew[i];
			for(i = 0; i < 100; i++)
				NEW[i] = folder[i];
			i = 0;

			// rename original folder to unlock
			rename(OLD, NEW);
		}

		// function for encrypting password
		void ENCRYPT(char initial[50])
		{
			length = strlen(initial) - 1;
			
			// re-initialize variables to avoid stacking error
			char encrypted[50] = "\0"; 
			char enTemp[50] = "\0";

			// loop for -13 shifting
			for(x = 0; x <= length; x++)
			{
				enTemp[x] = initial[x] - 13;
			}
			
			// reverse string
			_strrev(enTemp);
			
			// loop for incremental shifting
			for(x = 0; x <= length; x++)
			{
				encrypted[x] = enTemp[x] + x;
			}

			// loop for re-assigning encrypted password to argument
			for(x = 0; x <= strlen(encrypted) - 1; x++)
			{
				initial[x] = encrypted[x];
			}

			x = 0;
		}
		
		// loop for decrypting password
		void DECRYPT(char initial[50])
		{	
			// re-initialize variables to avoid stacking error
			char decrypted[50] = "\0";
			char deTemp[50] = "\0";

			// decrypt extra layer of protection
			for(i = 0; i <= (strlen(initial)/2) - 1; i++)
			{
				initial[i] = initial[1 + 2 * i];
			}

			initial[i] = '\0';

			length = strlen(initial) - 1;

			// loop for decremental shifting
			for(x = length; x >= 0; x--)
			{
				deTemp[x] = initial[x] - x;
			}
			
			// reverse string
			_strrev(deTemp);
			
			// loop for +13 shifting
			for(x = 0; x <= length; x++)
			{
				decrypted[x] = deTemp[x] + 13;
			}

			// loop for re-assigning decrypted password to argument
			for(x = 0; x <= strlen(decrypted) - 1; x++)
			{
				initial[x] = decrypted[x];
			}

			x = 0;
		}

		// function for storing account
		void STORE(string location, char user[50], char pass[50])
		{
			crypt.UNLOCK(crypt.folderUnlock, crypt.folderUnlockNew);
			// declare variables
			x = 0;
			time_t record;
			time(&record);
			srand(time(NULL));

			// print secured main account information to main.txt
			file.open(location);
			ENCRYPT(pass);
			file << user << endl;
					
			// extra layer of protection
			while(1)
			{
				char random;
				if(pass[x] == '\0')
				{
					break;
				} else
				{
					random = char(rand()% 223 + 32); // insert random characters
					if(random == ' ')
					{
						random = char(255);
					}

					file << random << pass[x];
					x++;
				}
			}

			stamp = ctime(&record);
			file << endl << stamp;
			file.close();
			crypt.LOCK(crypt.folderUnlock, crypt.folderUnlockNew);
		}

		// function for user confirmation
		void CONFIRM(char passConfirm[50])
		{
			attempt = 1;
			START:
				// check number of attempts
				if(attempt <= 5)
				{
					// if number of attempts is still tolerable
					cin.sync();
					if(attempt > 1)
					{
						COLOR(177);
						cout << "\nAttempt: " << attempt;
						cout << endl;
					}

					// prompt user for program password for validation
					COLOR(177);
					cout << "Enter your program password to continue: ";
					COLOR(191);
					ASTERISK(password);
					COLOR(240);

					// check if password and program password matched
					if(strcmp(password, passConfirm))
					{
						// if it did not match
						AGAIN:
							// prompt user to try again
							cin.sync();
							COLOR(177);
							cout << "\nPassword did not match. Try Again?(Y/N): ";
							COLOR(191);
							crypt.SINGLE(tryAgain); cout << endl;
							COLOR(240);

							switch(tryAgain[0])
							{
								case 'Y':
								case 'y':
									attempt++;
									goto START;
									break;
								case 'N':
								case 'n':
									cout << "\nExiting";
									Sleep(1500);
									exit(0);
									break;
								default:
									cout << "Invalid\n";
									goto AGAIN;
							}
					}
				} else
				{
					cout << "\nAttempt exceeded";
					cout << "\nExiting";
					Sleep(1500);
					exit(0);
				}
		}

		// function for loading animation
		void LOAD()
		{
			int z = 100;
			cout << '-' << flush;
			while(z != 0) 
			{
				z--;
				Sleep(1);
				cout << "\b\\" << flush;
				Sleep(1);
				cout << "\bI" << flush;
				Sleep(1);
				cout << "\b/" << flush;
				Sleep(1);
				cout << "\b-" << flush;
			}

			cout << "\b " << flush;
		}
} crypt;

class INTRO : public SECURE
{
	private:
		int x, attempt;
		char tryAgain[30];
	public:
		char user[50], pass[50], checkPass[50];
		char USER[50], PASS[50];
		char passTemp[50];
		char username[50], usernameCheck[50];
		string fileLocation, folder, attrib, folderTemp;
		char passConfirm[50];

		// function for positioning
		void CENTER(int x, int y)
		{
			// initialize screem
			HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

			// initialize x and y coordinates
			COORD cursor;
			cursor.X = x;
			cursor.Y = y;

			// set cursor position
			SetConsoleCursorPosition(screen, cursor);
		}

		// function for prelogin events
		void PRELOGIN()
		{
			START:
				// prompt user for username
				system("color F0");
				CENTER(30, 10);
				COLOR(177);
				cout << "Enter Username\n";
				CENTER(30, 11);
				COLOR(191);
				NOSPACE(username);

				system("cls");
				system("color F0");

				CENTER(30, 10);
				COLOR(177);
				cout << "Verify Username\n";
				CENTER(30, 11);
				COLOR(191);
				NOSPACE(usernameCheck);

				system("cls");
				system("color F0");

				// check if username input and program username matched
				if(!strcmp(username, usernameCheck))
				{
					// initialize directory and file location
					for(x = 0; x < 50; x++)
						crypt.folderUnlock[x] = '\0';
					for(x = 0; x < 50; x++)
						crypt.folderUnlockNew[x] = '\0';
					x = 0;
					strcat_s(crypt.folderUnlock, "C:/[SAS]");
					strcat_s(crypt.folderUnlockNew, "C:/[SAS]");
					folder = username;
					strcat_s(crypt.folderUnlock, username);
					strcat_s(crypt.folderUnlockNew, username);
					folder = "C:/[SAS]" + folder;
					strcat_s(crypt.folderUnlockNew, ".{645FF040-5081-101B-9F08-00AA002F954E}");
					fileLocation = folder + "/MAIN.txt";

					// unlock folder for reading if it exists
					crypt.UNLOCK(crypt.folderUnlock, crypt.folderUnlockNew);

					// read main account
					ifstream mainInput;
					mainInput.open(fileLocation);

					// check main.txt availability
					if(mainInput.is_open())
					{
						// if main.txt is available
						// read main account information from main.txt
						CENTER(35, 10);
						cout << "Loading ";
						crypt.LOAD();
						mainInput >> user;
						mainInput >> pass;

						mainInput.close();

						// decrypt main password for login
						crypt.DECRYPT(pass);
						for(x = 0; x < 50; x++)
							passConfirm[x] = '\0';
						strcat_s(passConfirm, pass);
						crypt.LOCK(crypt.folderUnlock, crypt.folderUnlockNew);
						LOGIN();
					} else
					{
						// if main.txt is not available
						// prompt user for username and password that would access the program
						mainInput.close();
						COLOR(177);
						cout << "S"; Sleep(50); cout << "E"; Sleep(50); cout << "C"; Sleep(50); cout << "U"; Sleep(50); cout << "R"; Sleep(50); cout << "E"; Sleep(50);
						cout << ' '; Sleep(50);
						cout << "A"; Sleep(50); cout << "C"; Sleep(50); cout << "C"; Sleep(50); cout << "O"; Sleep(50); cout << "U"; Sleep(50); cout << "N"; Sleep(50); cout << "T"; Sleep(50);
						cout << ' '; Sleep(50);
						cout << "S"; Sleep(50); cout << "Y"; Sleep(50); cout << "S"; Sleep(50); cout << "T"; Sleep(50); cout << "E"; Sleep(50); cout << "M"; Sleep(50);
						cout << endl; Sleep(50);
						COLOR(240);
						Sleep(300);
						cout << "Please enter your username and password.\n";
						Sleep(300);
						cout << "This will serve as your account to access the program.\n";
						Sleep(300);
						cout << "Save a copy of the SAS account somewhere safe." << endl << endl;
						Sleep(300);

						PASSAGAIN:
							COLOR(177);
							cout << "Username: ";
							COLOR(191);
							cout << username << endl;
							Sleep(300);
							COLOR(177);
							cout << "Password: ";
							COLOR(191);
							ASTERISK(pass);
							cout << endl;
							COLOR(177);
							cout << "Re-enter Password: ";
							COLOR(191);
							ASTERISK(checkPass);
							COLOR(240);

							// compare password and re-entered password
							if(!strcmp(pass, checkPass))
							{
								// if pass and checkPass matched
								// create directory for main.txt
								folderTemp = folder;
								const char *folderCreate = folderTemp.c_str();
								attrib = "attrib +s +h " + folder; 
								const char *folderAttrib = attrib.c_str();
								
								CreateDirectory(folderCreate, NULL);						
								WinExec(folderAttrib, NULL);	

								cout << "\n\nSaving ";
								crypt.LOAD();
								cout << endl;

								// store account to main.txt
								crypt.STORE(fileLocation, username, pass);

								cout << "Account created successfully.\n\nExiting";
								Sleep(3000);

								// call PRELOGIN function to start over
								system("cls");
								PRELOGIN();
							} else
							{
								// if pass and checkPass did not match
								// call PRELOGIN function to start over
								cout << endl;
								AGAIN:
									COLOR(177);	
									cout << "\nPassword did not match. Try Again?(Y/N): ";
									COLOR(191);
									cin.sync();
									crypt.SINGLE(tryAgain); cout << endl;
									COLOR(240);

									// options to Try Again
									switch(tryAgain[0])
									{
										case 'Y':
										case 'y':
											cout << endl;
											goto PASSAGAIN;
											break;
										case 'N':
										case 'n':
											system("cls");
											PRELOGIN();
											break;
										default:
											cout << "Invalid\n";
											goto AGAIN;
									}
							}
					}
				} else
				{
					// if username did not match
					// start over
					system("cls");
					goto START;
				}
		}

		// function for login events
		void LOGIN()
		{
			attempt = 1;
			START:
				system("color f0");
				// check if attempt is greater than 1
				if(attempt > 1)
				{
					// if is greater than 1
					// display attempt
					CENTER(30, 9);
					cout << "Attempt: " << attempt << "\n";
				}

				// prompt user for username and password
				strcpy_s(USER, username);
				CENTER(30, 10);
				COLOR(177);
				cout << "Enter Your Password";
				CENTER(30, 11);
				COLOR(191);
				ASTERISK(PASS);
				
				AGAIN:
					COLOR(240);
					// check if USER and PASS match the database
					if(!strcmp(user, USER) && !strcmp(pass, PASS))
					{
						// if matched
						// proceed when USER and PASS
						system("cls");
						system("color f0");
						CENTER(30, 10);
						COLOR(177);
						cout << "logging you in,";
						CENTER(30, 11);
						COLOR(191);
						cout << USER;
						Sleep(1500);
						system("cls");
					} else
					{
						// if it did not match
						// prompt user to Try Again
						CENTER(30, 13);
						cout << "Access Denied";

						// check if attempt is still tolerable
						if(attempt < 5)
						{
							// if still is
							// prompt user to try again
							cin.sync();
							CENTER(30, 14);
							cout << "\t\t\t\t\t";
							CENTER(30, 14);
							COLOR(177);
							cout << "Try Again?(Y/N): ";
							COLOR(191);
							crypt.SINGLE(tryAgain); cout << endl;
							COLOR(240);
						} else
						{
							// if is not
							// exit
							CENTER(30, 13);
							cout << "Attempt Exceeded";
							CENTER(30, 14);
							cout << "Exiting";
							Sleep(1500);
							exit(0);
						}

						// options to Try Again
						switch(tryAgain[0])
						{
							case 'Y':
							case 'y':
								attempt++;
								system("cls");
								goto START;
								break;
							case 'N':
							case 'n':
								CENTER(30, 15);
								cout << "Exiting";
								Sleep(1500);
								exit(0);
								break;
							default:
								CENTER(30, 14);
								cout << "\t\t\t\t\t\n\t\t\t\t\t\n\t\t\t\t\t\n\t\t\t\t\t\n\t\t\t\t\t\n";
								CENTER(30, 15);
								cout << "Invalid";
								goto AGAIN;
						}
					}
		}
} login;

class MAIN : public INTRO
{
	private:
		char choice[30], tryAgain[30], sure[30];
		char selectionInput[50];
		char randomPass[50];
		string selection;
		int x, i, randomLength;
	public:
		// function for displaying welcome screen
		void WELCOME()
		{
			system("color 0f");
			CENTER(25, 12);
			cout << "       000000000000000000";
			Sleep(100);
			CENTER(25, 6);
			cout << "       0000000    0000000";
			Sleep(100);
			CENTER(25, 19);
			cout << "         00000000000000";
			Sleep(100);
			CENTER(25, 8);
			cout << "     00000            00000";
			Sleep(100);
			CENTER(25, 4);
			cout << "             100001";
			Sleep(100);
			CENTER(25, 17);
			cout << "      000000000  000000000";
			Sleep(100);
			CENTER(25, 20);
			cout << "            10000001";
			Sleep(100);
			CENTER(25, 14);
			cout << "     000000000    000000000";
			Sleep(100);
			CENTER(25, 5);
			cout << "         00000000000000";
			Sleep(100);
			CENTER(25, 10);
			cout << "     0000     1001     0000";
			Sleep(100);
			CENTER(25, 13);
			cout << "      00000000000000000000";
			Sleep(100);
			CENTER(25, 16);
			cout << "     0000000000  0000000000";
			Sleep(100);
			CENTER(25, 9);
			cout << "     00000             0000";
			Sleep(100);
			CENTER(25, 15);
			cout << "     0000000000  0000000000";
			Sleep(100);
			CENTER(25, 7);
			cout << "      00000          00000";
			Sleep(100);
			CENTER(25, 18);
			cout << "       000000000000000000";
			Sleep(100);
			CENTER(25, 11);
			cout << "     00   000000000000   00";
			CENTER(44, 20);
			system("color 0f");
			Sleep(50);
			system("color f0");
			Sleep(50);
			system("color 0f");
			Sleep(50);
			system("color f0");
			Sleep(50);
			system("color 0f");
			Sleep(50);
			system("color f0");
			Sleep(50);
			system("color 0f");
			Sleep(50);
			system("color f0");
			Sleep(50);
			system("color 0f");
			Sleep(50);
			system("color f0");
			Sleep(1000);

			COLOR(251);
			CENTER(2, 7);
			cout << "   _____                              ___                               __ ";
			Sleep(50);
			CENTER(2, 8);
			cout << "  / ___/___  _______  __________     /   | ______________  __  ______  / /_ ";
			Sleep(50);
			CENTER(2, 9);
			cout << "  \\__ \\/ _ \\/ ___/ / / / ___/ _ \\   / /| |/ ___/ ___/ __ \\/ / / / __ \\/ __/";
			Sleep(50);
			CENTER(2, 10);
			cout << " ___/ /  __/ /__/ /_/ / /  /  __/  / ___ / /__/ /__/ /_/ / /_/ / / / / /_  ";
			Sleep(50);
			CENTER(2, 11);
			cout << "/____/\\___/\\___/\\__,_/_/__ \\___/  /_/ _|_\\___/\\___/\\____/\\__,_/_/ /_/\\__/  ";
			Sleep(50);
			CENTER(2, 12);
			cout << "                    / ___/__  _______/ /____  ____ ___                     ";
			Sleep(50);
			CENTER(2, 13);
			cout << "                    \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\                    ";
			Sleep(50);
			CENTER(2, 14);
			cout << "                   ___/ / /_/ (__  ) /_/  __/ / / / / /                    ";
			Sleep(50);
			CENTER(2, 15);
			cout << "                  /____/\\__, /____/\\__/\\___/_/ /_/ /_/                     ";
			Sleep(50);
			CENTER(2, 16);
			cout << "                       /____/                                              ";
			CENTER(44, 20);
			Sleep(2000);

			system("cls");
			system("color f0");
		}

		// function for pre-program
		void PRE()
		{
			COLOR(177);
			CENTER(29, 7);
			cout << "Secure your accounts now";
			CENTER(28, 8);
			cout << "with ";
			COLOR(191);
			CENTER(33, 8);
			cout << "Secure Account System";
			COLOR(240);
			Sleep(500);
			CENTER(30, 10);
			cout << "Please select an option";
			Sleep(150);
			CENTER(34, 11);
			cout << "(C) Continue";
			Sleep(150);
			CENTER(34, 12);
			cout << "(H) Help";
			Sleep(150);
			CENTER(34, 13);
			cout << "(A) About";
			Sleep(150);
			AGAIN:
				CENTER(34, 15);
				cout << "Option: ";
				COLOR(191);
				crypt.SINGLE(choice);
				COLOR(240);

				switch(choice[0])
				{
					case 'C':
					case 'c':
						system("cls");
						break;
					case 'H':
					case 'h':
						COLOR(176);
						system("cls");
						CENTER(2, 1);
						cout << "   _____                              ___                               __ ";
						CENTER(2, 2);
						cout << "  / ___/___  _______  __________     /   | ______________  __  ______  / /_";
						CENTER(2, 3);
						cout << "  \\__ \\/ _ \\/ ___/ / / / ___/ _ \\   / /| |/ ___/ ___/ __ \\/ / / / __ \\/ __/";
						CENTER(2, 4);
						cout << " ___/ /  __/ /__/ /_/ / /  /  __/  / ___ / /__/ /__/ /_/ / /_/ / / / / /_  ";
						CENTER(2, 5);
						cout << "/____/\\___/\\___/\\__,_/_/__ \\___/  /_/ _|_\\___/\\___/\\____/\\__,_/_/ /_/\\__/  ";
						CENTER(2, 6);
						cout << "                    / ___/__  _______/ /____  ____ ___                     ";
						CENTER(2, 7);
						cout << "                    \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\                    ";
						CENTER(2, 8);
						cout << "                   ___/ / /_/ (__  ) /_/  __/ / / / / /                    ";
						CENTER(2, 9);
						cout << "                  /____/\\__, /____/\\__/\\___/_/ /_/ /_/                     ";
						CENTER(2, 10);
						cout << "                       /____/                                              ";
						COLOR(191);
						CENTER(20, 12);
						cout << "Create an SAS account by typing in a new";
						Sleep(10);
						CENTER(20, 13);
						cout << "username and password on the logon screen.";
						Sleep(10);
						CENTER(20, 15);
						cout << "Sign in to your account by typing in your";
						Sleep(10);
						CENTER(20, 16);
						cout << "existing username and password on the logon screen.";
						Sleep(10);
						CENTER(20, 18);
						cout << "Secure Account System can accommodate";
						Sleep(10);
						CENTER(20, 19);
						cout << "multiple users.";
						Sleep(10);
						CENTER(20, 21);
						cout << "Usernames only accept alphanumeric characters";
						Sleep(10);
						CENTER(20, 22);
						cout << "(0-9, A-Z), underscore (_), at symbol (@),";
						Sleep(10);
						CENTER(20, 23);
						cout << "and period.";
						Sleep(10);
						CENTER(20, 25);
						cout << "Passwords accept any standard characters.";
						Sleep(10);
						CENTER(20, 27);
						cout << "Maximum characters for username and";
						Sleep(10);
						CENTER(20, 28);
						cout << "password is 50 characters.";
						Sleep(10);
						CENTER(20, 30);
						cout << "Account names only accept letters.";
						Sleep(10);
						CENTER(20, 32);
						cout << "Choose an option by typing in the";
						Sleep(10);
						CENTER(20, 33);
						cout << "corresponding letter to the desired choice.";
						Sleep(10);
						CENTER(20, 35);
						cout << "Save a copy of the SAS account somewhere safe.";
						Sleep(10);
						CENTER(20, 36);
						cout << "Forgetting so will require manual retrieval.";
						Sleep(10);
						CENTER(20, 38);
						cout << "Save a copy of the name of the accounts";
						Sleep(10);
						CENTER(20, 39);
						cout << "saved. Forgetting so will require manual";
						Sleep(10);
						CENTER(20, 40);
						cout << "retrieval. Use straight-forward and simple";
						Sleep(10);
						CENTER(20, 41);
						cout << "names to avoid such situation.";
						Sleep(10);
						CENTER(20, 43);
						cout << "SAS account is designed to be permanent.";
						Sleep(10);
						CENTER(20, 44);
						cout << "If, otherwise, the SAS account is desired";
						Sleep(10);
						CENTER(20, 45);
						cout << "to be changed, navigate to";
						Sleep(10);
						CENTER(20, 46);
						cout << "Manage Account > Update > Type in MAIN.";
						Sleep(10);
						CENTER(20, 47);
						cout << "You can then change your SAS account.";
						Sleep(10);
						CENTER(20, 49);
						cout << "The Manage Account feature allows the user";
						Sleep(10);
						CENTER(20, 50);
						cout << "to add an account to the collection, update";
						Sleep(10);
						CENTER(20, 51);
						cout << "an added account, delete an account, and";
						Sleep(10);
						CENTER(20, 52);
						cout << "retrieve a saved account.";
						Sleep(10);
						CENTER(20, 54);
						cout << "Accounts are automatically secured-";
						Sleep(10);
						CENTER(20, 55);
						cout << "it is encrypted and locked with an";
						Sleep(10);
						CENTER(20, 56);
						cout << "additional layer of protection.";
						Sleep(10);
						CENTER(20, 58);
						cout << "The Generate Random Password feature allows";
						Sleep(10);
						CENTER(20, 59);
						cout << "the user to generate a random password in";
						Sleep(10);
						CENTER(20, 60);
						cout << "alphanumeric, numbers, letters or custom";
						Sleep(10);
						CENTER(20, 61);
						cout << "characters. It also allows the user to add";
						Sleep(10);
						CENTER(20, 62);
						cout << "an account or update an existing account";
						Sleep(10);
						CENTER(20, 63);
						cout << "using the generated password.";
						Sleep(10);
						CENTER(20, 65);
						cout << "If you want to delete the SAS account";
						Sleep(10);
						CENTER(20, 66);
						cout << "and all accounts therewith, deactivate the";
						Sleep(10);
						CENTER(20, 67);
						cout << "SAS account through the main menu.";
						Sleep(10);
						CENTER(20, 68);
						cout << "CAUTION: All accounts will be deleted";
						Sleep(10);
						CENTER(20, 69);
						cout << "by doing so.";
						Sleep(10);
						CENTER(20, 71);
						cout << "Adding a new account with the same name";
						Sleep(10);
						CENTER(20, 72);
						cout << "as an existing account will overwrite it.";
						Sleep(10);
						CENTER(20, 74);
						cout << "Password confirmation allows limited";
						Sleep(10);
						CENTER(20, 75);
						cout << "attempts. Exceeding so will exit SAS.";
						Sleep(10);
						CENTER(20, 77);
						cout << "Account names are not case sensitive";
						Sleep(10);
						CENTER(20, 78);
						cout << "i.e. clark is the same as CLARK.";
						Sleep(10);
						CENTER(20, 80);
						cout << "Press any key to continue";
						Sleep(10);
						CENTER(5, 1);
						system("pause > 0");
						system("cls");
						system("color f0");
						PRE();
						break;
					case 'A':
					case 'a':
						COLOR(176);
						system("cls");
						CENTER(2, 1);
						cout << "   _____                              ___                               __ ";
						CENTER(2, 2);
						cout << "  / ___/___  _______  __________     /   | ______________  __  ______  / /_";
						CENTER(2, 3);
						cout << "  \\__ \\/ _ \\/ ___/ / / / ___/ _ \\   / /| |/ ___/ ___/ __ \\/ / / / __ \\/ __/";
						CENTER(2, 4);
						cout << " ___/ /  __/ /__/ /_/ / /  /  __/  / ___ / /__/ /__/ /_/ / /_/ / / / / /_  ";
						CENTER(2, 5);
						cout << "/____/\\___/\\___/\\__,_/_/__ \\___/  /_/ _|_\\___/\\___/\\____/\\__,_/_/ /_/\\__/  ";
						CENTER(2, 6);
						cout << "                    / ___/__  _______/ /____  ____ ___                     ";
						CENTER(2, 7);
						cout << "                    \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\                    ";
						CENTER(2, 8);
						cout << "                   ___/ / /_/ (__  ) /_/  __/ / / / / /                    ";
						CENTER(2, 9);
						cout << "                  /____/\\__, /____/\\__/\\___/_/ /_/ /_/                     ";
						CENTER(2, 10);
						cout << "                       /____/                                              ";
						COLOR(177);
						CENTER(5, 12);
						cout << "SAS lets users";
						Sleep(10);
						CENTER(5, 13);
						cout << "[1]";
						COLOR(191);
						CENTER(8, 13);
						cout << " to save a collection of account information";
						Sleep(10);
						COLOR(177);
						CENTER(5, 14);
						cout << "[2]";
						COLOR(191);
						cout << " to generate a random password";
						Sleep(10);
						COLOR(177);
						CENTER(5, 15);
						cout << "[3]";
						COLOR(191);
						cout << " to automatically secure the collection";
						Sleep(10);
						COLOR(177);
						CENTER(5, 16);
						cout << "[4]";
						COLOR(191);
						cout << " to automatically encrypt the information";
						Sleep(10);
						COLOR(177);
						CENTER(5, 17);
						cout << "[5]";
						COLOR(191);
						cout << " to provide convenience and security in handling several accounts";
						Sleep(10);
						COLOR(177);
						CENTER(25, 19);
						cout << "Secure Account System ver 1.0";
						Sleep(10);
						CENTER(25, 20);
						cout << "Created by ";
						COLOR(191);
						cout << "Luke Clark Andrada";
						Sleep(10);
						COLOR(177);
						CENTER(27, 22);
						cout << "Press any key to continue";
						Sleep(10);
						CENTER(5, 1);
						system("pause > 0");
						system("cls");
						system("color f0");
						PRE();
						break;
					default:
						CENTER(42, 15);
						cout << "\t\t\t\t\t";
						CENTER(34, 16);
						cout << "Invalid";
						goto AGAIN;
				}
		}

		// function for main menu
		void MENU()
		{
			// diplay options
			START:
				system("color f0");
				COLOR(15);
				cout << "Home\n\n";
				Sleep(100);
				COLOR(177);
				cout << "What do you like to do?\n"; Sleep(100);
				COLOR(240);
				cout << "     (A) Manage Account\n"; Sleep(100);
				cout << "     (G) Generate Random Password\n"; Sleep(100);
				cout << "     (D) Deactivate Account Collection\n"; Sleep(100);
				cout << "     (E) Exit"; Sleep(100);

				cout << endl;
				AGAIN:
					// prompt user to select action
					cin.sync();
					COLOR(177);
					cout << "\nOption: ";
					COLOR(191);
					crypt.SINGLE(choice); cout << endl;
					COLOR(240);

					switch(choice[0])
					{
						case 'A':
						case 'a':
							system("cls");
							ACCOUNT();
							break;
						case 'G':
						case 'g':
							system("cls");
							GENPASS();
							break;
						case 'D':
						case 'd':
							system("cls");
							DEACTIVATE();
							break;
						case 'E':
						case 'e':
							cout << "\nExiting";
							Sleep(1500);
							exit(0);
							break;
						default:
							cout << "Invalid\n";
							goto AGAIN;
					}
		}

		// function for account menu
		void ACCOUNT()
		{
			// display options
			START:
				system("color f0");
				COLOR(15);
				cout << "Home > Account\n\n"; Sleep(100);
				COLOR(177);
				cout << "What do you like to do?\n"; Sleep(100);
				COLOR(240);
				cout << "     (A) Add a new account\t\t[R] Retrieve an account\n"; Sleep(100);
				cout << "     (D) Delete an existing account\t[B] Back to Main Menu\n"; Sleep(100);
				cout << "     (U) Update an existing account\t[E] Exit"; Sleep(100);
				COLOR(240);

				cout << endl;
				AGAIN:
					// prompt user to select action
					cin.sync();
					COLOR(177);
					cout << "\nOption: ";
					COLOR(191);
					crypt.SINGLE(choice); cout << endl;

					COLOR(240);
					switch(choice[0])
					{
						case 'A':
						case 'a':
							system("cls");
							ADD();
							break;
						case 'D':
						case 'd':
							system("cls");
							DEL();
							break;
						case 'U':
						case 'u':
							system("cls");
							UPDATE();
							break;
						case 'R':
						case 'r':
							system("cls");
							RETRIEVE();
							break;
						case 'B':
						case 'b':
							system("cls");
							MENU();
							break;
						case 'E':
						case 'e':
							cout << "\nExiting";
							Sleep(1500);
							exit(0);
							break;
						default:
							cout << "Invalid\n";
							goto AGAIN;
					}
		}

		// function for selecting existing account
		void SELECT()
		{
			// prompt user for account
			START:
				COLOR(177);
				cout << "Enter the account you want to access: ";
				COLOR(191);
				NOSPACE(selectionInput);
				COLOR(240);
				cout << endl;

				// set file location
				selection = _strupr(selectionInput);
				selection = login.folder + '/' + selection + ".txt";

				crypt.UNLOCK(crypt.folderUnlock,crypt.folderUnlockNew);
				// open file
				ifstream file;
				file.open(selection);

				// check if file is open
				if(!file.is_open())
				{
					// if not
					// prompt user to try again
					cout << "File not found.\n";

					AGAIN:
						cin.sync();
						COLOR(177);
						cout << "\nTry Again? (Y/N): ";
						COLOR(191);
						crypt.SINGLE(tryAgain); cout << endl;
						COLOR(240);

						switch(tryAgain[0])
							{
								case 'Y':
								case 'y':
									cout << endl;
									goto START;
									break;
								case 'N':
								case 'n':
									system("cls");
									MENU();
									break;
								default:
									cout << "\nInvalid";
									goto AGAIN;
							}
				}

				file.close();
				crypt.LOCK(crypt.folderUnlock,crypt.folderUnlockNew);
		}

		// function for adding new account
		void ADD()
		{
			// re-initialize variables to avoid stacking error
			for(x = 0; x < 50; x++)
				user[x] = '\0';
			for(x = 0; x < 50; x++)
				pass[x] = '\0';
			x = 0;

			system("color f0");
			COLOR(15);
			// prompt user for name of account
			cout << "Home > Account > Add\n\n";
			Sleep(100);
			COLOR(177);
			cout << "Enter name of account: ";
			COLOR(191);
			NOSPACE(selectionInput);
			COLOR(240);
			cout << endl;

			// set file location
			selection = _strupr(selectionInput);
			selection = login.folder + '/' + selection + ".txt";
			
			ADDAGAIN:
				// prompt user for account
				cout << endl;
				COLOR(177);
				cout << "Username: ";
				COLOR(191);
				NOSPACE(user);
				cout << endl;
				COLOR(177);
				cout << "Password: ";
				COLOR(191);
				ASTERISK(pass);
				cout << endl;
				COLOR(177);
				cout << "Re-enter Password: ";
				COLOR(191);
				ASTERISK(checkPass);
				COLOR(240);

				Sleep(300);
				// compare password and re-entered password
				if(!strcmp(pass, checkPass))
				{
					// if matched
					// save account
					cout << endl << endl;
					crypt.CONFIRM(login.passConfirm);
					Sleep(300);
					SUREAGAIN:
						cin.sync();
						COLOR(177);
						cout << "\nSave " << user << "?(Y/N): ";
						COLOR(191);
						crypt.SINGLE(sure); cout << endl;
						COLOR(240);

						switch(sure[0])
						{
							case 'Y':
							case 'y':
								crypt.STORE(selection, user, pass);
								cout << "\nEncrypting ";
								crypt.LOAD();
								cout << "\nAccount created successfully.\n";
								break;
							case 'N':
							case 'n':
								break;
							default:
								cout << "Invalid\n";
								goto SUREAGAIN;
						}
		
						// prompt user for the next action to take
						cout << endl;
						COLOR(177);
						cout << "What do you want to do?\n"; Sleep(100);
						COLOR(240);
						cout << "     (A) Add another account\n"; Sleep(100);
						cout << "     (B) Back to Main Menu\n"; Sleep(100);
						cout << "     (E) Exit\n"; Sleep(100);
						COLOR(230);

						AGAIN: 
							cout << endl;
							// prompt user to select an action
							cin.sync();
							COLOR(177);
							cout << "Option: ";
							COLOR(191);
							crypt.SINGLE(choice); cout << endl;
							COLOR(240);

							switch(choice[0])
							{
								case 'A':
								case 'a':
									system("cls");
									ADD();
									break;
								case 'B':
								case 'b':
									system("cls");
									MENU();
									break;
								case 'E':
								case 'e':
									cout << "\nExiting";
									Sleep(1500);
									exit(0);
									break;
								default:
									cout << "Invalid\n";
									goto AGAIN;
							}
				} else
				{
					// if pass and checkPass did not match
						PASSAGAIN:
							// prompt user to try again
							cin.sync();
							COLOR(177);
							cout << "\nPassword did not match. Try Again?(Y/N): ";
							COLOR(191);
							crypt.SINGLE(choice); cout << endl;
							COLOR(240);

							switch(choice[0])
							{
								case 'Y':
								case 'y':
									goto ADDAGAIN;
									break;
								case 'N':
								case 'n':
									cout << "\nExiting";
									Sleep(1500);
									exit(0);
									break;
								default:
									cout << "Invalid\n";
									goto PASSAGAIN;
							}
				}
		}

		// function for deleting an existing account
		void DEL()
		{
			system("color f0");
			COLOR(15);
			cout << "Home > Account > Delete\n\n";
			Sleep(100);
			SELECT();

			crypt.UNLOCK(crypt.folderUnlock,crypt.folderUnlockNew);
			// convert file location to const char to be read by remove function
			const char *delSelection = selection.c_str();
			
			Sleep(100);
			crypt.CONFIRM(login.passConfirm);
			Sleep(100);

			// delete the file
			SUREAGAIN:
				cin.sync();
				COLOR(177);
				cout << "\nDelete " << selectionInput << "?(Y/N): ";
				COLOR(191);
				crypt.SINGLE(sure); cout << endl;
				COLOR(240);

				switch(sure[0])
				{
					case 'Y':
					case 'y':
						remove(delSelection);
						crypt.LOCK(crypt.folderUnlock,crypt.folderUnlockNew);
						cout << "\nAccount deleted successfully.\n";
						break;
					case 'N':
					case 'n':
						break;
					default:
						cout << "Invalid\n";
						goto SUREAGAIN;
				}
			
				// prompt the user to select next action
				COLOR(177);
				cout << "\nWhat do you want to do?\n"; Sleep(100);
				COLOR(240);
				cout << "     (D) Delete another account\n"; Sleep(100);
				cout << "     (B) Back to Main Menu\n"; Sleep(100);
				cout << "     (E) Exit\n"; Sleep(100);
				COLOR(240);

				AGAIN: 
					cin.sync();
					COLOR(177);
					cout << "\nOption: ";
					COLOR(191);
					crypt.SINGLE(choice); cout << endl;
					COLOR(240);

					switch(choice[0])
					{
						case 'D':
						case 'd':
							system("cls");
							DEL();
							break;
						case 'B':
						case 'b':
							system("cls");
							MENU();
							break;
						case 'E':
						case 'e':
							cout << "\nExiting";
							Sleep(1500);
							exit(0);
							break;
						default:
							cout << "Invalid\n";
							goto AGAIN;
					}
		}

		// function for updating an existing account
		void UPDATE()
		{
			// re-initialize variables to avoid stacking error
			for(x = 0; x < 50; x++)
				user[x] = '\0';
			for(x = 0; x < 50; x++)
				pass[x] = '\0';
			x = 0;

			system("color f0");
			COLOR(15);
			// prompt user for which account
			cout << "Home > Account > Update\n\n";
			Sleep(100);
			SELECT();

			Sleep(100);
			// prompt user for new account information
			COLOR(177);
			cout << "Enter new username and password\n";
			cout << "Username: ";
			COLOR(191);
			NOSPACE(user);
			cout << endl;
			COLOR(177);
			cout << "Password: ";
			COLOR(191);
			ASTERISK(pass);
			cout << endl;
			COLOR(177);
			cout << "Re-enter Password: ";
			COLOR(191);
			ASTERISK(checkPass);
			COLOR(240);
			Sleep(100);

			// compare password and re-entered password
			if(!strcmp(pass, checkPass))
			{
				// if matched
				// update the account
				cout << endl << endl;
				crypt.CONFIRM(login.passConfirm);
				Sleep(100);
				SUREAGAIN:
					cin.sync();
					COLOR(177);
					cout << "\nSave " << user << "?(Y/N): ";
					COLOR(191);
					crypt.SINGLE(sure); cout << endl;
					COLOR(240);

					switch(sure[0])
					{
						case 'Y':
						case 'y':
							crypt.STORE(selection, user, pass);
							cout << "\nEncrypting ";
							crypt.LOAD();
							cout << "\nAccount updated successfully.\n\n";
							break;
						case 'N':
						case 'n':
							break;
						default:
							cout << "Invalid\n";
							goto SUREAGAIN;
					}
		
					// prompt user to select next action
					COLOR(177);
					cout << "What do you want to do?\n"; Sleep(100);
					COLOR(240);
					cout << "     (U) Update another account\n"; Sleep(100);
					cout << "     (B) Back to Main Menu\n"; Sleep(100);
					cout << "     (E) Exit\n"; Sleep(100);

					AGAIN: 
						cin.sync();
						COLOR(177);
						cout << "\nOption: ";
						COLOR(191);
						crypt.SINGLE(choice); cout << endl;
						COLOR(240);

						switch(choice[0])
						{
							case 'U':
							case 'u':
								system("cls");
								UPDATE();
								break;
							case 'B':
							case 'b':
								system("cls");
								MENU();
								break;
							case 'E':
							case 'e':
								cout << "\nExiting";
								Sleep(1500);
								exit(0);
								break;
							default:
								cout << "Invalid\n";
								goto AGAIN;
						}
			} else
			{
				// if pass and checkPass did not match
				// prompt user to try again
				PASSAGAIN:
					cin.sync();
					COLOR(177);
					cout << "\nPassword did not match. Try Again?(Y/N): ";
					COLOR(191);
					crypt.SINGLE(choice); cout << endl;
					COLOR(240);

					switch(choice[0])
					{
						case 'Y':
						case 'y':
							system("cls");
							UPDATE();
							break;
						case 'N':
						case 'n':
							cout << "\nExiting";
							Sleep(1500);
							exit(0);
							break;
						default:
							cout << "Invalid\n";
							goto PASSAGAIN;
					}
			}
		}

		// function for retrieving an existing account
		void RETRIEVE()
		{
			// re-initialize variables to avoid stacking error
			for(x = 0; x < 50; x++)
				user[x] = '\0';
			for(x = 0; x < 50; x++)
				pass[x] = '\0';
			x = 0;
			char day[5], month[5];
			string date;

			system("color f0");
			COLOR(15);
			// prompt user to select which account
			cout << "Home > Account > Retrieve\n\n";
			Sleep(100);
			SELECT();

			Sleep(100);
			crypt.CONFIRM(login.passConfirm);

			crypt.UNLOCK(crypt.folderUnlock, crypt.folderUnlockNew);
			// open file
			// read account information
			ifstream file;
			file.open(selection);

			file >> user;
			file >> pass;
			file >> day >> month;
			getline(file, date);

			// decrypt pass
			crypt.DECRYPT(pass);
			cout << "\n\nDecrypting ";
			crypt.LOAD();
			cout << endl;

			// display account information
			COLOR(177);
			cout << "\nUsername: " << user; Sleep(100);
			cout << "\nPassword: " << pass; Sleep(100);
			cout << "\nRecord: " << day << ' ' << month << date;  Sleep(100);
			COLOR(240);

			file.close();
			crypt.LOCK(crypt.folderUnlock,crypt.folderUnlockNew);

			// prompt user to select next action
			cout << "\n\nAccount retrieved successfully.\n\n";  Sleep(100);
			COLOR(177);
			cout << "What do you want to do?\n";  Sleep(100);
			COLOR(240);
			cout << "     (R) Retrieve another account\n";  Sleep(100);
			cout << "     (B) Back to Main Menu\n";  Sleep(100);
			cout << "     (E) Exit\n";  Sleep(100);
			COLOR(240);

			AGAIN: 
				cin.sync();
				COLOR(177);
				cout << "\nOption: ";
				COLOR(191);
				crypt.SINGLE(choice); cout << endl;
				COLOR(240);

				switch(choice[0])
				{
					case 'R':
					case 'r':
						system("cls");
						RETRIEVE();
						break;
					case 'B':
					case 'b':
						system("cls");
						MENU();
						break;
					case 'E':
					case 'e':
						cout << "\nExiting";
						Sleep(1500);
						exit(0);
						break;
					default:
						cout << "Invalid\n";
						goto AGAIN;
				}
		}

		// function for password generator mode selection
		void GENPASS()
		{
			// display options
			system("color f0");
			START:
				COLOR(15);
				cout << "Home > Generate\n\n"; Sleep(100);
				COLOR(177);
				cout << "What type of characters?\n"; Sleep(100);
				COLOR(240);
				cout << "     (A) Alphanumeric\t(C) Custom\n"; Sleep(100);
				cout << "     (L) Letters\t(B) Back to Main Menu\n"; Sleep(100);
				cout << "     (N) Numbers\t(E) Exit\n"; Sleep(100);

				// prompt user for length of the password to be generated
				LENGTHAGAIN:
					cin.sync();
					COLOR(177);
					cout << "\nPassword Length: ";
					COLOR(191);
					cin >> randomLength;
					COLOR(240);

					// check input failures
					if(cin.fail())
					{
						cin.clear();
						cout << "Invalid\n";
						goto LENGTHAGAIN;
					}

					// check if the length is sufficient
					if(randomLength > 50 || randomLength < 1)
					{
						// if it exceeded
						// prompt user to enter new length
						cout << "Length exceeded limit\n";

						SUREAGAIN:
							cin.sync();
							COLOR(177);
							cout << "\nEnter new settings?(Y/N): ";
							COLOR(191);
							crypt.SINGLE(tryAgain); cout << endl;
							COLOR(240);

							switch(tryAgain[0])
							{
								case 'Y':
								case 'y':
									goto LENGTHAGAIN;
									break;
								case 'N':
								case 'n':
									system("cls");
									MENU();
									break;
								default:
									cout << "Invalid\n";
									goto SUREAGAIN;
							}
					}

					MODEAGAIN:
						// prompt user to select mode
						cin.sync();
						COLOR(177);
						cout << "Mode: ";
						COLOR(191);
						crypt.SINGLE(choice); cout << endl;
						COLOR(240);

						switch(choice[0])
						{
							case 'A':
							case 'a':
								system("cls");
								ALPHA(randomLength);
								break;
							case 'L':
							case 'l':
								system("cls");
								LETTERS(randomLength);
								break;
							case 'N':
							case 'n':
								system("cls");
								NUMBERS(randomLength);
								break;
							case 'C':
							case 'c':
								system("cls");
								CUSTOM(randomLength);
								break;
							case 'B':
							case 'b':
								system("cls");
								MENU();
								break;
							case 'E':
							case 'e':
								cout << "\nExiting";
								Sleep(1500);
								exit(0);
								break;
							default:
								cout << "Invalid\n\n";
								goto MODEAGAIN;
						}
			}

		// function for password generator sub menu
		void GENPASSMENU(char mode)
		{
			// display options
			COLOR(177);
			cout << "\n\nWhat do you want to do?\n"; Sleep(100);
			COLOR(240);
			cout << "     (N) Create a new account using the generated password\n"; Sleep(100);
			cout << "     (U) Update an existing account using the generated password\n"; Sleep(100);
			cout << "     (G) Generate a new password\n"; Sleep(100);
			cout << "     (M) Choose another mode\n"; Sleep(100);
			cout << "     (B) Back to Main Menu\n"; Sleep(100);
			cout << "     (E) Exit\n"; Sleep(100);

			AGAIN:
				// prompt user to select an 
				COLOR(177);
				cout << "\nOption: ";
				cin.sync();
				COLOR(191);
				crypt.SINGLE(choice); cout << endl;
				COLOR(240);
				
				switch(choice[0])
				{
					case 'N':
					case 'n':
						system("cls");
						GENADD();
						break;
					case 'U':
					case 'u':
						system("cls");
						GENUPDATE();
						break;
					case 'G':
					case 'g':
						switch(mode)
						{
							case 'A':
							case 'a':
								system("cls");
								ALPHA(randomLength);
								break;
							case 'L':
							case 'l':
								system("cls");
								LETTERS(randomLength);
								break;
							case 'N':
							case 'n':
								system("cls");
								NUMBERS(randomLength);
								break;
							case 'C':
							case 'c':
								system("cls");
								CUSTOM(randomLength);
								break;
						}
						break;
					case 'M':
					case 'm':
						system("cls");
						GENPASS();
						break;
					case 'B':
					case 'b':
						system("cls");
						MENU();
						break;
					case 'E':
					case 'e':
						cout << "\nExiting";
						Sleep(1500);
						exit(0);
						break;
					default:
						cout << "Invalid\n";
						goto AGAIN;
				}
		}

		// function for generating random alphanumeric password
		void ALPHA(int length)
		{
			// declare and initialize variables
			i = 0;
			for(x = 0; x <= 49; x++)
				randomPass[x] = '\0';
			int size = length;
			srand(time(NULL));
			char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

			system("color f0");
			COLOR(15);
			cout << "Home > Generate > Alphanumeric\n\n";

			// loop for generating the password
			while(size--)
			{
				x = rand() % 61;
				randomPass[i] = alpha[x];
				i++;
			}

			Sleep(100);
			COLOR(177);
			cout << "Random Password: " << randomPass;
			GENPASSMENU('A');
		}

		// function for generating random letter password
		void LETTERS(int length)
		{
			// declare and initialize variables
			i = 0;
			for(x = 0; x <= 49; x++)
				randomPass[x] = '\0';
			int size = length;
			srand(time(NULL));
			char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

			system("color f0");
			COLOR(15);
			cout << "Home > Generate > Letters\n\n";

			// loop for generating the password
			while(size--)
			{
				x = rand() % 51;
				randomPass[i] = letters[x];
				i++;
			}

			Sleep(100);
			COLOR(177);
			cout << "Random Password: " << randomPass;
			GENPASSMENU('L');
		}

		// function for generating random numeric password
		void NUMBERS(int length)
		{
			// declare and initialize variables
			i = 0;
			for(x = 0; x <= 49; x++)
				randomPass[x] = '\0';
			x = 0;
			int size = length;
			srand(time(NULL));
			char numbers[] = "0123456789";

			system("color f0");
			COLOR(15);
			cout << "Home > Generate > Numbers\n\n";

			// loop for generating the password
			while(size--)
			{
				x = rand() % 9;
				randomPass[i] = numbers[x];
				i++;
			}

			Sleep(100);
			COLOR(177);
			cout << "Random Password: " << randomPass;
			GENPASSMENU('N');
		}

		// function for generating random custom password
		void CUSTOM(int length)
		{
			// declare and initialize variables
			i = 0;
			for(x = 0; x < 50; x++)
				randomPass[x] = '\0';
			x = 0;
			int size = length;
			srand(time(NULL));
			cin.sync();
			char custom[50] = "\0";

			system("color f0");
			COLOR(15);
			// prompt the user for custom characters
			cout << "Home > Generate > Custom\n\n";
			Sleep(100);
			COLOR(177);
			cin.sync();
			cout << "Enter custom characters: ";
			COLOR(191);
			crypt.NOSPACE(custom);
			COLOR(240);
			cout << endl;

			// loop for generating variables
			while(size--)
			{
				x = rand() % (strlen(custom) - 1);
				randomPass[i] = custom[x];
				i++;
			}

			Sleep(100);
			COLOR(177);
			cout << "Random Password: " << randomPass;
			GENPASSMENU('C');
		}

		// function for using the generated password to create a new account
		void GENADD()
		{
			system("color f0");
			COLOR(15);
			// prompt user for input
			cout << "Home > Generate > Add\n\n";
			Sleep(100);
			COLOR(177);
			cout << "Enter name of account: ";
			COLOR(191);
			NOSPACE(selectionInput);
			COLOR(240);
			cout << endl;

			// set file location
			selection = _strupr(selectionInput);
			selection = login.folder + '/' + selection + ".txt";
			
			ADDAGAIN:
				// prompt user for username
				cout << endl;
				Sleep(100);
				COLOR(177);
				cout << "Username: ";
				COLOR(191);
				NOSPACE(user);
				strcpy_s(pass, randomPass);

				COLOR(240);
				cout << endl << endl;
				Sleep(100);
				crypt.CONFIRM(login.passConfirm);
				Sleep(100);

				// save account
				SUREAGAIN:
					cin.sync();
					COLOR(177);
					cout << "\nSave " << user << "?(Y/N): ";
					COLOR(191);
					crypt.SINGLE(sure); cout << endl;
					COLOR(240);

					switch(sure[0])
					{
						case 'Y':
						case 'y':
							crypt.STORE(selection, user, pass);
							cout << "\nEncrypting ";
							crypt.LOAD();
							cout << "\nAccount created successfully.\n";
							break;
						case 'N':
						case 'n':
							cout << endl;
							break;
						default:
							cout << "Invalid\n";
							goto SUREAGAIN;
					}
		
					// prompt user to select next action
					cout << endl;
					Sleep(100);
					COLOR(177);
					cout << "What do you want to do?\n"; Sleep(100);
					COLOR(240);
					cout << "     (G) Generate a new password\n"; Sleep(100);
					cout << "     (B) Back to Main Menu\n"; Sleep(100);
					cout << "     (E) Exit\n"; Sleep(100);

					cout << endl;
					AGAIN: 
						cin.sync();
						COLOR(177);
						cout << "Option: ";
						COLOR(191);
						crypt.SINGLE(choice); cout << endl;
						COLOR(240);

						switch(choice[0])
						{
							case 'G':
							case 'g':
								system("cls");
								GENPASS();
								break;
							case 'B':
							case 'b':
								system("cls");
								MENU();
								break;
							case 'E':
							case 'e':
								cout << "\nExiting";
								Sleep(1500);
								exit(0);
								break;
							default:
								cout << "Invalid\n\n";
								goto AGAIN;
						}
		}

		// function for using the generated password to update an existing account
		void GENUPDATE()
		{
			system("color f0");
			COLOR(15);
			// prompt user to select which account
			cout << "Home > Generate > Update\n\n";
			Sleep(100);
			SELECT();
			Sleep(100);

			// prompt user for new username
			COLOR(177);
			cout << "Enter new username\n";
			Sleep(100);
			cout << "Username: ";
			COLOR(191);
			NOSPACE(user);
			strcpy_s(pass, randomPass);
			COLOR(240);
			Sleep(100);

			// update account
			cout << endl << endl;
			crypt.CONFIRM(login.passConfirm);
			Sleep(100);
			SUREAGAIN:
				cin.sync();
				COLOR(177);
				cout << "\nSave " << user << "?(Y/N): ";
				COLOR(191);
				crypt.SINGLE(sure); cout << endl;
				COLOR(240);

				switch(sure[0])
				{
					case 'Y':
					case 'y':
						crypt.STORE(selection, user, pass);
						cout << "\nEncrypting ";
						crypt.LOAD();
						cout << "\nAccount updated successfully.\n\n";
						break;
					case 'N':
					case 'n':
						break;
					default:
						cout << "Invalid\n";
						goto SUREAGAIN;
				}
		
				// prompt user to select next action
				Sleep(100);
				COLOR(177);
				cout << "What do you want to do?\n"; Sleep(100);
				COLOR(240);
				cout << "     (G) Generate a new password\n"; Sleep(100);
				cout << "     (B) Back to Main Menu\n"; Sleep(100);
				cout << "     (E) Exit\n"; Sleep(100);

				AGAIN: 
					cin.sync();
					COLOR(177);
					cout << "\nOption: ";
					COLOR(191);
					crypt.SINGLE(choice); cout << endl;
					COLOR(240);

					switch(choice[0])
					{
						case 'G':
						case 'g':
							system("cls");
							GENPASS();
							break;
						case 'B':
						case 'b':
							system("cls");
							MENU();
							break;
						case 'E':
						case 'e':
							cout << "\nExiting";
							Sleep(1500);
							exit(0);
							break;
						default:
							cout << "Invalid\n";
							goto AGAIN;
					}
		}

		// function for deactivating accout collection
		void DEACTIVATE()
		{
			char dOLD[50], dNEW[] = "C:/TRASH";

			system("color f0");
			COLOR(15);
			cout << "Home > Deactivate\n\n";
			Sleep(100);

			crypt.CONFIRM(login.passConfirm);
			Sleep(100);

			// delete the file
			SUREAGAIN:
				cin.sync();
				COLOR(177);
				cout << "\nDeactivate Account?(Y/N): ";
				COLOR(191);
				crypt.SINGLE(sure); cout << endl;
				COLOR(240);
				
				switch(sure[0])
				{
					case 'Y':
					case 'y':
							crypt.UNLOCK(crypt.folderUnlock,crypt.folderUnlockNew);
							for(x = 0; x < 50; x++)
								dOLD[x] = '\0';
							x = 0;

							strcpy_s(dOLD, crypt.folderUnlock);
							rename(dOLD, dNEW);

							cout << "\nDeleting ";
							crypt.LOAD();
							cout << "\nAccount deleted successfully.";
							Sleep(300);
							cout << "\n\nExiting";

							CLEAR(dNEW);						
							RemoveDirectory(dNEW);
							Sleep(3000);
							system("cls");
							exit(0);
							break;
					case 'N':
					case 'n':
						system("cls");
						MENU();
						break;
					default:
						cout << "Invalid\n";
						goto SUREAGAIN;
				}
		}

		// function for clearing the folder of all files
		void CLEAR(char folder[50])
		{
		 char fileFound[256];
		 char folderPath[50];
		 strcpy_s(folderPath, folder);
		 WIN32_FIND_DATA info;
		 HANDLE hp; 
		 sprintf_s(fileFound, "%s\\*.*", folderPath);
		 hp = FindFirstFile(fileFound, &info);

		 do
			{
			   sprintf_s(fileFound,"%s\\%s", folderPath, info.cFileName);
			   DeleteFile(fileFound);
 
			}while(FindNextFile(hp, &info)); 

		 FindClose(hp);
		}
} menu;

int main()
{
	system("color F0");

	// set the console title
	SetConsoleTitle("Secure Account System");

	// call WELCOME()
	menu.WELCOME();

	// call PRE()
	menu.PRE();

	// call PRELOGIN() for prelogin events
	login.PRELOGIN();

	while(1)
	{
		// call MENU();
		menu.MENU();
	}

	system("pause > 0");
}
