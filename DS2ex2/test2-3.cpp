// 10720111 ³¯¤Ö·u 10720115 ªL¯Ñ¶h

#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>


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


	    void print() {
	    	cout << "[" << inputId << "]"
				     << nameSchool << "\t"
					 << nameMajor << "\t" << division << "\t"
					 << level << "\t" << numStudent << "\t"
					 << numTeacher << "\t" << numGraduate << "\n";
		}


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

		void reset() {
			collegeSet.clear() ;
		}

}; // class CollegeList

typedef struct CT23 { // the data item type for storing in a 2-3 tree node
	// College type for 2-3 tree
	vector<CollegeType> sExtra ; // this is the extra info, grad number and such...
	string sName ; // the key or school name

} CollegeType23 ;

class Node23 {	// the node type for 2-3 tree.
	public:
		Node23 * parent ; // points to the parent
		CT23 data [3] ; // the storage area for collegeType info.
		Node23 * child [4] ; // the pointer array for children nodes,
		// where [0] is left, [1] is mid, [2] is right.

		Node23() {
			clear() ;
		}

		void clear() { // clears node of info
			parent = NULL ;
			data[0].sExtra.clear() ;
			data[0].sName.clear() ;
			data[1].sExtra.clear() ;
			data[1].sName.clear() ;
			data[2].sExtra.clear() ;
			data[2].sName.clear() ;
			child[0] = NULL ;
			child[1] = NULL ;
			child[2] = NULL ;
			child[3] = NULL ;
		}

		bool add( CollegeType in ) {  // adds in into a node23 item, returns false when full
			// handles empty and non-empty situations.
			if(  data[0].sName.empty() && data[1].sName.empty() ) { // 1.brand new creation
				data[0].sExtra.push_back(in) ;
				data[0].sName = in.nameSchool ; // store items into data
				child[0] = NULL ; // initalize pointers
				child[1] = NULL ;
				child[2] = NULL ;
				child[3] = NULL ;
			}
			else if( ( !data[0].sName.empty() && data[1].sName.empty() ) ) {	// 2.Already has one item
				if( strcmp( in.nameSchool.c_str(), data[0].sName.c_str() ) == 0 ) {
					data[0].sExtra.push_back(in) ; // adds in directly to list
				}
				else {
					// add and sort
					data[1].sExtra.push_back(in) ;
					data[1].sName = in.nameSchool ;
					sort() ;
				}
			} // else if
			else {	// 3. It is FULL!
				if( strcmp( in.nameSchool.c_str(), data[0].sName.c_str() ) == 0 )
					data[0].sExtra.push_back(in) ; // same name as name1
				else if( strcmp( in.nameSchool.c_str(), data[1].sName.c_str() ) == 0 )
					data[1].sExtra.push_back(in) ; // same name as name2
				else {
					data[2].sExtra.push_back(in) ;
					data[2].sName = in.nameSchool ;
					sort() ; // HERE

					return false ; // notify outisde via false...
				}
			}

			return true ;
		} // bool add( CollegeType )

		bool add( vector<CollegeType> in ) { // adds info through sExtra of someOther node
			int index = dataSize() ;
			data[index].sName = in[0].nameSchool ;
			for( int i = 0 ; i < in.size() ; i++ ) {
				data[index].sExtra.push_back( in[i] ) ;
			}

			sort() ;
		}

		void sort() { // sort the keys in data from smallest to greatest
			int size = dataSize() ;
			for( int i = 0 ; i < size ; i++ ) {
				for( int j = i + 1 ; j < size ; j++ )
					if( strcmp( data[i].sName.c_str(),data[j].sName.c_str() ) > 0 )
						swap(i,j) ;
			}
		} // end void

		int dataSize() { // return size of data array
			int size = 0 ;;
			for( int i = 0; i < 3 ; i++ ) {
				if( !data[i].sName.empty() )
					size++ ;
			}
			return size ;
		}

