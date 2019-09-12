#include <iostream>

#define INFINITY 2147483647


/*
 *This Program defines a room node, and generates a maze of connecting rooms
 *it implements breadth first, depth first, and shortest path search functions
 *to fin the endpoint from the start point, and then allows user navigation of the maze
 *
 *Data Structures @ TCC
 *
 *Arick Mounts
 */

using namespace std;
struct node{
  string name;
  struct node * north;
  struct node * south;
  struct node * east;
  struct node * west;
  struct node * top;
  struct node * bottom;
	int distance;
  int visited;
  int floor;
	struct node * back;
};

struct node_list{
	struct node * my_node;
	struct node_list * next;
};

struct player{
  struct node * location;
  int game_over;
};

struct node_list * queue = NULL;

void describe_room( struct node * current_room);
void draw_map( struct player * p, struct node * map[], int width, int height );
void queue_insert( struct node_list * list );
void breadth_first_search( struct node * start, struct node * end );
void depth_first_search( struct node * start, struct node * end );
void clear_checks( struct node * map[], int size );
void show_path( struct node * );
struct node * find_shortest_distance( struct node * node_array[], int );
void shortest_path( struct node * node_array[], struct node * start, int size );
struct node_list * dequeue();

int main() {

  struct player * p = new player;
  p->location = NULL;
  p->game_over = 0;

  //array of nodes
  struct node* map[15];

  //nodes
  struct node * r1_1 = new struct node;
  struct node * r1_2 = new struct node;
  struct node * r1_3 = new struct node;
  struct node * r1_4 = new struct node;
  struct node * r1_5 = new struct node;
  struct node * r1_6 = new struct node;
  struct node * r1_7 = new struct node;
  struct node * r2_1 = new struct node;
  struct node * r2_2 = new struct node;
  struct node * r2_3 = new struct node;
  struct node * r2_4 = new struct node;
  struct node * r2_5 = new struct node;
  struct node * r3_1 = new struct node;
  struct node * r3_2 = new struct node;
  struct node * r3_3 = new struct node;

//populate arrray
  map[ 0 ] = r1_1;
  map[ 1 ] = r1_2;
  map[ 2 ] = r1_5;
  map[ 3 ] = r1_3;
  map[ 4 ] = r1_6;
  map[ 5 ] = r1_7;
  map[ 6 ] = r1_4;
  map[ 7 ] = r2_1;
  map[ 8 ] = r2_2;
  map[ 9 ] = r2_5;
  map[ 10 ] = r2_4;
  map[ 11 ] = r2_3;
  map[ 12 ] = r3_2;
  map[ 13 ] = r3_1;
  map[ 14 ] = r3_3;


//set the fields of nodes
r1_1->name = "Starting room";
r1_1->top = NULL;
r1_1->bottom = NULL;
r1_1->north = NULL;
r1_1->south = r1_3;
r1_1->east = r1_2;
r1_1->west = NULL;
r1_1->floor = 1;

r1_2->name = "Foyer";
r1_2->top = NULL;
r1_2->bottom = NULL;
r1_2->north = NULL;
r1_2->south = r1_6;
r1_2->east = r1_5;
r1_2->west = r1_1;
r1_2->floor = 1;

r1_3->name = "Pool";
r1_3->top = NULL;
r1_3->bottom = NULL;
r1_3->north = r1_1;
r1_3->south = r1_4;
r1_3->east = r1_6;
r1_3->west = NULL;
r1_3->floor = 1;

r1_4->name = "Powder room";
r1_4->top = NULL;
r1_4->bottom = NULL;
r1_4->north = r1_3;
r1_4->south = NULL;
r1_4->east = NULL;
r1_4->west = NULL;
r1_4->floor = 1;

r1_5->name = "Living Room";
r1_5->top = r2_1;
r1_5->bottom = NULL;
r1_5->north = NULL;
r1_5->south = r1_7;
r1_5->east = NULL;
r1_5->west = r1_2;
r1_5->floor = 1;

r1_6->name = "Kitchen";
r1_6->top = NULL;
r1_6->bottom = NULL;
r1_6->north = r1_2;
r1_6->south = NULL;
r1_6->east = r1_7;
r1_6->west = r1_3;
r1_6->floor = 1;

r1_7->name = "Dining room";
r1_7->top = NULL;
r1_7->bottom = NULL;
r1_7->north = r1_5;
r1_7->south = NULL;
r1_7->east = NULL;
r1_7->west = r1_6;
r1_7->floor = 1;

r2_1->name = "Hallway";
r2_1->top = NULL;
r2_1->bottom = r1_5;
r2_1->north = NULL;
r2_1->south = r2_4;
r2_1->east = r2_2;
r2_1->west = NULL;
r2_1->floor = 2;

r2_2->name = "Bedroom";
r2_2->top = NULL;
r2_2->bottom = NULL;
r2_2->north = NULL;
r2_2->south = r2_3;
r2_2->east = NULL;
r2_2->west = r2_1;
r2_2->floor = 2;

r2_3->name = "Master Bathroom";
r2_3->top = r3_3;
r2_3->bottom = NULL;
r2_3->north = r2_2;
r2_3->south = NULL;
r2_3->east = NULL;
r2_3->west = NULL;
r2_3->floor = 2;

r2_4->name = "Theater";
r2_4->top = NULL;
r2_4->bottom = NULL;
r2_4->north = r2_1;
r2_4->south = NULL;
r2_4->east = NULL;
r2_4->west = r2_5;
r2_4->floor = 2;

r2_5->name = "Den";
r2_5->top = r3_1;
r2_5->bottom = NULL;
r2_5->north = NULL;
r2_5->south = NULL;
r2_5->east = r2_4;
r2_5->west = NULL;
r2_5->floor = 2;

r3_1->name = "Guest room";
r3_1->top = NULL;
r3_1->bottom = r2_5;
r3_1->north = NULL;
r3_1->south = NULL;
r3_1->east = NULL;
r3_1->west = r3_2;
r3_1->floor = 3;

r3_2->name = "Guest bathroom";
r3_2->top = NULL;
r3_2->bottom = NULL;
r3_2->north = NULL;
r3_2->south = NULL;
r3_2->east = r3_1;
r3_2->west = NULL;
r3_2->floor = 3;

r3_3->name = "Ending room";
r3_3->top = NULL;
r3_3->bottom = r2_3;
r3_3->north = NULL;
r3_3->south = NULL;
r3_3->east = NULL;
r3_3->west = NULL;
r3_3->floor = 3;


//Breadth First search
clear_checks(map, 15);
breadth_first_search (r1_1, r3_3);
clear_checks(map, 15);

//Depth First search

depth_first_search(r1_1, r3_3);
clear_checks(map, 15);


//Shortest path
shortest_path( map, map[ 0 ], 15 );
//printf( "The shortest path between %s and %s is %d\n", map[ 0 ]->name, map[ 5 ]->name, map[ 5 ]->distance );
cout << "The shortest path between " << map[ 0 ]->name <<" and " << map[ 14 ]->name << " is "<< map[ 14 ]->distance << endl;
show_path( map[ 14 ] );

cout << "\n\n---------------------------\n\n";


//User Input
p->location = map[0];
char user_input = 'z';
int saved_index = 0;

  while( !p->game_over ){
    //p->location->visited = 2;
    describe_room( p->location );
    if (p->location == r3_3){
      cout << "You made it to the end! congratulations!" << endl;
      p->game_over = 1;
      continue;
    }
    printf( "What is your command: " );
    user_input = getchar();
    while( (getchar()!='\n') );
    switch( user_input ){
      case 'q':
        p->game_over = 1;
        break;
      case 'n':
        if( p->location->north ){
          p->location = p->location->north;
          //p->location->visited = 2;
        }
        break;
      case 's':
        if( p->location->south ){
          p->location = p->location->south;
          //p->location->visited = 2;
        }
        break;
      case 'e':
        if( p->location->east ){
          p->location = p->location->east;
          //p->location->visited = 2;
        }
        break;
      case 'w':
        if( p->location->west ){
          p->location = p->location->west;
          //p->location->visited = 2;
        }
        break;
        case 'u':
        if( p->location->top ){
          p->location = p->location->top;
          //p->location->visited = 2;
        }
        break;
        case 'd':
        if( p->location->bottom ){
          p->location = p->location->bottom;
          //p->location->visited = 2;
        }
        break;
        case 'm':
          draw_map( p, map, 3, 5);
        break;
      }
  }
}


  void draw_map( struct player * p, struct node * map[], int width, int height ){
	int i = 0;
	int x = 0;
	int y = 0;
	// For each row...
	for( y = 0; y < height; y++ ){
		// For each column...
		for( x = 0; x < width; x++ ){
			// Draw a row showing the room number and any lateral connections.
			//printf( "%03d%s", map[ i + x ]->room_number, ( ( map[ i + x ]->east_path) ? "--" : "  " ) );
      if (p->location->floor == map[ i + x]->floor ){
      printf( " %s %s", ((p->location == map[ i + x]) ? "P" : "+"), ( ( map[ i + x ]->east) ? "--" : "  " ) );
      }else{printf("     ");}

      

		}
		printf( "\n" );
		for( x = 0; x < width; x++ ){
			// Draw any horizontal connections.
      if (p->location->floor == map[ i + x]->floor ){
			printf( " %s   ", ( ( map[ i + x ]->south ) ? "|" : " " ) );
      }else{printf("     ");}
		}
		printf( "\n" );
		i = i + width;
	}
}

  void describe_room( struct node * current_room){
    cout << "You are in the " << current_room->name << endl;
    if( current_room->top){cout << "There is a ladder up." << endl;}
    if( current_room->bottom){cout << "There is a ladder down." << endl;}
    if( current_room->north){cout << "There is a doorway to the north." << endl;}
    if( current_room->south){cout << "There is a doorway to the south." << endl;}
    if( current_room->east){cout << "There is a doorway to the east." << endl;}
    if( current_room->west){cout << "There is a doorway to the west." << endl;}
  };


