// 10720111 ³¯¤Ö·u
 
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
			
		}
	
}; // CollegeType

class CollegeList {
	// contain a list of college
	
	vector<CollegeType> collegeSet ;
	
	public:
		
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
				Print();
				
			return success ;
	
		} // Load
		
		void Print(){
			// print all data from the vector
			for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
				cout << collegeSet[i].nameSchool << "\t" << collegeSet[i].nameMajor << "\t"
					 << collegeSet[i].division << "\t" << collegeSet[i].level << "\t" 
					 << collegeSet[i].numStudent << "\t" << collegeSet[i].numTeacher << "\t"
					 << collegeSet[i].numGraduate << "\n";
			} // for
		} // Print
		
		vector<CollegeType> GetSet(){
			return collegeSet;
		} // GetSet 
		
		void ResetList(){
			// clear the list
			vector<CollegeType>().swap( collegeSet ) ;
		}
		
}; // class CollegeList

typedef struct TreeNode {
	CollegeType college; 
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

class CollegeTree {
	// a binary search tree for college
	
	TreeNode* root ;
	
	public:
		
		CollegeTree() {
			root = NULL;
		}
		~CollegeTree() {
			ResetTree() ;
		}
		
		void DeleteByGraduate( int num ) {
			
			FindDeleteByGraduate( root, num );
			GetHeight();
		}
		void FindDeleteByGraduate( TreeNode*& walk, int num ) {
			// delete college that has graduates smaller or equal to num
			if ( walk == NULL ) {
				// NULL do nothing
				;
			} 
			else if ( walk->college.numGraduate <= num ) {
				// smaller or equal, delete all left child and itself
				// right side might have equal one
				FindDeleteByGraduate( walk->right, num ) ;    // search right part to delete equal one
				FindDeleteByGraduate( walk->left, num ) ;    // delete smaller left part
				cout << walk->college.nameSchool << "\t" << walk->college.nameMajor << "\t"
					 << walk->college.division << "\t" << walk->college.level << "\t" 
					 << walk->college.numStudent << "\t" << walk->college.numTeacher << "\t"
					 << walk->college.numGraduate << "\n";
					 
				TreeNode* temp = walk ;   
				walk = walk->right ;    // replace right part to root
				delete temp ;
			} 
			else {
				// root larger, search left for smaller one
				FindDeleteByGraduate( walk->left, num ) ; 
			}
		} // Find and delete node
		bool IsEmpty(){
			if ( root == NULL )
				return true ;
				
			return false ;
		} // if it is empty
		void ResetTree(){
			// delete all node, root point to NULL
			DeleteAllNode( root ) ;
			root = NULL ;
		}
		void DeleteAllNode( TreeNode*& walk ) {
			// pass through all node from walk & delete them
				if ( walk == NULL )
					;
				else {
					DeleteAllNode( walk->left ) ;
					DeleteAllNode( walk->right ) ;
					delete walk ;
					walk == NULL ;
				}
				
		} // DeleteAllNode
		
		void Build( vector<CollegeType> collegeSet ) {
			// build a binary tree from vector of college
			for (int i = 0; i < collegeSet.size() ; i++ ){
				InsertNode( root, collegeSet.at(i) );
			} // for
			
			GetHeight();
				
		} // Build
		
		void InsertNode( TreeNode*& walk, CollegeType college ){
			// insert node to the binary tree
			if ( walk == NULL) {
				walk = new TreeNode;
				walk->college = college;
				walk->left = NULL;
				walk->right = NULL;
			}
			else if ( college.numGraduate < walk->college.numGraduate )
				InsertNode(walk->left, college);
			else if ( college.numGraduate >= walk->college.numGraduate )
				InsertNode(walk->right, college);
		} // InsertNode
		
		void GetHeight(){
			cout << "Tree Height is "<< FindHeight( root ) << ".\n";
		} // GetHeight
		
		int FindHeight(TreeNode* walk) {
			// find the height of the tree
			if ( walk == NULL ) {
				return 0;
			}
			else {
				int leftDepth = FindHeight( walk->left ) ;
				int rightDepth = FindHeight( walk->right ) ;
				
				if ( leftDepth > rightDepth )
					return leftDepth + 1 ;
				else
					return rightDepth + 1 ;
			} // else
			 
		} // FindHeight
};

int main(){
	
	int cmd = 0;
	cout << "(1)Create a binary tree\n(2)Delete node and data\n(0)Exit\nSelect a task: " ;
	cin >> cmd ;
	CollegeList collegeList ;
	CollegeTree tree ;
	while (cmd != 0) {
		
		if (cmd == 1) {
			// reset vector and tree to reuse
			collegeList.ResetList() ;
			tree.ResetTree() ;
			// create a vector & tree from a file
			string fileName;
			cout << "File name:";
			cin >> fileName;
			if ( collegeList.Load(fileName) )
				tree.Build( collegeList.GetSet() );
			else {
				cout << "Load file failed.\n" ;
			}
				
		} // cmd 1
		else if ( cmd == 2 ) {
			// delete data from both tree and vector
			if ( tree.IsEmpty() ) {
				cout << "You should build a tree first.\n" ;
			}
			else {
			
				int graduateToDelete = -1 ;
				cout << "Delete all college that has graduates smaller or equal to this non negative interger: " ;
				cin >> graduateToDelete ;
				tree.DeleteByGraduate( graduateToDelete ) ;
				collegeList.DeleteGraduate( graduateToDelete ) ;
			}
			
		} // cmd == 2
		
		cout << "\n(1)Create a binary tree\n(2)Delete node and data\n(0)Exit\nSelect a task: " ;
		cin >> cmd ;
		
	} // while cmd != 0
	
	cout << "\nProgram end." ;
	
	return 0;
}
