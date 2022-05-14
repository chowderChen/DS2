// 10720115 ªL¯Ñ¶h 10720111 ³¯¤Ö·u
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include <limits>
using namespace std;

class DjkNode {
	public:
		int index ;
		float weight ;
	public:
		DjkNode( int num, float fl ) {
			index = num ;
			weight = fl ;
		}
};

class MinHeap {

	public:
		vector<DjkNode> heap ;

	public:

		void load( float weight[], bool visited[], int size ) {
			// load weights IFF unvisited.
			for( int i = 0 ; i < size ; i++ ) {

				if( !visited[i] && weight[i] != numeric_limits<float>::infinity() ) {
					heap.push_back( DjkNode( i,weight[i] ) ) ;
					reheapUp() ;
				}

			} // end for
		}

		void swap( int y, int z ) { // swaps index y,z's elements in heap vector
			DjkNode tempZ = heap[z] ;
			heap[z] = heap[y] ;
			heap[y] = tempZ ;
		}

		void reheapUp() { // Maintenance function for HeapInsert
			for( int i = heap.size() - 1 ; i >  0 ; i = (i-1) / 2 )
				if( heap[i].weight < heap[ (i - 1) / 2 ].weight )
					swap( i ,(i - 1) / 2  ) ;
		}

		int min() { // return min weight's index
			if( !heap.empty() ) {
				return heap[0].index ;
			}

			else
				return -1 ;
		}

};

class StudentPair {
    public:
    char id1[10] ; // sender
    char id2[10] ; // receiver
    float weight ;
};

class AdjListNode {
public:
    string id2 ;
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
    /*
    AdjListNode* Insert( StudentPair pairInf, AdjListNode* node ) { // insert in ascending order
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
    */
    void Insert( string name, AdjListNode*& node ) { // insert in ascending order
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

    void Insert( string name, float weight, AdjListNode*& node ) { // insert in ascending order
        if ( node == NULL ) {
            node = new AdjListNode() ;
            node->id2 = name ;
            node->weight = weight ;
            node->next = NULL ;
        }
        else if ( node->id2.compare( name ) < 0 ) { // in > current.  node < name
            //cout << "smaller" << endl ;
            Insert( name, weight, node->next ) ;
        }
        else if ( node->id2.compare( name ) > 0 ) { // in < current
            //cout << "larger, so put in" << endl ;
            AdjListNode* temp = new AdjListNode() ;
            temp->id2 = name ;
            temp->weight = weight ;
            temp->next = node ;
            node = temp ;
        }
    } // AdjListNode Insert

    /*
    AdjListNode* Insert( string name, float weight, AdjListNode* node ) { // insert in ascending order
        if ( node == NULL ) {
            node = new AdjListNode() ;
            node->id2 = name ;
            node->weight = weight ;
            node->next = NULL ;
            return node ;
        }
        else if ( node->id2.compare( name ) < 0 ) { // in > current.  node < name
            //cout << "smaller" << endl ;
            node->next = Insert( name, weight, node->next ) ;
            return node ;
        }
        else if ( node->id2.compare( name ) > 0 ) { // in < current
            //cout << "larger, so put in" << endl ;
            AdjListNode* temp = new AdjListNode() ;
            temp->id2 = name ;
            temp->weight = weight ;
            temp->next = node ;
            return temp ;
        }
    } // AdjListNode Insert
    */
    /*
    void add( StudentPair pairInf ) {
        //cout << "in add" << endl ;
        head = Insert( pairInf, head ) ;
    }
    */
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

class Graph {
    vector< AdjList > adjList ; // main list
    string fileNO ; // file number
    float weightUB ; // upper bound of weight
    vector< AdjList > ccList ; // connected component list
    // above are private variable

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
                     //<< ", " << oneSet.weight << endl ;
            } // end for
        } // end else

        file.close() ;
        return true ;
    } // bool readFile

    // above are private method
