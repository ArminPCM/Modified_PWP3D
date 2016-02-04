#ifndef __RENDERER_3D_OBJECT__
#define __RENDERER_3D_OBJECT__

#include "..\..\Others\PerseusDefines.h"

#include "..\..\Renderer\Model\Model.h"
#include "..\..\Renderer\Model\ModelH.h"

#include "..\..\Renderer\Transforms\ObjectCoordinateTransform.h"

using namespace Renderer::Model3D;
using namespace Renderer::Transforms;
using namespace Renderer::Primitives;

#include <string>

namespace Renderer
{
	namespace Objects
	{
		class Renderer3DObject
		{
		public:
			//contains R,t for object for each view
			ObjectCoordinateTransform** objectCoordinateTransform;

			int objectId;
			int viewCount;

			Model* model;
			ModelH** drawingModel;

			Renderer3DObject(std::string fileName, int viewCount, int objectId) 
			{
				this->viewCount = viewCount;
				this->objectId = objectId;

				objectCoordinateTransform = new ObjectCoordinateTransform*[viewCount];

				for (int i=0; i<viewCount; i++)
				{
					objectCoordinateTransform[i] = new ObjectCoordinateTransform();
					objectCoordinateTransform[i]->rotation = new Quaternion(0, 0, 0);
					objectCoordinateTransform[i]->translation = VECTOR3DA(0, 0, 0);
				}

				model = new Model(fileName);
				drawingModel = new ModelH*[viewCount];
				for (int i=0; i<viewCount; i++)
				{
					drawingModel[i] = new ModelH();
					model->ToModelHInit(drawingModel[i]);
				}
			}

			void GetModelViewMatrix(float* modelViewMatrix, int viewId)
			{ this->objectCoordinateTransform[viewId]->GetModelViewMatrix(modelViewMatrix);	}

			~Renderer3DObject(void) {
				delete model;

				for (int i=0; i<viewCount; i++)
				{
					delete objectCoordinateTransform[i];
					delete drawingModel[i];
				}

				delete objectCoordinateTransform;
				delete drawingModel;
			}
		};
	}
}

#endif