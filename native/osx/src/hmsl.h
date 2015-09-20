//
//  hmsl.h
//  HMSL-OSX
//
//  Created by Andrew C Smith on 1/27/15.
//  Copyright (c) 2015 Andrew C Smith. All rights reserved.
//

#ifndef HMSL_OSX_hmsl_h
#define HMSL_OSX_hmsl_h

#include <CoreMIDI/CoreMIDI.h>
#include <CoreGraphics/CGContext.h>

#ifndef PF_DEFAULT_DICTIONARY
#define PF_DEFAULT_DICTIONARY "pforth.dic"
#endif

#ifndef HMSL_COLORS
#define HMSL_COLORS

#define HMSL_COLORS_SIZE 16
#define HMSL_COLORS_MASK 0b00001111

// Colors taken from the Macintosh II color palette, System 4.1
// https://en.wikipedia.org/wiki/List_of_software_palettes#Apple_Macintosh_default_16-color_palette
static const double hmslWhite[4] = {1.0, 1.0, 1.0, 1.0};
static const double hmslBlack[4] = {0.0, 0.0, 0.0, 1.0};
static const double hmslRed[4] = {0.867, 0.0, 0.0, 1.0};
static const double hmslBlue[4] = {0.0, 0.0, 0.8, 1.0};
static const double hmslCyan[4] = {0.0, 0.6, 1.0, 1.0};
static const double hmslMagenta[4] = {1.0, 0.0, 0.6, 1.0};
static const double hmslYellow[4] = {1.0, 1.0, 0.0, 1.0};
static const double hmslOrange[4] = {1.0, 0.4, 0.0, 1.0};
static const double hmslPurple[4] = {0.2, 0.0, 0.6, 1.0};
static const double hmslGreen[4] = {0.0, 0.667, 0.0, 1.0};
static const double hmslDarkGreen[4] = {0.0, 0.4, 0.0, 1.0};
static const double hmslBrown[4] = {0.4, 0.2, 0.0, 1.0};
static const double hmslTan[4] = {0.6, 0.4, 0.2, 1.0};
static const double hmslLightGrey[4] = {0.733, 0.733, 0.733, 1.0};
static const double hmslMediumGrey[4] = {0.533, 0.533, 0.533, 1.0};
static const double hmslDarkGrey[4] = {0.267, 0.267, 0.267, 1.0};

static const double* hmslColors[HMSL_COLORS_SIZE] = {
  hmslWhite, hmslBlack, hmslOrange, hmslRed, hmslMagenta, hmslPurple,
  hmslBlue, hmslCyan, hmslGreen, hmslDarkGreen, hmslBrown, hmslTan,
  hmslLightGrey, hmslMediumGrey, hmslDarkGrey, hmslBlack
};

#endif

#define EVENT_BUFFER_SIZE 256
#define EVENT_BUFFER_MASK 0b11111111

/*
 * Global structs
 */

typedef struct HMSLPoint {
  int32_t x;
  int32_t y;
} HMSLPoint;

typedef struct HMSLSize {
  int32_t w;
  int32_t h;
} HMSLSize;

typedef struct HMSLRect {
  HMSLPoint origin;
  HMSLSize size;
} HMSLRect;

enum HMSLColor {
  WHITE,
  BLACK,
  RED,
  GREEN,
  BLUE,
  CYAN,
  MAGENTA,
  YELLOW
};

typedef struct HMSLContext {
  HMSLPoint currentPoint;
  HMSLPoint mouseEvent;
  enum HMSLColor color;
  enum HMSLEventID *events;
  uint32_t events_read_loc;
  uint32_t events_write_loc;
} hmslContext;

typedef struct HMSLWindow {
  short rect_top;
  short rect_left;
  short rect_bottom;
  short rect_right;
  long title;
} hmslWindow;

enum HMSLEventID {
  EV_NULL,
  EV_MOUSE_DOWN,
  EV_MOUSE_UP,
  EV_MOUSE_MOVE,
  EV_MENU_PICK,
  EV_CLOSE_WINDOW,
  EV_REFRESH,
  EV_KEY
} anHMSLEventID;

/*
 * global variables
 */


hmslContext gHMSLContext;
CGContextRef drawingContext;

/*
 * hmsl_gui.m
 */

int32_t hostInit( void );
void hostTerm( void );
uint32_t hostOpenWindow( hmslWindow *window );
void hostCloseWindow( uint32_t window );
void hostSetCurrentWindow( uint32_t window );
void hostDrawLineTo( int32_t x, int32_t y );
void hostMoveTo( int32_t x, int32_t y );
void hostDrawText( uint32_t address, int32_t count );
uint32_t hostGetTextLength( uint32_t addr, int32_t count );
void hostFillRectangle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void hostSetColor( int32_t color );
void hostSetBackgroundColor( int32_t color );
void hostSetDrawingMode( int32_t mode );
void hostSetFont( int32_t font );
void hostSetTextSize( int32_t size );
void hostGetMouse( uint32_t x, uint32_t y);
int32_t hostGetEvent( int32_t timeout );

/*
 * communication with the obj-c layer
 */

void hmslAddEvent( enum HMSLEventID );
enum HMSLEventID hmslGetEvent( void );
char* nullTermString( const char*, int32_t );
void hmslDrawLine( HMSLPoint start, HMSLPoint end );
void hmslSetCurrentWindow( uint32_t );
void hmslCloseWindow( uint32_t );
uint32_t hmslOpenWindow( const char* title, short x, short y, short w, short h );
void hmslFillRectangle( HMSLRect rect );
void hmslDrawText( const char*, int32_t, HMSLPoint );
uint32_t hmslGetTextLength( const char*, int32_t );
void hmslSetDrawingColor( CGContextRef, const double* );
void hmslSetBackgroundColor( const double* );
void hmslSetTextSize( int32_t );

/* 
 * hmsl_midi.m
 */

void midiSourceProc(MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon);
int hostMIDI_Init();
void hostMIDI_Term( void );
int hostMIDI_Write( unsigned char *addr, int count, int vtime );
int hostMIDI_Recv( void );
int hostClock_QueryTime( void );
int hostClock_QueryRate( void );
void hostSleep( int msec );

int getMainScreenRefreshRate( void );

#endif
