#ifndef WORLD_H_
#define WORLD_H_

#include "ofMain.h"

namespace arm_slam
{

    class World
    {
        public:
            World();
            virtual ~World();

            bool IsValid(int x, int y)
            {
                return x >= 0 && x < data.width && y >= 0 && y < data.height;
            }

            bool Collides(int x, int y)
            {
                if(IsValid(x, y))
                {
                    return collisionBuffer[(x + y * data.width)];
                }
                return true;
            }

            float GetDist(int x, int y)
            {
                if(IsValid(x, y))
                {
                    return signedDistance[(x + y * data.width)];
                }
                else
                {
                    return 0.0f;
                }
            }

            ofVec2f GetGradient(int x, int y)
            {
                float d0 = GetDist(x, y);
                float dx = GetDist(x + 1, y);
                float dy = GetDist(x, y + 1);
                return ofVec2f(dx - d0, dy - d0) * d0;

            }

            void Initialize()
            {
                collisionBuffer.resize(data.width * data.height);
                signedDistance.resize(distdata.width * distdata.height);
                for (int x = 0; x< data.width; x++)
                {
                    for(int y = 0; y < data.height; y++)
                    {
                        collisionBuffer[x + y * data.width] = data.getColor(x, y).r == 0;
                        ofColor dist = distdata.getColor(x, y);
                        signedDistance[x + y * data.width] = (float)dist.r - (float)dist.g;
                    }
                }
            }



            ofImage data;
            ofImage distdata;
            std::vector<bool> collisionBuffer;
            std::vector<float>signedDistance;
    };

}

#endif // WORLD_H_ 
