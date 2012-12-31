# Link

http://fms.komkon.org/GameBoy/Tech/LinkFormat.gif
http://pypi.python.org/pypi/pyserial
http://www.arduino.cc/en/Reference/PortManipulation

# Cool music

:)

Vibrasphere - Erosion (Alter Nature Remix)

# Tetris RE

## Init  (0x29)

ROM0:04C5                 ld      a, $29 ; ')'   
ROM0:04C7                 ld      [SB], a        
ROM0:04C9                 ld      a, $81 ; 'ü'   
ROM0:04CB                 ld      [SC], a        

## Choice music  (28 - 31) 0x1C -> 0x1F

ROM0:0190                 ld      a, [byte_FFCF] 
ROM0:0192                 ld      [SB], a        
ROM0:0194                 ld      hl, $FF02      
ROM0:0197                 ld      [hl], $81 ; 'ü'

## Select OK (0x50)

ROM0:0190                 ld      a, [byte_FFCF] 
ROM0:0192                 ld      [SB], a        

## Select row (0 -> 7)

ROM0:0190                 ld      a, [byte_FFCF] 
ROM0:0192                 ld      [SB], a        

## Start (0x60)

ROM0:0190                 ld      a, [byte_FFCF] 
ROM0:0192                 ld      [SB], a        

## 0x00

ROM0:0828                 xor     a
ROM0:0829                 ld      [byte_C210], a
ROM0:082C                 ld      [byte_FF98], a
ROM0:082E                 ld      [byte_FF9C], a
ROM0:0830                 ld      [byte_FF9B], a
ROM0:0832                 ld      [byte_FFFB], a
ROM0:0834                 ld      [byte_FF9F], a
ROM0:0836                 ld      [byte_FFCC], a
ROM0:0838                 ld      [SB], a       

## 0x29

ROM0:08FB                 ld      a, $29 ; ')'
ROM0:08FD                 ld      [SB], a     
ROM0:08FF                 ld      a, $81 ; 'ü'
ROM0:0901                 ld      [SC], a     

## Sequence 0xC92

ROM0:0913                 ld      hl, $C902   
...
ROM0:091E                 ldi     a, [hl]     
ROM0:091F                 ld      [SB], a     

## 

ROM0:097B                 ld      [byte_FFCC], a  
ROM0:097D                 ld      a, $29 ; ')'    

## Send object (0xFF fois) 0xC300

ROM0:0990                 ld      hl, unk_C300    
ROM0:0993                 ld      b, 0            
ROM0:0995
ROM0:0995 loc_995:                                
ROM0:0995                 xor     a               
ROM0:0996                 ld      [byte_FFCC], a  
ROM0:0998                 ldi     a, [hl]         
ROM0:0998                                         
ROM0:0999                 call    sub_A98         
ROM0:099C                 ld      [SB], a         
ROM0:099E                 ld      a, $81 ; 'ü'    
ROM0:09A0                 ld      [SC], a         
ROM0:09A2
ROM0:09A2 loc_9A2:                                
ROM0:09A2                 ld      a, [byte_FFCC]  
ROM0:09A4                 and     a               
ROM0:09A5                 jr      z, loc_9A2      
ROM0:09A7                 inc     b               
ROM0:09A8                 jr      nz, loc_995     

## Send 0x30 until receive 0x56

ROM0:09AA loc_9AA:                                
ROM0:09AA                 call    sub_A98         
ROM0:09AD                 call    sub_A98         
ROM0:09B0                 xor     a               
ROM0:09B1                 ld      [byte_FFCC], a  
ROM0:09B3                 ld      a, $30 ; '0'    
ROM0:09B5                 ld      [SB], a         
ROM0:09B7                 ld      a, $81 ; 'ü'    
ROM0:09B9                 ld      [SC], a         
ROM0:09BB
ROM0:09BB loc_9BB:                                
ROM0:09BB                 ld      a, [byte_FFCC]  
ROM0:09BD                 and     a               
ROM0:09BE                 jr      z, loc_9BB      
ROM0:09C0                 ld      a, [SB]         
ROM0:09C2                 cp      $56 ; 'V'       
ROM0:09C4                 jr      nz, loc_9AA     

0xAA --> LOSE
0x77 --> FINISH 20 lines