// 10720111 ³¯¤Ö·u 10720115 ªL¯Ñ¶h 
 
#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

class CollegeType {
	// a college with it's information
	public:
		
		int inputId ; // The input number of school 
		string nameSchool;	// name of the college
		string nameMajor ;	// major
		string division ;	// 
		string level ;
		int numStudent ;
		int numTeacher ;
		int numGraduate ;
		
		void Reset() {
			// reset the data of the college
			
			nameSchool = "";
			nameMajor = "" ;
			division = "";
			level = "";
			numStudent = 0;
			numTeacher = 0 ;
			numGraduate = 0 ;
			inputId = 0 ;
		}
	
}; // CollegeType

class CollegeList {
	// contain a list of college
	public:
		vector<CollegeType> collegeSet ;
		
		void DeleteGraduate( int num ) {
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				if ( collegeSet.at(i).numGraduate <= num ) {
					/*cout << collegeSet[i].nameSchool << "\t" << collegeSet[i].nameMajor << "\t"
						 << collegeSet[i].division << "\t" << collegeSet[i].level << "\t" 
						 << collegeSet[i].numStudent << "\t" << collegeSet[i].numTeacher << "\t"
						 << collegeSet[i].numGraduate << "\n";*/
						 
					collegeSet.erase( collegeSet.begin() + i ) ;
					i-- ;
				} // if match
			} // for
		} // Delete Graduate
		bool Load( string fileName ) {
	    	// Load a file, turn it into a vector
	    
		    FILE *infile = NULL ;
		    bool success = false ;
		    fileName = "input" + fileName + ".txt" ;
		    infile = fopen(fileName.c_str(), "r" ) ;
		
			if ( infile == NULL )
				;
			else{
		
		        char tempChar ;
		        // unwanted data remove
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
		        		
		        	} //while
		        	
		        	aCollege.numStudent = atoi( stringStudent.c_str() ) ;
		        	aCollege.numTeacher = atoi( stringTeacher.c_str() ) ;
		        	aCollege.numGraduate = atoi( stringGraduate.c_str() ) ;
		        	inputId++ ; // changed
		        	aCollege.inputId = inputId ; // Additonal AYYYY 
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
			
			// if load success, print the content you save 
			if (success)
				;
				// Print();
				
			return success ;
	
		} // Load
		
		void Print(){
			// print all data from the vector
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				cout << "[" << collegeSet[i].inputId << "]" << collegeSet[i].nameSchool << "\t" // show inputID
					 << collegeSet[i].nameMajor << "\t" << collegeSet[i].division << "\t"  
					 << collegeSet[i].level << "\t" << collegeSet[i].numStudent << "\t" 
					 << collegeSet[i].numTeacher << "\t" << collegeSet[i].numGraduate << "\n";
			} // for
		} // Print
		
}; // CollegeList 

class MinHeap {
	
	public:
		vector<CollegeType> heap ;
		
	public:
		
		bool loadVector( vector<CollegeType> data ) {
			// load heap from data.
			if (data.empty() )
				return false ;
				
			else {
				for( int i = 0 ; i < data.size() ; i++ ) {
					heap.push_back( data.at(i) ) ;
					ReheapUp() ;
				} // end for
			}
			
			return true ;
		}
		
		void swap( int y, int z ) { // swaps index y,z's elements in heap vector 
			CollegeType tempZ = heap[z] ;
			heap[z] = heap[y] ;
			heap[y] = tempZ ;
		}
		
		void heapRebuild( int root ) {
			// Transforms a semi-heap into a real one.
			int child = 2 * root + 1 ; // left child
			if( child < heap.size() ) {
				int rightChild = child + 1 ;
				if( ( rightChild < heap.size() ) && (heap[rightChild].numGraduate < heap[child].numGraduate ) )
					swap( rightChild, child ) ; 
				if( heap[root].numGraduate > heap[child].numGraduate  ) {
					swap( root, child ) ;
					heapRebuild(child) ;
				} // end if
			} // end if
		} // end heapRebuild
		
		int bottom() {
			// finds bottom-right-most
			int index = bottomLeftmost() ;
			for( ; index < heap.size() ; index++ )
				;
			return index - 1 ;
		}
		
