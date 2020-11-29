// #### 2DLayers Include 
#include "UI/UIShapeDisc.h"
// #### Core Include
#include "Core.h"
// #### Renderer Include
#include "ModuleRenderer.h"
#include "Texture.h"

//#//////////////////////////////
//#		UIShapeDisc
//#//////////////////////////////
IMPLEMENT_CLASS_INFO(UIShapeDisc)

IMPLEMENT_CONSTRUCTOR(UIShapeDisc)
{
	
}

void UIShapeDisc::SetTexUV(UIItem* item, UIVerticesInfo* aQI)
{
	const int sliceCount = mSliceCount;
	VInfo2D::Data* buf = reinterpret_cast<VInfo2D::Data*>(aQI->Buffer());
	UITexturedItem* texturedLocalThis = static_cast<UITexturedItem*>(item);
	kfloat ratioX, ratioY, sx, sy;
	unsigned int p2sx, p2sy;
	texturedLocalThis->GetTexture()->GetSize(sx, sy);
	texturedLocalThis->GetTexture()->GetPow2Size(p2sx, p2sy);
	texturedLocalThis->GetTexture()->GetRatio(ratioX, ratioY);

	v2f uv_min = texturedLocalThis->getUVMin();
	v2f uv_max = texturedLocalThis->getUVMax();

	if (uv_min == v2f(FLT_MAX, FLT_MAX)) uv_min = { 0,0 };
	if (uv_max == v2f(FLT_MAX, FLT_MAX)) uv_max = { ratioX, ratioY };

	v2f dxy ( 0.5f / (float)p2sx, 0.5f / (float)p2sy);

	uv_min += dxy;
	uv_max -= dxy;

	v2f realsize = uv_max- uv_min;
	v2f halfSize = realsize * 0.5f;
	v2f center = (uv_max+ uv_min) * 0.5f;

	std::vector<v2f>	circlePos;
	circlePos.resize(sliceCount + 1);

	float angle = (2.0 * PI) / ((double)sliceCount);
	circlePos[0] = center;
	for (int i = 1; i <= sliceCount; i++)
	{
		circlePos[i] = center;
		float currentAngle = angle * (double)i - angle * 0.5;
		circlePos[i].x += halfSize.x * cosf(currentAngle);
		circlePos[i].y += halfSize.y * sinf(currentAngle);
	}

	int j = 0;
	for (int i = 0; i < sliceCount; i++)
	{
		buf[j].setTexUV(circlePos[0]);
		buf[j + 1].setTexUV(circlePos[(i + 1)]);
		buf[j + 2].setTexUV(circlePos[((i + 1) % sliceCount) + 1]);
		j += 3;
	}
	
}
void UIShapeDisc::SetVertexArray(UIItem* item, UIVerticesInfo* aQI)
{
	const int sliceCount = mSliceCount;
	aQI->Resize(3 * mSliceCount); // 3 vertices per triangles, 16 triangles
	VInfo2D::Data* buf = reinterpret_cast<VInfo2D::Data*>(aQI->Buffer());

	v2f realsize = item->GetSize();
	v2f halfSize = realsize * 0.5f;
	v2f center = realsize * 0.5f;

	std::vector<v2f>	circlePos;
	circlePos.resize(sliceCount + 1) ;

	float angle = (2.0 * PI) / ((double)sliceCount);
	circlePos[0] = center;
	for (int i = 1; i <= sliceCount; i++)
	{
		circlePos[i] = center;
		float currentAngle = angle * (double)i - angle * 0.5;
		circlePos[i].x += halfSize.x * cosf(currentAngle);
		circlePos[i].y += halfSize.y * sinf(currentAngle);
	}
	
	item->TransformPoints(circlePos.data(),sliceCount+1);

	int j=0;
	for (int i = 0; i < sliceCount; i++)
	{
		buf[j].setVertex(circlePos[0]);
		buf[j + 1].setVertex(circlePos[(i+1)]);
		buf[j + 2].setVertex(circlePos[((i+1) % sliceCount)+1]);
		j += 3;
	}
}
