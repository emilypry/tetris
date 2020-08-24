#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// Pin definitions
#define scl 15
#define sda 16
#define res 9 
#define dc 8
#define cs 10

#define up  7
#define down 6
#define left 5 
#define right 4
#define A 3
#define B 2

// u16 color definitions
#define c0  0x0000  //black
#define c1  0xF020  //red
#define c2  0x2FF0 //sea foam
#define c3  0xFE60  //gold
#define c4  0xCE9A  //grayblue
#define c5  0x0AEB  //turquoise
#define c6  0xEAE1  //orange
#define c7  0xC0A8 // magenta
#define c8  0xE76E  //beige

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, res);

const int r = 3;  // Height/width of each grid box in pixels. 

int grid[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row0: 0-15
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row1: 16-31
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row2: 32-47
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row3: 48-63
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row4: 64-79
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row5: 80-95
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row6: 96-111
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row7: 112-127
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row8: 128-143
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row9: 144-159
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row10: 160-175
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row11: 176-191
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row12: 192-207
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row13: 208-223
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row14: 224-239
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row15: 240-255
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    //row16: 256-271
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    //row17: 272-287

int points; // The points for a given game
int level; // The current level for a given game

class Toy{
  private:
    String type;
    int gx; // x coordinate in the grid - 0-15; (gx*r)+r = actual x
    int gy; // y coordinate in the grid - 0-18; (gy*r)+r = actual y
    int pos;
  public:
    Toy(String type, int gx, int gy, int pos){
      this->type = type;
      this->gx = gx;
      this->gy = gy;
      this->pos = pos;
    }

    void draw(bool color){
      // True if want color, false if want to erase.
      uint16_t c = c0;

      if(type=="L"){
        if(color==true){
          c = c1;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*3, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*3), r, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r*3, r, c);
          display.fillRect((gx*r)+r, (gy*r)+(r*2), r, r, c);
        }else if(pos==3){
          display.fillRect((gx*r)+r, (gy*r)+r, r*2, r, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*2), r, r*2, c);
        }else if(pos==4){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r, c);
          display.fillRect((gx*r)+(r*-1), (gy*r)+(r*2), r*3, r, c);
        }  
         
      }else if(type=="BL"){
        if(color==true){
          c = c2;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*3, c);
          display.fillRect((gx*r), (gy*r)+(r*3), r, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r, c);
          display.fillRect((gx*r)+r, (gy*r)+(r*2), r*3, r, c);
        }else if(pos==3){
          display.fillRect((gx*r)+r, (gy*r)+r, r*2, r, c);
          display.fillRect((gx*r)+r, (gy*r)+(r*2), r, r*2, c);
        }else if(pos==4){
          display.fillRect((gx*r)+r, (gy*r)+r, r*3, r, c);
          display.fillRect((gx*r)+(r*3), (gy*r)+(r*2), r, r, c);
        }
         
      }else if(type=="stick"){
        if(color==true){
          c = c3;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r*4, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*4, c);
        }
        
      }else if(type=="square"){
        if(color==true){
          c = c4;
        }
        display.fillRect((gx*r)+r, (gy*r)+r, r*2, r*2, c);
        
      }else if(type=="S"){
        if(color==true){
          c = c5;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r*2, r, c);
          display.fillRect((gx*r), (gy*r)+(r*2), r*2, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*2, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*2), r, r*2, c);
        }
        
      }else if(type=="BS"){
        if(color==true){
          c = c6;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r*2, r, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*2), r*2, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*2, c);
          display.fillRect((gx*r), (gy*r)+(r*2), r, r*2, c);          
        }

      }else if(type=="T"){
        if(color==true){
          c = c7;
        }
        if(pos==1){
          display.fillRect((gx*r)+r, (gy*r)+r, r*3, r, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*2), r, r, c);
        }else if(pos==2){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*3, c);
          display.fillRect((gx*r), (gy*r)+(r*2), r, r, c);
        }else if(pos==3){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r, c);
          display.fillRect((gx*r), (gy*r)+(r*2), r*3, r, c);
        }else if(pos==4){
          display.fillRect((gx*r)+r, (gy*r)+r, r, r*3, c);
          display.fillRect((gx*r)+(r*2), (gy*r)+(r*2), r, r, c);
        }
      }
    }

    void update_grid(int num){
      // Updates grid with a new shape. 1 to add, 0 to delete.
      for(int i=0; i<18; i++){
        if(gy==i){  // If that's the right row (as defined by gy), then 
          if(type=="L"){  // make the x coord, in that row, 1 or 0.
            if(pos==1){
              grid[(i*16)+gx] = num; 
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              grid[((i+2)*16)+(gx+1)] = num;
              break;             
            }else if(pos==2){
              grid[(i*16)+gx] = num; 
              grid[(i*16)+(gx+1)] = num;
              grid[(i*16)+(gx+2)] = num;
              grid[((i+1)*16)+gx] = num;
              break;              
            }else if(pos==3){
              grid[(i*16)+gx] = num; 
              grid[(i*16)+(gx+1)] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              grid[((i+2)*16)+(gx+1)] = num;
              break;              
            }else if(pos==4){
              grid[(i*16)+gx] = num; 
              grid[((i+1)*16)+(gx-2)] = num;
              grid[((i+1)*16)+(gx-1)] = num;
              grid[((i+1)*16)+gx] = num;
              break;               
            }
            
          }else if(type=="BL"){
            if(pos==1){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              grid[((i+2)*16)+(gx-1)] = num;
              break;              
            }else if(pos==2){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              grid[((i+1)*16)+(gx+2)] = num;
              break;              
            }else if(pos==3){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              break;              
            }else if(pos==4){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[(i*16)+(gx+2)] = num;
              grid[((i+1)*16)+(gx+2)] = num;
              break;              
            }

          }else if(type=="stick"){
            if(pos==1){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[(i*16)+(gx+2)] = num;
              grid[(i*16)+(gx+3)] = num;
              break;              
            }else if(pos==2){
              grid[(i*16)+gx] = num; 
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              grid[((i+3)*16)+gx] = num;
              break;           
            }
          
          }else if(type=="square"){
            grid[(i*16)+gx] = num;
            grid[(i*16)+(gx+1)] = num;
            grid[((i+1)*16)+gx] = num;
            grid[((i+1)*16)+(gx+1)] = num;
            break;  
                      
          }else if(type=="S"){
            if(pos==1){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[((i+1)*16)+(gx-1)] = num;
              grid[((i+1)*16)+gx] = num;
              break;              
            }else if(pos==2){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              grid[((i+2)*16)+(gx+1)] = num;
              break;             
            }
            
          }else if(type=="BS"){
            if(pos==1){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              grid[((i+1)*16)+(gx+2)] = num;
              break;              
            }else if(pos==2){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+1)*16)+(gx-1)] = num;
              grid[((i+2)*16)+(gx-1)] = num;
              break;              
            }
            
          }else if(type=="T"){
            if(pos==1){
              grid[(i*16)+gx] = num;
              grid[(i*16)+(gx+1)] = num;
              grid[(i*16)+(gx+2)] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              break;              
            }else if(pos==2){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              grid[((i+1)*16)+(gx-1)] = num;
              break;              
            }else if(pos==3){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+(gx-1)] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              break;             
            }else if(pos==4){
              grid[(i*16)+gx] = num;
              grid[((i+1)*16)+gx] = num;
              grid[((i+2)*16)+gx] = num;
              grid[((i+1)*16)+(gx+1)] = num;
              break;             
            }
          } 
        }
      }
    } 

    bool hit_below(){
      // Checks if any block sticking out horizontally in toy has another block below
      // it, or the bottom of the container. Returns true if so.
      for(int i=0; i<18; i++){
        if(gy==i){
          if(type=="L"){
            if(pos==1){
              if(grid[((i+3)*16)+gx] == 1 ||        // Underneath bottom left block
              grid[((i+3)*16)+(gx+1)] == 1 ||       // Underneath bottom right block
              gy+3 == 18){                          // Bottom of container
                return true;
              }
            }else if(pos==2){
              if(grid[((i+1)*16)+(gx+1)] == 1 ||    // Underneath top middle block
              grid[((i+1)*16)+(gx+2)] == 1 ||       // Underneath top right block
              grid[((i+2)*16)+gx] == 1 ||           // Underneath bottom block
              gy+2 == 18){                          // Bottom of container
                return true;
              }         
            }else if(pos==3){
              if(grid[((i+1)*16)+gx] == 1 ||        // Underneath top left block
              grid[((i+3)*16)+(gx+1)] == 1 ||       // Underneath bottom block 
              gy+3 == 18){                          // Bottom of container
                return true;
              }             
            }else if(pos==4){
              if(grid[((i+2)*16)+(gx-2)] == 1 ||    // Underneath bottom left block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Underneath bottom middle block
              grid[((i+2)*16)+gx] == 1 ||           // Underneath bottom right block
              gy+2 == 18){                          // Bottom of container
                return true;                           
              }            
            }

          }else if(type=="BL"){
            if(pos==1){
              if(grid[((i+3)*16)+gx] == 1 ||        // Underneath bottom right block
              grid[((i+3)*16)+(gx-1)] == 1 ||       // Underneath bottom left block
              gy+3 == 18){                          // Bottom of container
                return true;
              }        
            }else if(pos==2){
              if(grid[((i+2)*16)+gx] == 1 ||        // Underneath bottom left block
              grid[((i+2)*16)+(gx+1)] == 1 ||       // Underneath bottom middle block
              grid[((i+2)*16)+(gx+2)] == 1 ||       // Underneath bottom right block
              gy+2 == 18){                          // Bottom of container
                return true;
              }             
            }else if(pos==3){
              if(grid[((i+1)*16)+(gx+1)] == 1 ||    // Underneath top right block
              grid[((i+3)*16)+gx] == 1 ||           // Underneath bottom block
              gy+3 == 18){                          // Bottom of container
                return true;
              }           
            }else if(pos==4){
              if(grid[((i+1)*16)+gx] == 1 ||        // Underneath top left block
              grid[((i+1)*16)+(gx+1)] == 1 ||       // Underneath top middle block
              grid[((i+2)*16)+(gx+2)] == 1 ||       // Underneath bottom block
              gy+2 == 18){                          // Bottom of container
                return true;
              }             
            }
            
          }else if(type=="stick"){
            if(pos==1){
              if(grid[((i+1)*16)+gx] == 1 ||        // Underneath leftmost block
              grid[((i+1)*16)+(gx+1)] == 1 ||       // Underneath second block
              grid[((i+1)*16)+(gx+2)] == 1 ||       // Underneath third block
              grid[((i+1)*16)+(gx+3)] == 1 ||       // Underneath rightmost block
              gy+1 == 18){                          // Bottom of container
                return true;
              }           
            }else if(pos==2){
              if(grid[((i+4)*16)+gx] == 1 ||        // Underneath bottom block
              gy+4 == 18){                          // Bottom of container
                return true;
              }             
            }
            
          }else if(type=="square"){
            if(grid[((i+2)*16)+gx] == 1 ||          // Underneath bottom left block
            grid[((i+2)*16)+(gx+1)] == 1 ||         // Underneath bottom right block
            gy+2 == 18){                            // Bottom of container
              return true;
            }
                      
          }else if(type=="S"){
            if(pos==1){
              if(grid[((i+1)*16)+(gx+1)] == 1 ||    // Underneath top right block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Underneath bottom left block
              grid[((i+2)*16)+gx] == 1 ||           // Underneath bottom right block
              gy+2 == 18){                          // Bottom of container
                return true;
              }         
            }else if(pos==2){
              if(grid[((i+2)*16)+gx] == 1 ||        // Underneath mid left block 
              grid[((i+3)*16)+(gx+1)] == 1 ||       // Underneath bottom right block 
              gy+3 == 18){                          // Bottom of container
                return true;
              }          
            }
            
          }else if(type=="BS"){
            if(pos==1){
              if(grid[((i+1)*16)+gx] == 1 ||        // Underneath top left block
              grid[((i+2)*16)+(gx+1)] == 1 ||       // Underneath bottom mid block
              grid[((i+2)*16)+(gx+2)] == 1 ||       // Underneath bottom right block
              gy+2 == 18){                          // Bottom of container
                return true;
              }            
            }else if(pos==2){
              if(grid[((i+2)*16)+gx] == 1 ||        // Underneath mid right block
              grid[((i+3)*16)+(gx-1)] == 1 ||       // Underneath bottom block
              gy+3 == 18){                          // Bottom of container
                return true;
              }        
            }
            
          }else if(type=="T"){
            if(pos==1){
              if(grid[((i+1)*16)+gx] == 1 ||        // Underneath top left block
              grid[((i+1)*16)+(gx+2)] == 1 ||       // Underneath top right block
              grid[((i+2)*16)+(gx+1)] == 1 ||       // Underneath bottom block
              gy+2 == 18){                          // Bottom of container
                return true;
              }            
            }else if(pos==2){
              if(grid[((i+3)*16)+gx] == 1 ||        // Underneath bottom block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Underneath left block
              gy+3 == 18){                          // Bottom of container
                return true;
              }           
            }else if(pos==3){
              if(grid[((i+2)*16)+(gx-1)] == 1 ||    // Underneath bottom left block
              grid[((i+2)*16)+gx] == 1 ||           // Underneath bottom mid block
              grid[((i+2)*16)+(gx+1)] == 1 ||       // Underneath bottom right block
              gy+2 == 18){                          // Bottom of container
                return true;
              }            
            }else if(pos==4){
              if(grid[((i+3)*16)+gx] == 1 ||        // Underneath bottom block
              grid[((i+2)*16)+(gx+1)] == 1 ||       // Underneath right block
              gy+3 == 18){                          // Bottom of container
                return true;
              }          
            }
          }
          return false;   
        }
      }
    } 

    bool hit_left(){
      // Returns true if a toy hits another toy on its left, or the left side of container.
      for(int i=0; i<18; i++){
        if(gy==i){
          if(type=="L"){
            if(pos==1){        
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of middle block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Left of bottom left block    
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of bottom block
              gx == 0){                             // Left side of container
                return true;      
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block 
              grid[((i+1)*16)+gx] == 1 ||           // Left of mid block
              grid[((i+2)*16)+gx] == 1 ||           // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block 
              grid[((i+1)*16)+(gx-3)] == 1 ||       // Left of bottom left block
              gx-2 == 0){                           // Left side of container
                return true;
              }
            }
            
          }else if(type=="BL"){
            if(pos==1){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of mid block
              grid[((i+2)*16)+(gx-2)] == 1 ||       // Left of bottom left block
              gx-1 == 0){                           // Left side of container
                return true;  
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of bottom left block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of mid block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx+1)] == 1 ||       // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }
            
          }else if(type=="stick"){
            if(pos==1){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of left block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block 
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of second block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Left of third block
              grid[((i+3)*16)+(gx-1)] == 1 ||       // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }
            
          }else if(type=="square"){
            if(grid[(i*16)+(gx-1)] == 1 ||          // Left of top left block
            grid[((i+1)*16)+(gx-1)] == 1 ||         // Left of bottom left block
            gx == 0){                               // Left side of container
              return true;
            }
            
          }else if(type=="S"){
            if(pos==1){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-2)] == 1 ||       // Left of bottom left block
              gx-1 == 0){                           // Left side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of mid left block
              grid[((i+2)*16)+gx] == 1 ||           // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }
            
          }else if(type=="BS"){
            if(pos==1){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+gx] == 1 ||           // Left of bottom left block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+(gx-2)] == 1 ||       // Left of mid left block
              grid[((i+2)*16)+(gx-2)] == 1 ||       // Left of bottom block
              gx-1 == 0){                           // Left side of container
                return true;
              }
            }
            
          }else if(type=="T"){
            if(pos==1){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top left block
              grid[((i+1)*16)+gx] == 1 ||           // Left of bottom block
              gx == 0){                             // Left side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Left of bottom block
              grid[((i+1)*16)+(gx-2)] == 1 ||       // Left of mid left block
              gx-1 == 0){                           // Left side of container
                return true;
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block
              grid[((i+1)*16)+(gx-2)] == 1 ||       // Left of bottom left block
              gx-1 == 0){                           // Left side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx-1)] == 1 ||        // Left of top block
              grid[((i+1)*16)+(gx-1)] == 1 ||       // Left of mid block
              grid[((i+2)*16)+(gx-1)] == 1 ||       // Left of bottom block
              gx == 0){                             // Left side of container
                return true;  
              }           
            }
          }
        }
      }
      return false;
    }

    bool hit_right(){
      // Returns true if a toy hits another toy on its right, or the right side of container.
      for(int i=0; i<18; i++){
        if(gy==i){
          if(type=="L"){
            if(pos==1){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of middle block
              grid[((i+2)*16)+(gx+2)] == 1 ||               // Right of bottom right block
              gx+2 == 16){                                  // Right side of container
                return true;      
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+3)] == 1 ||                // Right of right block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of bottom block
              gx+3 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx+2)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+2)] == 1 ||               // Right of mid block
              grid[((i+2)*16)+(gx+2)] == 1 ||               // Right of bottom block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of bottom right block
              gx+1 == 16){                                  // Right side of container
                return true;
              }
            }
            
          }else if(type=="BL"){
            if(pos==1){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of mid block
              grid[((i+2)*16)+(gx+1)] == 1 ||               // Right of bottom right block
              gx+1 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+3)] == 1 ||               // Right of bottom right block
              gx+3 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx+2)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of mid block
              grid[((i+2)*16)+(gx+1)] == 1 ||               // Right of bottom block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx+3)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+3)] == 1 ||               // Right of bottom block
              gx+3 == 16){                                  // Right side of container
                return true;  
              }
            }
            
          }else if(type=="stick"){
            if(pos==1){
              if(grid[(i*16)+(gx+4)] == 1 ||                // Right of right block
              gx+4 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block 
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of second block
              grid[((i+2)*16)+(gx+1)] == 1 ||               // Right of third block
              grid[((i+3)*16)+(gx+1)] == 1 ||               // Right of bottom block
              gx+1 == 16){                                  // Right side of container
                return true;
              }
            }
            
          }else if(type=="square"){
            if(grid[(i*16)+(gx+2)] == 1 ||                  // Right of top right block
            grid[((i+1)*16)+(gx+2)] == 1 ||                 // Right of bottom right block
            gx+2 == 16){                                    // Right side of container
              return true;
            }
            
          }else if(type=="S"){
            if(pos==1){
              if(grid[(i*16)+(gx+2)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of bottom right block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+2)] == 1 ||               // Right of mid right block
              grid[((i+2)*16)+(gx+2)] == 1 ||               // Right of bottom block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }
            
          }else if(type=="BS"){
            if(pos==1){
              if(grid[(i*16)+(gx+2)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+3)] == 1 ||               // Right of bottom right block
              gx+3 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of mid right block
              grid[((i+2)*16)+gx] == 1 ||                   // Right of bottom block
              gx+1 == 16){                                  // Right side of container
                return true;
              }
            }
            
          }else if(type=="T"){
            if(pos==1){
              if(grid[(i*16)+(gx+3)] == 1 ||                // Right of top right block
              grid[((i+1)*16)+(gx+2)] == 1 ||               // Right of bottom block
              gx+3 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==2){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+1)] == 1 ||               // Right of mid right block
              grid[((i+2)*16)+(gx+1)] == 1 ||               // Right of bottom block
              gx+1 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==3){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+1)*16)+(gx+2)] == 1 ||               // Right of bottom right block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }else if(pos==4){
              if(grid[(i*16)+(gx+1)] == 1 ||                // Right of top block
              grid[((i+2)*16)+(gx+1)] == 1 ||               // Right of bottom block
              grid[((i+1)*16)+(gx+2)] == 1 ||               // Right of right block
              gx+2 == 16){                                  // Right side of container
                return true;
              }
            }
          }
        }
      }
      return false;
    }

    void move_down(){
      // Toy moves down by one position (r).
      delay(10);
      draw(false);
      update_grid(0);
  
      gy += 1;
  
      draw(true);
      update_grid(1);
    }

    void move_left(){
      // Moves the toy left by one position (r), if it's not hitting anything on its left.
      if(hit_left()==false){ 
        delay(1);
        draw(false);
        update_grid(0);
  
        gx -= 1;
  
        draw(true);
        update_grid(1);
      }
    }

    void move_right(){
      // Moves the toy right by one position (r), if it's not hitting anything on its right.
      if(hit_right()==false){ 
        delay(1);
        draw(false);
        update_grid(0);
  
        gx += 1;
  
        draw(true);
        update_grid(1);
      }      
    }
    
    void rotate(String dir){
      // Rotates the toy left or right (l, r).
      draw(false);
      update_grid(0);

      delay(20);
      
      if(type=="L" || type=="BL" || type=="T"){       // 4 positions
        if(dir=="r"){     // If turning right (clockwise),
          if(pos==4){
            pos = 1;      // if currently at position 4, turn to 1,
          }else{
            pos += 1;     // and otherwise just add 1 to position.
          }
        }else if(dir=="l"){
          if(pos==1){
            pos = 4;
          }else{
            pos -= 1;
          }
        }
      }else if(type=="stick" || type=="S" || type=="BS"){   // 2 positions
        if(pos==1){
          pos = 2;
        }else if(pos==2){
          pos = 1;
        }
      }else if(type=="square"){                             // 1 position
        pos = 1;
      }

      draw(true);
      update_grid(1);
    }  
};

