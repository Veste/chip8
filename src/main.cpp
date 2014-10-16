#include <cstdio>
#include <cstring>

#include "Chip8.h"


bool load_file( ) {
  char f_name[64];
  printf( "Type file: " );
  scanf( " %63s", f_name );

  printf( "\n%s\n", f_name );

  return false;
}


int main ( int argc, char *argv[] ) {

  char command = '\0';

  while ( command != 'x' ) {

    printf( "Choose an option:\n" );
    printf( "     load a file   (l)\n" );
#ifdef _DEBUG
    if ( file_loaded ) {
      printf( "     print file    (p)\n" );
    }
#endif //_DEBUG
    printf( "     exit          (x)\n" );

    scanf( " %c", &command );

    bool file_loaded = false;

    switch ( command ) {
      case 'l':
        file_loaded = load_file( );
        break;
#ifdef _DEBUG
      case 'p':
        if ( file_loaded ) {
          print_file( );
        }
        break;
#endif //_DEBUG
      default:
        break;
    }

    printf( "\n" );
  }

}