struct node_list * dequeue(){
	struct node_list * temp = queue;
	struct node_list * back = NULL;
	if( !temp ){
		return NULL;
	}else if( !temp->next ){
		queue = NULL;
		return temp;
	}else{
		while( temp->next ){
			back = temp;
			temp = temp->next;
		}
		back->next = NULL;
	}
	return temp;
}


void clear_checks( struct node * map[], int size ){
	
	int i = 0;
	for( i = 0; i < size; i++ ){
		map[ i ]->visited = 0;
		map[ i ]->distance = INFINITY;
		map[ i ]->back = NULL;
	}
}

void queue_insert( struct node_list * list ){
	list->next = queue;
	queue = list;
}



void breadth_first_search( struct node * start, struct node * end ){
	
		int found = 0;
		struct node_list * q = (struct node_list * )malloc( sizeof( struct node_list ) );
		q->my_node = start;
		q->next = NULL;
		queue_insert( q );
		do{
			struct node_list * temp = dequeue();
			cout << "Temp is looking at:" << temp->my_node->name << ", visited: " << temp->my_node->visited  << endl;
			if( temp->my_node == end ){
				printf( "Breadth first: found a solution\n\n\n---------------------------\n\n" );
				found = 1;
			}else{
				if( !temp->my_node->visited ){
					temp->my_node->visited = 1;
          if( temp->my_node->top ){
						struct node_list * top_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						top_temp->my_node = temp->my_node->top;
						queue_insert( top_temp );
					}if( temp->my_node->bottom ){
						struct node_list * bottom_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						bottom_temp->my_node = temp->my_node->bottom;
						queue_insert( bottom_temp );
					}
					if( temp->my_node->north ){
						struct node_list * north_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						north_temp->my_node = temp->my_node->north;
						queue_insert( north_temp );
					}
					if( temp->my_node->south ){
						struct node_list * south_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						south_temp->my_node = temp->my_node->south;
						queue_insert( south_temp );
					}
					if( temp->my_node->east ){
						struct node_list * east_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						east_temp->my_node = temp->my_node->east;
						queue_insert( east_temp );
					}
					if( temp->my_node->west ){
						struct node_list * west_temp = (struct node_list *)malloc( sizeof( struct node_list ) );
						west_temp->my_node = temp->my_node->west;
						queue_insert( west_temp );
					}
				}
			}
		}while( queue && !found );
		if( !found ){
			printf( "Breadth first: no solution found\n\n\n---------------------------\n\n" );
		}
}

