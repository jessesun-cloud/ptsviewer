#include "src/ptsviewer.h"
#include <cmath>
#ifdef SUPPORT_PTX
#include <ptxreader.hpp>
#endif

extern "C"
void _loadPTX(cloud_t* pCloud, const char* FilePath)
{
#ifdef SUPPORT_PTX
  PtxReader reader(FilePath);
  vector< shared_ptr<ScanNode>> nodes;
  reader.LoadScan(1, nodes);
  cloud_t* cloud = pCloud;
  memset(cloud, 0, sizeof(cloud_t));
  if (nodes.size() == 0)
  { return ; }
  size_t size = 0;
  bool hasColor = false;
  for (int i = 0; i < nodes.size(); i++)
  {
    vector<float>& pts = nodes[i]->Position();
    size += pts.size() / 3;
    hasColor = nodes[i]->Color().size();
  }
  cloud->vertices = (float*)malloc(sizeof(float) * size * 3);
  if (hasColor)
  { cloud->colors = (uint8_t*)malloc(3 * size); }
  cloud->pointcount = (int)size;
  size = 0;
  size_t _pointsCount = 0;
  for (int i = 0; i < nodes.size(); i++)
  {
    vector<float>& pts = nodes[i]->Position();
    size_t np = pts.size() / 3;
    size = _pointsCount;
    _pointsCount += np;
    memcpy(cloud->vertices + size * 3, pts.data(), sizeof(float) * 3 * np);
    if (hasColor)
    { memcpy(cloud->colors + size * 3, nodes[i]->Color().data(), 3 * np); }
    nodes[i]->GetBox((double*)&cloud->boundingbox.min,
                     (double*)&cloud->boundingbox.max);
  }
#endif
}
