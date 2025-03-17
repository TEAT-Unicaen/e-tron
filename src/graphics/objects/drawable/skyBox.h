#pragma once

#include "drawable.h"
#include "../../utils/image.h"
#include "../meshes/sphere/sphere.h"
#include "../bindable/bindableBase.h"

class SkyBox : public Drawable {
public:
	SkyBox(Renderer& renderer, std::shared_ptr<Image> pImage ,float size = 1.0f);
};