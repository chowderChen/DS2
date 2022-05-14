#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std ;

typedef struct S {
    char id[10] ;
    char name[10] ;
    unsigned char score[6] ;
    float mean ;
} Student ;

int Text2Binary( string fileName ){
    fstream inFile, outFile ;
    inFile.open( ( "input" + fileName + ".txt" ).c_str(), fstream::in ) ;
    if ( !inFile.is_open() ) {
        return 0 ;
    }
    else {
        fileName = "input" + fileName + ".bin" ;
        outFile.open( fileName.c_str(), fstream::out | fstream::binary ) ; // create a bin file
        char buffer[255] ; // buffer to keep whole record.
        int studentNum = 0 ; // total number of student
        while( inFile.getline( buffer, 255, '\n' ) ) { // retrieve one entire record
            // buffer get the record
            string temp ;
            Student oneSet ;
            int columnNo = 0, pre = 0, pos = 0 ; // pre:start of column. pos:end of column
            studentNum++ ;
            temp.assign( buffer ) ; // copy buffer to temp. duplicate entire record of buffer.
            pos = temp.find_first_of( '\t', pre ) ; // find the end of the first field( id/name/score... )
            while( pos != string::npos ) {
                // npos: maximum value of size_t, end of data type string
                // or when string::find() find nothing, it return string::npos
                switch( ++columnNo ) { // retrieve one field
                    case 1: strcpy( oneSet.id, temp.substr( pre, pos - pre ).c_str() ) ;
                            // retrieve id
                        break ;
                    case 2: strcpy( oneSet.name, temp.substr( pre, pos - pre ).c_str() ) ;
                            // retrieve name
                        break ;
                    default: oneSet.score[columnNo - 3] = atoi( temp.substr( pre, pos - pre ).c_str() ) ;
                        break ;
                } // end switch
                pre = ++pos ;
                pos = temp.find_first_of( '\t', pre ) ;
            } // end while
            pos = temp.find_last_of( '\t' ) ;
            oneSet.mean = atof( temp.substr(pos+1).c_str() ) ; // get mean
            outFile.write( (char*)&oneSet, sizeof( oneSet ) ) ; // write record to bin file
        } // end while
        outFile.close() ;
        inFile.close() ;
        return studentNum ;
    } // end else
} // end Text2Binary()

bool ReadBin( string fileName, vector<Student>& sList ) {
    fstream file ;
    Student oneSet ;
    int studentNum = 0 ;
    fileName = "input" + fileName + ".bin" ;
    file.open( fileName.c_str(), fstream::in | fstream::binary ) ;
    if ( file.is_open() ) {
        file.seekg( 0, file.end ) ;
        studentNum = file.tellg() / sizeof(oneSet) ;
        file.seekg( 0, file.beg ) ;
        for ( int i = 0 ; i < studentNum ; i++ ) {
            file.read( (char*)&oneSet, sizeof( oneSet ) ) ;
            sList.push_back( oneSet ) ;
            // cout << "[" << i+1 << "]" << oneSet.id << ", " << oneSet.name << endl ;
        } // end for
    } // end if
    else {
      return false;
    }
    file.close() ;
    return true ;
} // end ReadBin()

bool is_prime(int n) {

    if (n == 1) {
        return false;
    }
    int i = 2;
    // loops from 2 to sqrt(x)
    while (i*i <= n) {
        if (n % i == 0) {
		    // it is not a prime number
            return false;
        }
        i++ ;
    }

    return true;
}

int findClosestPrime( int num ) { // find prime greater tham and closest to num * 1.2
	num = num * 1.2 + 1 ;
	for( ; !is_prime(num) ; num++ )
		; // stops when num is a prime number
	return num ;
}

class HashType {
public:
    char id[10] ;
    char name[10] ;
    float mean ;
    int hValue ; // hash value

    HashType() {
        for( int i = 0 ; i < 10 ; i++ ) {
        	id[i] = '\0' ;
        	name[i] = '\0' ;
		}
        mean = 0.0 ;
        hValue = -1 ;
    } // end HashType

    void Set( Student student, int inHValue ) {
        strcpy( id, student.id ) ;
        strcpy( name, student.name ) ;
        mean = student.mean ;
        hValue = inHValue ;
    } // end Set()

    void SetID( char temp[10] ) {
    	strcpy(id,temp) ;
	}

    void Initialize() {
        for( int i = 0 ; i < 10 ; i++ ) {
        	id[i] = '\0' ;
        	name[i] = '\0' ;
		}
        mean = 0.0 ;
        hValue = -1 ;
    }

    bool IsEmpty() {
        if ( hValue == -1 ) {
            return true ;
        }
        return false ;
    } // end IsEmpty

};

class Hash {
protected:
    vector<HashType> table ;
    int tableSize ;
public:
    Hash() {
        tableSize = 0 ;
    }

