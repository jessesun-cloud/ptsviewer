#pragma once

//#include "scanReader\scanReader.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "iostream"
#define SCANREADER_API 

class SCANREADER_API ImpPointRenderInterface
{
public:
    virtual void DrawPoints(int start, int npt, bool bVariableColor) = 0;
    virtual void AddPoints(int npt, float* pPointWidth, 
      unsigned char *pRgbaColor, float *pPoints, float *pNormals) = 0;
};

class SCANREADER_API ImpVertexBufferRenderBase : public ImpPointRenderInterface
{
protected:
  float* mpWidthBuffer;
  int mPointCount;
  bool mbInit;

public:
    static void Init();
    static bool IsVboAvailable();
    static ImpVertexBufferRenderBase* Create(bool bUseVbo = true);

    virtual ~ImpVertexBufferRenderBase() { }
    ImpVertexBufferRenderBase();
    
    int GetPointCount() { return mPointCount; }
    virtual void AddPoints(int npt, float* pPointWidth,
      unsigned char *pRgbaColor, float *pPoints, float *pNormals) = 0;

    void DrawPoints(int start, int npt,
                 bool bVariableThickness, bool bVariableColor);

    virtual void DrawPoints(int start, int npt, bool bVariableColor) = 0;
    virtual void AddPoints(int npt, float* pPointWidth,
      unsigned char *pRgbaColor, double *pPoints, float *pNormals) {};
};

class SCANREADER_API ImpVertexBufferRender : public  ImpVertexBufferRenderBase
{
  float* mpPointBuffer;
  unsigned char* mpColorBuffer;
  float *mpNormalBuffer;

public:
  ImpVertexBufferRender()
  {
    mpPointBuffer = NULL;
    mpColorBuffer = NULL;
    mpNormalBuffer = NULL;
  }
  virtual void DrawPoints(int start, int npt, bool bVariableColor);
  virtual void AddPoints(int npt, float* pPointWidth,
               unsigned char *pRgbaColor, float *pPoints, float *pNormals);
};

class SCANREADER_API ImpVertexBufferVboRender : public  ImpVertexBufferRenderBase
{
  GLuint mVboId[3];
  bool mbHasColor;
  bool mbHasNormal;
  bool mbDouble;
public:
  ImpVertexBufferVboRender();
  virtual void AddPoints(int npt, float* pPointWidth,
               unsigned char *pRgbaColor, float *pPoints, float *pNormals);
  virtual void DrawPoints(int start, int npt, bool bVariableColor);
  virtual ~ImpVertexBufferVboRender();
  virtual void AddPoints(int npt, float* pPointWidth,
    unsigned char *pRgbaColor, double *pPoints, float *pNormals);
  virtual void AddRgbPoints(int npt, float* pPointWidth,
    unsigned char *pRgbaColor, float *pPoints, float *pNormals);
};