		bool clear( int i ) { // clears index i in data array
			if( i < 0 || i > 2 )
				return false ;
			data[i].sExtra.clear() ;
			data[i].sName.clear() ;
			return true ;
		}

		bool swap( int num1, int num2 ) { // swap index num1 num2 in data[]
			if(  num1 > 3 || num1 < 0  ||  num2 > 3 || num2 < 0  )
				return false ;

			CT23 temp1 ;
			temp1.sExtra = data[num1].sExtra ;
			temp1.sName = data[num1].sName ;
			data[num1].sExtra = data[num2].sExtra ;
			data[num1].sName = data[num2].sName ;
			data[num2].sExtra = temp1.sExtra ;
			data[num2].sName = temp1.sName ;

			return true ;
		}

		bool isLeaf() { // true if it is, vise versa
			if( child[0] == NULL && child[1] == NULL && child[2] == NULL )
				return true ;
			return false ;
		}

		bool twoNode() {
			if( ( !data[0].sName.empty() && data[1].sName.empty() ) )
				return true ;
			return false ;
		}

		bool threeNode() {
			if( ( !data[0].sName.empty() && !data[1].sName.empty() && data[2].sName.empty() ) )
				return true ;
			return false ;
		}

		bool overLoaded() { // checks if a node has more than 2 data items AKA overloaded
			if( dataSize() > 2 )
				return true ;
			return false ;
		}

		bool hasChild() {
			for( int i = 0 ; i < dataSize() ; i++ )
				if( child[i] != NULL )
					return true ;
			return false ;
		}

		string name1() {
			return data[0].sName ;
		}

		string name2() {
			return data[1].sName ;
		}

		string name3() {
			return data[2].sName ;
		}

		bool swapChild( int num1, int num2 ) {
			if( num1 < 0 || num1 > 3 || num2 < 0 || num2 > 3 )
				return false ;
			Node23 * temp1 = child[num1] ;
			child[num1] = child[num2] ;
			child[num2] = temp1 ;
			return true ;
		}

		int childSize() {
			int size = 0 ;
			for( int i = 0 ; i < 4 ; i++)
				if( child[i] != NULL )
					size++ ;
			return size ;
		}

		void sortChild() { // sorts child nodes from smallest to greatest
			for( int i = 0 ; i < childSize() ; i++ )
				for( int j = i + 1 ; j < childSize() ; j++ )
					if( strcmp( child[i]->name().c_str() , child[j]->name().c_str() ) > 0 )
						swapChild( i, j ) ;
		}

		string name() { // return greatest name of data[]
			return data[dataSize()-1].sName ;
		}

		void print() {
		    int num = 0 ;
		    vector<int> printedIndex ;
		    while ( printedIndex.size() < dataSize() ) {
                int minInputnum = -1 ;
                for ( int j = 0 ; j < dataSize() ; j++ ) {
                    bool repeat = false ;
                    for ( int i = 0 ; i < printedIndex.size() && !repeat ; i++ ) {
                        if ( j == printedIndex[i] ) {
                            repeat = true ;
                        } // if
                    }
                    if ( !repeat ) {
                        if ( minInputnum == -1 ) {
                            minInputnum = j ;
                        }
                        else if ( data[j].sExtra[0].inputId < data[minInputnum].sExtra[0].inputId ) {
                            minInputnum = j ;
                        }
                    } // if
                } // for
                for( int j = 0 ; j < data[minInputnum].sExtra.size() ; j++ ) {
                        num++ ;
                        cout << num << ". " ;
                        data[minInputnum].sExtra[j].print() ;
                } // for
                printedIndex.push_back( minInputnum ) ;
		    } // while
		} // print()
};

class TTTree {
	// 2-3 tree
	public:
		Node23 * root ; // points to the root of the 2-3 tree

		TTTree() { // constructor
			// constructor
			root = NULL ;
		}