		int bottomLeftmost() {
			// finds bottom-left-most
			int index = 0 ;
			for( ; index < heap.size() ; index = index * 2 + 1 )
				;
			return ( index - 1 ) / 2 ;
		}
		
		void ReheapUp() { // Maintenance function for HeapInsert
			for( int i = heap.size() - 1 ; i >  0 ; i = (i-1) / 2 )
				if( heap[i].numGraduate < heap[ (i - 1) / 2 ].numGraduate )
					swap( i ,(i - 1) / 2  ) ;
		}
		
		bool printNode(int index) { // prints inputnumber and grad number of index in heap
			if( index < 0 || index >= heap.size() )
				return false ;
			cout << "[" << heap[index].inputId << "]" << " " << heap[index].numGraduate << endl ;
			return true ;
		} 

};

typedef struct HN {
	int inputNum ;
	int graduates ;
	CollegeType college ;
} HeapNode ;

class MinMaxHeap {
	
	vector<HeapNode> minMaxHeap ; // heap
	int num ; // total number of nodes
	
	public:
		MinMaxHeap() {
			num = 0 ;
		} // MinMaxHeap
		
		void ListToHeap( vector<CollegeType> collegeSet ) {
			HeapNode heapNode ;
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				// turn CollegeType into HeapNode
				heapNode.inputNum = collegeSet[i].inputId ;
				heapNode.graduates = collegeSet[i].numGraduate ;
				heapNode.college = collegeSet[i] ;
				Insert( heapNode ) ;
				// Print() ;
			} // for
		} // ListToHeap
		
		void Swap( HeapNode& place, HeapNode& parent ) {
			HeapNode temp = place ;
			place = parent ;
			parent = temp ;
		} // Swap
		
		void MinGrandSwap( int place ) {
			int parent = (place - 1) / 2 ;
			parent = (parent - 1) / 2 ;
			while ( parent >= 0 && minMaxHeap[place].graduates < minMaxHeap[parent].graduates ) {
				Swap( minMaxHeap[place], minMaxHeap[parent] ) ;
				place = parent ;
				parent = (place - 1) / 2 ;
				parent = (parent - 1) / 2 ;
			} // while
		} // Min
		
		void MaxGrandSwap( int place ) {
			int parent = (place - 1) / 2 ;
			parent = (parent - 1) / 2 ;
			while ( parent > 0 && minMaxHeap[place].graduates > minMaxHeap[parent].graduates ) {
				Swap( minMaxHeap[place], minMaxHeap[parent] ) ;
				place = parent ;
				parent = (place - 1) / 2 ;
				parent = (parent - 1) / 2 ;
			} // while
		} // Max
		
		void Insert( HeapNode heapNode ) {
			minMaxHeap.push_back( heapNode ) ;
			int place = num ;
			int parent = (place - 1) / 2 ;
			if ( IsMin( num ) ) { // if at min level
				if ( parent > 0 && minMaxHeap[place].graduates > minMaxHeap[parent].graduates ) {
					// switch place and parent
					Swap( minMaxHeap[place], minMaxHeap[parent] ) ;
					// check grandparents
					place = parent ;
					// at max level, grandparent is larger
					MaxGrandSwap( place ) ;
				} // if
				else if ( parent > 0 && minMaxHeap[place].graduates <= minMaxHeap[parent].graduates ) {
					MinGrandSwap( place ) ;
				} // else if
			} // if
			else { // if at max level
				if ( parent >= 0 && minMaxHeap[place].graduates < minMaxHeap[parent].graduates ) {
					// switch place and parent
					Swap( minMaxHeap[place], minMaxHeap[parent] ) ;
					// check grandparents
					place = parent ;
					MinGrandSwap( place ) ;
				} // if
				else if ( parent >= 0 && minMaxHeap[place].graduates >= minMaxHeap[parent].graduates ){
					MaxGrandSwap( place ) ;
				} // else if
			} // else
			num++ ;
		} // Insert
		
		bool IsMin( int number ) { // find if it is at min level
			bool isMin = true ;
			while ( number > 0 ) {
				number = (number - 1) / 2 ;
				if ( isMin ) {
					isMin = false ;
				} // if
				else {
					isMin = true ;
				} // else
			} // while
			/*
			if ( isMin )
				cout << "is min" << endl ;
			else
				cout << "is max" << endl ;
			*/
			return isMin ;
		} // IsMin
		
		void Result() {
			// print root
			cout << "root: "
			     << "[" << minMaxHeap[0].inputNum << "] "
				 << minMaxHeap[0].graduates << endl ;
			// print bottom
			cout << "bottom: "
			     << "[" << minMaxHeap[num-1].inputNum << "] "
				 << minMaxHeap[num-1].graduates << endl ;
			// print leftmost
			cout << "leftmost bottom: "
			     << "[" << minMaxHeap[LeftmostBottomLocation()].inputNum << "] "
				 << minMaxHeap[LeftmostBottomLocation()].graduates << endl ;
		} // Result
		
		int LeftmostBottomLocation() {
				int number = num ;
				int twoMultiple = 0 ;
				while ( number / 2 > 0 ) {
					twoMultiple++ ;
					number = number / 2 ;
				} // while
				int leftmostLocation = 1 ;
				while ( twoMultiple > 0 ) {
					leftmostLocation = leftmostLocation * 2 ;
					twoMultiple-- ;
				} // while
				return leftmostLocation - 1 ;
		} // Leftmost 
		
		void Reset() {
			vector<HeapNode>().swap( minMaxHeap ) ;
			num = 0 ;
		} // Reset
		
		void Print() {
			for ( int i = 0 ; i < minMaxHeap.size() ; i++ ) {
				cout  << " " << minMaxHeap[i].graduates << endl ;
			} 
			cout << endl ;
		} // Print()
		
		void DeleteMin() { // compare child and grand child every node
			// replace root with the last one
			minMaxHeap[0] = minMaxHeap[num - 1] ;
			minMaxHeap.erase( minMaxHeap.begin() + num - 1 ) ;
			num = num - 1 ; 
			// find smaller child
			int smaller = 0 ;
			if ( num >= 3 ) {
				if ( minMaxHeap[1].graduates > minMaxHeap[2].graduates ) {
					smaller = 2 ;
				}
				else {
					smaller = 1 ;
				}
			}
			else if ( num >= 2 ) {
				smaller = 1 ;
			}
			// swap root and child if needed
			if ( minMaxHeap[smaller].graduates < minMaxHeap[0].graduates ) {
				Swap( minMaxHeap[smaller], minMaxHeap[0] ) ;
			}
			// check grandchild with "root"
			int place = 0 ;
			int child = place * 2 + 1 ;
			child = child * 2 + 1 ;
			child = FindSmallestSameLevel( child ) ;
			while ( child < num && minMaxHeap[ child ].graduates < minMaxHeap[place].graduates ) {
				Swap( minMaxHeap[ child ], minMaxHeap[place] ) ;
				place = child ;
				child = child * 2 + 1 ;
				// find smaller child
				smaller = place ;
				if ( num > child + 1 ) {
					if ( minMaxHeap[child].graduates > minMaxHeap[child+1].graduates ) {
						smaller = child+1 ;
					}
					else {
						smaller = child ;
					}
				}
				else if ( num > child ) {
					smaller = child ;
				}
				// swap root and child if needed
				if ( minMaxHeap[smaller].graduates < minMaxHeap[place].graduates ) {
					Swap( minMaxHeap[smaller], minMaxHeap[place] ) ;
				}
				child = child * 2 + 1 ;
				child = FindSmallestSameLevel( child ) ;
			}
		} // DeleteMin
		
		int FindSmallestSameLevel( int place ) {
			int smaller1 = place ;
			int smaller2 = place ;
			if ( place >= num ) {
				return place ;
			}
			else if ( place + 3 < num ) {
				if ( minMaxHeap[place].graduates > minMaxHeap[place+1].graduates ) {
					smaller1 = place + 1 ;
				}
				smaller2 = place + 2 ;
				if ( minMaxHeap[place+2].graduates > minMaxHeap[place+3].graduates ) {
					smaller2 = place + 3 ;
				}
			}
			else if ( place + 2 < num ) {
				if ( minMaxHeap[place].graduates > minMaxHeap[place+1].graduates ) {
					smaller1 = place + 1 ;
				}
				smaller2 = place + 2 ;
			}
			else if ( place + 1 < num ) {
				smaller2 = place + 1 ;
			}
			if ( minMaxHeap[smaller1].graduates < minMaxHeap[smaller2].graduates ) {
				return smaller1 ;
			}
			else {
				return smaller2 ;
			}	
		} // FindSmallest
		
		int MMDelete( int n ) {
			int count = 1 ;
			while ( num > 0 && n != 0 ) {
				cout << "Top " << count << ": " 
					 << "[" << minMaxHeap[0].inputNum << "] " 
					 << minMaxHeap[0].college.nameSchool << ", " 
					 << minMaxHeap[0].college.division << ", " 
					 << minMaxHeap[0].college.level << ", " 
					 << minMaxHeap[0].graduates << endl ;
				DeleteMin() ;
				n-- ;
				count++ ;
			}
		}
		
		int findLevel( int index ) {
        	// find places current level
	        int levels = 0 ;
	        for( ; index >= 0 ; index = ( index -1 ) / 2  ) {
	            levels++ ;
	        }
	        cout << "WUT" ;
        	return levels ;
    	}
    	
    	void inOrder( int place ) {
    		if ( place >= num ) {
    			;
			}
			else {
				inOrder( place * 2 + 1 ) ;
				cout << minMaxHeap[place].graduates << ", " ;
				inOrder( place * 2 + 2 ) ; 
			}
		}
    	
}; // class MinMaxHeap 

