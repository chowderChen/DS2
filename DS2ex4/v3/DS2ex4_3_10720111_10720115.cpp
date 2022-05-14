// 10720115 ªL¯Ñ¶h 10720111 ³¯¤Ö·u
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
using namespace std;

class DirectedGraph {

    class StudentPair {
        public:
        char id1[10] ; // sender
        char id2[10] ; // receiver
        float weight ;
    };

    class AdjListNode {
    public:
        string id2 ; // receiver
        float weight ;
        AdjListNode* next ;

        AdjListNode() {
            next = NULL ;
        }

        AdjListNode( StudentPair pairInf ) {
            id2 = pairInf.id2 ;
            weight = pairInf.weight ;
            next = NULL ;
        }

        void init( AdjListNode*& node ) {
            if ( node != NULL ) {
                init( node->next ) ;
                delete node ;
                node = NULL ;
            }
        }

    }; // class AdjListNode

    class AdjList { // An element of the main Sender vector
        public:
        string id1 ; // sender
        AdjListNode* head ; // head of reciever list
        int inf ; // influence value

        AdjList() {
            head = NULL ;
            inf = -1 ;
        }

        AdjList( StudentPair pairInf ) {
            id1 = pairInf.id1 ;
            head = new AdjListNode( pairInf ) ;
        }

        AdjListNode* Insert( StudentPair pairInf, AdjListNode* node ) { // insert in ascending order
			// small->big
            if ( node == NULL ) { // first insertion
                //cout << "in NULL" << endl ;
                node = new AdjListNode( pairInf ) ;
                return node ;
            }
            else if ( node->id2.compare( pairInf.id2 ) < 0 ) { // in > current
                //cout << "smaller" << endl ;
                node->next = Insert( pairInf, node->next ) ;
                return node ;
            }
            else if ( node->id2.compare( pairInf.id2 ) > 0 ) { // in < current
                //cout << "larger, so put in" << endl ;
                AdjListNode* temp = new AdjListNode( pairInf ) ;
                temp->next = node ;
                return temp ;
            }
        } // AdjListNode Insert

        /*AdjListNode* Insert( string name, AdjListNode* node ) { // insert in ascending order
			// small->big
            if ( node == NULL ) { // first insertion
                //cout << "in NULL" << endl ;
                node = new AdjListNode() ;
                node->id2 = name ;
                return node ;
            }
            else if ( node->id2.compare( name ) < 0 ) { // in > current
                //cout << "smaller" << endl ;
                node->next = Insert( name, node->next ) ;
                return node ;
            }
            else if ( node->id2.compare( name ) > 0 ) { // in < current
                //cout << "larger, so put in" << endl ;
                AdjListNode* temp = new AdjListNode() ;
                temp->id2 = name ;
                temp->next = node ;
                return temp ;
            }
        } // AdjListNode Insert*/

        void Insert( string name, AdjListNode*& node ) { // insert in ascending order
			// small->big
            if ( node == NULL ) { // first insertion
                //cout << "in NULL" << endl ;
                node = new AdjListNode() ;
                node->id2 = name ;
                node->next = NULL ;
            }
            else if ( node->id2.compare( name ) < 0 ) { // in > current
                //cout << "smaller" << endl ;
                Insert( name, node->next ) ;
            }
            else if ( node->id2.compare( name ) > 0 ) { // in < current
                //cout << "larger, so put in" << endl ;
                AdjListNode* temp = new AdjListNode() ;
                temp->id2 = name ;
                temp->next = node ;
                node = temp ;
            }
        } // AdjListNode Insert

        void add( StudentPair pairInf ) {
            //cout << "in add" << endl ;
            head = Insert( pairInf, head ) ;
        }

        void init() {
            id1 = "";
            head = NULL ;
        }

        void print() {
            recurPrint( head ) ;
        }

        void recurPrint( AdjListNode* node ) {
            if ( node == NULL ) {
                ;
            }
            else {
                cout << node->id2 << endl ;
                recurPrint( node->next ) ;
            }
        } // recurPrint

        void init( AdjListNode*& node ) {
            if ( node != NULL ) {
                init( node->next ) ;
                delete node ;
                node = NULL ;
            }
        }

    }; // class AdjList
    // above are private class