		void insert( Node23 * & rot ,CollegeType in ) { // inserts in into the 2-3 tree through rot traversal

			if( rot == NULL ) { // first insertion
				rot = new Node23 ;
				rot->add(in) ;

			} // end if
			else if( rot->isLeaf() ) { // rot is a leaf.
				if( rot->add(in) )
					;
				else { // the node is full.
					split(rot) ;
				}
			} // end else if
			else if( rot->twoNode() ) { // is a 2-node
				if( strcmp( in.nameSchool.c_str() , rot->name1().c_str() ) == 0 ) {
					rot->add(in) ;
				}
				else if( strcmp( in.nameSchool.c_str() , rot->name1().c_str() ) > 0 ) {
					insert( rot->child[2], in) ;
				}
				else {
					insert( rot->child[0], in ) ;
				}
			} // end else if
			else { // is a 3-node
				if( strcmp( in.nameSchool.c_str() , rot->name1().c_str() ) <= 0 ) {
					if( strcmp( in.nameSchool.c_str() , rot->name1().c_str() ) == 0 )
						rot->add(in) ;
					else {
						insert( rot->child[0], in ) ; // walks left
					}
				}
				else if( strcmp( in.nameSchool.c_str() , rot->name2().c_str() ) >= 0 ) {
					if( strcmp( in.nameSchool.c_str() , rot->name2().c_str() ) == 0 )
						rot->add(in) ;
					else {
						insert( rot->child[2], in ) ; // walks right
					}
				}
				else {
					insert( rot->child[1], in ) ; // walks mid
				}

			} // end else

		} // end insert

		void split( Node23*& rot ) {
			if( rot->parent == NULL ) {
				Node23* mid = new Node23 ;
				mid->add( rot->data[1].sExtra ) ; // here maybe ERROR
				rot->clear(1) ;

				Node23 * big = new Node23 ;
				big->add( rot->data[2].sExtra ) ;
				rot->clear(2) ;

				Node23 * small = rot ;

				root = mid ;
				root->child[0] = small ;
				small->parent = root ;
				root->child[2] = big ;
				big->parent = root ;

				if( small->hasChild() ) {
					// deal with child nodes.*****
					small->child[2]->parent = big ;
					small->child[3]->parent = big ;
					big->child[0] = small->child[2] ;
					big->child[2] = small->child[3] ;
					small->child[2] = NULL ;
					small->child[3] = NULL ;

					small->child[2] = small->child[1] ; // move small child 1 to 2
					small->child[1] = NULL ;
				}

				// root = rot ; // HOLY FUCK W
			}
			else if( !rot->hasChild() ) { // is leaf
				rot->parent->add( rot->data[1].sExtra ) ;
				rot->clear(1) ;

				Node23* big = new Node23 ;
				big->add(rot->data[2].sExtra ) ;
				rot->clear(2) ;
				big->parent = rot->parent ;

				insertChild( big->parent, big) ; // connect to parent correctly
				big->parent->sortChild() ;

				if(rot->parent->overLoaded() )
					split( rot->parent ) ;
			}

			else { // internal AKA Not root and has child

				Node23 * big = new Node23 ;
				big->add( rot->data[2].sExtra ) ; // big gets data[2]'s data
				rot->clear(2) ; // clear original big

				rot->parent->add(rot->data[1].sExtra) ; // give mid data to parent
				rot->clear(1) ; // clear original mid

				big->parent = rot->parent ; // points big's parent to rot's parent

				insertChild( big->parent, big) ;
				big->parent->sortChild() ;

				Node23 * small = rot ;
				// deal with child nodes.*****************************************
				small->child[2]->parent = big ;
				small->child[3]->parent = big ;
				big->child[0] = small->child[2] ;
				big->child[2] = small->child[3] ;
				small->child[2] = NULL ;
				small->child[3] = NULL ;

				small->child[2] = small->child[1] ; // move small child 1 to 2
				small->child[1] = NULL ;
				// deal with child nodes.*****************************************
				if( rot->parent->overLoaded() )
					split( rot->parent ) ; // recurse
			}

		} // end void

		bool insertChild( Node23*& parent, Node23*& big ) {
			for( int i = 0 ; i < 4 ; i++ ) { // may have error here
				if( parent->child[i] == NULL ) {
					parent->child[i] = big ;
					return true ;
				}
			}
			return false ;
		}