    int HashFunction ( char id[10] ) {
        int key = 0 ;
        for ( int i = 0 ; id[i] != '\0' ; i++ ) {
            if ( i == 0 ) {
                key = id[i] ;
            }
            else if ( i == 3 || i == 6 ) {
                key = key * id[i] % tableSize ;
            }
            else {
                key = key * id[i] ;
            }
        } // end for
        key = key % tableSize ;
        return key ;
    } // end HashFunction()

    void SetTableSize( vector<Student> sList ) {
        tableSize = findClosestPrime( sList.size() ) ;
        HashType aHashType ;
        for ( int i = 0 ; i < tableSize ; i++ ) {
            table.push_back( aHashType ) ;
        }
    } // end SetTableSize()

    int PositionOffset(int initial, int steps ) {
        if( steps != 0 ) {
            int rem = steps % tableSize ; // rem < tablesize
            int result = initial + rem ; // May exceed last index
            if( result > tableSize - 1 )
                result = result - tableSize ; // compensate

            return result ;
        } // end if
        return initial ;
    } // end PositionOffset()

    void Export( string hashType, string fileName ) {
        fstream file ;
        fileName = hashType + fileName + ".txt" ;
        file.open( fileName.c_str(), fstream::out ) ;
        if( strcmp( hashType.c_str(), "linear" ) == 0 )
        	file << " --- Hash table created by Linear probing    ---\n" ;
        if( strcmp( hashType.c_str(), "quadratic" ) == 0 )
        	file << " --- Hash table created by Quadratic probing    ---\n" ;
        for ( int i = 0 ; i < tableSize ; i++ ) {
            file << "[" << i << "]" ;
            if ( !table.at(i).IsEmpty() ) {
                file << "          "
                     << table.at(i).hValue << ",   "
                     << table.at(i).id << ",     "
                     << table.at(i).name << ",      "
                     << table.at(i).mean ;
            } // end if
            file << "\n" ;
        } // end for
        file << " ----------------------------------------------------- " << endl ;
        file.close() ;
    } // end Export()

};

class LinearHash: public Hash {
public:
    void LinearProbe( vector<Student> sList ) {
        for ( int i = 0 ; i < sList.size() ; i++ ) {
            int hValue = HashFunction( sList[i].id ) ;
            if ( table[hValue].IsEmpty() ) {
                table[hValue].Set( sList[i], hValue ) ;
                // cout << "one probe success." << endl ;
            } // end if
            else {
                bool probeSuccess = false ;
                for ( int j = PositionOffset( hValue, 1 ) ; j != hValue && !probeSuccess ; j = PositionOffset( j, 1 ) ) {
                    if ( table[j].IsEmpty() ) {
                        table[j].Set( sList[i], hValue ) ;
                        probeSuccess = true ;
                        // cout << "one probe success." << endl ;
                    } // end if
                } // for
            } // end else
        } // end for
    } // end LinearProbe()

    float Search( char id[10] ) { // return probeCount
        bool isFound = false ;
        int key = HashFunction( id ) ;
        float probeCount = 0 ;
        for ( int i = key ; !isFound ; i = PositionOffset( i, 1 ) ) {
            probeCount++ ;
            if( strcmp( id, table[i].id ) == 0 || table[i].IsEmpty() ) {
            	isFound = true ;
            }
        } // end for
        return probeCount ;
    } //end Search()

    bool Search( string id, int& probes, string& name, float& mean ) { // return probeCount
        probes  = 0 ;
        bool isFound = false ;
        char tempId[10] ;
        for ( int i = 0 ; i < 10 ; i++ ) {
            tempId[i] = id[i] ;
        }
        int key = HashFunction( tempId ) ;

        for ( int i = key ; !isFound ; i = PositionOffset( i, 1 ) ) {
            probes++ ;
            if( strcmp( id.c_str(), table[i].id ) == 0 ) {
                name = table[i].name ;
                mean = table[i].mean ;
                return true ;
            }

            else if( table[i].IsEmpty() )
                return false ;
        } // end for

    } //end Search()

    void AverageSearchExist( vector<Student> sList ) {
        float averageTime = 0 ;
        for ( int i = 0 ; i < sList.size() ; i++ ) {
            averageTime = averageTime + Search( sList.at(i).id ) ;
        } // for
        averageTime = averageTime / sList.size() ;
        cout << "Successful search: "
             << fixed << setprecision( 4 ) << averageTime << " comparisons on average."
             << endl ;
    } // end AverageSearchExist()

    float SearchEmpty( int i ) { // i = some location
        float probeCount = 0 ;
        bool foundEmpty = false ;
        for ( ; !foundEmpty ; i = PositionOffset(i,1) ) {
            probeCount++ ;
            if( table[i].IsEmpty() )
            	foundEmpty = true ;
        }

        return probeCount ;
    } // end SearchEmpty()

