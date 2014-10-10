#ifndef __CHIP_8_CORE__
#define __CHIP_8_CORE__

class Chip8 {

public:
  Chip8();
  ~Chip8();

  void initialize();

  bool load_prog( char* file_name );

private:
  unsigned char *memory;  // The emulator's memory (4kb)
  unsigned char *V;       // General registers (16)
                          // VF is the 'carry flag'
  unsigned short I;       // Index register
  unsigned short pc;      // Program counter
  unsigned short opcode;  // The current opcode

  unsigned char *gfx;     // The graphics area (64x32)

  unsigned char delay_t;  // Delay timer
  unsigned char sound_t;  // Sound timer (buzzer)

  unsigned short *stack;  // 16-level stack
  unsigned short sp;      // Stack pointer

  unsigned char *keys;    // 16 keys (hex input)

};

#endif //__CHIP_8_CORE__