    vector< AdjList > adjList ; // main list
    string fileNO ; // file number
    float weightLB ; // lower bound of weight
    // above are private vairabl  e

    bool readFile( vector< StudentPair >& pairInf ) {
        string fileName = "pairs" + fileNO + ".bin" ;
        fstream file ;
        file.open( fileName.c_str(), fstream::in | fstream::binary ) ;
        int studentNum = 0 ;
        StudentPair oneSet ;
        if ( !file.is_open() ) {
            return false ;
        } // end if
        else {
            file.seekg( 0, file.end ) ;
            studentNum = file.tellg() / sizeof(oneSet) ;
            file.seekg( 0, file.beg ) ;
            for ( int i = 0 ; i < studentNum ; i++ ) {
                file.read( (char*)&oneSet, sizeof( oneSet ) ) ;
                pairInf.push_back( oneSet ) ;
                //cout << "[" << i+1 << "]" << oneSet.id1 << ", " << oneSet.id2
                  //   << ", " << oneSet.weight << endl ;
            } // end for
        } // end else

        file.close() ;
        return true ;
    } // bool readFile

    // above are private method
public:

    DirectedGraph() {
        ;
    }

	int loc( AdjList guy ) { // finds location of guy in vector adjLisy, if guy exists

		for( int i = 0 ; i < adjList.size() ; i++ ) {
			if( guy.id1.compare(adjList[i].id1) == 0 )
				return i ;
		}

		return -1 ; // nothing found
	}

	int loc( string id, int start, int end ) { // finds location of identical id in vector if id exists

		if( end >= start ) {
			int mid = (start+end)/2 ;

			if( id.compare(adjList[mid].id1) == 0 )
				return mid ;
			else if( id.compare(adjList[mid].id1) > 0 ) {
				// right
				return loc(id,mid+1,end) ;
			}
			else {
				// left
				return loc(id,start,mid-1) ;
			}

		}
	}

	void swap( int i1, int i2 ) {
		// swaps i1,i2 in vector
		AdjList t1 = adjList[i1] ;
		adjList[i1] = adjList[i2] ;
		adjList[i2] = t1 ;
	}

	void connectionCounts( AdjList guy, int& counts, vector< string >& connectedIds ) { // count == conectionCount of guy
		// count == connection count
		// BFS

		bool visited[adjList.size()] ; // for traking purposes
		for( int i = 0 ; i < adjList.size() ; i++ ) { // intialization
			visited[i] = false ;
		}

		queue<AdjList> q ;
		visited[loc(guy)] = true ; // // first find guy and mark as visited
		q.push(guy) ; // enqueue guy
        AdjListNode *temp ; // for popping purposes

		while( !q.empty() ) {
            //cout << "in" << endl ;
		    temp = q.front().head ; // save to temp, NOTE: may have error
			q.pop() ;
			for( ; temp != NULL ; temp = temp->next ) {
				int newLoc = loc(temp->id2,0,adjList.size()-1) ;
                if ( !visited[newLoc] ) {
                    visited[newLoc] = true ;
                    q.push(adjList[newLoc]) ;
                    counts++ ;
                    connectedIds.push_back( adjList.at(newLoc).id1 ) ;
                }
			} // for
		} // while

        sort( connectedIds.begin(), connectedIds.end() ) ;

	} // void connectionCounts

	void cnt() { // method for conectionCount sorting vector & ouput file
	    int cc[adjList.size()] ; // array of all the conectionCounts of vector
	    for( int i = 0 ; i < adjList.size() ; i++ ) { // intialization
			cc[i] = 0 ;
		}

	    // save all connection counts in cc first...
        vector< vector< string > > connection ;
	    for( int i = 0 ; i < adjList.size() ; i++ ) {
            vector<string> connectedIds ;
	    	connectionCounts( adjList[i],cc[i], connectedIds ) ;
	    	connection.push_back( connectedIds ) ;
	    	//cout << cc[i] << endl ;
		}

		// sort records via connectionCount
		int temp ;
		vector<string> tempConnect;

		for( int i = 0 ; i < adjList.size() ; i++ ) {
			for( int j = i + 1 ; j < adjList.size() ; j++ ) {
				if( cc[i] < cc[j] ) { // swap cc & vector elements
					swap(i,j) ; // swap in vector

					temp = cc[i] ;
					cc[i] = cc[j] ; // swap in cc
					cc[j] = temp ;

					tempConnect = connection.at(i);
					connection.at(i) = connection.at(j) ;
					connection.at(j) = tempConnect ;
				} // end if
			} // end for
		} // end for

		// export connection
		exportConnection( cc, connection ) ;
	} // end cnt()