    void AverageSearchNonExist() {
        float averageTime = 0 ;
        HashType temp ; // nothing in here...
        for ( int i = 0 ; i < tableSize ; i++ ) {
            if( !table[i].IsEmpty() ) { // not empty.
            	averageTime = averageTime + SearchEmpty(i) ;
			}
			else { // nothing there, so +1
				averageTime++ ;
			}
        }

        averageTime = averageTime / tableSize - 1 ;

        cout << "Unsuccessful search: "
             << fixed << setprecision( 4 ) << averageTime << " comparisons on average."
             << endl ;
    } // AverageSearchNonExist()

    void PrintTable() {
        for ( int i = 0 ; i < tableSize ; i++ ) {
            if ( !table.at(i).IsEmpty() ) {
                cout << table.at(i).hValue << endl ;
            }
        }
    }
}; // end class LinearHash

class QuadHash: public Hash {
public:

    void QuadProbe( vector<Student> sList ) { // creats table via,quad probing
    	bool inserted = false ;
        for ( int i = 0 ; i < sList.size() ; i++ ) {
            int hValue = HashFunction( sList[i].id ) ; // hash
            inserted = false ;
            for ( int j = 0 ; (j*j) < tableSize * tableSize && !inserted ; j++ ) {
                int step = j * j ; // j squared
                int newPos = PositionOffset(hValue, step) ;
                if ( table[newPos].IsEmpty() ) {
                    table[newPos].Set( sList[i], hValue ) ; // not sure hValue = legit
                    inserted = true ;
                } // end if

            } // for

        } // end for

    } // end QuadProbe()

    bool Compare( char id1[10], char id2[10] ) { // compares char[] id1, id2
		for( int i = 0 ; i < 10 ; i++ ) {
			if( id1[i] != id2[i] ) {
				return false ;
			}
		}

		return true ;
	}

    float Search( char id[10] ) { // return probeCount
        bool isFound = false ;
        int key = HashFunction( id ) ;

        float probeCount = 0 ;
        int steps = 0 ;
        for ( int newPos = key ; !isFound && steps*steps < tableSize * tableSize ; steps++ ) {
            probeCount++ ;
            newPos = PositionOffset(key,steps*steps) ;
            if( strcmp( id, table[newPos].id ) == 0 ) {
            	isFound = true ;
            }
        } // end for

        if( !isFound ) {
			probeCount = 0 ; // Prevents non-existent searches. from counting probes
			cout << id << " is too big!" << endl ;
		}

        return probeCount ;
    } //end Search()

    bool Search( string id, int& probeCount, string& name, float& mean ) {
        bool isFound = false ;
        char tempId[10] ;
        for ( int i = 0 ; i < 10 ; i++ ) {
            tempId[i] = id[i] ;
        }
        int key = HashFunction( tempId ) ;

        probeCount = 0 ;
        int steps = 0 ;
        for ( int newPos = key ; !isFound && steps*steps < tableSize * tableSize ; steps++ ) {
            probeCount++ ;
            newPos = PositionOffset(key,steps*steps) ;
            if( strcmp( id.c_str(), table[newPos].id ) == 0 ) {
            	isFound = true ;
            	name = table[newPos].name ;
            	mean = table[newPos].mean ;
            	return true ;
            }
            else if ( table[newPos].IsEmpty() ) {
                return false ;
            }
        } // end for

        if( !isFound ) {
			return false ;
		}

        return true ;
    } // end bool Search()

    void AverageSearchExist( vector<Student> sList ) {
        float averageTime = 0 ;
        int sampleSize = sList.size() ;
        int probes = 0 ;
        for ( int i = 0 ; i < sList.size() ; i++ ) {
        	probes = Search( sList.at(i).id ) ;
            averageTime = averageTime + probes ;
            if( probes == 0 ) {
            	sampleSize-- ;
            }

        } // for
        averageTime = averageTime / sampleSize ;
        cout << "Successful search: "
             << fixed << setprecision( 4 ) << averageTime << " comparisons on average."
             << endl ;
    } // end AverageSearchExist()

    float SearchEmpty( int i ) { // i = some location
        float probeCount = 0 ;
        bool foundEmpty = false ;
        int key = i ;
        for ( int steps = 0 ; !foundEmpty ; steps++ ) {
            probeCount++ ;
            if( table[PositionOffset(key,steps*steps)].IsEmpty() )
            	foundEmpty = true ;
        }

        return probeCount ;
    } // end SearchEmpty()

    void AverageSearchNonExist() {
        float averageTime = 0 ;
        HashType temp ; // nothing in here...
        for ( int i = 0 ; i < tableSize ; i++ ) {
            if( !table[i].IsEmpty() ) { // not empty.
            	averageTime = averageTime + SearchEmpty(i) ;
				// cout << SearchEmpty(i) << endl ;
			}

			else { // nothing there, so +1
				averageTime++ ;
			}
        }

        averageTime = averageTime / tableSize - 1 ;

        cout << "Unsuccessful search: "
             << fixed << setprecision( 4 ) << averageTime << " comparisons on average."
             << endl ;
    } // AverageSearchNonExist()

}; // end class QuadHash


#endif // HASH_H_INCLUDED