void depth_first_search( struct node * start, struct node * end ){
	
	// Boolean value that we test at the end.
	int found = 0;
	
	// Create a linked list which we treat like a stack.
	struct node_list * stack = ( struct node_list * )malloc( sizeof( struct node_list ) );
	stack->my_node = start; //  Start with the "first" node
	stack->next = NULL; // Only one element on the stack at the start.
	
	do{
		// Pop the first element off of the stack and store in temp.
		struct node_list * temp = stack;
		stack = stack->next;
		cout << "Popping: " <<temp->my_node->name  <<", visited: " << temp->my_node->visited <<endl; 
		if( temp->my_node == end ){
			printf( "Depth First found a solution!\n\n\n---------------------------\n\n" );
			found = 1;
		}else{
			// If we haven't visited it yet...
			if( !temp->my_node->visited ){
				temp->my_node->visited = 1; // Mark it as visited.
				// Then for each available direction...
        if( temp->my_node->top ){
					// Create a node for the linked list and push it onto the list...
					struct node_list * top_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					top_temp->my_node = temp->my_node->top;
					top_temp->next = stack;
					stack = top_temp;
					//printf("n Pushing %s onto the stack\n", temp->my_node->top->name );
				}
        if( temp->my_node->bottom ){
					// Create a node for the linked list and push it onto the list...
					struct node_list * bottom_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					bottom_temp->my_node = temp->my_node->bottom;
					bottom_temp->next = stack;
					stack = bottom_temp;
					//printf("n Pushing %s onto the stack\n", temp->my_node->bottom->name );
				}
				if( temp->my_node->north ){
					// Create a node for the linked list and push it onto the list...
					struct node_list * north_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					north_temp->my_node = temp->my_node->north;
					north_temp->next = stack;
					stack = north_temp;
					//printf("n Pushing %s onto the stack\n", temp->my_node->north->name );
				}
				if( temp->my_node->south ){
					struct node_list * south_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					south_temp->my_node = temp->my_node->south;
					south_temp->next = stack;
					stack = south_temp;
					//printf("s Pushing %s onto the stack\n", temp->my_node->south->name );
				}
				if( temp->my_node->east ){
					struct node_list * east_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					east_temp->my_node = temp->my_node->east;
					east_temp->next = stack;
					stack = east_temp;
					//printf("e Pushing %s onto the stack\n", temp->my_node->east->name );
				}
				if( temp->my_node->west ){
					struct node_list * west_temp = (struct node_list * )malloc(sizeof( struct node_list ) );
					west_temp->my_node = temp->my_node->west;
					west_temp->next = stack;
					stack = west_temp;
					//printf("w Pushing %s onto the stack\n", temp->my_node->west->name );
				}
			}
		}
	}while( stack && !found );
	if( !found ){
		printf( "Depth first search: no solution found\n\n\n---------------------------\n\n" );
	}
}