bool left_click(){
  // Checks if left button does one full click.
  if(digitalRead(left)==LOW){
    delay(40);
    return true;
  }
  return false;
}

bool right_click(){
  // Checks if right button does one full click.
  if(digitalRead(right)==LOW){
    delay(40);
    return true;
  }
  return false;
}

bool down_click(){
  // Checks if down button does one full click.
  if(digitalRead(down)==LOW){
    delay(40);
    return true;
  }
  return false;
}

bool up_click(){
  // Checks if up button does one full click.
  if(digitalRead(up)==LOW){
    delay(40);
    return true;
  }
  return false;
}

bool a_click(){
  // Checks if A button does one full click.
  if(digitalRead(A)==LOW){
    delay(40);
    return true;
  }
  return false;
}

bool b_click(){
  // Checks if B button does one full click.
  if(digitalRead(B)==LOW){
    delay(40);
    return true;
  }
  return false;
}


bool main_menu(){
  // Draws the main menu. Returns true when player hits play.
  display.fillScreen(0);

  
  
  display.setTextSize(2);

  for(int i=0; i<25; i++){
    display.setCursor(12, i);
    display.setTextColor(c3);
    display.print("TETRIS");
    delay(40);

    display.setCursor(12, i);
    display.setTextColor(c0);
    display.print("TETRIS");
    delay(1);
  }

  display.setCursor(12, 26);
  display.setTextColor(c3);
  display.print("TETRIS");
  delay(1000);

  for(int i=0; i<10; i++){
    display.setCursor(12, 26);
    display.setTextColor(c3);
    display.print("TETRIS");
    delay(40);

    display.setCursor(12, 26);
    display.setTextColor(c0);
    display.print("TETRIS");
    delay(40);    
  }

  display.setCursor(12, 26);
  display.setTextColor(c3);
  display.print("TETRIS");
  delay(100);
    
  display.setTextSize(0);
  


  while(true){    
    display.setCursor(r*12, r*18);
    display.setTextColor(c2);
    display.print("PLAY");
    delay(150);

    for(int i=0; i<7; i++){
      if(a_click()==true || b_click()==true){
        return true;
      }
      delay(100);
    }

    display.setCursor(r*12, r*18);
    display.setTextColor(c0);
    display.print("PLAY");

    for(int i=0; i<7; i++){
      if(a_click()==true || b_click()==true){
        return true;
      }
      delay(100);
    }
  } return false;
}