public:

    Graph() {
        weightUB = 0 ;
    }

	int loc( AdjList guy ) { // finds location of guy in vector adjLisy, if guy exists

		for( int i = 0 ; i < adjList.size() ; i++ ) {
			if( guy.id1.compare(adjList[i].id1) == 0 )
				return i ;
		}

		return -1 ; // nothing found
	}

	int loc( string id, int start, int end ) { // finds location of id in adjList if id exists

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

		} // if
        else {
            return -1 ;
        }
	} // loc

	int loc( string id, int start, int end, vector<AdjList> vAdj ) {
        /*
        finds location of id in vector vAdj
        if not found, return -1 ;
        */
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

	void swap( int i1, int i2 ) {
		// swaps i1,i2 in vector
		AdjList t1 = adjList[i1] ;
		adjList[i1] = adjList[i2] ;
		adjList[i2] = t1 ;
	}

    static bool cmpAdjList( const AdjList &a, const AdjList &b ) {
        return a.id1 < b.id1 ;
    }

    void create() {
        // loaf file & create adj list
        cout << "file number: " ;
        cin >> fileNO ;
        vector< StudentPair > pairInf ;
        if ( readFile( pairInf ) ) {
            cout << "Input a real number in (0,1]: " ;
            float upperBound ;
            cin >> upperBound ;

            if ( 0 >= upperBound || upperBound > 1 ) {
                cout << "### It is NOT in (0,1] ###" << endl ;
            }
            else {
                weightUB = upperBound ;
                // create adj list
                for ( int i = 0 ; i < pairInf.size() ; i++ ) {
                    if ( pairInf.at(i).weight <= upperBound ) {
                        addPair( pairInf.at(i).id1, pairInf.at(i).id2, pairInf.at(i).weight ) ;
                        addPair( pairInf.at(i).id2, pairInf.at(i).id1, pairInf.at(i).weight ) ;
                    } // if <= upperBound

                } // for all pair inf

                // sort main list
                sort( adjList.begin(), adjList.end() , cmpAdjList ) ;
                exportGraphToAdj( upperBound ) ;
            } // else

        } // if read file success
        else { // read file failed
        	cout << "INVALID file number, try again" << endl ;
		}

    } // bool create

    void addPair( string id1, string id2, float weight ) {
        // add pair into adj list
        bool found = false ;

        for ( int j = 0 ; j < adjList.size() && !found ; j++ ) {
            // check if there's a the same one
            if ( adjList.at(j).id1.compare( id1 ) == 0 ) {
                // put reicever in
                found = true ;
                //adjList.at(j).head = adjList.at( j ).Insert( id2, weight, adjList.at(j).head ) ;
                adjList.at( j ).Insert( id2, weight, adjList.at(j).head ) ;
            }
        }

        if ( !found ) {
            AdjList newList ;
            newList.id1 = id1 ;
            //newList.head = newList.Insert( id2, weight, newList.head ) ;
            //newList.Insert( id2, weight, newList.head ) ;
            newList.head = new AdjListNode() ;
            newList.head->id2 = id2 ;
            newList.head->weight = weight ;
            newList.head->next = NULL ;
            adjList.push_back( newList ) ;
        }
    } // addPair

    void exportGraphToAdj( float upperBound ) {
        // export adj list
        // count num of main list ids and total nodes
        stringstream ss ;
        ss << upperBound ;

        fstream file ;
        string fileName = "pairs" + fileNO + "_" + ss.str() + ".adj" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << adjList.size() << " IDs in total.  >>>"
             << endl ;
        cout << "<<<  There are " << adjList.size() << " IDs in total.  >>>"
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
        cout << "<<<  There are " << nodeCount << " nodes in total.  >>>" << endl ;
        file.close() ;
    } // export adj list

    void printMainList() {
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            cout << adjList.at(i).id1 << endl ;
        }
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
	    for ( int i = 0 ; i < ccList.size() ; i++ ) {
            ccList.at(i).init() ;
	    }

		adjList.clear() ;
		ccList.clear() ;
		fileNO = "" ;
		weightUB = 0 ;
	}
    /*
	bool setBound( float weight ) {
	    if ( weight < 0 || weight > 1 ) {
            cout << "Invalid lower bound." << endl ;
            return false ;
	    }
	    else {
            weightLB = weight ;
            return true ;
	    }
	}
    */
	static cmpInfValue( AdjList& a, AdjList& b ) {
        return b.inf < a.inf ;
	}

	void cc() {
	    // computing connected component
	    stack<string> stk ;
	    //vector<AdjList> ccList ; // connected component
	    bool visited[adjList.size()] ; // traking
        for( int j = 0 ; j < adjList.size() ; j++ ) { // intialize
            visited[j] = false ;
        }

	    for( int i = 0 ; i < adjList.size() ; i++ ) {
            if( !visited[i] ) { // not in other components
                visited[i] = true ;
                AdjList curList ;

                curList.id1 = adjList.at(i).id1 ;
                curList.inf = 0 ;

                stk.push(curList.id1) ;
                // DFS
                while ( !stk.empty() ) {
                    AdjListNode *ptr = adjList.at( loc( stk.top(), 0, adjList.size() - 1 ) ).head ;
                    stk.pop() ;
                    for(  ; ptr != NULL ; ptr = ptr->next ) {
                        int newLoc = loc( ptr->id2, 0, adjList.size() - 1 ) ;
                        if ( !visited[newLoc] ) {
                            if ( ptr->id2.compare( adjList.at(i).id1 ) != 0 ) {
                                // avoid sender being put into receiver list
                                curList.inf++ ;
                                curList.Insert( ptr->id2, curList.head ) ;
                            }
                            visited[newLoc] = true ;
                            stk.push( ptr->id2 ) ;
                        } // if
                    } // for ptr != NULL
                } // while Stack not empty
                ccList.push_back( curList ) ;
            } // if not in other components
	    } // for all node
	    sort( ccList.begin(), ccList.end(), cmpInfValue ) ;
	    exportcc( ccList ) ;
	} // cc

	void exportcc( vector<AdjList> ccList ) {
	    stringstream ss ;
        ss << weightUB ;

        fstream file ;
        string fileName = "pairs" + fileNO + "_" + ss.str() + ".cc" ;
        file.open( fileName.c_str(), fstream::out ) ;
        file << "<<<  There are " << ccList.size() << " connected components in total.  >>>"
             << endl ;
        cout << "<<<  There are " << ccList.size() << " connected components.  >>>"
             << endl ;
        for ( int i = 0 ; i < ccList.size() ; i++ ) {
            file << "[" << i+1 << "]  "
                 << "size = " << ccList.at(i).inf + 1 << endl ;

            file << "   ( 1) " << ccList.at(i).id1 ;
            AdjListNode* node = ccList.at(i).head ;
            for ( int j = 2 ; node != NULL ; j++, node = node->next ) {
                if ( j % 8 == 1 ) {
                    file << endl ;
                }
                file << "   ( " << j << ") " << node->id2  ;
            } // for
            file << endl ;
        } // end for
        file.close() ;
	} // export connected components

    ~Graph() {
        clear() ;
    }

    // Below are additional functions for Dijkstra's

    void listAllId() {
    	// output all id's
    	int count = 0 ; // reset on 8 ;
    	for( int i = 0 ; i < adjList.size() ; i++ ) {
    		// run through entire adjList
			count++ ;
			cout << "  " << adjList[i].id1 ;
			if( count == 8 ) {
				count = 0 ;
				cout << endl ;
			}
		}

		if( count != 8 )
			cout << endl ; // for last line enter.

	} // end listAllId

	bool unvisited(int index, bool visited[] ) {
		// checks if adjList(index) still has unvisited adjacent vertices.
		AdjListNode * cur = adjList[index].head ;
		for( ; cur != NULL ; cur = cur->next ) {
			if ( !visited[loc(cur->id2,0,adjList.size() - 1 ) ] )
				return true ;
		}

		return false ;

	}

	int ccSize( string origin ) {
        // get the size of conneceted components of origin id

	    bool visited[adjList.size()] ; // traking
        for( int j = 0 ; j < adjList.size() ; j++ ) { // intialize
            visited[j] = false ;
        }

        int i = loc( origin, 0, adjList.size() - 1 ) ;
        visited[i] = true ;

        int components = 1 ; // size

        stack<string> stk ;
        stk.push(origin) ;
        // DFS
        while ( !stk.empty() ) {
            AdjListNode *ptr = adjList.at( loc( stk.top(), 0, adjList.size() - 1 ) ).head ;
            stk.pop() ;
            for(  ; ptr != NULL ; ptr = ptr->next ) {
                int newLoc = loc( ptr->id2, 0, adjList.size() - 1 ) ;
                if ( !visited[newLoc] ) {
                    if ( ptr->id2.compare( adjList.at(i).id1 ) != 0 ) {
                        // avoid sender being put into receiver list
                        components++ ;
                    }
                    visited[newLoc] = true ;
                    stk.push( ptr->id2 ) ;
                } // if
            } // for ptr != NULL
        } // while Stack not empty
        return components ;
	} // ccSize

    void dijkstra( string origin ) {

    	// find and save all shoretest paths in a weight array.
    	// origin is the origin vertex

    	int newLoc = 0 ; // for loc() saving.
    	int temp = 0 ; // not important
    	float weight[adjList.size()] ; // stores all currnet weights
    	bool visited[adjList.size()] ; // stores visit state

    	newLoc = loc(origin,0,adjList.size() - 1 ) ;

		// Check first if origin actually exists in list.

		if( newLoc != -1 ) {
    		for( int i = 0 ; i < adjList.size() ; i++ ) {
                // intialization
    			visited[i] = false ;
    			weight[i] = numeric_limits<float>::infinity() ;
			}

			weight[newLoc] = 0 ;

			vector<DjkNode> result ; // where all shortest paths & their indexes reside

			// start visiting....
			int pathSize = ccSize(origin) ;
			for( int times = 1 ; times < pathSize ; times++ ) {
				// NOTE: newLoc is detrimantal to the loop, make sure it's correct at all times...

				// = current vertex
				visited[newLoc] = true ;

				// replace any new min paths
				for(AdjListNode * cur = adjList[newLoc].head ; cur != NULL ; cur = cur->next ) {
					temp = loc(cur->id2,0,adjList.size() - 1 ) ;
					if( !visited[temp] && ( ( weight[newLoc] + cur->weight ) < weight[temp] ) )
						weight[temp] = weight[newLoc] + cur->weight ;
				}

				// next vertex = walk smallest and unvisted path
				// USE HEAP????, this heap must SOTRE both the index and weight
				MinHeap mh ;
				mh.load( weight, visited, adjList.size() ) ;
				newLoc = mh.min() ;
				//cout << adjList.at(newLoc).id1 << endl ;
				if ( weight[newLoc] != numeric_limits<float>::infinity() ) {
    	            DjkNode newSP(newLoc, weight[newLoc]) ;
        	        result.push_back(newSP) ;
				}
			} // end for() all components

			// RESULT????? A array of weights....
		    // NOTE: How do we output this to a file????
        	sort( result.begin(), result.end(), cmpDjkNode ) ;
        	exportShortestPath( result, origin ) ;
		} // if loc != -1

		else
			cout << "This ID doesn't exsist!" << endl ;

	} // end dijkstra()

    static cmpDjkNode( DjkNode& a, DjkNode& b ) {
        return a.weight < b.weight ;
	}

    void exportShortestPath( vector<DjkNode> result, string origin ) {
        stringstream ss ;
        ss << weightUB ;
        fstream file ;
        string fileName = "pairs" + fileNO + "_" + ss.str() + ".ds" ;
        file.open( fileName.c_str(), fstream::app ) ;

        file << "origin:" << origin << endl ;
        for( int i = 0 ; i < result.size() ; i++ ) {
            if ( i % 8 == 0 && i != 0 ) {
                file << endl ;
            }
            file << "  ( " << i + 1 << ")  " << adjList.at(result.at(i).index).id1
                 << ", " << result.at(i).weight ;
        }
        file << endl << endl ;
        file.close() ;
    } // export shortest path

    float PrimMinSpanningTree( AdjList cc ) {
        // cc is a connected component
        int numCC = ccSize( cc.id1 ) ;
        bool visited[adjList.size()] ;
        float weight[adjList.size()] ;
        for ( int i = 0 ; i < adjList.size() ; i++ ) {
            visited[i] = false ;
            weight[i] = numeric_limits<float>::infinity() ;
        }

        int nowLoc = loc( cc.id1, 0, adjList.size() -1 ) ;
        visited[nowLoc] = true ;
        int counter = 0 ;
        float result = 0.0 ; // total weight
        while( numCC - 1 > counter ) {
            //
            for ( AdjListNode* walk = adjList.at(nowLoc).head ; walk != NULL ; walk = walk->next ) {
                int tempLoc = loc( walk->id2, 0, adjList.size() - 1 ) ;
                if (!visited[tempLoc] && weight[tempLoc] > walk->weight ) {
                    weight[ tempLoc ] = walk->weight ;
                }
            } // for all receiver

            MinHeap mh ;
            mh.load( weight, visited, adjList.size() ) ;
            nowLoc = mh.min() ;

            visited[nowLoc] = true ;
            result = result + weight[nowLoc] ;
            //cout << weight[nowLoc] << endl ;
            counter++ ;
        } // while
        return result ;
    } // Prim min spanning tree

    void minSpanningTree() {
        for ( int i = 0 ; i < ccList.size() ; i++ ) {
            float result = PrimMinSpanningTree( ccList.at(i) ) ;
            cout << "The MST cost of connected component { " << i + 1 << "} = "
                 << result << endl ;
        } // for all components
    }

    bool ccIsEmpty() {
        if( ccList.empty() ) {
            return true ;
        }
        return false ;
    } //

}; // class DirectedGraph