int main() {
	MinMaxHeap minMaxHeap ;
	cout << "*****ENTER 1 TO BUILD MIN-HEAP*******" << endl ;
	cout << "*****ENTER 2 TO BUILD MIN-MAX-HEAP***" << endl ;
	cout << "*****ENTER 3 TO REMOVE FROM MINMAXHEAP***" << endl ;
	cout << "*****ENTER 0 TO EXIT  ***************" << endl ;
	int mode = 0 ;
	cin >> mode ;
	while( mode != 0 ) {
		string fileNum ;
		if( mode == 1) { // Selected mid-heap
			cout << "ENTER INPUT FILE NUMBER:(ex.101) " << endl ;
			cin >> fileNum ;
			CollegeList data ;
			if ( !data.Load(fileNum) ) 
				cout << "THERE'S BEEN AN ERROR WITH THE FILE" << endl ;
			else {
				MinHeap minHeap ;
				minHeap.loadVector(data.collegeSet) ;
				cout << "root: " ;
				minHeap.printNode(0) ;
				cout << "bottom: " ;
				minHeap.printNode(minHeap.bottom() ) ;
				cout << "leftmost bottom: " ;
				minHeap.printNode(minHeap.bottomLeftmost() ) ;
				cout << endl ;
			} 
		} // if mode 1
		
		else if( mode == 2 ) { // selected min-max-heap
			cout << "ENTER INPUT FILE NUMBER:(ex.101) " << endl ;
			cin >> fileNum ;
			CollegeList colleges ;
			if ( !colleges.Load(fileNum) ) {
				cout << "THERE'S BEEN AN ERROR WITH THE FILE" << endl ;
			} // if
			else {
				minMaxHeap.Reset() ; 
				minMaxHeap.ListToHeap( colleges.collegeSet );
				minMaxHeap.Result() ;
				// minMaxHeap.Print() ;
				// minMaxHeap.inOrder(0) ;
			} // else 
		} // else if mode 2
		else if ( mode == 3 ) {
			int toDelete = 0 ;
			cout << "How many to delete: " ;
			cin >> toDelete ;
			minMaxHeap.MMDelete( toDelete ) ;
		}
		else
			cout << "INVAILD COMMAND..." << endl ;
			
		cout << "\n*****ENTER 1 TO BUILD MIN-HEAP*******" << endl ;
		cout << "*****ENTER 2 TO BUILD MIN-MAX-HEAP***" << endl ;
		cout << "*****ENTER 3 TO REMOVE FROM MIN-MAX-HEAP***" << endl ;
		cout << "*****ENTER 0 TO EXIT  ***************" << endl ;
		cin >> mode ;
	} // while mode != 0
	cout << "exiting..." << endl ;
	return 0 ;
} // end main