bool pick_level(){
  // Displays the level picker, makes level = the chosen level.
  // Returns true when player has picked level.
  clear_all();
  
  display.fillScreen(0);
  
  display.setCursor(r*6, r*3);
  display.setTextColor(c7);
  display.print("PICK LEVEL");

  display.setTextColor(c2);

  int x = 2;
  int y = 2;
  for(int i=1; i<11; i++){
    if(i < 6){
      display.setCursor(r*x, r*8);
      x += 6;
    }else{
      display.setCursor(r*y, r*15);
      y += 6;
    }
    display.print(String(i));
  }

  int l_dash = 1;
  draw_level_dash(l_dash, true);
  delay(500);
  
  while(true){
    if((right_click()==true || down_click()==true) && l_dash<10){
      draw_level_dash(l_dash, false); // Delete previous
      l_dash += 1;
      draw_level_dash(l_dash, true);  // Draw current
      delay(150);
    }else if((left_click()==true || up_click()==true) && l_dash>1){
      draw_level_dash(l_dash, false); // Delete previous
      l_dash -= 1;
      draw_level_dash(l_dash, true);  // Draw current
      delay(150);
    }

    if(a_click()==true || b_click()==true){
      level = l_dash;
      return true;
    }
  }
}

bool play(){  
  // Plays one game of Tetris. Stops when toys fill up to the top.
  // Returns true when player chooses to quit or loses
  display.fillScreen(0);
  points = 0;
  int new_level = 0;

  draw_container();
  draw_level(true, true);
  draw_total(true, true);

  while(true){
    if(grid[(7*r)+r]==1){   // If there are toys at the very top of the screen, 
      display.fillScreen(c1);  // end the game.
      display.setCursor(r*9, r*7);
      display.setTextColor(c0);
      display.print("You lost...");

      display.setCursor(r*2, r*13);
      display.print("but you got");
      display.setCursor(r*2, r*16);
      display.print(String(points)+" points");

      delay(8000);
      return true;
    }

    bool pause_and_quit = create_and_drop(); // drop a toy, and quit if user chooses to
    if(pause_and_quit == true){  // If user has chosen to quit, then break from the game.
      return true;
    }
             
    // After toy has landed, see if any rows are filled. If so, drop them and give points.
    int num_rows_dropped = 0;
    for(int row=0; row<18; row++){
      if(check_if_row_full(row)==true){
        drop_full_row(row);
        num_rows_dropped += 1;

        draw_total(false, true);  // Delete previous points
        add_points(num_rows_dropped); // Add new points
        draw_total(true, true);   //Draw new points

        new_level += (num_rows_dropped * 5);

        if(new_level>=30){
          if(level<10){
            draw_level(false, true);
            level += 1;
            draw_level(true, true);

            new_level = 0;
          } 
        }
      }
    }
  }
}