class Prompts {
	public:
	void choices() {
		cout << "****   Graph data manipulation     ****" << endl ;
    	cout << "* 1. Create adjacency lists           *" << endl ;
		cout << "* 2. Build connected components       *" << endl ;
		cout << "* 3. Find shortest paths by Dijkstra  *" << endl ;
		cout << "* 4. Generate minimum spanning trees  *" << endl ;
		cout << "* 0. QUIT                             *" << endl ;
		cout << "***************************************" << endl ;
	}

	void prompt() {
		cout << "Input(0, 1, 2, 3, 4): " ;
	}

	void mi3_ID() {
		cout << "Input a student ID [0: exit]: " ;
	}
};

int main() {
	Graph graph ;
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
				cout << "Build adj list before computing conection components " << endl ;
			else {
                graph.cc() ;
			}
		}

		else if ( mode.compare("3") == 0 ) {
            if ( graph.empty() ) {
                cout << "Build adj list before using Dijkstra's dick" << endl ;
            }
            else {
                graph.listAllId() ; // print all id choices
                p.mi3_ID() ; //
                cin >> mode ;
                while( mode.compare("0") != 0 ) {

                	// 1.find all shortest paths to all other vertices
                    graph.dijkstra( mode ) ;
                	// 2.output  the paths into a file somehow?

                	p.mi3_ID() ;
                	cin >> mode ;
				}

				// 3.close file

            }
		} // else if mode 3

		else if ( mode.compare("4") == 0 ) {
            if( graph.ccIsEmpty() ) {
                cout << "Get connected components first.\n" ;
            }
            else {
                graph.minSpanningTree() ;
            }

		} // else if mode == 4

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