	void exportConnection( int cc[], vector< vector< string > > connection ) {
	    fstream file ;
        string fileName = "pairs" + fileNO + ".cnt" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << adjList.size() << " IDs in total.  >>>"
             << endl ;

        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            // output a vertex & its connection
            file << "[" << i+1 << "]  " << adjList.at(i).id1
                 << "( " << cc[i] << " ):" << endl ;
            for ( int j = 0 ; j < connection.at(i).size() ; j++ ) {
                if ( j % 10 == 0 && j != 0 ) {
                    file << endl ;
                }
                file << "  (" << j+1 << ") " << connection.at(i).at(j)  ;
            }
            file << endl ;
        } // end for
        file.close() ;
	}

    static bool cmpAdjList( const AdjList &a, const AdjList &b ) {
        return a.id1 < b.id1 ;
    }

    void create() {
        cout << "file number: " ;
        cin >> fileNO ;
        vector< StudentPair > pairInf ;
        if ( readFile( pairInf ) ) {
            cout << "read file success" << endl ;
            // make the directd graph
            for ( int i = 0 ; i < pairInf.size() ; i++ ) {
                //cout << i << " times" << endl ;
                bool found = false ;

                for ( int j = 0 ; j < adjList.size() && !found ; j++ ) {
                    // check if there's a the same one
                    if ( adjList.at(j).id1.compare( pairInf.at(i).id1 ) == 0 ) {
                        // put reicever in
                        found = true ;
                        adjList.at( j ).add( pairInf.at(i) ) ;
                    }
                }

                if ( !found ) {
                    // put sender, receiver in
                    AdjList newList( pairInf.at(i) ) ; // add reveiver & sneder into newList
                    adjList.push_back( newList ) ; // push newList into adjList
                }

                // put receiver into main list
                found = false ;
                for ( int j = 0 ; j < adjList.size() && !found ; j++ ) {
                    // check if there's a the same one
                    if ( adjList.at(j).id1.compare( pairInf.at(i).id2 ) == 0 ) {
                        found = true ;
                    }
                }
                if ( !found ) {
                    //cout << "not found" << endl ;
                    AdjList newList ;
                    newList.id1 = pairInf.at(i).id2 ;
                    adjList.push_back( newList ) ;
                }
            } // for

            // after complete the graph, sort the main list
            sort( adjList.begin(), adjList.end() , cmpAdjList ) ;
            exportGraphToAdj() ;
        } // if
        else { // read file failed
        	cout << "INVALID file number, try again" << endl ;
		}
    } // bool create

    void printMainList() {
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            cout << adjList.at(i).id1 << endl ;
        }
    }

    void exportGraphToAdj() {
        fstream file ;
        string fileName = "pairs" + fileNO + ".adj" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << adjList.size() << " IDs in total.  >>>"
             << endl ;
        int nodeCount = 0 ;
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            file << "[" << i+1 << "]  " << adjList.at(i).id1 << ":" << endl ;
            AdjListNode* node = adjList.at(i).head ;
            for ( int j = 1 ; node != NULL ; j++, node = node->next ) {
                if ( j % 10 == 1 && j != 1 ) {
                    file << endl ;
                }
                nodeCount++ ;
                file << "   (" << j << ") " << node->id2 << ", " << node->weight ;
            }
            file << endl ;
        } // end for
        file << "<<<  There are " << nodeCount << " nodes in total.  >>>" << endl ;
        file.close() ;
    }

    bool empty() {
    	if( adjList.empty() )
    		return true ;
    	else
    		return false ;
	}

	void clear() {
	    for ( int i = 0 ; i < adjList.size() ; i++ ) {
            adjList.at(i).init() ;
	    }
		adjList.clear() ;
		weightLB = -1 ;
	}

	bool setWeightLowerBound( float weight ) {
	    if ( weight < 0 || weight > 1 ) {
            cout << "Invalid lower bound." << endl ;
            return false ;
	    }
	    else {
            weightLB = weight ;
            return true ;
	    }
	}

	void computeCnt() {
        queue<string> q;
        vector<AdjList> infList ;

        // compute influence value of all sender
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            bool visited[adjList.size()] ; // for traking purposes
            for( int j = 0 ; j < adjList.size() ; j++ ) { // intialization
                visited[j] = false ;
            }

            visited[i] = true ;
            AdjList curList ;
            AdjListNode *dummy = NULL ;

            curList.id1 = adjList.at(i).id1 ;
            curList.inf = 0 ;

            q.push(curList.id1) ;
            // BFS
            while ( !q.empty() ) {
                AdjListNode *ptr = adjList.at( loc( q.front(), 0, adjList.size() - 1 ) ).head ;
                q.pop() ;
                for(  ; ptr != NULL ; ptr = ptr->next ) {

                    int newLoc = loc( ptr->id2, 0, adjList.size() - 1 ) ;
                    if ( !visited[newLoc] ) {

                        curList.inf++ ;
                        curList.Insert( ptr->id2, curList.head ) ;


                        visited[newLoc] = true ;

                        // check record
                        int infI = loc( ptr->id2, 0, infList.size() - 1, infList ) ;

                        if ( infI == -1 ) {
                            q.push( ptr->id2 ) ;
                        }
                        else{
                            for( AdjListNode* walk = infList.at(infI).head ; walk != NULL ; walk = walk->next ) {
                                int tempLoc = loc( walk->id2, 0, adjList.size()-1 ) ;
                                if ( !visited[tempLoc] ) {

                                    curList.Insert( walk->id2 , curList.head ) ;
                                    visited[tempLoc] = true ;
                                    curList.inf++ ;

                                } // if
                            } // for
                        } // else

                    } // if

                } // for

            } // while Stack not empty

			infList.push_back( curList ) ;

        } // for

        sort( infList.begin(), infList.end(), cmpInfValue ) ;
        exportCnt( infList ) ;
	} // computingInf()

	void computeInf() {
        stack<string> Stack;
        vector<AdjList> infList ;

        // compute influence value of all sender
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            bool visited[adjList.size()] ; // for traking purposes
            for( int j = 0 ; j < adjList.size() ; j++ ) { // intialization
                visited[j] = false ;
            }

            visited[i] = true ;
            AdjList curList ;
            AdjListNode *dummy = NULL ;

            curList.id1 = adjList.at(i).id1 ;
            curList.inf = 0 ;

            Stack.push(curList.id1) ;
            // DFS
            while ( !Stack.empty() ) {
                AdjListNode *ptr = adjList.at( loc( Stack.top(), 0, adjList.size() - 1 ) ).head ;
                Stack.pop() ;
                for(  ; ptr != NULL ; ptr = ptr->next ) {

                    int newLoc = loc( ptr->id2, 0, adjList.size() - 1 ) ;
                    if ( !visited[newLoc] ) {

                        if ( ptr->weight >= weightLB ) { // weight check
                            // avoid sender being put into receiver list
                            if ( ptr->id2.compare( adjList.at(i).id1 ) != 0 ) {
                                curList.inf++ ;
                                curList.Insert( ptr->id2, curList.head ) ;
                            }

                            visited[newLoc] = true ;

                            // check record
                            int infI = loc( ptr->id2, 0, infList.size() - 1, infList ) ;

                            if ( infI == -1 ) {
                                Stack.push( ptr->id2 ) ;
                            }
                            else{
                                for( AdjListNode* walk = infList.at(infI).head ; walk != NULL ; walk = walk->next ) {
                                    int tempLoc = loc( walk->id2, 0, adjList.size()-1 ) ;
                                    if ( !visited[tempLoc] ) {
                                        curList.Insert( walk->id2 , curList.head ) ;
                                        visited[tempLoc] = true ;
                                        curList.inf++ ;

                                    } // if
                                } // for
                            } // else

                        } //
                    } // if
                } // for
            } // while Stack not empty


            // add into list if influence value > 0
            if ( curList.inf > 0 ) {
                infList.push_back( curList ) ;

            } // if

        } // for

        sort( infList.begin(), infList.end(), cmpInfValue ) ;
        exportInf( infList ) ;
	} // computingInf()

    int loc( string id, int start, int end, vector<AdjList> vAdj ) { // finds location of identical id in vector if id exists
        if( end >= start ) {
            int mid = (start+end)/2 ;

            if( id.compare(vAdj[mid].id1) == 0 )
                return mid ;
            else if( id.compare(vAdj[mid].id1) > 0 ) {
                // right
                return loc(id,mid+1, end, vAdj ) ;
            }
            else {
                // left
                return loc(id,start,mid-1, vAdj ) ;
            }

        }
        else {
            return -1 ;
        }
    } // loc

	static cmpInfValue( AdjList& a, AdjList& b ) {
        return b.inf < a.inf ;
	}

	void exportInf( vector<AdjList> infList ) {
        fstream file ;
        string fileName = "pairs" + fileNO + ".inf" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << infList.size() << " IDs in total.  >>>"
             << endl ;
        cout << "<<<  There are " << infList.size() << " IDs in total.  >>>"
             << endl ;
        for ( int i = 0 ; i < infList.size() ; i++ ) {
            file << "[" << i+1 << "]  " << infList.at(i).id1
                 << "(" << infList.at(i).inf << "):" << endl ;

            AdjListNode* node = infList.at(i).head ;
            for ( int j = 1 ; node != NULL ; j++, node = node->next ) {
                if ( j % 10 == 1 && j != 1 ) {
                    file << endl ;
                }
                file << "   (" << j << ") " << node->id2  ;
            } // for
            file << endl ;
        } // end for
        file.close() ;
	} // exportInf

	void exportCnt( vector<AdjList> infList ) {
        fstream file ;
        string fileName = "pairs" + fileNO + ".cnt" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << infList.size() << " IDs in total.  >>>"
             << endl ;
        cout << "<<<  There are " << infList.size() << " IDs in total.  >>>"
             << endl ;
        for ( int i = 0 ; i < infList.size() ; i++ ) {
            file << "[" << i+1 << "]  " << infList.at(i).id1
                 << "(" << infList.at(i).inf << "):" << endl ;

            AdjListNode* node = infList.at(i).head ;
            for ( int j = 1 ; node != NULL ; j++, node = node->next ) {
                if ( j % 10 == 1 && j != 1 ) {
                    file << endl ;
                }
                file << "   (" << j << ") " << node->id2  ;
            } // for
            file << endl ;
        } // end for
        file.close() ;
	} // exportInf

    ~DirectedGraph() {
        clear() ;
    }

}; // class DirectedGraph

