#pragma pack(1)

typedef struct
{
    unsigned char fileMarker1;       /* 'B' */                       
    unsigned char fileMarker2;       /* 'M' */ 
    unsigned int   bfSize;             
    unsigned short unused1;           
    unsigned short unused2;           
    unsigned int   imageDataOffset;  /* Offset to the start of image data */
 }FILEHEADER;

 typedef struct                       
 { 
    unsigned int   biSize;            
    signed int     width;            /* Width of the image */ 
    signed int     height;           /* Height of the image */ 
    unsigned short planes;             
    unsigned short bitPix;             
    unsigned int   biCompression;      
    unsigned int   biSizeImage;        
    int            biXPelsPerMeter;    
    int            biYPelsPerMeter;    
    unsigned int   biClrUsed;          
    unsigned int   biClrImportant;     
 }INFOHEADER;

 #pragma pack()