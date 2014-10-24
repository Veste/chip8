#include <cstdio>
#include <cstring>

#include "Chip8.h"


bool load_file( ) {
  char f_name[64];
  printf( "Type file: " );
  int f_name_len = scanf( " %63s", f_name );

  printf( "\n%s\n", f_name );

  if ( strcmp( f_name, "whoop" ) == 0 ) {
    printf( "File loaded!\n" );
    return true;
  } else {
    printf( "File not loaded.\n" );
    return false;
  }
}


void print_file( ) {

}


int main ( int argc, char *argv[] ) {

  char command = '\0';

  while ( command != 'x' ) {

#ifdef DEBUG
    bool file_loaded = false;
#endif //DEBUG

    printf( "Choose an option:\n" );
    printf( "     load a file   (l)\n" );
#ifdef DEBUG
    if ( file_loaded ) {
      printf( "     print file    (p)\n" );
    }
#endif //DEBUG
    printf( "     exit          (x)\n" );

    int c_len = scanf( " %c", &command );

    switch ( command ) {
      case 'l':
        file_loaded = load_file( );
        break;
#ifdef DEBUG
      case 'p':
        if ( file_loaded ) {
          print_file( );
        }
        break;
#endif //DEBUG
      default:
        break;
    }

    printf( "\n" );
  }

}