class Prompts {
	public:
	void choices() {
		cout << "*** Graph data manipulation ****" << endl ;
    	cout << "* 1. Build adjacency list      *" << endl ;
		cout << "* 2. Compute connection counts *" << endl ;
		cout << "* 3. Compute influence value   *" << endl ;
		cout << "* 0. QUIT                      *" << endl ;
		cout << "********************************" << endl ;
	}

	void prompt() {
		cout << "Input(0, 1, 2, 3): " ;
	}
};

int main() {
	DirectedGraph graph ;
	Prompts p ;
	string mode ;
	p.choices() ;
	p.prompt() ;
	cin >> mode ;

	while( mode.compare("0") != 0 ) {

		if( mode.compare("1" ) == 0 ) {
			graph.clear() ;
    		graph.create() ;
		}

		else if( mode.compare("2") == 0 ) {
			if( graph.empty() )
				cout << "Build adj list before computing conection counts " << endl ;
			else
				graph.computeCnt() ;
		}

		else if ( mode.compare("3") == 0 ) {
            if ( graph.empty() ) {
                cout << "Build adj list before computing influence." << endl ;
            }
            else {
                cout << "Input a real number in [0,1]: " ;
                float weightLB = 0.0 ;
                cin >> weightLB ;
                if ( graph.setWeightLowerBound( weightLB ) ) {
                    graph.computeInf();
                }
            }
		} // else if mode 3

		else
			cout << "Invalid choice,try again." << endl ;

        cout << endl ;
		p.choices() ;
		p.prompt() ;
		cin >> mode ;

	} // while


    cout << "EXITING..." ;

    return 0 ;
}
