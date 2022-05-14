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

typedef struct AVLTN {
	vector< CollegeType > list ; // a list of data with the same gradautes 
	AVLTN* left ;
	AVLTN* right ;
} AVLTreeNode ;

class AVLTree {
	
	AVLTreeNode* root ;
	public:
		AVLTree() {
			// construst
			root = NULL ;	
		}
		
		~AVLTree() {
			// destruct
			Initialize() ;
		} // 
	
		void Build( vector<CollegeType> list ) {
			// build AVL tree from a vector of department
			for ( int i = 0 ; i < list.size() ; i++ ){
				root = Insert( root, list.at(i) ) ;
			} // for
		} // Build
		
		AVLTreeNode* Insert( AVLTreeNode* walk, CollegeType department ) { 
			if ( walk == NULL ) {
				walk = new AVLTreeNode ;
				walk->list.push_back( department ) ;
				walk->left = NULL ;
				walk->right = NULL ;
				return walk ;
			} // if
			else if ( department.numGraduate == walk->list[0].numGraduate ) {
				walk->list.push_back( department ) ;
				return walk ;
			} // else if
			else if ( department.numGraduate < walk->list[0].numGraduate ) {
				walk->left = Insert( walk->left, department ) ;
				return Rotate( walk ) ;
			}
			else if ( department.numGraduate > walk->list[0].numGraduate ) {
				walk->right = Insert( walk->right, department ) ;
				return Rotate( walk ) ;
			} // else if
		} // Insert
		
		AVLTreeNode* Rotate( AVLTreeNode* node ) {
			if ( node == NULL ) {
				;
			} // if 
			else if ( -1 <= BF( node ) && BF( node ) <= 1 ) {
				// if balanced, no need to rotate
				;
			} // else if 
			else if ( BF( node ) == 2 ) {
				// lean to the left
				if ( BF( node->left ) == -1 ) { 
					// if left child lean to the right, rotates it, makes it lean to the left
					node->left = SingleRR( node->left ) ;
				} // end if
				node = SingleLL( node ) ;	
			} // else if BF == 2
			else if ( BF( node ) == -2 ) {
				// lean to the right
				if ( BF( node->right ) == 1 ) { 
					node->right = SingleLL( node->right ) ;	
				} 
				node = SingleRR( node ) ;
			} // else if BF == -2
			
			return node ;
			
			/*
			else if ( BF( node ) > 2 ) {
				// need rotate, find the node which need to
				Rotate( node->left ) ; 
			} // else if
			else if ( BF( node ) < -2 ) {
				// need rotate, find the node which need to
				Rotate( node->right ) ;
			} // else if
			*/
		} // Rotate()
		
		AVLTreeNode* SingleLL( AVLTreeNode* node ) {
			// rotate with left child
			AVLTreeNode* temp = node->left ;
			node->left = temp->right ;
			temp->right = node ;
			return temp ;
		} // LL
		
		AVLTreeNode* SingleRR( AVLTreeNode* node ) {
			AVLTreeNode* temp = node->right ;
			node->right = temp->left ;
			temp->left = node ;
			return temp ;
		} // RR
		
		int BF( AVLTreeNode* node ) {
			// balance factor
			return Height( node->left ) - Height( node->right ) ;
		} // BF
		
		int Height( AVLTreeNode* walk ) {
			// tree height
			if ( walk == NULL ) {
				return 0;
			} 
			else {
				int leftDepth = Height( walk->left ) ;
				int rightDepth = Height( walk->right ) ;
				
				if ( leftDepth > rightDepth )
					return leftDepth + 1 ;
				else
					return rightDepth + 1 ;
			} // else
		} // Height
		
		int NodeTotal( AVLTreeNode* walk ) {
			if ( walk == NULL ) {
				return 0 ;
			}
			else {
				return 	1 + NodeTotal( walk->left ) + NodeTotal( walk->right ) ; 
			} // else
		} // NodeTotal
		
		AVLTreeNode*& GetRoot() {
			return root ;
		}
		
		void PrintNode( AVLTreeNode* walk ) {
			for ( int i = 0 ; i < walk->list.size() ; i++ ) {
				cout << i + 1 << ": [" << walk->list[i].inputId << "] "
				     << walk->list[i].nameSchool << ", "
				     << walk->list[i].nameMajor << ", "
				     << walk->list[i].division << ", "
				     << walk->list[i].level << ", "
				     << walk->list[i].numGraduate << endl ;
			} // for
		} // PrintNode
		
		void Initialize() {
			DeleteTree( root ) ;
		} // Initialize
		
		void DeleteTree( AVLTreeNode*& walk ) {
			if ( walk == NULL ) {
				;
			}
			else {
				DeleteTree( walk->left ) ;
				DeleteTree( walk->right ) ;
				delete walk ;
				walk = NULL ;
			}
		}
		
		void InOrderTravel( AVLTreeNode* walk ) {
			if ( walk == NULL ) {
				;
			}
			else {
				InOrderTravel( walk->left ) ;
				cout << walk->list[0].numGraduate << endl ;
				InOrderTravel( walk->right ) ;
			} // else
		} // InOrderTravel
		
}; // class AVLTree

int main() {
	cout << "(1) 2-3 tree" << endl 
	     << "(2) AVL tree" << endl
	     << "(0) Exit" << endl
	     << "Mission: " ;
	int cmd = 0 ;
	cin >> cmd ;
	CollegeList list ;
	AVLTree avlTree ;
	while ( cmd != 0 ) {
		if ( cmd != 1 && cmd != 2 ) {
			cout << "Unknown command." << endl ;
		} // if
		else {
			string fileNum ;
			cout << "File number: " ;
			cin >> fileNum ;
			if ( cmd == 1 ) { // 2-3 tree
				
			} // if cmd 1
			else if ( cmd == 2 ) { // AVL tree
				// Initialize list & AVL tree
				vector< CollegeType >().swap( list.collegeSet ) ;
				avlTree.Initialize() ;
				// load & build
				list.Load( fileNum ) ;
				avlTree.Build( list.collegeSet ) ;
				// output
				cout << "Height: " << avlTree.Height( avlTree.GetRoot() ) << endl 
				     << "Number of node: " << avlTree.NodeTotal( avlTree.GetRoot() ) << endl ;
				avlTree.PrintNode( avlTree.GetRoot() ) ;
			} // else if cmd 2
		} // else
		
		cout << "\n(1) 2-3 tree" << endl 
	         << "(2) AVL tree" << endl
	         << "(0) Exit" << endl
	         << "Mission: " ;
		cin >> cmd ;
	} // while cmd != 0
	return 0 ;
} // main