		void build( vector<CollegeType> data ) {
			for( int i = 0 ; i < data.size() ; i++ ) {
				insert(root,data[i]) ;
				// NameInOrder( root ) ;
				// cout << endl ;
			} // for
		}

		void reset() {
			root = NULL ;
		}

		int height( Node23 * rot ) { // returns tree height
			if( rot == NULL )
				return 0 ;
			else if( rot->twoNode() ) {
				int leftSub = height(rot->child[0] ) ;
				int rightSub = height( rot->child[2] ) ;

				if( leftSub > rightSub )
					return leftSub + 1 ;
				else
					return rightSub + 1 ;
			}

			else {
				int leftSub = height(rot->child[0] ) ;
				int midSub = height(rot->child[1] ) ;
				int rightSub = height(rot->child[2] ) ;
				return findMax( leftSub, leftSub, leftSub ) + 1 ;

			}
		}

		int findMax( int num1, int num2, int num3 ) {
			int max = 0 ;
			int arr[] = {num1,num2,num3} ;
			for( int i = 0; i < 3 ; i++ ) {
				if( arr[i] > max )
					max = arr[i] ;
			}

			return max ;
		}

		int numOfNodes( Node23 * rot, int & count ) { // returns numberOfNodes
			if ( rot == NULL )
				return 0 ;
			else if( rot->twoNode() ) {
				numOfNodes( rot->child[0], count ) ;
				count++ ;
				numOfNodes( rot->child[2], count ) ;
			}

			else {
				numOfNodes( rot->child[0], count ) ;
				count++ ;
				numOfNodes( rot->child[1], count ) ;
				numOfNodes( rot->child[2], count ) ;
			}

		}

		void rootData() { // outputs all root data
			root->print() ;
		}

		void inOrder( Node23 * rot ) {
			if ( rot == NULL )
				;
			else if( rot->twoNode() ) {
				inOrder( rot->child[0] ) ;
				// rot->print() ;
				cout << "2NODE : "  ;
				rot->data[0].sExtra[0].print() ;
				inOrder( rot->child[2] ) ;
			}
			else {
				inOrder( rot->child[0] ) ;
				// cout << "3NODE 1.: "  ;
				rot->data[0].sExtra[0].print() ;
				inOrder( rot->child[1] ) ;
				// 201cout << "3NODE 2.: "  ;
				// rot->data[1].sExtra[0].print() ;
				inOrder( rot->child[2] ) ;
			} // else
		} // inOrder()

		void NameInOrder( Node23* walk ) {
			if ( walk == NULL ) {
				;
			} // if
			else {
				NameInOrder( walk->child[0] ) ;
				cout << walk->data[0].sName << endl ;
				if ( walk->threeNode() ) {
					NameInOrder( walk->child[1] ) ;
					cout << walk->data[1].sName << endl ;
				} // if
				NameInOrder( walk->child[2] ) ;
			} // else if
		} // NameInOrder()

};

int main() {

	CollegeList list ;
	TTTree tttree ;
	string fileNum ;
	cout << "File number: " ;
	cin >> fileNum ;
	int count = 0 ;
	while ( fileNum.compare( "0" ) != 0 ) {
		tttree.reset() ;
		list.reset() ;
		list.Load(fileNum) ;
		tttree.build( list.collegeSet ) ;
		// height
		cout << "Tree height is: "<< tttree.height(tttree.root) << endl ;
		// number of nodes
		tttree.numOfNodes(tttree.root, count ) ;
		cout << "Number of nodes: " << count << endl ;
		// data of root
		tttree.rootData() ;

        // cout <<"IN ORDER" << endl ;
		// tttree.inOrder( tttree.root ) ;
        // tttree.NameInOrder( tttree.root ) ;
		cout << "\nFile number: " ;
		cin >> fileNum ;
		count = 0 ;

	} // end while

	return 0 ;
} // main