void clear_all(){
  // Resets variables once a game has ended so a new one can start.
  display.fillScreen(0);
  
  for(int i=0; i<18; i++){  // Empty out grid.
    for(int x=0; x<16; x++){
      grid[(i*16)+x] = 0;
    }
  }
  points = 0;
  level = 1;
}


// Functions for main_menu().

// Functions for pick_level().
void draw_level_dash(int x, bool color){
  // Draws the dash to select level, sets the level.
  uint16_t c = c0;
  if(color == true){
    c = c8;
  }

  display.setTextColor(c);

  int a = 2;
  int b = 2;
  for(int i=1; i<11; i++){
    if(i<6){
      if(x==i){
        display.setCursor(r*a, r*11);
        display.print("^");
        break;
      }
      a += 6;
    }else{
      if(x==i){
        display.setCursor(r*b, r*18);
        display.print("^");
        break;
      }
      b += 6;
    }
  }
}



// Functions for play().
bool create_and_drop(){
  // Creates a new toy, drops it, moves it left, right, or down, and rotates it, 
  // on basis of button presses. Ends when the toy lands on top of something.
  // Returns true if user chooses to quit while toy is falling. 
  int n = random(7);
  String type;      // Type of toy
  int start;        // x-coord to drop from 
  if(n==0){
    type = "L";
    start = 7;
  }else if(n==1){
    type = "BL";
    start = 8;
  }else if(n==2){
    type = "stick";
    start = 6;
  }else if(n==3){
    type = "square";
    start = 8;
  }else if(n==4){
    type = "S";
    start = 7;
  }else if(n==5){
    type = "BS";
    start = 8;
  }else{
    type = "T";
    start = 7;
  }

  Toy new_toy = Toy(type, start, 0, 1);

  // Levels, 1-10
  int wait = 1100;
  for(int l_i = 1; l_i<11; l_i++){
    if(level==l_i){
      break;
    }
    wait -= 100;
  }

  new_toy.draw(true);
  new_toy.update_grid(1);
  delay(wait);
  
  while(true){ // Drop a toy down one position, move it, pause/quit
    if(new_toy.hit_below()==true){ // Stop making it move_down() if hit below.
      break;
    }
    
    new_toy.move_down();

    for(int i=0; i<wait/100; i++){
      if(new_toy.hit_below()==true){  // Stop making if move_down() if hit below.
        break;
      }
      
      if(left_click()==true){   // Move left, right, down
        if(new_toy.hit_left()==false){
          new_toy.move_left();
        }
      }else if(right_click()==true){
        if(new_toy.hit_right()==false){
          new_toy.move_right();
        }
      }else if(down_click()==true){
        new_toy.move_down();
      } 
      
      if(a_click()==true){    // Rotate left, right
        new_toy.rotate("l");
      }else if(b_click()==true){
        new_toy.rotate("r");   
      }

      if(up_click()==true){   // Pause it   
        draw_pause(true);
        draw_dash(true);  // Print dash by play to start off
        bool play = false;
        delay(400);
        while(true){
          if(up_click()==true || down_click()==true){
            if(play==true){
              draw_dash(true);  // Print dash by play
              play = false;
            }else{
              draw_dash(false); // Print dash by quit
              play = true;
            }
            delay(200);
          }
          if(a_click() == true || b_click() == true){
            if(play==false){    // If play has become false, go back to playing game
              draw_pause(false);
              draw_dash(false);
              draw_total(true, true);
              draw_level(true, true);
              break;
            }else if(play==true){  // If play has become true, go to main menu
              draw_pause(false);
              draw_dash(false);
              display.fillScreen(0);
              return true;
            }
          }
        }
      }
      delay(100);
    }
  }
  return false;
}

