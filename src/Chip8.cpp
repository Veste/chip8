#include "Chip8.h"
#include <cstdio>
#include <algorithm>

#define FONTSET_SIZE 80
// Characters are 4 wide, 5 tall
unsigned char chip8_fontset[FONTSET_SIZE] = 
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#define MEMORY_SIZE 4096
#define REGISTERS 16
#define GFX_SIZE (64*32)
#define STACK_SIZE 16
#define KEYS_SIZE 16

Chip8::Chip8() {
  memory = new unsigned char[MEMORY_SIZE];

  V = new unsigned char[REGISTERS];

  gfx = new unsigned char[GFX_SIZE];

  stack = new unsigned short[STACK_SIZE];

  keys = new unsigned char[KEYS_SIZE];
}

Chip8::~Chip8() {
  delete[] memory;
  delete[] V;
  delete[] gfx;
  delete[] stack;
  delete[] keys;
}

void Chip8::initialize() {

  pc        = 0x200;     // Programs start at 0x200
  opcode    = 0;
  I         = 0;
  sp        = 0;

  std::fill( gfx, gfx + GFX_SIZE, 0 );
  std::fill( stack, stack + STACK_SIZE, 0 );
  std::fill( V, V + REGISTERS, 0 );
  std::fill( memory, memory + MEMORY_SIZE, 0 );

  for ( int i = 0; i < FONTSET_SIZE; i++ ) {
    memory[i] = chip8_fontset[i];
  }

  delay_t = 0;
  sound_t = 0;
}

// Bytes of memory available for the program
#define PROGRAM_MEMORY 3584

bool Chip8::load_prog( char* file_name ) {

  FILE *prog;
  prog = fopen( file_name, "rb" );
  if ( prog == NULL ) {
    // TODO: File open error message here
    return false;
  } 

  fseek( prog, 0, SEEK_END );
  long file_size = ftell( prog );
  rewind( prog );

  // TODO: Ensure that program fits into memory

  unsigned char *buffer;
  buffer = (unsigned char*) malloc(sizeof(unsigned char)*file_size);
  if ( buffer == NULL ) {
    // TODO: Memory error message
    fclose( prog );
    return false;
  }

  size_t result = fread( buffer, 1, file_size, prog );
  fclose( prog );
  if ( result != file_size ) {
    // TODO: Reading error message
    return false;
  }

  for ( int i = 0; i < file_size; i++ ) {
    // TODO: Make 512 a define
    memory[i + 512] = buffer[i];
  }

  free( buffer );
  return true;
}


// Debugging function definitions
#ifdef _DEBUG
void Chip8::print_memory() {

  const int cols = 4;
  // There are 2 bytes in every element of the print
  const int rows = MEMORY_SIZE / (cols + cols);

  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < cols; j++ ) {
      int cell_i = i + (rows * j);
      if ( (cell_i+1) < MEMORY_SIZE ) {
        printf( "%2x %2x\t", 
          memory[cell_i], 
          memory[cell_i+1]);
      }
    }
    printf( "\n" );
  }

}
#endif
