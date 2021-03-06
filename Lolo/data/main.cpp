#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

FILE * fin;
FILE * fout;
unsigned char * buffer;
unsigned int offset;
unsigned int i,j,k,total,filesize;
int width;
int Setup();
int write_screens(int num, unsigned int offset);

int main(int argc, char *argv[])
{
    printf("Ripper for Zelda Uzebox\n");
    printf("Only use version Zelda(u) PRG 0!!!\n");
    if(!Setup())
        return 0;
    fprintf(fout,"//////////////////////////////////////\n");
    fprintf(fout,"//Generated by Z Ripper///////////////\n");
    fprintf(fout,"//////////////////////////////////////\n");

	
	offset = 0x1697C+32;
    fprintf(fout,"const uint8_t OWPrimarySquare[] PROGMEM = {\n");
    for(i=0;i<56+8;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    offset = 0x169B4+32;
    fprintf(fout,"const uint8_t OWSecondarySquare[] PROGMEM = {\n");
    for(i=0;i<64;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
  
  	offset = 0;
    fprintf(fout,"const uint16_t OWColumnDirectory[] PROGMEM = {\n");
    unsigned int basectp = buffer[105743+16+offset++];//get low byte of base
    basectp += (buffer[105743+16+offset--]<<8)+16;//get hi byte of base
	
	unsigned int ctp;
	for(i=0;i<16;i++){
    	ctp = buffer[105743+16+offset++];//get low byte
    	ctp += ((buffer[105743+16+offset++])*256)+16;//get hi byte
        ctp -= basectp;
	
		fprintf(fout,"%d,",ctp);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    
    fprintf(fout,"const uint8_t OWColumnData[] PROGMEM = {\n");
    for(i=0;i<16*16*11;i++){
        fprintf(fout,"%d,",buffer[89048+16+i]);
		filesize++;    
		if(++width > 128){
			fprintf(fout,"\n");
			width = 0;
		}
    }
	/*
    for(i=basectp;i<basectp+ctp+(16*11);i++){//for now just grab a bunch of data...should calculate out the last table shorter but...
        fprintf(fout,"%d,",buffer[i]);
		filesize++;    
    }*/
    fprintf(fout,"};\n\n");
  
  	offset = 0;
    fprintf(fout,"const uint8_t SecretsTable[] PROGMEM = {\n");
    for(i=0;i<6;i++){
        fprintf(fout,"%d,",buffer[92534+16+offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    offset = 0;
    fprintf(fout,"const uint8_t OWScreenTable[] PROGMEM = {\n");
	for(j=0;j<16;j++){
	for(i=0;i<16;i++){
        fprintf(fout,"%d,",buffer[87064+16+offset++]);
		filesize++;    
    }
    fprintf(fout,"\n");
}
    fprintf(fout,"};\n\n");
    
        offset = 0;
    fprintf(fout,"const uint8_t StartingLocations[] PROGMEM = {\n");
    for(i=0;i<9;i++){
        fprintf(fout,"%d,",buffer[0+16+offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    

    offset = 0x4000;
    offset += 16;
    unsigned int ttp = buffer[offset];
    ttp += buffer[offset+1]*256;
    ttp += 16;
	unsigned int textpointers[40];
    fprintf(fout,"const uint16_t TextPointers[] PROGMEM = {\n");
    for(i=0;i<38;i++){
		ctp = buffer[offset++];//LSB
		ctp += buffer[offset++]*256;//MSB
		ctp += 16;
		textpointers[i] = ctp;
		ctp -= ttp;     
	    fprintf(fout,"%d,",ctp);
		filesize++;    
    }
    fprintf(fout,"};\n\n");    

    offset = 0x404C;
    offset += 16;
    fprintf(fout,"const uint8_t NPCText[] PROGMEM = {\n");
    for(i=0;i<38;i++){
    	offset = textpointers[i];
    	do{
        	fprintf(fout,"%d,",buffer[offset]);
			filesize++;
		}while(!(buffer[offset++] & 0b10000000));
    }
    fprintf(fout,"};\n\n");
    
    offset = 0x6D97;
    offset += 16;
    fprintf(fout,"const uint8_t LostWoodsPath[] PROGMEM = {\n");// (01 = East, 02 = West, 04 = South, 08 = North)
    for(i=0;i<4;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    offset = 0x6D97;
    offset += 16;
    fprintf(fout,"const uint8_t LostHillsPath[] PROGMEM = {\n");// (01 = East, 02 = West, 04 = South, 08 = North)
    for(i=0;i<3;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    

    offset = 0x19334;
    offset += 16;
    fprintf(fout,"const uint8_t OverworldShortcuts[] PROGMEM = {\n");
    for(i=0;i<4;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    
    offset = 0x7596;
    offset += 16;
    fprintf(fout,"const uint8_t SwordDamage[] PROGMEM = {\n");
    for(i=0;i<3;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    

    
    offset = 0x18580;
    offset += 16;
    fprintf(fout,"const uint8_t OverworldMap[] PROGMEM = {\n");
    for(i=0;i<(8*16);i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    


    offset = 0x18627;
    offset += 16;
    fprintf(fout,"const uint8_t StoreItems[] PROGMEM = {\n");
    for(i=0;i<12;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    
    offset = 0x18663;
    offset += 16;
    fprintf(fout,"const uint8_t StorePrices[] PROGMEM = {\n");
    for(i=0;i<12;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    
    offset = 91928+16;
    fprintf(fout,"const uint8_t UWSquareTable[] PROGMEM = {\n");
    for(i=0;i<8;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
      	offset = 0;
    fprintf(fout,"const uint16_t UWColumnDirectory[] PROGMEM = {\n");
    basectp = buffer[91908+16+offset++];//get low byte of base
    basectp += (buffer[91908+16+offset--]<<8)+16;//get hi byte of base
	

	for(i=0;i<16;i++){
    	ctp = buffer[91908+16+offset++];//get low byte
    	ctp += ((buffer[91908+16+offset++])*256)+16;//get hi byte
        ctp -= basectp;
	
		fprintf(fout,"%d,",ctp);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    
    fprintf(fout,"const uint8_t UWColumnData[] PROGMEM = {\n");
    for(i=0;i<16*NUMUNDERWORLDCOLUMNTABLES*11;i++){
        fprintf(fout,"%d,",buffer[90838+16+i]);
		filesize++;    
    	if(++width > 128){
			fprintf(fout,"\n");
			width = 0;
		}
	}
    fprintf(fout,"};\n\n");
 
 
     offset = 90334+16;
    fprintf(fout,"const uint8_t UWScreenTable[] PROGMEM = {\n");
    for(i=0;i<64*12;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");   
    
    
    //018790 is color??
      offset = 0x18890;
    fprintf(fout,"const uint8_t UWLevelScreens[] PROGMEM = {\n");
    for(i=0;i<8*8;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 
    
    
      offset = 100096+16;
    fprintf(fout,"const uint8_t UWDoorDataNS[] PROGMEM = {\n");//first 128 bytes from block 0(levels 1-6), second from block 1(levels 7-9), next 256 are for second quest
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
      offset = 100864+16;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
      offset = 101632+16;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
	}
      offset = 102400+16;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 

      offset = 100096+16+128;//WE door data is 128 bytes from data block start or immediately after NS tables
    fprintf(fout,"const uint8_t UWDoorDataWE[] PROGMEM = {\n");//first 128 bytes from block 0(levels 1-6), second from block 1(levels 7-9), next 256 are for second quest
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
      offset = 100864+16+128;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
      offset = 101632+16+128;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
	}
      offset = 102400+16+128;
    for(i=0;i<128;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 
    
    //1083392 first byte for enemy
    
    fprintf(fout,"#define LOSTWOODSLOCATION %d\n",buffer[0x6DA7+16]);
    fprintf(fout,"#define LOSTHILLSLOCATION %d\n",buffer[0x6DC9+16]);
    fprintf(fout,"#define LOSTWOODSEXIT %d\n",buffer[0x6DC0+16]);
    fprintf(fout,"#define LOSTHILLSEXIT %d\n",buffer[0x6DD2+16]);
    
    fprintf(fout,"#define BLUEMEDICINEPRICE %d\n",buffer[0x1865A+16]);
    fprintf(fout,"#define REDMEDECINEPRICE %d\n",buffer[0x1865C+16]);
    
    fprintf(fout,"#define OVERWORLDSTARTSCREEN %d\n",buffer[0x1932F+16]);
   // fprintf(fout,"#define OVERWORLDSTARTHPOS %d\n,",buffer[0x+16]);
    fprintf(fout,"#define OVERWORLDSTARTVPOS %d\n",buffer[0x19328+16]);

    fprintf(fout,"#define BOMBS 0\n");
    fprintf(fout,"#define WOODSWORD 1\n");
    fprintf(fout,"#define WHITESWORD 2\n");
    fprintf(fout,"#define MAGICSWORD 3\n");
    fprintf(fout,"#define BAIT 4\n");
    fprintf(fout,"#define RECORDER 5\n");
    fprintf(fout,"#define BLUECANDLE 6\n");
    fprintf(fout,"#define REDCANDLE 7\n");
    fprintf(fout,"#define WOODENARROW 8\n");
    fprintf(fout,"#define SILVERARROW 9\n");
    fprintf(fout,"#define BOW 10\n");
    fprintf(fout,"#define MAGICKEY 11\n");
    fprintf(fout,"#define RAFT 12\n");
    fprintf(fout,"#define STEPLADDER 13\n");
    fprintf(fout,"#define GLITCHMOBLIN 14\n");
    fprintf(fout,"#define FIVERUPEE 15\n");
    fprintf(fout,"#define MAGICWAND 16\n");
    fprintf(fout,"#define MAGICBOOK 17\n");
    fprintf(fout,"#define BLUERING 18\n");
    fprintf(fout,"#define REDRING 19\n");
    fprintf(fout,"#define POWERBRACELET 20\n");
    fprintf(fout,"#define LETTER 21\n");
    fprintf(fout,"#define COMPASS 22\n");
    fprintf(fout,"#define MAP 23\n");
    fprintf(fout,"#define RUPEE 24\n");
    fprintf(fout,"#define KEY 25\n");
    fprintf(fout,"#define HEARTCONTAINER 26\n");
    fprintf(fout,"#define TRIFORCEPIECE 27\n");
    fprintf(fout,"#define MAGICSHIELD 28\n");
    fprintf(fout,"#define BOOMERANG 29\n");
    fprintf(fout,"#define MAGICBOOMERANG 30\n");
    fprintf(fout,"#define BLUEPOTION 31\n");
    fprintf(fout,"#define REDPOTION 32\n");
    fprintf(fout,"#define CLOCK 33\n");
    fprintf(fout,"#define HEART 34\n");
    fprintf(fout,"#define FAIRY 35\n");
    //fprintf(fout,"#define UNUSED1 36\n,");
    fprintf(fout,"#define NOTHING 63\n");
    
    fprintf(fout,"\n\n\n");
    
    offset = 0x18167;
    offset += 16;
    fprintf(fout,"const uint8_t SecondQuestChanges[] PROGMEM = {\n");//7 places to change in 2nd quest
    for(i=0;i<11;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
    
    offset = 0x1EF66;
    offset += 16;
    fprintf(fout,"const uint8_t RecorderSecretScreens[] PROGMEM = {\n");//11 places recorder unveils secrets
    for(i=0;i<3;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n");
	


    
    
    fprintf(fout,"};\n\n");
		
	
	
	
	fprintf(fout,"#define TOTALDATASIZE %u",filesize);
    fclose(fout);
    fout = fopen("graphics.txt","w");
   // WriteGraphics();
    fclose(fout);
    
    
    //get the PCM data
    fout = fopen("dpcm.txt","w");
	
	  offset = 0xC000;
    for(i=0;i<0xC740;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 
	
	  offset = 0xC800;
    for(i=0;i<0x1E0;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 
	

	  offset = 0xCA00;
    for(i=0;i<0x900;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 

	  offset = 0xD300;
    for(i=0;i<0xCE0;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 
    
	  offset = 0xE000;
    for(i=0;i<0x420;i++){
        fprintf(fout,"%d,",buffer[offset++]);
		filesize++;    
    }
    fprintf(fout,"};\n\n"); 

	fclose(fout);
    
    return 1;
}

int write_screens(int num, unsigned int offset){
    int j,k,total=0;
    for(j=0;j<num;j++){
        for(k=0;k<48;k++){
            fprintf(fout,"%d,",buffer[offset++]);
        }
        fprintf(fout,"//screen %d\n",j);
        total += 48;
    }
    return total;   
}


int WriteGraphics(){
    fprintf(fout,"const uint8_t PalletData[] PROGMEM = {//TO BE MADE MANUALLY... :(  };\n\n");
    //offset is first tile in name table, followed by a tile that doesnt go in name table
    //followed by one that does and so on.
    unsigned char tbuffer[16];
    unsigned char wbuffer[16];
    for(i=0;i<NUMLEVELS;i++){
        offset = NameTableOffsets[i];
        for(j=0;j<208;j++){
            //ROUGHLY 208 TILES WE WOULD WANT TO IMPORT, TODO!!!
            for(k=0;k<16;k++)//each tile is 2 8bit planes so 16 bytes
                tbuffer[k] = buffer[offset++];
            

            //1 tile we use followed by one tile not in the name table!
            offset += 16;
        }
    }
    return 0;    
}

int Setup(){
    fin = fopen("zelda.nes","rb");
    if(!fin){
        printf("Could not open zelda.nes, place this file in directory.\n");         
        return 0;
    }
    fout = fopen("zdat.txt","w");
    if(!fout){
        printf("Could not open zdata.inc for writing.\n");
        return 0;
    }
    //find the size
    fseek(fin, 0, SEEK_END);
    long int lSize = ftell(fin);
    rewind(fin);

    buffer = (unsigned char*)malloc(sizeof(unsigned char)*lSize);
    if(buffer == NULL){
        printf("Failed to allocate buffer.\n");
        return 0;
    }
    
    size_t result = fread (buffer,1,lSize,fin);
    if(lSize != result){
        printf("Read error %d is not %d.\n",result,lSize);
        return 0;    
    }
    offset = 0;
    fclose(fin);
    return 1;   
}