bool check_if_row_full(int row){
  // Returns true if the row is full.
  bool full;
  for(int x=0; x<16; x++){
    if(grid[(row*16)+x] == 0){
      full = false;
      break;
    }
    full = true;
  }
  return full;
}

void drop_full_row(int row){
  // Drops the full row.
  uint16_t recolor[] = {c1, c2, c3, c4, c5, c6, c7};
  int c = 0;
  for(int i=0; i<3; i++){
    for(int i=0; i<16; i++){
      display.fillRect((i*r)+r, (row*r)+r, r, r, recolor[c]);
      delay(20);
    }
    c += 1;
    for(int i=15; i>=0; i--){
      display.fillRect((i*r)+r, (row*r)+r, r, r, recolor[c]);
      delay(20);
    }
    c += 1;
  }

  int new_grid[288];
  int new_grid_ind = 17;

  for(int i=17; i>=0; i--){  // Go through each row of old grid, starting from bottom
    if(i==row){             // For the row we're getting rid of,
      continue;             // skip over it.
    }else{                  // If we're not getting rid of this row, add it to new_grid.
      for(int x=0; x<16; x++){
        new_grid[(new_grid_ind*16)+x] = grid[(i*16)+x];
      }
      new_grid_ind -= 1;
    }   
  }

  // For all remaining rows in new_grid, make them 0s. 
  for(new_grid_ind; new_grid_ind>=0; new_grid_ind--){
    for(int x=0; x<16; x++){
      new_grid[(new_grid_ind*16)+x] = 0;      
    }
  }

  // Make grid new_grid
  for(int i=0; i<18; i++){
    for(int x=0; x<16; x++){
      grid[(i*16)+x] = new_grid[(i*16)+x];
      display.fillRect((x*r)+r, (i*r)+r, r, r, c0);
    }
  }
    
  // Recolor the blocks still on screen.
  for(int i=0; i<18; i++){
    for(int x=0; x<16; x++){
      if(grid[(i*16)+x]==1){
        int num = random(7); 
        display.fillRect((x*r)+r, (i*r)+r, r, r, recolor[num]);
        delay(20);
      }
    }
  }
  delay(200);
}

