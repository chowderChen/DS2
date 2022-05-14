// 第3組 10720111陳少暉, 10720115林耕逸

#include "hash_v2.h"
using namespace std ;

class Prompts {
	public:

	void choices() {
		cout << "******* Hash Table ******" << endl ;
    	cout << "* 1. Linear probing     *" << endl ;
		cout << "* 2. Quadratic probing  *" << endl ;
		cout << "* 0. QUIT               *" << endl ;
		cout << "*************************" << endl ;
	}

	void prompt() {
		cout << "Input(0, 1, 2): " ;
	}
};

int main() {
    Prompts prompt ;
    prompt.choices() ;
    prompt.prompt() ;

    string fileName ;
	string mode ; // 0,1,2
	cin >> mode ;

	while( strcmp(mode.c_str(), "0" ) != 0 ) {

		if( strcmp(mode.c_str(), "1" ) == 0 || strcmp(mode.c_str(), "2" ) == 0 ) {
			cout << "Enter file number(301): " ;
    		cin >> fileName ;
		    Text2Binary( fileName ) ;
		    vector< Student > sList;
 		    if ( ReadBin( fileName, sList ) ) {

 		    	if( strcmp(mode.c_str(), "1" ) == 0 ) { // linear
 		    		cout << "Creating table via linear probing..." << endl ;
 		    		LinearHash linearHash ;
   					linearHash.SetTableSize( sList ) ;
					linearHash.LinearProbe(sList) ;

					linearHash.AverageSearchNonExist() ;
   			    	linearHash.AverageSearchExist( sList ) ;
					linearHash.Export("linear", fileName) ;

					cout << endl << "Input a student Id to search ( 0 to quit ) : " ;
					string id ;
					cin >> id ;
					while ( id.compare( "0" ) != 0 ) {
                        int probeCount = 0 ;
                        string name ;
                        float mean = 0.0 ;
                        cout << endl ;
                        if ( linearHash.Search( id, probeCount, name, mean ) ) {
                            cout << "{ " << id << ", " << name
                                 << fixed << setprecision( 2 ) << ", " << mean << " } "
                                 << "is found after " << probeCount << " probes." << endl ;
                        } // end if
                        else {
                            cout << id << "is not found after " << probeCount << " probes." << endl ;

                        }

                        cout << endl << "Input a student Id to search ( 0 to quit ) : " ;
                        cin >> id ;

					} // end while
				} // end if linear

				else if ( strcmp(mode.c_str(), "2" ) == 0 ) { // quad
                    cout << "Creating table via quadratic probing..." << endl ;
                    QuadHash quadHash ;
   					quadHash.SetTableSize( sList ) ;
					quadHash.QuadProbe(sList) ;

					quadHash.AverageSearchNonExist() ;
   			    	quadHash.AverageSearchExist( sList ) ;
					quadHash.Export("quadratic", fileName.c_str()) ;

					cout << endl << "Input a student Id to search ( 0 to quit ) : " ;
					string id ;
					cin >> id ;
					while ( id.compare( "0" ) != 0 ) {
                        int probeCount = 0 ;
                        string name ;
                        float mean = 0.0 ;
                        cout << endl ;
                        if ( quadHash.Search( id, probeCount, name, mean ) ) {
                            cout << "{ " << id << ", " << name
                                 << ", " << fixed << setprecision( 2 ) << mean << " } "
                                 << "is found after " << probeCount << " probes." << endl ;
                        } // end if
                        else {
                            cout << id << " is not found after " << probeCount << " probes." << endl ;
                            // char temp[10] = { '2', '3', '2', '1', '2', '3', '1', '\0'} ;
                            // 232134123412
                            // cout << quadHash.HashFunction( temp ) << endl ;
                        }

                        cout << endl << "Input a student Id to search ( 0 to quit ) : " ;
                        cin >> id ;

					} // end while

				} // end if quad

 		    	cout << endl ;
			} // end if

			else
 		    	cout << "NO SUCH FILE!" << endl ;


		}

		else
			cout << "Invalid choice,try again bruh." << endl ;

        prompt.choices() ;
		prompt.prompt() ;
		cin >> mode ;
	}

	cout << "EXITING..." << endl ;


    return 0 ;
}