void shortest_path( struct node * node_array[], struct node * start, int size ){
	
	struct node * current_node = NULL;
	clear_checks( node_array, size );
	start->distance = 0;
	
	while( ( current_node = find_shortest_distance( node_array, size ) ) ){
		if( current_node->distance == INFINITY ){
			break;
		}
		current_node->visited = 1;
    if( current_node->top ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->top->distance ){
				current_node->top->distance = temp_distance;
				current_node->top->back = current_node;
			}
		}if( current_node->bottom ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->bottom->distance ){
				current_node->bottom->distance = temp_distance;
				current_node->bottom->back = current_node;
			}
		}
		if( current_node->north ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->north->distance ){
				current_node->north->distance = temp_distance;
				current_node->north->back = current_node;
			}
		}
		if( current_node->south ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->south->distance ){
				current_node->south->distance = temp_distance;
				current_node->south->back = current_node;
			}
		}
		if( current_node->east ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->east->distance ){
				current_node->east->distance = temp_distance;
				current_node->east->back = current_node;
			}
		}
		if( current_node->west ){
			int temp_distance = current_node->distance + 1;
			if( temp_distance < current_node->west->distance ){
				current_node->west->distance = temp_distance;
				current_node->west->back = current_node;
			}
		}
	}
}


struct node * find_shortest_distance( struct node * node_array[], int size ){
	struct node * rv = NULL;
	int i = 0;
	for( i = 0; i < size; i++ ){
		if( ( !node_array[ i ]->visited ) && ( node_array[ i ]->distance < INFINITY ) ){
			if( !rv ){
				rv = node_array[ i ];
			}else if( node_array[ i ]->distance < rv->distance ){
				rv = node_array[ i ];
			}
		}
	}
	return rv;
}

// Simple walk thru the linked list path to show the shortest path.
void show_path( struct node * end ){
	if( end->back ){
		show_path( end->back );
	}
	//printf( "Node: %s\n", end->name );
  cout << "Node: " << end->name << endl;
}