void add_points(int rows_dropped){
  // Adds, prints, and returns current points.

  // Delete previous total.
  draw_total(false, true);

  int new_points = rows_dropped * 5;
  points += new_points;

  // Flash new_points a few times
  for(int i=0; i<5; i++){
    display.setTextColor(c5);
    display.setTextSize(0);
    display.setCursor(r*23, r*10);
    display.print("+"+String(new_points));    
  
    delay(80);
    
    display.setTextColor(c0);
    display.setCursor(r*23, r*10);
    display.print("+"+String(new_points));

    delay(80);
  }
}



void draw_total(bool color, bool keep_label){
  // Draws the place for total points.
  uint16_t c = c0;
  uint16_t ct = c0;
  if(color==true){
    c = c2;
    ct = c3;
  }
  if(keep_label==true){
    ct = c3;
  }else{
    ct = c0;
  }
  
  display.setTextColor(ct);
  display.setCursor(r*21, r*13);
  display.print("TOTAL");

  display.setTextColor(c);
  display.setCursor(r*21, r*16);
  display.print(String(points));
  
}

void draw_container(){
  display.fillRect(0, 0, r*18, r, c8); // top
  display.fillRect(0, r, r, r*18, c8); //left
  display.fillRect(0, r*19, r*18, r, c8); //bottom
  display.fillRect(r*17, r, r, r*18, c8);  //right
}

