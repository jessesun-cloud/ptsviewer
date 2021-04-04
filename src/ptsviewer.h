#pragma once
/*******************************************************************************
 *
 *       Filename:  ptsviewer.h
 *
 *    Description:  OpenGL viewer for pts point cloud files
 *
 *        Created:  06/11/2011 08:42:39 PM
 *       Compiler:  gcc
 *
 *         Author:  Lars Kiesow (lkiesow), lkiesow@uos.de
 *        Company:  Universität Osnabrück
 *
 ******************************************************************************/
#pragma once
#include <stdio.h>
#include <stdint.h>
#ifdef BUILD_LIBRPLY
//#include <libgen.h>
#include <rply.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>
#include <float.h>

#define FILE_FORMAT_NONE 0
#define FILE_FORMAT_UOS  1
#define FILE_FORMAT_PLY  2

/* Functions */
void loadPts(char* ptsfile, size_t idx);
void mouseMoved(int x, int y);
void mousePress(int button, int state, int x, int y);
void drawScene();
void keyPressed(unsigned char key, int x, int y);
void resizeScene(int w, int h);
void init();
int  main(int argc, char** argv);
void printHelp();
uint8_t determineFileFormat(char* filename);

/* Type definitions */
typedef struct
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
} coord3d_t;

typedef struct
{
  coord3d_t min;
  coord3d_t max;
} boundingbox_t;

typedef struct
{
  float*        vertices;
  uint8_t*      colors;
  uint32_t      pointcount;
  int           enabled;
  coord3d_t     trans;
  coord3d_t     rot;
  int           selected;
  char*         name;
  boundingbox_t boundingbox;
} cloud_t;

/* Define viewer modes */

#define VIEWER_MODE_NORMAL  0
#define VIEWER_MODE_SELECT  1
#define VIEWER_MODE_MOVESEL 2
