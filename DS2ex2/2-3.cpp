// 10720111 ³¯¤Ö·u 10720115 ªL¯Ñ¶h 
 
#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <array>

using namespace std;

class CollegeType {
	// a department with it's information
	public:
		int inputId ; // The input number of school 
		string nameSchool;	
		string nameMajor ;	
		string division ;	
		string level ;
		int numStudent ;
		int numTeacher ;
		int numGraduate ;
		
		void Reset() {
			// reset the data of the college
			inputId = 0 ;
			nameSchool = "";
			nameMajor = "" ;
			division = "";
			level = "";
			numStudent = 0;
			numTeacher = 0 ;
			numGraduate = 0 ;
		} // Reset()
	
}; // class CollegeType

class CollegeList {
	// contain a list of department
	public:
		vector< CollegeType > collegeSet ;
		
		void DeleteGraduate( int num ) {
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				if ( collegeSet.at(i).numGraduate <= num ) {
					/*
					cout << collegeSet[i].nameSchool << "\t" << collegeSet[i].nameMajor << "\t"
						 << collegeSet[i].division << "\t" << collegeSet[i].level << "\t" 
						 << collegeSet[i].numStudent << "\t" << collegeSet[i].numTeacher << "\t"
						 << collegeSet[i].numGraduate << "\n";
					*/
					collegeSet.erase( collegeSet.begin() + i ) ;
					i-- ;
				} // if 
			} // for
		} // DeleteGraduate()
		
		bool Load( string fileName ) {
	    	// Load a file, turn it into a vector
		    FILE *infile = NULL ;
		    bool success = false ;
		    // open .txt file
		    fileName = "input" + fileName + ".txt" ;
		    infile = fopen(fileName.c_str(), "r" ) ;
		
			if ( infile == NULL )
				;
			else{
		        char tempChar ;
		        // remove unwanted data 
		        for ( int i = 0 ; i < 3 ; i++ )
		        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' )
		            	;
		
		        CollegeType aCollege ;
		        aCollege.Reset() ;
		        
		        int inputId = 0 ;
				int numTab = 0 ;
				string stringStudent = "" ;
				string stringTeacher = "" ;
				string stringGraduate = "" ;
				
		        while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
		        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) {
		        		// use tabs to identify the information I want
		        		if ( tempChar == '\t' )
		        			numTab++ ;
		        		else if ( numTab == 1 )
		        			aCollege.nameSchool = aCollege.nameSchool + tempChar ;
		        		else if ( numTab == 3 )
		        			aCollege.nameMajor = aCollege.nameMajor + tempChar ;
		        		else if ( numTab == 4 )
		        			aCollege.division = aCollege.division + tempChar ;
		        		else if ( numTab == 5 )
		        			aCollege.level = aCollege.level + tempChar ;
		        		else if ( numTab == 6 )
		        			stringStudent = stringStudent + tempChar ;
		        		else if ( numTab == 7 )
		        			stringTeacher = stringTeacher + tempChar ;
		        		else if ( numTab == 8 )
		        			stringGraduate = stringGraduate + tempChar ;
		        		
		        	} // while
		        	
		        	aCollege.numStudent = atoi( stringStudent.c_str() ) ;
		        	aCollege.numTeacher = atoi( stringTeacher.c_str() ) ;
		        	aCollege.numGraduate = atoi( stringGraduate.c_str() ) ;
		        	
		        	inputId++ ; 
		        	aCollege.inputId = inputId ; 
		            collegeSet.push_back( aCollege ) ;
		            
		            aCollege.Reset();
			        
		            stringStudent = "" ;
		            stringTeacher = "" ;
		            stringGraduate = "" ;
		            numTab = 0 ;
		            
		        } // while not EOF
		        success = true ;
		        fclose( infile ) ;
			} // else
			
			if (success) {
				;
			} // if 
			return success ;
		} // Load()
		
		void Print() {
			// print all data 
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				cout << "[" << collegeSet[i].inputId << "]" 
				     << collegeSet[i].nameSchool << "\t" 
					 << collegeSet[i].nameMajor << "\t" << collegeSet[i].division << "\t"  
					 << collegeSet[i].level << "\t" << collegeSet[i].numStudent << "\t" 
					 << collegeSet[i].numTeacher << "\t" << collegeSet[i].numGraduate << "\n";
			} // for
		} // Print()
		
}; // class CollegeList 

typedef struct CT23 { // the data item type for storing in a 2-3 tree node
	// College type for 2-3 tree 
	string sName ; // the key or school name
	vector<CollegeType> sExtra ; // this is the extra info, grad number and such...
} DataType23 ;

class Node23 { // the node of 2-3 tree
	int numData ;
	int numChild ;
	
	public:
		DataType23 leftData ;
		DataType23 rightData ;
		DataType23 tempData ;
		
		Node23* leftChild ;
		Node23* midChild ;
		Node23* rightChild ;
		
		Node23() {
			leftChild = NULL ;
			midChild = NULL ;
			rightChild = NULL ;
			numData = 0 ;
			numChild = 0 ;
		} // Node23() 
		
		Node23( CollegeType data ) {
			left.sName = data.nameSchool ;
			left.sExtra.push_back( data ) ;
			numData = 1 ;
			leftChild = NULL ;
			midChild = NULL ;
			rightChild = NULL ;
			numChild = 0 ;
		}
		int GetNumData() {
			return numData ;
		}
		int GetNumChild() {
			return numChild ;
		}
}; // class Node23

class TTTree {
	public:
		Node23* root ; 
		
		TTTree() { // constructor
			// constructor
			root = NULL ;
		} // TTTree()
		
		void Build( vector< CollegeType > list ) {
			for ( int i = 0 ; i < list.size() ; i++ ) {
				Insert( root, list[i] ) ;
			} // for
		} // Build()
		
		void Insert( Node23*& walk, CollegeType data ) {
			if ( walk == NULL ) {
				walk = new Node23( data ) ;
			}
			else if ( walk->GetNumData() == 1 ) {
				if ( walk->leftData.sName.compare( data.nameSchool ) == 0 ) {
					walk->leftData.sExtra.push_back( data.nameSchool ) ;
				}
				else if ( walk->leftData.sName.compare( data.nameSchool ) > 0 ) {
					
				}
				else if ( walk->leftData.sName.compare( data.nameSchool ) < 0 ) {
					
				}
			} // else if
			else if ( walk->GetNumData() == 2 ) {
				
			}
		} // Insert()
		
}; // class TTTree

int main() {
	CollegeList list ;
	string fileNum ;
	cout << "File number: " ;
	cin >> fileNum ;
	
	return 0 ;
} // main