void draw_level(bool color, bool keep_label){
  // Draws the place for level.
  uint16_t c = c0;
  uint16_t ct = c0;
  if(color==true){
    c = c2;
    ct = c3;
  }
  if(keep_label==true){
    ct = c3;
  }else{
    ct = c0;
  }
  display.setTextColor(ct);
  display.setCursor(r*21, r*3);
  display.print("LEVEL"); 

  display.setTextColor(c);
  display.setCursor(r*21, r*6);
  display.print(String(level));
}

void draw_pause(bool color){
  // Draws the pause and gives options to continue or quit.
  uint16_t c = c0;
  if(color == true){
    c = c3;
  }

  draw_level(false, false);
  draw_total(false, false);

  display.setCursor(r*21, r*4);
  display.setTextColor(c);
  display.print("PAUSE");

  display.setCursor(r*23, r*8);
  display.print("play");

  display.setCursor(r*23, r*12);
  display.print("quit");

}

void draw_dash(bool play){
  // On pause screen, draws dash by play if true, by quit if false.

  if(play == true){
    display.setCursor(r*21, r*12); // Delete by quit
    display.setTextColor(c0);
    display.print("-");
    
    display.setCursor(r*21, r*8); // Draw by play
    display.setTextColor(c2);
    display.print("-");
  }else{
    display.setCursor(r*21, r*8); // Delete by play
    display.setTextColor(c0);
    display.print("-");   

    display.setCursor(r*21, r*12); // Draw by quit
    display.setTextColor(c2);
    display.print("-");
  }
}


void the_full_game(){
  // Makes the full game play, by looping main menu - pick level - play. 
  while(true){
    bool go_to_pick_level = main_menu();
    
    if(go_to_pick_level == true){
      bool go_to_play = pick_level();
      
      if(go_to_play == true){
        bool go_to_main_menu = play();

        if(go_to_main_menu == true){
          continue;
        }
      }
    }
  }
  
}


void setup() {  
  display.begin();
  display.fillScreen(0);

  pinMode(left, INPUT);
  
  the_full_game();
}

 
void loop(){
}
