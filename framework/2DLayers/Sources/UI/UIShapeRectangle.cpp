// #### 2DLayers Include 
#include "UI/UIShapeRectangle.h"
// #### Core Include
#include "Core.h"
// #### Renderer Include
#include "ModuleRenderer.h"
#include "Texture.h"

//#//////////////////////////////
//#		UIShapeRectangle
//#//////////////////////////////
IMPLEMENT_CLASS_INFO(UIShapeRectangle)

IMPLEMENT_CONSTRUCTOR(UIShapeRectangle)
{
	
}

void UIShapeRectangle::SetTexUV(UIItem* item, UIVerticesInfo* aQI)
{
	UITexturedItem* titem = static_cast<UITexturedItem*>(item);
	Texture* texture = titem->GetTexture();
	if (!texture)
	{
		return;
	}
	aQI->Flag |= UIVerticesInfo_Texture;

	bool is_bgr = false;
	if (texture->getValue("IsBGR", is_bgr) && is_bgr)
	{
		aQI->Flag |= UIVerticesInfo_BGRTexture;
	}

	kfloat ratioX, ratioY, sx, sy;
	unsigned int p2sx, p2sy;
	texture->GetSize(sx, sy);
	texture->GetPow2Size(p2sx, p2sy);
	texture->GetRatio(ratioX, ratioY);

	v2f uv_min = titem->getUVMin();
	v2f uv_max = titem->getUVMax();

	if (uv_min == v2f(FLT_MAX, FLT_MAX)) uv_min = { 0,0 };
	if (uv_max == v2f(FLT_MAX, FLT_MAX)) uv_max = { ratioX, ratioY };

	v2f image_size{ sx * ratioX, sy * ratioY };

	kfloat dx = 0.5f / ((float)p2sx);
	kfloat dy = 0.5f / ((float)p2sy);

	VInfo2D::Data* buf = reinterpret_cast<VInfo2D::Data*>(aQI->Buffer());

	// triangle strip order
	buf[0].setTexUV(uv_min.x + dx, uv_min.y + dy);
	buf[1].setTexUV(uv_min.x + dx, uv_max.y - dy);
	buf[3].setTexUV(uv_max.x - dx, uv_max.y - dy);
	buf[2].setTexUV(uv_max.x - dx, uv_min.y + dy);
}
void UIShapeRectangle::SetVertexArray(UIItem* item, UIVerticesInfo* aQI)
{
	aQI->Flag |= UIVerticesInfo_Vertex;

	aQI->Resize(4);
	VInfo2D::Data* buf = reinterpret_cast<VInfo2D::Data*>(aQI->Buffer());

	Point2D pt[4];
	item->GetTransformedPoints(pt);
	// triangle strip order
	buf[0].setVertex(pt[0].x, pt[0].y);
	buf[1].setVertex(pt[1].x, pt[1].y);
	buf[3].setVertex(pt[2].x, pt[2].y);
	buf[2].setVertex(pt[3].x, pt[3].y);
}
