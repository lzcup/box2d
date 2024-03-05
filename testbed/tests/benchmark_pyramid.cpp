// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test.h"

class BenchmarkPyramid : public Test
{
public:
BenchmarkPyramid()
{
	int baseCount = 10;
	int stackCount = 182;
	float extent = 0.5f;
	float groundWidth = 2.0f * extent * stackCount * (baseCount + 1.0f);

	{
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);

		b2EdgeShape shape;
		shape.SetTwoSided(b2Vec2(-0.5f * groundWidth, 0.0f), b2Vec2(0.5f * groundWidth, 0.0f));
		ground->CreateFixture(&shape, 0.0f);
	}

	b2PolygonShape shape;
	shape.SetAsBox(extent, extent);
	float baseWidth = 2.0f * extent * baseCount;

	for (int32 k = 0; k < stackCount; ++k)
	{
		float centerX = -0.5f * groundWidth + k * (baseWidth + 2.0f * extent) + extent;

		for (int32 i = 0; i < baseCount; ++i)
		{
			float y = (2.0f * i + 1.0f) * extent;

			for (int32 j = i; j < baseCount; ++j)
			{
				float x = (i + 1.0f) * extent + 2.0f * (j - i) * extent + centerX;

				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position = { x, y };
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&shape, 5.0f);
			}
		}
	}
}

	static Test* Create()
	{
		return new BenchmarkPyramid;
	}
};

static int testIndex = RegisterTest("Benchmark", "Many Pyramids", BenchmarkPyramid::Create);
